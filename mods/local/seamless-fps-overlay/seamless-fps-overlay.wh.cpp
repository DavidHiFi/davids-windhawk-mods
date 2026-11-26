// ==WindhawkMod==
// @id              seamless-fps-overlay
// @name            Seamless FPS Overlay
// @description     FPS, frame times and PC temperatures over any game, with nothing put into the game
// @version         1.1.3
// @author          DavidHiFi
// @github          https://github.com/DavidHiFi
// @homepage        https://github.com/DavidHiFi/davids-windhawk-mods
// @donateUrl       https://ko-fi.com/DavidHiFi
// @include         windhawk.exe
// @include         windhawk-mod.exe
// @include         windhawk-mod-elevated.exe
// @compilerOptions -DWIN32_LEAN_AND_MEAN -lole32 -loleaut32 -luuid -lshell32 -lgdi32 -lgdiplus -ld2d1 -ldwrite -ldwmapi -luser32 -lcomctl32 -liphlpapi -ladvapi32 -lshlwapi -lwindowscodecs -luxtheme -lcomdlg32 -limm32 -lversion -lpdh -lruntimeobject -lws2_32 -ldxgi
// ==/WindhawkMod==

// ==WindhawkModReadme==
/*
# Seamless FPS Overlay

An in-game overlay for FPS, frame times, the worst moments and your graphics
card and processor readings. It looks like the RivaTuner benchmark layout,
moving pictures included, and nothing is put into the game: Windows itself
reports each frame, so it is safe with anti-cheat and works over Plutonium.

![Seamless FPS Overlay preview](https://raw.githubusercontent.com/DavidHiFi/davids-windhawk-mods/main/media/previews/seamless-fps-overlay.png)

## What's new in 1.1.3
The benchmark layout is now one panel. The sections sit together with no
gaps, split by thin lines, and both columns start and end level. Separate
boxes are still there under Boxes if you liked them.

## What's new in 1.1.2
Long names no longer run into their numbers. Each box now grows to fit what
it shows, and it never shrinks back and forth while you play.
Memory speed and the graphics driver version show again when Seamless
Taskbar is also running.

## What's new in 1.1.1
The overlay now starts every time. Before, it could quietly fail to come back
after an update or a Windhawk reload and stay gone until you changed a
setting. It also closes faster, and if its process ever goes missing,
Windhawk brings it back by itself.

## What's new in 1.1.0
The Benchmark layout now matches the old RivaTuner one: the card name on top,
frame rate, game info, processor cores and system memory on the left, and the
graphics card, video memory and processor on the right, each in its own glass
box. The graphics card fan spins as fast as the real fan, a busy chip gets
flames and the processor runs its code. New readings: smoothness, which
DirectX or Vulkan the game uses, play time, driver version, a load bar for
each core, memory speed, video memory temperature and two processor clocks.
Every box can move sides, change places, grow and take its own colour. Every
name can be renamed, every warning limit set, and the graph and the moving
pictures each have their own switches. The common settings sit on the first
page.

## Features
- **The RivaTuner look, cleaner.** Eight boxes in two columns with Mocha
  colours, a blue to mauve gradient you can flip, rounded corners and crisp
  text. The pictures are drawn fresh, not copied.
- **Real frame numbers.** FPS, frame time, the slowest 1% and 0.1% of frames,
  the average and smoothness over the last 20 seconds, and a frame time graph
  where spikes are stutters.
- **PC readings.** Graphics card load, power, clocks, fan, temperature and hot
  spot. Video memory use, temperature and clock. Processor load, power,
  clocks and temperature, a bar per core, and system memory use and speed. A
  reading the PC can't give shows a dash, never a made-up zero.
- **Change the small things.** Each box's side, place, size and colour, the
  name in front of every number, each warning limit, the graph's length,
  height and style, and the speed of each moving part.
- **Four layouts.** Benchmark, FPS only, one line and a tall list.
- **Shows up only in games.** It appears when the app in front draws its own
  frames the way games do, and stays away from browsers and the desktop. Or
  keep it up everywhere, or only over the games you list.
- **Light on the PC.** The numbers redraw only when they change, and the moving
  pictures stop while the overlay is hidden.
- **Fades and slides** in and out. Turn it off or pick a speed under Look,
  Motion. It stays still when Windows animation effects are off.

## Default shortcuts

| Shortcut | What it does |
|---|---|
| Ctrl+Alt+Shift+] | Show or hide the overlay |
| (none) | Next layout |

Change or clear either in the settings. The tray icon shows or hides the
overlay with a click. Right-click it for layouts and settings.

## Notes
- It draws over borderless and windowed games. A game in true exclusive full
  screen draws over everything, so the overlay can't show there. Switch the
  game to borderless.
- Counting frames needs administrator rights, so the mod runs in Windhawk's
  administrator helper.
- Processor temperature and power need the PawnIO driver. Without it those
  show a dash and everything else still works.
- Input delay is not measured yet, so that line is off by default.

## Credits
Processor readings use [PawnIO](https://pawnio.eu) by namazso (LGPL-2.1).
*/
// ==/WindhawkModReadme==

// ==WindhawkModSettings==
/*
- preset: "benchmark"
  $name: "Layout"
  $description: "Benchmark is the two-column layout from your old RivaTuner setup, with the moving pictures. FPS only shows one number. One line puts the main numbers in a single row. Tall list puts each number on its own line."
  $options:
  - benchmark: "Benchmark (your RivaTuner layout)"
  - fps: "FPS only"
  - compact: "One line"
  - vertical: "Tall list"
- showOnStart: true
  $name: "Show when the mod starts"
  $description: "Off, the overlay waits until you press the shortcut or click the tray icon."
- showWhen: "games"
  $name: "Show the overlay"
  $description: "In games shows it over any program that draws its own frames, the way games do. Always keeps it up everywhere, desktop included. Only listed games uses the list on the Games and keys page."
  $options:
  - games: "In games"
  - always: "Always"
  - listed: "Only listed games"
- toggleHotkey: "Ctrl+Alt+Shift+]"
  $name: "Show or hide shortcut"
  $description: "The same keys your Afterburner used. Click the box and press the keys. Backspace clears it."
- corner: "topLeft"
  $name: "Corner"
  $description: "Which corner of the screen the overlay sits in."
  $options:
  - topLeft: "Top left"
  - topRight: "Top right"
  - bottomLeft: "Bottom left"
  - bottomRight: "Bottom right"
- scale: 100
  $name: "Size"
  $description: "In percent. 100 is the normal size."
- background: "glass"
  $name: "Background"
  $description: "Blurred glass blurs the game behind each box. See-through tint is a light dark wash. Solid dark is the easiest to read. None leaves only the text, with a soft shadow."
  $options:
  - glass: "Blurred glass"
  - tint: "See-through tint"
  - solid: "Solid dark"
  - none: "None"
- opacity: 100
  $name: "Opacity"
  $description: "How solid the whole overlay is, in percent."
- cornerRadius: 12
  $name: "Corner roundness"
  $description: "How round the box corners are, in pixels. 0 gives square corners."
- flipGradient: false
  $name: "Flip the gradient"
  $description: "Off, blue sits at the top left and mauve at the bottom right. On, they swap."
- animations: true
  $name: "Moving pictures"
  $description: "The spinning fan, the flames on a busy chip and the running code on the processor. They stop while the overlay is hidden."
- updateRate: "500"
  $name: "Update speed"
  $description: "How often the numbers change. Slower is easier to read and a little lighter on the PC."
  $options:
  - 250: "Four times a second"
  - 500: "Twice a second"
  - 1000: "Once a second"
- showGpuName: true
  $name: "Graphics card name"
  $description: "The line across the top."
- throttleWarn: true
  $name: "Slow-down note"
  $description: "Shows HEAT LIMIT or POWER LIMIT when a chip slows itself down."
- fps: true
  $name: "FPS"
  $description: "Frames per second right now."
- low01: true
  $name: "Worst moments (slowest 0.1% of frames)"
  $description: "The frame rate during the very worst moments of the last 20 seconds."
- low1: true
  $name: "Bad moments (slowest 1% of frames)"
  $description: "The frame rate during the slowest moments of the last 20 seconds."
- avgFps: true
  $name: "Average FPS"
  $description: "Over the last 20 seconds."
- jitter: true
  $name: "Smoothness"
  $description: "How much the time between frames jumps around, in milliseconds. Lower feels smoother."
- frameTime: true
  $name: "Frame time"
  $description: "How long each frame takes, in milliseconds."
- frameGraph: true
  $name: "Frame time graph"
  $description: "A line of the last few seconds of frame times. Tall spikes are stutters."
- latency: false
  $name: "Input delay"
  $description: "This mod cannot measure it yet, so it shows a dash. Off by default."
- api: true
  $name: "Graphics engine"
  $description: "Whether the game draws with DirectX 9, 11, 12, OpenGL or Vulkan."
- session: true
  $name: "Play time"
  $description: "How long the game in front has been running."
- driver: true
  $name: "Driver version"
  $description: "The graphics driver version."
- cpuName: true
  $name: "Processor name"
- coreBars: true
  $name: "Load bar for each core"
- coreBarsEach: "core"
  $name: "One bar for each"
  $description: "Threads gives twice as many bars on processors that run two threads per core."
  $options:
  - core: "Core"
  - thread: "Thread"
- ram: true
  $name: "Memory in use"
  $description: "In percent."
- ramUsed: true
  $name: "Memory in use, in GB"
  $description: "Used and total."
- ramSpeed: true
  $name: "Memory speed"
  $description: "In MT/s, the number on the memory box."
- ramClock: true
  $name: "Memory clock"
  $description: "In MHz, half the speed above."
- gpuArt: true
  $name: "Graphics card picture"
  $description: "The card drawing with its fan."
- gpuUsage: true
  $name: "Load"
  $description: "How busy the card is, in percent."
- gpuPower: true
  $name: "Power"
  $description: "In watts."
- gpuClock: true
  $name: "Clock"
  $description: "In MHz."
- gpuFan: true
  $name: "Fan speed"
  $description: "In RPM, with the percent next to it."
- gpuTemp: true
  $name: "Temperature"
- gpuHotspot: true
  $name: "Hot spot"
  $description: "The hottest point on the chip."
- vram: true
  $name: "How full"
  $description: "In percent of the card's memory."
- vramUsed: true
  $name: "Used, in GB"
  $description: "Used and total."
- vramTemp: true
  $name: "Temperature"
  $description: "Some cards do not report it. Then it shows a dash."
- gpuMemClock: true
  $name: "Clock"
  $description: "In MHz."
- cpuArt: true
  $name: "Processor picture"
  $description: "The chip drawing with its running code."
- cpuUsage: true
  $name: "Load"
  $description: "How busy the processor is, in percent."
- cpuPower: true
  $name: "Power"
  $description: "In watts. Needs the PawnIO driver, or it shows a dash."
- cpuClock: true
  $name: "Boost clock"
  $description: "The fastest core right now, in GHz."
- cpuBusyClock: true
  $name: "Busy clock"
  $description: "The average clock while the cores are working, in MHz."
- cpuTemp: true
  $name: "Temperature"
  $description: "Needs the PawnIO driver, or it shows a dash."
- showName: true
  $name: "Show this box"
  $description: "The graphics card name across the top, with a note when the card slows down to stay cool or within its power limit."
- columnName: "left"
  $name: "Side"
  $options:
  - left: "Left column"
  - right: "Right column"
- orderName: 1
  $name: "Place in its column"
  $description: "1 is the top. Boxes with the same number keep their usual order."
- sizeName: 100
  $name: "Size"
  $description: "In percent of the overlay size."
- colourName: "same"
  $name: "Name colour"
  $description: "The colour of the words and pictures in this box."
  $options:
  - same: "Same as the names"
  - gradient: "Blue to mauve"
  - blue: "Blue"
  - mauve: "Mauve"
  - lavender: "Lavender"
  - sapphire: "Sapphire"
  - sky: "Sky"
  - teal: "Teal"
  - green: "Green"
  - yellow: "Yellow"
  - peach: "Peach"
  - pink: "Pink"
  - red: "Red"
  - white: "White"
  - custom: "My own colour"
- showFrames: true
  $name: "Show this box"
  $description: "FPS, the worst moments, the average, smoothness and the frame time graph."
- columnFrames: "left"
  $name: "Side"
  $options:
  - left: "Left column"
  - right: "Right column"
- orderFrames: 2
  $name: "Place in its column"
  $description: "1 is the top. Boxes with the same number keep their usual order."
- sizeFrames: 100
  $name: "Size"
  $description: "In percent of the overlay size."
- colourFrames: "same"
  $name: "Name colour"
  $description: "The colour of the words and pictures in this box."
  $options:
  - same: "Same as the names"
  - gradient: "Blue to mauve"
  - blue: "Blue"
  - mauve: "Mauve"
  - lavender: "Lavender"
  - sapphire: "Sapphire"
  - sky: "Sky"
  - teal: "Teal"
  - green: "Green"
  - yellow: "Yellow"
  - peach: "Peach"
  - pink: "Pink"
  - red: "Red"
  - white: "White"
  - custom: "My own colour"
- showInfo: true
  $name: "Show this box"
  $description: "Which DirectX or Vulkan the game uses, how long you have played and the driver version."
- columnInfo: "left"
  $name: "Side"
  $options:
  - left: "Left column"
  - right: "Right column"
- orderInfo: 3
  $name: "Place in its column"
  $description: "1 is the top. Boxes with the same number keep their usual order."
- sizeInfo: 100
  $name: "Size"
  $description: "In percent of the overlay size."
- colourInfo: "same"
  $name: "Name colour"
  $description: "The colour of the words and pictures in this box."
  $options:
  - same: "Same as the names"
  - gradient: "Blue to mauve"
  - blue: "Blue"
  - mauve: "Mauve"
  - lavender: "Lavender"
  - sapphire: "Sapphire"
  - sky: "Sky"
  - teal: "Teal"
  - green: "Green"
  - yellow: "Yellow"
  - peach: "Peach"
  - pink: "Pink"
  - red: "Red"
  - white: "White"
  - custom: "My own colour"
- showCores: true
  $name: "Show this box"
  $description: "The processor name and a small load bar for each core."
- columnCores: "left"
  $name: "Side"
  $options:
  - left: "Left column"
  - right: "Right column"
- orderCores: 4
  $name: "Place in its column"
  $description: "1 is the top. Boxes with the same number keep their usual order."
- sizeCores: 100
  $name: "Size"
  $description: "In percent of the overlay size."
- colourCores: "same"
  $name: "Name colour"
  $description: "The colour of the words and pictures in this box."
  $options:
  - same: "Same as the names"
  - gradient: "Blue to mauve"
  - blue: "Blue"
  - mauve: "Mauve"
  - lavender: "Lavender"
  - sapphire: "Sapphire"
  - sky: "Sky"
  - teal: "Teal"
  - green: "Green"
  - yellow: "Yellow"
  - peach: "Peach"
  - pink: "Pink"
  - red: "Red"
  - white: "White"
  - custom: "My own colour"
- showMemory: true
  $name: "Show this box"
  $description: "How much memory is in use, and its speed."
- columnMemory: "left"
  $name: "Side"
  $options:
  - left: "Left column"
  - right: "Right column"
- orderMemory: 5
  $name: "Place in its column"
  $description: "1 is the top. Boxes with the same number keep their usual order."
- sizeMemory: 100
  $name: "Size"
  $description: "In percent of the overlay size."
- colourMemory: "same"
  $name: "Name colour"
  $description: "The colour of the words and pictures in this box."
  $options:
  - same: "Same as the names"
  - gradient: "Blue to mauve"
  - blue: "Blue"
  - mauve: "Mauve"
  - lavender: "Lavender"
  - sapphire: "Sapphire"
  - sky: "Sky"
  - teal: "Teal"
  - green: "Green"
  - yellow: "Yellow"
  - peach: "Peach"
  - pink: "Pink"
  - red: "Red"
  - white: "White"
  - custom: "My own colour"
- showCard: true
  $name: "Show this box"
  $description: "The card picture with its spinning fan, load, power, clock, fan and temperatures."
- columnCard: "right"
  $name: "Side"
  $options:
  - left: "Left column"
  - right: "Right column"
- orderCard: 1
  $name: "Place in its column"
  $description: "1 is the top. Boxes with the same number keep their usual order."
- sizeCard: 100
  $name: "Size"
  $description: "In percent of the overlay size."
- colourCard: "same"
  $name: "Name colour"
  $description: "The colour of the words and pictures in this box."
  $options:
  - same: "Same as the names"
  - gradient: "Blue to mauve"
  - blue: "Blue"
  - mauve: "Mauve"
  - lavender: "Lavender"
  - sapphire: "Sapphire"
  - sky: "Sky"
  - teal: "Teal"
  - green: "Green"
  - yellow: "Yellow"
  - peach: "Peach"
  - pink: "Pink"
  - red: "Red"
  - white: "White"
  - custom: "My own colour"
- showVram: true
  $name: "Show this box"
  $description: "The memory on the graphics card: how full, how hot and its clock."
- columnVram: "right"
  $name: "Side"
  $options:
  - left: "Left column"
  - right: "Right column"
- orderVram: 2
  $name: "Place in its column"
  $description: "1 is the top. Boxes with the same number keep their usual order."
- sizeVram: 100
  $name: "Size"
  $description: "In percent of the overlay size."
- colourVram: "same"
  $name: "Name colour"
  $description: "The colour of the words and pictures in this box."
  $options:
  - same: "Same as the names"
  - gradient: "Blue to mauve"
  - blue: "Blue"
  - mauve: "Mauve"
  - lavender: "Lavender"
  - sapphire: "Sapphire"
  - sky: "Sky"
  - teal: "Teal"
  - green: "Green"
  - yellow: "Yellow"
  - peach: "Peach"
  - pink: "Pink"
  - red: "Red"
  - white: "White"
  - custom: "My own colour"
- showProcessor: true
  $name: "Show this box"
  $description: "The chip picture, load, power, clocks and temperature."
- columnProcessor: "right"
  $name: "Side"
  $options:
  - left: "Left column"
  - right: "Right column"
- orderProcessor: 3
  $name: "Place in its column"
  $description: "1 is the top. Boxes with the same number keep their usual order."
- sizeProcessor: 100
  $name: "Size"
  $description: "In percent of the overlay size."
- colourProcessor: "same"
  $name: "Name colour"
  $description: "The colour of the words and pictures in this box."
  $options:
  - same: "Same as the names"
  - gradient: "Blue to mauve"
  - blue: "Blue"
  - mauve: "Mauve"
  - lavender: "Lavender"
  - sapphire: "Sapphire"
  - sky: "Sky"
  - teal: "Teal"
  - green: "Green"
  - yellow: "Yellow"
  - peach: "Peach"
  - pink: "Pink"
  - red: "Red"
  - white: "White"
  - custom: "My own colour"
- capitals: true
  $name: "Names in capitals"
  $description: "Off, the names show the way you typed them."
- lblFps: "FPS"
  $name: "FPS"
- lbl01: "0.1%"
  $name: "Worst moments"
- lbl1: "1%"
  $name: "Bad moments"
- lblAvg: "AVG"
  $name: "Average"
- lblJitter: "JITTER"
  $name: "Smoothness"
- lblFrame: "FRAME TIME"
  $name: "Frame time"
- lblLatency: "LATENCY"
  $name: "Input delay"
- lblApi: "API"
  $name: "Graphics engine"
- lblTime: "PLAY TIME"
  $name: "Play time"
- lblDriver: "DRIVER"
  $name: "Driver version"
- lblRam: "RAM"
  $name: "Box name"
- lblRamUsed: "USED"
  $name: "In use"
- lblRamSpeed: "SPEED"
  $name: "Speed"
- lblRamClock: "CLOCK"
  $name: "Clock"
- lblGpuLoad: "LOAD"
  $name: "Load"
- lblGpuPower: "POWER"
  $name: "Power"
- lblGpuClock: "CLOCK"
  $name: "Clock"
- lblFan: "FAN"
  $name: "Fan"
- lblGpuTemp: "TEMP"
  $name: "Temperature"
- lblHotspot: "HOT SPOT"
  $name: "Hot spot"
- lblVram: "VRAM"
  $name: "Box name"
- lblVramUsed: "USED"
  $name: "Used"
- lblVramTemp: "TEMP"
  $name: "Temperature"
- lblVramClock: "CLOCK"
  $name: "Clock"
- lblCpuLoad: "LOAD"
  $name: "Load"
- lblCpuPower: "POWER"
  $name: "Power"
- lblCpuBoost: "BOOST"
  $name: "Boost clock"
- lblCpuBusy: "BUSY CLOCK"
  $name: "Busy clock"
- lblCpuTemp: "TEMP"
  $name: "Temperature"
- warnColour: "red"
  $name: "Warning colour"
  $description: "A number past its limit turns this colour."
  $options:
  - gradient: "Blue to mauve"
  - blue: "Blue"
  - mauve: "Mauve"
  - lavender: "Lavender"
  - sapphire: "Sapphire"
  - sky: "Sky"
  - teal: "Teal"
  - green: "Green"
  - yellow: "Yellow"
  - peach: "Peach"
  - pink: "Pink"
  - red: "Red"
  - white: "White"
  - custom: "My own colour"
- gpuTempWarn: 83
  $name: "Graphics card hotter than"
  $description: "In \u00b0C."
- hotspotWarn: 95
  $name: "Hot spot or video memory hotter than"
  $description: "In \u00b0C."
- cpuTempWarn: 85
  $name: "Processor hotter than"
  $description: "In \u00b0C."
- vramWarn: 95
  $name: "Video memory fuller than"
  $description: "In percent."
- ramWarn: 90
  $name: "System memory fuller than"
  $description: "In percent."
- fpsWarn: 0
  $name: "FPS lower than"
  $description: "0 turns this warning off."
- graphStyle: "line"
  $name: "Graph style"
  $options:
  - line: "Line"
  - area: "Filled"
  - bars: "Bars"
- graphSeconds: 3
  $name: "Graph length"
  $description: "How many seconds the graph shows."
- graphHeight: 36
  $name: "Graph height"
  $description: "In pixels, before the overlay size."
- graphTop: "50"
  $name: "Top of the graph"
  $description: "The frame time at the top edge. Fit to the frames picks it from what is on screen."
  $options:
  - auto: "Fit to the frames"
  - 33: "33 ms (30 FPS)"
  - 50: "50 ms (20 FPS)"
  - 100: "100 ms (10 FPS)"
- spikeMarks: true
  $name: "Mark stutters"
  $description: "A small mark above each big spike."
- fanSpin: true
  $name: "Spinning fan"
  $description: "Spins as fast as the real fan, scaled down."
- fanSpeed: 100
  $name: "Fan spin speed"
  $description: "In percent. 100 follows the real fan."
- flames: true
  $name: "Flames on a busy chip"
  $description: "Small flames around a load ring that is nearly full."
- flameAt: 97
  $name: "Flames start at"
  $description: "Load in percent."
- binaryCode: true
  $name: "Running code"
  $description: "The ones and zeros on the processor picture."
- smoothDials: true
  $name: "Smooth dials"
  $description: "Rings and needles glide to a new number."
- throttlePulse: true
  $name: "Pulse the slow-down note"
  $description: "HEAT LIMIT and POWER LIMIT gently pulse."
- animFps: "30"
  $name: "Picture frame rate"
  $description: "How often the moving pictures redraw. Lower costs less."
  $options:
  - 15: "15 a second"
  - 30: "30 a second"
  - 60: "60 a second"
- gpuGaugeMax: 3000
  $name: "Graphics clock dial ends at"
  $description: "In MHz."
- cpuGaugeMax: 6000
  $name: "Processor clock dial ends at"
  $description: "In MHz."
- offsetX: 16
  $name: "Distance from the side"
  $description: "In pixels."
- offsetY: 16
  $name: "Distance from the top or bottom"
  $description: "In pixels."
- monitor: "game"
  $name: "Screen"
  $description: "Follow the game moves the overlay to whichever screen the game is on."
  $options:
  - game: "Follow the game"
  - primary: "Main screen"
- panels: "one"
  $name: "Boxes"
  $description: "One panel puts every section in a single box, split by thin lines. Separate boxes gives each section its own box, like RivaTuner."
  $options:
  - one: "One panel"
  - cards: "Separate boxes"
- blockGap: 6
  $name: "Gap between boxes"
  $description: "Only used with separate boxes. In pixels."
- bgStrength: 100
  $name: "Background strength"
  $description: "How dark the box fill is, in percent. 0 leaves only the blur."
- rounded: true
  $name: "Rounded corners"
  $description: "Off gives square corners at any roundness."
- border: true
  $name: "Edge"
  $description: "A thin line around each box."
- borderColour: "gradient"
  $name: "Edge colour"
  $description: "Type gradient for the blue to mauve edge, or a colour like #45475A."
- fontFace: "FiraCode Nerd Font"
  $name: "Font"
  $description: "Any font installed on this PC. If it is missing, Segoe UI is used."
- fontWeight: "bold"
  $name: "Thickness"
  $options:
  - normal: "Normal"
  - medium: "Medium"
  - semibold: "Semibold"
  - bold: "Bold"
  - heavy: "Heavy"
- textSize: 100
  $name: "Text size"
  $description: "In percent, on top of the overlay size."
- labelStyle: "gradient"
  $name: "Name colour"
  $description: "The colour of the names, like GPU and FPS, and of the pictures."
  $options:
  - gradient: "Blue to mauve"
  - blue: "Blue"
  - mauve: "Mauve"
  - text: "White"
  - custom: "My own colour"
- valueStyle: "text"
  $name: "Number colour"
  $description: "The colour of the numbers."
  $options:
  - text: "White"
  - gradient: "Blue to mauve"
  - custom: "My own colour"
- customColour: "#F5C2E7"
  $name: "My own colour"
  $description: "Used wherever a colour is set to My own colour."
- gameList: ""
  $name: "Listed games"
  $description: "Used when Show the overlay is set to Only listed games. Program names split by commas, like cs2.exe, plutonium-bootstrapper-win32.exe."
- hideList: ""
  $name: "Never show over"
  $description: "Program names split by commas. The overlay stays hidden over these."
- presetHotkey: ""
  $name: "Next layout shortcut"
  $description: "Steps through the four layouts. Empty means no shortcut."
- settingsTrayIcon: true
  $name: "Tray icon"
  $description: "Click it to show or hide the overlay. Right-click it for layouts and settings."
- settingsGlass: true
  $name: "Blurred settings window"
  $description: "On, the settings window is see-through glass with Windows acrylic behind it. Off, it is solid. Applies when you save."
- nativeSettingsTitleBar: false
  $name: "Native Windows title bar"
  $description: "Use the Windows title bar and window buttons for this settings window. Applies when you save."
- flyoutAnimation: true
  $name: "Show and hide animation"
  $description: "The overlay fades and slides in when it shows, and out when it hides. It stays still when Windows animation effects are off."
- animationSpeed: "global"
  $name: "Animation speed"
  $description: "Follow the global speed uses the one speed shared by all DavidHiFi mods."
  $options:
  - global: "Follow the global speed"
  - veryQuick: "Very quick"
  - quick: "Quick"
  - normal: "Normal"
  - relaxed: "Relaxed"
  - slow: "Slow"
*/
// ==/WindhawkModSettings==

// ---- Sensor core (shared with Seamless Taskbar), rev from sensor-core.inc ----
// Seamless sensor core. One self-contained block, no dependency on the mod
// that embeds it. Reads CPU, RAM, GPU, network and disk numbers without
// HWiNFO, and shares them between processes through one named block.
//
// Sources: NT and PDH (CPU load, RAM, disk), IP helper (network), PawnIO
// with the signed AMDFamily17 module (CPU temperature, power, clocks,
// voltage; needs an elevated process), NVAPI with NVML as the fallback and
// for watts (NVIDIA GPU). Anything a source cannot give stays NaN.
//
// Embed: #include this file once, link -lpdh -liphlpapi -ladvapi32.
// API, rules and elevation needs: README.md beside this file.
#ifndef SEAMLESS_SENSORS_CORE_INC
#define SEAMLESS_SENSORS_CORE_INC

#include <winsock2.h>
#include <ws2tcpip.h>
#include <windows.h>
#include <winternl.h>
#include <pdh.h>
#include <iphlpapi.h>
#include <netioapi.h>
#include <sddl.h>
#include <intrin.h>
#include <dxgi.h>

#include <atomic>
#include <cstdint>
#include <cstring>
#include <cwchar>
#include <limits>

namespace seamless_sensors {

constexpr int SENSOR_CORE_REV = 4;
constexpr uint32_t kLayoutVersion = 1;
constexpr uint32_t kMagic = 0x534E5353;  // 'SSNS'
constexpr uint32_t kMaxCores = 64;
constexpr uint32_t kMaxCcds = 8;
constexpr wchar_t kMappingName[] = L"Global\\SeamlessSensors.v1";
constexpr wchar_t kDemandEventName[] = L"Global\\SeamlessSensors.v1.demand";
constexpr wchar_t kPublisherMutexName[] = L"Global\\SeamlessSensors.publisher";

// Which sources answered in the last sample (Snapshot::sources).
enum SourceBits : uint32_t {
    kSrcNt = 1u << 0,      // CPU load, RAM
    kSrcPdh = 1u << 1,     // disk
    kSrcNet = 1u << 2,     // network
    kSrcPawnIO = 1u << 3,  // CPU temperature, power, clocks, voltage
    kSrcNvapi = 1u << 4,   // NVIDIA GPU through NVAPI
    kSrcNvml = 1u << 5,    // NVIDIA GPU through NVML
};

inline double NaN() { return std::numeric_limits<double>::quiet_NaN(); }

// Works under -ffast-math too (std::isnan does not).
inline bool IsValid(double v) {
    uint64_t bits;
    std::memcpy(&bits, &v, sizeof(bits));
    return (bits & 0x7FF0000000000000ull) != 0x7FF0000000000000ull;
}

// Plain data, the same bytes in every process. Units are in the names.
// Every double is NaN when its source is missing.
struct Snapshot {
    uint32_t size;          // sizeof(Snapshot) of the writer
    uint32_t sources;       // SourceBits that answered
    uint64_t tick;          // GetTickCount64() when sampled, 0 = never
    uint32_t sequence;      // sample counter
    uint32_t logicalCores;
    uint32_t physicalCores;
    uint32_t ccdCount;

    double cpuUsage;                     // %, all cores
    double cpuCoreUsage[kMaxCores];      // %, per logical processor
    double cpuTemp;                      // C, Tctl/Tdie
    double cpuCcdTemp[kMaxCcds];         // C, per CCD
    double cpuPackagePower;              // W
    double cpuCoresPower;                // W, sum of cores
    double cpuClockAvg;                  // MHz, mean of cpuCoreClock
    double cpuClockMax;                  // MHz, fastest core
    double cpuCoreClock[kMaxCores];      // MHz, per physical core (P-state)
    double cpuEffectiveClockAvg;         // MHz, mean busy clock (APERF)
    double cpuCoreEffectiveClock[kMaxCores];  // MHz, per physical core
    double cpuCoreVoltage;               // V, SVI2 core rail
    double cpuSocVoltage;                // V, SVI2 SoC rail

    double ramUsedMB;
    double ramTotalMB;
    double ramLoad;                      // %

    double gpuUsage;                     // %
    double gpuTemp;                      // C
    double gpuHotspot;                   // C
    double gpuMemJunction;               // C
    double gpuPower;                     // W
    double gpuClock;                     // MHz, graphics
    double gpuMemClock;                  // MHz
    double gpuVramUsedMB;
    double gpuVramTotalMB;
    double gpuFanRpm;
    double gpuFanPercent;                // %

    double netDownBps;                   // bytes per second
    double netUpBps;
    double diskReadBps;
    double diskWriteBps;
    double diskActive;                   // %, busiest-time style

    wchar_t cpuName[64];
    wchar_t gpuName[64];

    // Rev 3 additions. Fields are only ever appended, so readers and
    // publishers of different revs still agree on everything before here.
    double cpuSocPower;                  // W, SVI2 SoC rail (AMD; "RAM watts" on the taskbar)
    double gpuMemPower;                  // W, NaN: only the card's own power chip knows it
    uint32_t gpuLuidLow;                 // DXGI adapter LUID of gpuName, 0/0 = unknown
    int32_t gpuLuidHigh;
    uint32_t gpuPciBus;                  // PCI bus number, kUnknownBus = unknown
    uint32_t gpuVendorId;                // 0x10DE NVIDIA, 0 = unknown

    // Rev 4 additions (same rule: appended only).
    uint32_t cpuVendorId;                // 0x1022 AMD, 0x8086 Intel, 0 = unknown
    uint32_t ramModules;                 // memory sticks fitted, 0 = unknown
    double ramSpeedMTs;                  // MT/s, configured memory speed (SMBIOS)
    double ramClockMHz;                  // MHz, half of ramSpeedMTs (HWiNFO "Memory Clock")
    double gpuThermalThrottle;           // 1 = slowed down by heat right now, 0 = not
    double gpuPowerThrottle;             // 1 = held at its power limit right now, 0 = not
    double cpuThermalThrottle;           // 1 = slowed down by heat right now (AMD HTC), 0 = not
    wchar_t gpuDriver[32];               // driver version, "" = unknown
};

constexpr uint32_t kUnknownBus = 0xFFFFFFFFu;

struct SharedHeader {
    uint32_t magic;
    uint32_t layout;
    uint32_t snapshotSize;
    uint32_t coreRev;
    volatile LONG seq;               // odd while the publisher writes
    uint32_t publisherPid;
    uint32_t intervalMs;
    uint32_t reserved0;
    volatile LONG64 heartbeatTick;   // publisher alive, even while idle
    uint64_t reserved[6];
};

struct SharedBlock {
    SharedHeader header;
    Snapshot snapshot;
};

constexpr SIZE_T kMappingSize = 64 * 1024;
static_assert(sizeof(SharedBlock) <= kMappingSize, "block too big");

inline void ResetSnapshot(Snapshot& s) {
    std::memset(&s, 0, sizeof(s));
    s.size = sizeof(Snapshot);
    double* first = &s.cpuUsage;
    double* last = &s.diskActive;
    for (double* p = first; p <= last; ++p) *p = NaN();
    s.cpuSocPower = NaN();
    s.gpuMemPower = NaN();
    s.gpuPciBus = kUnknownBus;
    s.ramSpeedMTs = NaN();
    s.ramClockMHz = NaN();
    s.gpuThermalThrottle = NaN();
    s.gpuPowerThrottle = NaN();
    s.cpuThermalThrottle = NaN();
}

namespace detail {

// ---------------------------------------------------------------- helpers

inline uint64_t FileTimeToU64(const LARGE_INTEGER& v) {
    return static_cast<uint64_t>(v.QuadPart);
}

inline double QpcSeconds() {
    static LARGE_INTEGER freq = [] {
        LARGE_INTEGER f;
        QueryPerformanceFrequency(&f);
        return f;
    }();
    LARGE_INTEGER now;
    QueryPerformanceCounter(&now);
    return static_cast<double>(now.QuadPart) / static_cast<double>(freq.QuadPart);
}

inline void CopyAnsiName(wchar_t* out, size_t outCount, const char* in, size_t inMax) {
    size_t n = 0;
    while (n < inMax && in[n]) ++n;
    while (n > 0 && in[n - 1] == ' ') --n;
    size_t start = 0;
    while (start < n && in[start] == ' ') ++start;
    size_t j = 0;
    for (size_t i = start; i < n && j + 1 < outCount; ++i)
        out[j++] = static_cast<unsigned char>(in[i]);
    out[j] = 0;
}

// --------------------------------------------------------------- CPU load

struct ProcPerf {  // SYSTEM_PROCESSOR_PERFORMANCE_INFORMATION
    LARGE_INTEGER IdleTime;
    LARGE_INTEGER KernelTime;
    LARGE_INTEGER UserTime;
    LARGE_INTEGER DpcTime;
    LARGE_INTEGER InterruptTime;
    ULONG InterruptCount;
};

using NtQsiFn = LONG(NTAPI*)(ULONG, PVOID, ULONG, PULONG);

struct CpuLoad {
    NtQsiFn query = nullptr;
    ProcPerf prev[kMaxCores] = {};
    uint32_t count = 0;
    bool havePrev = false;

    bool Open() {
        HMODULE ntdll = GetModuleHandleW(L"ntdll.dll");
        query = ntdll ? reinterpret_cast<NtQsiFn>(
                            GetProcAddress(ntdll, "NtQuerySystemInformation"))
                      : nullptr;
        havePrev = false;
        return query != nullptr;
    }

    void Sample(Snapshot& s) {
        if (!query) return;
        ProcPerf now[kMaxCores];
        ULONG got = 0;
        if (query(8 /* SystemProcessorPerformanceInformation */, now, sizeof(now), &got) < 0)
            return;
        uint32_t n = got / sizeof(ProcPerf);
        if (n == 0) return;
        if (n > kMaxCores) n = kMaxCores;
        if (havePrev && n == count) {
            uint64_t totalBusy = 0, totalAll = 0;
            for (uint32_t i = 0; i < n; ++i) {
                uint64_t idle = FileTimeToU64(now[i].IdleTime) - FileTimeToU64(prev[i].IdleTime);
                uint64_t all = (FileTimeToU64(now[i].KernelTime) - FileTimeToU64(prev[i].KernelTime)) +
                               (FileTimeToU64(now[i].UserTime) - FileTimeToU64(prev[i].UserTime));
                uint64_t busy = all > idle ? all - idle : 0;
                s.cpuCoreUsage[i] = all ? 100.0 * static_cast<double>(busy) / static_cast<double>(all) : 0.0;
                totalBusy += busy;
                totalAll += all;
            }
            s.cpuUsage = totalAll ? 100.0 * static_cast<double>(totalBusy) / static_cast<double>(totalAll) : 0.0;
            s.sources |= kSrcNt;
        }
        s.logicalCores = n;
        std::memcpy(prev, now, n * sizeof(ProcPerf));
        count = n;
        havePrev = true;
    }
};

inline void SampleMemory(Snapshot& s) {
    MEMORYSTATUSEX m = {};
    m.dwLength = sizeof(m);
    if (!GlobalMemoryStatusEx(&m)) return;
    s.ramTotalMB = static_cast<double>(m.ullTotalPhys) / (1024.0 * 1024.0);
    s.ramUsedMB = static_cast<double>(m.ullTotalPhys - m.ullAvailPhys) / (1024.0 * 1024.0);
    s.ramLoad = m.ullTotalPhys ? 100.0 * static_cast<double>(m.ullTotalPhys - m.ullAvailPhys) /
                                     static_cast<double>(m.ullTotalPhys)
                               : NaN();
    s.sources |= kSrcNt;
}

inline void ReadCpuName(wchar_t* out, size_t count) {
    int regs[4];
    char brand[49] = {};
    __cpuid(regs, 0x80000000);
    if (static_cast<unsigned>(regs[0]) >= 0x80000004) {
        for (int i = 0; i < 3; ++i) {
            __cpuid(regs, 0x80000002 + i);
            std::memcpy(brand + i * 16, regs, 16);
        }
    }
    CopyAnsiName(out, count, brand, 48);
}

inline uint32_t ReadCpuVendor() {
    int r[4];
    __cpuid(r, 0);
    if (r[1] == 0x68747541 && r[3] == 0x69746E65 && r[2] == 0x444D4163) return 0x1022;  // AuthenticAMD
    if (r[1] == 0x756E6547 && r[3] == 0x49656E69 && r[2] == 0x6C65746E) return 0x8086;  // GenuineIntel
    return 0;
}

// Configured memory speed from the firmware's memory device tables (SMBIOS
// type 17): the speed the sticks really run at (EXPO/XMP included), the same
// number HWiNFO shows as "Memory Clock" doubled. Read once; it cannot change
// without a reboot.
inline void ReadRamSpeed(uint32_t& mts, uint32_t& modules) {
    mts = 0;
    modules = 0;
    const DWORD rsmb = 0x52534D42;  // 'RSMB'
    UINT need = GetSystemFirmwareTable(rsmb, 0, nullptr, 0);
    if (need < 8 || need > (1u << 20)) return;
    BYTE* buf = static_cast<BYTE*>(HeapAlloc(GetProcessHeap(), 0, need));
    if (!buf) return;
    if (GetSystemFirmwareTable(rsmb, 0, buf, need) == need) {
        DWORD len = *reinterpret_cast<DWORD*>(buf + 4);
        const BYTE* p = buf + 8;
        const BYTE* end = buf + 8 + (len < need - 8 ? len : need - 8);
        while (p + 4 <= end) {
            BYTE type = p[0], size = p[1];
            if (size < 4 || p + size > end) break;
            if (type == 17 && size >= 0x22) {
                WORD sz = *reinterpret_cast<const WORD*>(p + 0x0C);
                if (sz != 0 && sz != 0xFFFF) {
                    ++modules;
                    uint32_t speed = *reinterpret_cast<const WORD*>(p + 0x20);  // configured speed
                    if (speed == 0xFFFF && size >= 0x5C) speed = *reinterpret_cast<const DWORD*>(p + 0x58);
                    if (!speed || speed == 0xFFFF) speed = *reinterpret_cast<const WORD*>(p + 0x15);  // rated
                    if (speed == 0xFFFF && size >= 0x58) speed = *reinterpret_cast<const DWORD*>(p + 0x54);
                    if (speed > 0 && speed < 20000 && speed > mts) mts = speed;
                }
            }
            if (type == 127) break;
            const BYTE* q = p + size;  // the strings after the table end with two zero bytes
            while (q + 1 < end && (q[0] || q[1])) ++q;
            p = q + 2;
        }
    }
    HeapFree(GetProcessHeap(), 0, buf);
}

// ------------------------------------------------------------- disk (PDH)

struct DiskPdh {
    PDH_HQUERY query = nullptr;
    PDH_HCOUNTER read = nullptr, write = nullptr, idle = nullptr;
    bool primed = false;

    bool Open() {
        if (PdhOpenQueryW(nullptr, 0, &query) != ERROR_SUCCESS) {
            query = nullptr;
            return false;
        }
        PdhAddEnglishCounterW(query, L"\\PhysicalDisk(_Total)\\Disk Read Bytes/sec", 0, &read);
        PdhAddEnglishCounterW(query, L"\\PhysicalDisk(_Total)\\Disk Write Bytes/sec", 0, &write);
        PdhAddEnglishCounterW(query, L"\\PhysicalDisk(_Total)\\% Idle Time", 0, &idle);
        primed = PdhCollectQueryData(query) == ERROR_SUCCESS;
        return true;
    }

    void Close() {
        if (query) PdhCloseQuery(query);
        query = nullptr;
        read = write = idle = nullptr;
        primed = false;
    }

    static bool Value(PDH_HCOUNTER c, double& out) {
        PDH_FMT_COUNTERVALUE v;
        if (!c || PdhGetFormattedCounterValue(c, PDH_FMT_DOUBLE | PDH_FMT_NOCAP100, nullptr, &v) != ERROR_SUCCESS)
            return false;
        if (v.CStatus != 0 /* VALID_DATA */ && v.CStatus != 1 /* NEW_DATA */) return false;
        out = v.doubleValue;
        return true;
    }

    void Sample(Snapshot& s) {
        if (!query || PdhCollectQueryData(query) != ERROR_SUCCESS) return;
        if (!primed) {
            primed = true;
            return;
        }
        double v;
        if (Value(read, v)) s.diskReadBps = v;
        if (Value(write, v)) s.diskWriteBps = v;
        if (Value(idle, v)) {
            double a = 100.0 - v;
            s.diskActive = a < 0 ? 0 : (a > 100 ? 100 : a);
        }
        if (IsValid(s.diskReadBps) || IsValid(s.diskActive)) s.sources |= kSrcPdh;
    }
};

// ---------------------------------------------------------------- network

struct Network {
    uint64_t prevIn = 0, prevOut = 0;
    double prevTime = 0;
    bool havePrev = false;

    void Sample(Snapshot& s) {
        PMIB_IF_TABLE2 table = nullptr;
        if (GetIfTable2(&table) != NO_ERROR || !table) return;
        uint64_t in = 0, out = 0;
        for (ULONG i = 0; i < table->NumEntries; ++i) {
            const MIB_IF_ROW2& r = table->Table[i];
            if (!r.InterfaceAndOperStatusFlags.HardwareInterface) continue;
            if (r.InterfaceAndOperStatusFlags.FilterInterface) continue;
            if (r.Type == IF_TYPE_SOFTWARE_LOOPBACK) continue;
            if (r.OperStatus != IfOperStatusUp) continue;
            in += r.InOctets;
            out += r.OutOctets;
        }
        FreeMibTable(table);
        double now = QpcSeconds();
        if (havePrev && now > prevTime && in >= prevIn && out >= prevOut) {
            double dt = now - prevTime;
            s.netDownBps = static_cast<double>(in - prevIn) / dt;
            s.netUpBps = static_cast<double>(out - prevOut) / dt;
            s.sources |= kSrcNet;
        }
        prevIn = in;
        prevOut = out;
        prevTime = now;
        havePrev = true;
    }
};

// ------------------------------------------------------- CPU via PawnIO

// AMDFamily17.bin, PawnIO.Modules 0.2.12, signed by its author.
// LGPL-2.1-or-later, source: https://github.com/namazso/PawnIO.Modules
alignas(16) inline constexpr unsigned char kAmdFamily17Blob[10652] = {
    0x00, 0x02, 0x00, 0x00, 0x7E, 0x41, 0x1C, 0xE8, 0x64, 0xAF, 0x05, 0x84, 0x2D, 0xC0, 0xF1, 0x6D, 0x57, 0x54, 0x26, 0x68,
    0x09, 0x2D, 0x62, 0x00, 0x12, 0xD7, 0xF2, 0x0D, 0x4B, 0x66, 0x16, 0x71, 0xF2, 0x2D, 0x4E, 0x56, 0xB4, 0x46, 0xD3, 0x65,
    0x4F, 0x10, 0x0F, 0x95, 0x55, 0x69, 0x95, 0x73, 0x8C, 0x0A, 0xF1, 0x1F, 0x37, 0x3A, 0xBE, 0x3E, 0x7E, 0x4B, 0xE8, 0x15,
    0xD8, 0x44, 0x58, 0x79, 0x5B, 0x59, 0x07, 0xDF, 0xD2, 0xF2, 0x33, 0xE9, 0x4C, 0x9E, 0x8C, 0x60, 0xDD, 0x3E, 0xE1, 0xF8,
    0x7E, 0x13, 0xD3, 0xEC, 0xF4, 0xCA, 0x58, 0xF8, 0x70, 0x56, 0xAE, 0xE7, 0x22, 0x8A, 0x05, 0x5F, 0xD4, 0x41, 0x93, 0xA6,
    0x2D, 0xE9, 0x56, 0x55, 0xE5, 0xAC, 0xCD, 0x59, 0x71, 0x98, 0x5B, 0x90, 0x3E, 0xDD, 0xA0, 0x97, 0xDA, 0xA8, 0x23, 0x0F,
    0x12, 0x26, 0x2F, 0xD8, 0xD4, 0x30, 0x06, 0x14, 0x3D, 0xB1, 0x80, 0x14, 0x27, 0xDF, 0x79, 0x6B, 0x35, 0xE6, 0x9D, 0x65,
    0x56, 0x87, 0xDB, 0x60, 0x19, 0x3C, 0x27, 0x1E, 0x74, 0x8F, 0x8F, 0xA2, 0xDB, 0xD4, 0x24, 0xD6, 0x25, 0x81, 0x78, 0x66,
    0x81, 0x34, 0x1A, 0x95, 0x60, 0x25, 0xEB, 0xE3, 0xD3, 0x4E, 0x9E, 0x5F, 0xF7, 0xBC, 0xD9, 0x85, 0xDE, 0x05, 0xBC, 0xEB,
    0x9C, 0x00, 0x04, 0x7F, 0x41, 0x4B, 0xEF, 0x01, 0xD3, 0x39, 0x94, 0x4E, 0x6E, 0x30, 0x6B, 0x12, 0xD3, 0xB9, 0x50, 0x7E,
    0x8E, 0x01, 0x70, 0x4D, 0x57, 0xED, 0xA1, 0x2F, 0x93, 0x9B, 0xC6, 0x19, 0x9D, 0xFB, 0x04, 0xEE, 0x58, 0xFF, 0x18, 0x1B,
    0xE9, 0x67, 0xE9, 0xD7, 0x44, 0x2E, 0xD8, 0x94, 0x93, 0xF1, 0xFF, 0x97, 0xB2, 0x91, 0xB2, 0x8D, 0x5D, 0xEF, 0xD5, 0x87,
    0x82, 0x41, 0x32, 0x50, 0x97, 0xA8, 0x7B, 0x95, 0x47, 0x97, 0x97, 0x37, 0x7A, 0xE4, 0xB9, 0xAE, 0xF3, 0x86, 0x43, 0x78,
    0x1D, 0xB4, 0xCD, 0x07, 0x59, 0x31, 0xFA, 0x8F, 0x24, 0x5E, 0x0A, 0x4D, 0xB2, 0x58, 0xCF, 0x81, 0x4C, 0x66, 0x16, 0x52,
    0xA5, 0x63, 0xC4, 0x91, 0xC0, 0x56, 0x48, 0x96, 0x96, 0x9E, 0x8A, 0x7D, 0x39, 0x8D, 0xA5, 0x55, 0xA0, 0x07, 0x19, 0xCF,
    0x28, 0x3A, 0xD0, 0x7D, 0x4F, 0xBE, 0x52, 0x98, 0x13, 0x85, 0x41, 0xE8, 0x41, 0xA9, 0xBE, 0xB0, 0xDB, 0x7F, 0xEF, 0x51,
    0x8D, 0x16, 0x55, 0x2B, 0x35, 0x6A, 0x19, 0xC8, 0x5E, 0xFF, 0x07, 0xBB, 0x02, 0xAC, 0x4B, 0x83, 0x11, 0x20, 0x3B, 0xD6,
    0x09, 0xD7, 0xBE, 0x7B, 0x25, 0xA9, 0x2E, 0x3F, 0x2C, 0xFC, 0x68, 0x8B, 0xD4, 0xC4, 0xEC, 0x9B, 0xF4, 0x07, 0xDA, 0x28,
    0x8A, 0xA8, 0x46, 0x72, 0xF2, 0xBC, 0x63, 0xA0, 0x8F, 0xC6, 0xBD, 0x4B, 0xCE, 0xA4, 0xCA, 0x16, 0x8A, 0x11, 0xB4, 0x61,
    0xE9, 0xF4, 0xF0, 0xF0, 0x60, 0x34, 0x5C, 0x19, 0x50, 0xA3, 0xE4, 0x81, 0x39, 0x4A, 0x22, 0xDC, 0xD3, 0x3A, 0x6B, 0xFF,
    0xDD, 0xAF, 0x7D, 0x28, 0x21, 0x31, 0xB7, 0x1D, 0xFF, 0x1A, 0xAE, 0xD0, 0xD4, 0xDB, 0xDF, 0x93, 0xA7, 0x43, 0xD6, 0x96,
    0xF1, 0x5F, 0xAD, 0x54, 0x97, 0xBA, 0x63, 0x10, 0xA4, 0xF1, 0xD8, 0xCB, 0xE3, 0xE8, 0xBE, 0x21, 0xDC, 0x46, 0xC8, 0x90,
    0x4C, 0x49, 0x8B, 0x91, 0xD5, 0x2A, 0x0D, 0x4A, 0x0B, 0x67, 0x4D, 0x3A, 0xD4, 0x2C, 0x45, 0xE4, 0xF9, 0x8D, 0x50, 0xD5,
    0xD8, 0x30, 0x7F, 0x35, 0xF0, 0xDE, 0xE4, 0x2F, 0xAA, 0x03, 0x23, 0xAE, 0xC2, 0x94, 0xCC, 0x45, 0xA0, 0x0E, 0x22, 0xE9,
    0xD8, 0x1C, 0x01, 0x61, 0x3A, 0xF4, 0xC7, 0x18, 0x7A, 0x9A, 0x61, 0x3E, 0xA0, 0x28, 0x62, 0xE3, 0x8F, 0xC5, 0x48, 0x5B,
    0xD5, 0x88, 0x95, 0x4F, 0xFB, 0x9F, 0x8F, 0xCD, 0x58, 0x49, 0xD8, 0xA9, 0xB8, 0x57, 0x77, 0x56, 0x98, 0x27, 0x00, 0x00,
    0xE1, 0xF1, 0x0B, 0x0B, 0x00, 0x00, 0x08, 0x00, 0x18, 0x01, 0x00, 0x00, 0x80, 0x26, 0x00, 0x00, 0x98, 0x27, 0x00, 0x00,
    0x98, 0xA7, 0x00, 0x00, 0xA0, 0x21, 0x00, 0x00, 0x3C, 0x00, 0x00, 0x00, 0x54, 0x00, 0x00, 0x00, 0x8C, 0x00, 0x00, 0x00,
    0x8C, 0x00, 0x00, 0x00, 0x8C, 0x00, 0x00, 0x00, 0x8C, 0x00, 0x00, 0x00, 0x8C, 0x00, 0x00, 0x00, 0xD0, 0x13, 0x00, 0x00,
    0x8E, 0x00, 0x00, 0x00, 0xD8, 0x1A, 0x00, 0x00, 0x9D, 0x00, 0x00, 0x00, 0x78, 0x17, 0x00, 0x00, 0xAC, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0xBC, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xC2, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0xCB, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xD5, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xEB, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x02, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0B, 0x01, 0x00, 0x00, 0x1F, 0x00, 0x69, 0x6F,
    0x63, 0x74, 0x6C, 0x5F, 0x72, 0x65, 0x61, 0x64, 0x5F, 0x6D, 0x73, 0x72, 0x00, 0x69, 0x6F, 0x63, 0x74, 0x6C, 0x5F, 0x72,
    0x65, 0x61, 0x64, 0x5F, 0x73, 0x6D, 0x6E, 0x00, 0x69, 0x6F, 0x63, 0x74, 0x6C, 0x5F, 0x77, 0x72, 0x69, 0x74, 0x65, 0x5F,
    0x6D, 0x73, 0x72, 0x00, 0x63, 0x70, 0x75, 0x69, 0x64, 0x00, 0x6D, 0x73, 0x72, 0x5F, 0x72, 0x65, 0x61, 0x64, 0x00, 0x6D,
    0x73, 0x72, 0x5F, 0x77, 0x72, 0x69, 0x74, 0x65, 0x00, 0x70, 0x63, 0x69, 0x5F, 0x63, 0x6F, 0x6E, 0x66, 0x69, 0x67, 0x5F,
    0x72, 0x65, 0x61, 0x64, 0x5F, 0x64, 0x77, 0x6F, 0x72, 0x64, 0x00, 0x70, 0x63, 0x69, 0x5F, 0x63, 0x6F, 0x6E, 0x66, 0x69,
    0x67, 0x5F, 0x77, 0x72, 0x69, 0x74, 0x65, 0x5F, 0x64, 0x77, 0x6F, 0x72, 0x64, 0x00, 0x67, 0x65, 0x74, 0x5F, 0x61, 0x72,
    0x63, 0x68, 0x00, 0x64, 0x65, 0x62, 0x75, 0x67, 0x5F, 0x70, 0x72, 0x69, 0x6E, 0x74, 0x00, 0x00, 0x43, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x1E, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x49, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x20, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x16, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x18, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0A, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xFF, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x2E, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x1A, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x30, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0E, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x20, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x49, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x20, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x28, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x28, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x16, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x20, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x28, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x08, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x1A, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x2C, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x16, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x20, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x28, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x07, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x1A, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x2C, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x16, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x20, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x28, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x05, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x1A, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x2C, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x16, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x20, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x28, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x1A, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x2C, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x16, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x20, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x28, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x1A, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x2C, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x20, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x2C, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x20, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x1E, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x49, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x20, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x16, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x18, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0A, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0xFF, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x2E, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x16, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x09, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x10, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x16, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x21, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xC0, 0xFD, 0xFF, 0xFF,
    0xFF, 0xFF, 0xFF, 0xFF, 0x16, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x18, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0A, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x08, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x26, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0A, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0xFF, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x2E, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x16, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x09, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x10, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x16, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x21, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x48, 0xFD, 0xFF, 0xFF,
    0xFF, 0xFF, 0xFF, 0xFF, 0x20, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x1E, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x49, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x20, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x16, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x18, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0A, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xFF, 0xFF, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x2E, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x16, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x09, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x10, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x16, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x21, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x90, 0xFE, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
    0x16, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x18, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x0A, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x10, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x26, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0A, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xFF, 0xFF, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x2E, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x16, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x09, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x10, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x16, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x21, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x18, 0xFE, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
    0x20, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x1E, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x49, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x1C, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xE0, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
    0x09, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0C, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0xE0, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x42, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x20, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x49, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0B, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0xE0, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x18, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x09, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x16, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x09, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x16, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x09, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x18, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x16, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x45, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x1C, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x20, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x49, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x09, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x25, 0x23, 0x22, 0x84, 0xE4, 0x9C, 0xF2, 0xCB, 0x16, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0B, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0xE0, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x0A, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x2C, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x07, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x16, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x09, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x10, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x16, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x21, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0xB8, 0xFD, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x16, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x0B, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xE0, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x0A, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x18, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x2C, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x07, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x16, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x09, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x10, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x16, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x21, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x50, 0xFD, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x16, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x0B, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xE0, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
    0x0A, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x10, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x2C, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x07, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x16, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x09, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x10, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x16, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x21, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xE8, 0xFC, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
    0x1C, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x20, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x20, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x1E, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x49, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x1C, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xE0, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x09, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0C, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0xE0, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x42, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x20, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x49, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0B, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0xE0, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x18, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x09, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x16, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x09, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x16, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x09, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x18, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x16, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x45, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x1C, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x20, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x49, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x1C, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xF8, 0xFF, 0xFF, 0xFF,
    0xFF, 0xFF, 0xFF, 0xFF, 0x0B, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xE0, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
    0x07, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0A, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xF0, 0x0F,
    0x00, 0x00, 0x00, 0x00, 0x2E, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0A, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x14, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x26, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x16, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x0B, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xE0, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
    0x07, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0A, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0F, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x2E, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0A, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x27, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x1A, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x2C, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0E, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0xD8, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x49, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x1C, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0xF8, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x0B, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0xE0, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x07, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0A, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0F, 0x00, 0x00, 0x00, 0x00, 0x00, 0x2E, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x0A, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0C, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x26, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x16, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0B, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0xE0, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x07, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0A, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0xF0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x2E, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x0A, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x27, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x1A, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x2F, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x0E, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xD0, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x49, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x1C, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xF8, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
    0x0B, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xE0, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x07, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x0A, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0F, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x2E, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0E, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xC8, 0xFF, 0xFF, 0xFF,
    0xFF, 0xFF, 0xFF, 0xFF, 0x49, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0xD8, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x28, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x10, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x16, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0xD0, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x28, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x08, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x1A, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x2F, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x15, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xC8, 0xFF, 0xFF, 0xFF,
    0xFF, 0xFF, 0xFF, 0xFF, 0x2F, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x1C, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x38, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x20, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x1E, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x49, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x18, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0A, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x10, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x26, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0A, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0xFF, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x2E, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x20, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x1E, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x49, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x18, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0A, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x26, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x0A, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xFF, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x2E, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x20, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x1E, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x49, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x18, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x0A, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x20, 0x00, 0xC0, 0x00, 0x00, 0x00, 0x00,
    0x39, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x23, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x68, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x18, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x0A, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xFF, 0x23, 0x00, 0xC0, 0x00, 0x00, 0x00, 0x00, 0x37, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x23, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x30, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x09, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x22, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x20, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x09, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x23, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xF0, 0x03, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x49, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x1C, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0xF8, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x09, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x0E, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xF8, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
    0x49, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0B, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xF8, 0xFF, 0xFF, 0xFF,
    0xFF, 0xFF, 0xFF, 0xFF, 0x18, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x09, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x79, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x16, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x09, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x10, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x16, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x45, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x1C, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x18, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x28, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x20, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0A, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x20, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x27, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0A, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x39, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x24, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x40, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x49, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x09, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x1C, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x20, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x49, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x1C, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xF8, 0xFF, 0xFF, 0xFF,
    0xFF, 0xFF, 0xFF, 0xFF, 0x09, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x20, 0x00, 0xC0, 0x00, 0x00, 0x00, 0x00,
    0x04, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x18, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x2D, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x15, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x09, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x10, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x2B, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0E, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0xF0, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x49, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xF0, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x16, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xF8, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
    0x0A, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xFF, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x2E, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x1A, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x15, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x39, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x23, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x40, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x49, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x09, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x1C, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x10, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x20, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x49, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x18, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0A, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x0F, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x2E, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x46, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x90, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x49, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x09, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x1C, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x10, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x20, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x22, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x28, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x49, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x09, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x1C, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x10, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x20, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x22, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xE8, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x4A, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0C, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0xB8, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x68, 0xFF, 0xFF, 0xFF,
    0xFF, 0xFF, 0xFF, 0xFF, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x58, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
    0x02, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x48, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x03, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x38, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x04, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x28, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x05, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x18, 0xFF, 0xFF, 0xFF,
    0xFF, 0xFF, 0xFF, 0xFF, 0x06, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x08, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
    0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xF8, 0xFE, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x09, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0xE8, 0xFE, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x0A, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0xD8, 0xFE, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x0E, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xC8, 0xFE, 0xFF, 0xFF,
    0xFF, 0xFF, 0xFF, 0xFF, 0x0F, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xB8, 0xFE, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
    0x1C, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x10, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x49, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x18, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x46, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x70, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x49, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x09, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x20, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x22, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x88, 0x02, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x49, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x09, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x20, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x22, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x58, 0x02, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x4A, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x23, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xC8, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x8B, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x88, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x79, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x78, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x7A, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x68, 0xFF, 0xFF, 0xFF,
    0xFF, 0xFF, 0xFF, 0xFF, 0x7B, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x58, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
    0xE7, 0x00, 0x00, 0xC0, 0x00, 0x00, 0x00, 0x00, 0x48, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xE8, 0x00, 0x00, 0xC0,
    0x00, 0x00, 0x00, 0x00, 0x38, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x00, 0x00, 0x01, 0xC0, 0x00, 0x00, 0x00, 0x00,
    0x28, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x04, 0x00, 0x01, 0xC0, 0x00, 0x00, 0x00, 0x00, 0x18, 0xFF, 0xFF, 0xFF,
    0xFF, 0xFF, 0xFF, 0xFF, 0x15, 0x00, 0x01, 0xC0, 0x00, 0x00, 0x00, 0x00, 0x08, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
    0x61, 0x00, 0x01, 0xC0, 0x00, 0x00, 0x00, 0x00, 0xF8, 0xFE, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x63, 0x00, 0x01, 0xC0,
    0x00, 0x00, 0x00, 0x00, 0xE8, 0xFE, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x64, 0x00, 0x01, 0xC0, 0x00, 0x00, 0x00, 0x00,
    0xD8, 0xFE, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x65, 0x00, 0x01, 0xC0, 0x00, 0x00, 0x00, 0x00, 0xC8, 0xFE, 0xFF, 0xFF,
    0xFF, 0xFF, 0xFF, 0xFF, 0x66, 0x00, 0x01, 0xC0, 0x00, 0x00, 0x00, 0x00, 0xB8, 0xFE, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
    0x67, 0x00, 0x01, 0xC0, 0x00, 0x00, 0x00, 0x00, 0xA8, 0xFE, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x68, 0x00, 0x01, 0xC0,
    0x00, 0x00, 0x00, 0x00, 0x98, 0xFE, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x69, 0x00, 0x01, 0xC0, 0x00, 0x00, 0x00, 0x00,
    0x88, 0xFE, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x6A, 0x00, 0x01, 0xC0, 0x00, 0x00, 0x00, 0x00, 0x78, 0xFE, 0xFF, 0xFF,
    0xFF, 0xFF, 0xFF, 0xFF, 0x6B, 0x00, 0x01, 0xC0, 0x00, 0x00, 0x00, 0x00, 0x68, 0xFE, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
    0x71, 0x00, 0x01, 0xC0, 0x00, 0x00, 0x00, 0x00, 0x58, 0xFE, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x92, 0x02, 0x01, 0xC0,
    0x00, 0x00, 0x00, 0x00, 0x48, 0xFE, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x93, 0x02, 0x01, 0xC0, 0x00, 0x00, 0x00, 0x00,
    0x38, 0xFE, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x96, 0x02, 0x01, 0xC0, 0x00, 0x00, 0x00, 0x00, 0x28, 0xFE, 0xFF, 0xFF,
    0xFF, 0xFF, 0xFF, 0xFF, 0x99, 0x02, 0x01, 0xC0, 0x00, 0x00, 0x00, 0x00, 0x18, 0xFE, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
    0x9A, 0x02, 0x01, 0xC0, 0x00, 0x00, 0x00, 0x00, 0x08, 0xFE, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x9B, 0x02, 0x01, 0xC0,
    0x00, 0x00, 0x00, 0x00, 0xF8, 0xFD, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xB0, 0x02, 0x01, 0xC0, 0x00, 0x00, 0x00, 0x00,
    0xE8, 0xFD, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xB1, 0x02, 0x01, 0xC0, 0x00, 0x00, 0x00, 0x00, 0xD8, 0xFD, 0xFF, 0xFF,
    0xFF, 0xFF, 0xFF, 0xFF, 0xB2, 0x02, 0x01, 0xC0, 0x00, 0x00, 0x00, 0x00, 0xC8, 0xFD, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
    0xB3, 0x02, 0x01, 0xC0, 0x00, 0x00, 0x00, 0x00, 0xB8, 0xFD, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xB4, 0x02, 0x01, 0xC0,
    0x00, 0x00, 0x00, 0x00, 0xA8, 0xFD, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x20, 0x10, 0x01, 0xC0, 0x00, 0x00, 0x00, 0x00,
    0x98, 0xFD, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x21, 0x10, 0x01, 0xC0, 0x00, 0x00, 0x00, 0x00, 0x88, 0xFD, 0xFF, 0xFF,
    0xFF, 0xFF, 0xFF, 0xFF, 0x22, 0x10, 0x01, 0xC0, 0x00, 0x00, 0x00, 0x00, 0x78, 0xFD, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
    0x2B, 0x10, 0x01, 0xC0, 0x00, 0x00, 0x00, 0x00, 0x68, 0xFD, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x49, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x09, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x20, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x1E, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x49, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x18, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x46, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x70, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x49, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x09, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x20, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x22, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x98, 0x01, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x49, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x09, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x20, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x22, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x68, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x4A, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x14, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xC8, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x00, 0x00, 0x01, 0xC0,
    0x00, 0x00, 0x00, 0x00, 0x88, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x04, 0x00, 0x01, 0xC0, 0x00, 0x00, 0x00, 0x00,
    0x78, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x15, 0x00, 0x01, 0xC0, 0x00, 0x00, 0x00, 0x00, 0x68, 0xFF, 0xFF, 0xFF,
    0xFF, 0xFF, 0xFF, 0xFF, 0x64, 0x00, 0x01, 0xC0, 0x00, 0x00, 0x00, 0x00, 0x58, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
    0x65, 0x00, 0x01, 0xC0, 0x00, 0x00, 0x00, 0x00, 0x48, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x66, 0x00, 0x01, 0xC0,
    0x00, 0x00, 0x00, 0x00, 0x38, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x67, 0x00, 0x01, 0xC0, 0x00, 0x00, 0x00, 0x00,
    0x28, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x68, 0x00, 0x01, 0xC0, 0x00, 0x00, 0x00, 0x00, 0x18, 0xFF, 0xFF, 0xFF,
    0xFF, 0xFF, 0xFF, 0xFF, 0x69, 0x00, 0x01, 0xC0, 0x00, 0x00, 0x00, 0x00, 0x08, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
    0x6A, 0x00, 0x01, 0xC0, 0x00, 0x00, 0x00, 0x00, 0xF8, 0xFE, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x6B, 0x00, 0x01, 0xC0,
    0x00, 0x00, 0x00, 0x00, 0xE8, 0xFE, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x92, 0x02, 0x01, 0xC0, 0x00, 0x00, 0x00, 0x00,
    0xD8, 0xFE, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x96, 0x02, 0x01, 0xC0, 0x00, 0x00, 0x00, 0x00, 0xC8, 0xFE, 0xFF, 0xFF,
    0xFF, 0xFF, 0xFF, 0xFF, 0xB1, 0x02, 0x01, 0xC0, 0x00, 0x00, 0x00, 0x00, 0xB8, 0xFE, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
    0xB3, 0x02, 0x01, 0xC0, 0x00, 0x00, 0x00, 0x00, 0xA8, 0xFE, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xB4, 0x02, 0x01, 0xC0,
    0x00, 0x00, 0x00, 0x00, 0x98, 0xFE, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x20, 0x10, 0x01, 0xC0, 0x00, 0x00, 0x00, 0x00,
    0x88, 0xFE, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x21, 0x10, 0x01, 0xC0, 0x00, 0x00, 0x00, 0x00, 0x78, 0xFE, 0xFF, 0xFF,
    0xFF, 0xFF, 0xFF, 0xFF, 0x22, 0x10, 0x01, 0xC0, 0x00, 0x00, 0x00, 0x00, 0x68, 0xFE, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
    0x2B, 0x10, 0x01, 0xC0, 0x00, 0x00, 0x00, 0x00, 0x58, 0xFE, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x49, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x09, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x20, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x1E, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x49, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x09, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x23, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x68, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x20, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0A, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x35, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x23, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x30, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x09, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x22, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x20, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x09, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x24, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xC8, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x09, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x23, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x68, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x30, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x0A, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x35, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x23, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x30, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x09, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x22, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x20, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x09, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x24, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x30, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x09, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x22, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x20, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x09, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x23, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x30, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x49, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x09, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0D, 0x00, 0x00, 0xC0, 0xFF, 0xFF, 0xFF, 0xFF, 0x20, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x49, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x1C, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0xF8, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x18, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x07, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0A, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0xFF, 0xFF, 0xFF, 0xFF, 0x00, 0x00, 0x00, 0x00, 0x2E, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0E, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0xF8, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x49, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xF8, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x16, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x09, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x16, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x21, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x38, 0xF4, 0xFF, 0xFF,
    0xFF, 0xFF, 0xFF, 0xFF, 0x24, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x40, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x49, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x09, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x22, 0x00, 0x00, 0xC0,
    0xFF, 0xFF, 0xFF, 0xFF, 0x1C, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x20, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x49, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x1C, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0xF8, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x09, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0E, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xF0, 0xFF, 0xFF, 0xFF,
    0xFF, 0xFF, 0xFF, 0xFF, 0x49, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x1C, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0xF8, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x0B, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xF0, 0xFF, 0xFF, 0xFF,
    0xFF, 0xFF, 0xFF, 0xFF, 0x18, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0xF8, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x16, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x09, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x10, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x16, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x45, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x1C, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x18, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0E, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0xE8, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x49, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0xF0, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x04, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x28, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x10, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x49, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xE8, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
    0x1C, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x18, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x20, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x1E, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x49, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x09, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x23, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x68, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x20, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0A, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x35, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x23, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x30, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x09, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x22, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x20, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x09, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x24, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0xC8, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x09, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x23, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x68, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x30, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x0A, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x35, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x23, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x30, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x09, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x22, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x20, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x09, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x24, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x30, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x09, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x22, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x20, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x09, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x23, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x30, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x49, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x09, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x0D, 0x00, 0x00, 0xC0, 0xFF, 0xFF, 0xFF, 0xFF, 0x20, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x49, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x1C, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xF8, 0xFF, 0xFF, 0xFF,
    0xFF, 0xFF, 0xFF, 0xFF, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x18, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x07, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0A, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xFF, 0xFF, 0xFF, 0xFF,
    0x00, 0x00, 0x00, 0x00, 0x2E, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0E, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0xF8, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x49, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0xF8, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x16, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x09, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x16, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x21, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x20, 0xF8, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
    0x24, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x40, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x49, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x09, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x22, 0x00, 0x00, 0xC0, 0xFF, 0xFF, 0xFF, 0xFF,
    0x1C, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x20, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x49, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x1C, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0xF8, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x18, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x0A, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x2C, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x07, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x16, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xF8, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
    0x16, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x09, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x10, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x16, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x45, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x02, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x1C, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x18, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x0E, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xF0, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
    0x49, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xF0, 0xFF, 0xFF, 0xFF,
    0xFF, 0xFF, 0xFF, 0xFF, 0x1C, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x10, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x20, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x1E, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x49, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x09, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x23, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x68, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x20, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0A, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x35, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x23, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x30, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x09, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x22, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x20, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x09, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x24, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xC8, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x09, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x23, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x68, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x30, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x0A, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x35, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x23, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x30, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x09, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x22, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x20, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x09, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x24, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x30, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x09, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x22, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x20, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x09, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x23, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x30, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x49, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x09, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0D, 0x00, 0x00, 0xC0, 0xFF, 0xFF, 0xFF, 0xFF, 0x20, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x49, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x1C, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0xF8, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x09, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x0E, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xF8, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
    0x49, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x1C, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xF8, 0xFF, 0xFF, 0xFF,
    0xFF, 0xFF, 0xFF, 0xFF, 0x0B, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xF8, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
    0x18, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x09, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x16, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x09, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x16, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x09, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x16, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x09, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x16, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x09, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x28, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x16, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x45, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x1C, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x30, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x0E, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xF0, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x49, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xF0, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
    0x28, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x20, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0A, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x20, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x27, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x0A, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x39, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x24, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x40, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x49, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xF0, 0xFF, 0xFF, 0xFF,
    0xFF, 0xFF, 0xFF, 0xFF, 0x1C, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x10, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x20, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x49, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0xF8, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x0A, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0xFF, 0xFF, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x2E, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0A, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x22, 0x10, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x35, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x23, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x40, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x49, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x09, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xBB, 0x00, 0x00, 0xC0, 0xFF, 0xFF, 0xFF, 0xFF,
    0x1C, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x10, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x20, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x49, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x18, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x07, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x16, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x09, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x60, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x16, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x09, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x16, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x09, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x16, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x09, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x16, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x09, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x28, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x16, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x45, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x1C, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x30, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0E, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0xF0, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x49, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xF0, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x28, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x20, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0A, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x20, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x27, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0A, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x39, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x24, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x40, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x49, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xF0, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
    0x1C, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x10, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x20, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x49, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x28, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x18, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x09, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x64, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x16, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x09, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x16, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x09, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x16, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x09, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x16, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x09, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x28, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x16, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x45, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x1C, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x30, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0E, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xF0, 0xFF, 0xFF, 0xFF,
    0xFF, 0xFF, 0xFF, 0xFF, 0x49, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0xF0, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x28, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x20, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x0A, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x20, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x27, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0A, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x39, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x24, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x40, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x49, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0xF0, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x1C, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x10, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x20, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x49, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xF0, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
    0x1C, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x10, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x20, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x1E, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x49, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x09, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x16, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x45, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x05, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x1C, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0A, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x35, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x23, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x30, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x49, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x09, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xBB, 0x00, 0x00, 0xC0, 0xFF, 0xFF, 0xFF, 0xFF,
    0x20, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x49, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x09, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x16, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x21, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x90, 0xE1, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x0A, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x06, 0x83, 0x86, 0x61, 0xF1, 0x46, 0xE9, 0xC0, 0x35, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x23, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x30, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x49, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x09, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xBB, 0x00, 0x00, 0xC0, 0xFF, 0xFF, 0xFF, 0xFF,
    0x20, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x49, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x1C, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0xF8, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x09, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x16, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x21, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x48, 0xE3, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x0E, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0xF8, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x49, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x1C, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0xF8, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0xF8, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x16, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x09, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x16, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x21, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x48, 0xE6, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x0E, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0xF0, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x49, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x1C, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xF8, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x03, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0xF8, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x16, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x09, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x16, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x21, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x38, 0xE6, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
    0x0E, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xE8, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x49, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x0B, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xE8, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
    0x18, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0B, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xF0, 0xFF, 0xFF, 0xFF,
    0xFF, 0xFF, 0xFF, 0xFF, 0x18, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x09, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x18, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x09, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x18, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x16, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x45, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x06, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x1C, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x20, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x49, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xF0, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x0A, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x17, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x36, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x24, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x68, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0xF0, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x0A, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x1A, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x38, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x24, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x30, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x09, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x22, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x20, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x09, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x23, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x40, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x49, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x09, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xBB, 0x00, 0x00, 0xC0, 0xFF, 0xFF, 0xFF, 0xFF,
    0x1C, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x18, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x20, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x49, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x09, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x1C, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x18, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x20, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x41, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x4D, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x44, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x46, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x61, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x6D, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x69, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x6C, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x79, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x31, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x37, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x3A, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x20, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x66, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x61, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x6D, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x69, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x6C, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x79, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x3A, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x20, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x25, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x78, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x20, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x6D, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x6F, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x64, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x65, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x6C, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x3A, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x20, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x25, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x78, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0A, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
};

using PawnOpenFn = HRESULT(WINAPI*)(PHANDLE);
using PawnLoadFn = HRESULT(WINAPI*)(HANDLE, const UCHAR*, SIZE_T);
using PawnExecFn = HRESULT(WINAPI*)(HANDLE, PCSTR, const ULONG64*, SIZE_T, PULONG64, SIZE_T, PSIZE_T);
using PawnCloseFn = HRESULT(WINAPI*)(HANDLE);

struct AmdPawn {
    HMODULE lib = nullptr;
    HANDLE pawn = nullptr;
    HANDLE pciMutex = nullptr;
    PawnExecFn exec = nullptr;
    PawnCloseFn close = nullptr;
    uint32_t family = 0, model = 0;
    double energyUnit = 0;  // joules per count
    uint32_t svi0 = 0, svi1 = 0;  // SMN offsets of the core and SoC rails
    uint32_t ccdCount = 0;
    uint32_t coreCount = 0;
    KAFFINITY coreMask[kMaxCores] = {};
    WORD coreGroup[kMaxCores] = {};
    struct CoreState {
        uint64_t aperf = 0, energy = 0;
        double time = 0;
        bool have = false;
    } core[kMaxCores];
    uint64_t pkgEnergy = 0;
    double pkgTime = 0;
    bool havePkg = false;
    bool failed = false;
    bool htcOk = false;  // THM_HTC answered with the enable bit and a sane limit

    static bool CpuIsAmdZen(uint32_t& family, uint32_t& model) {
        int r[4];
        __cpuid(r, 0);
        if (r[1] != 0x68747541 /* Auth */ || r[3] != 0x69746E65 /* enti */ || r[2] != 0x444D4163 /* cAMD */)
            return false;
        __cpuid(r, 1);
        uint32_t base = (r[0] >> 8) & 0xF, ext = (r[0] >> 20) & 0xFF;
        family = base == 0xF ? base + ext : base;
        model = ((r[0] >> 4) & 0xF) | (((r[0] >> 16) & 0xF) << 4);
        return family >= 0x17 && family <= 0x1A;
    }

    static HMODULE LoadPawnLib() {
        wchar_t path[MAX_PATH];
        DWORD n = ExpandEnvironmentStringsW(L"%ProgramFiles%\\PawnIO\\PawnIOLib.dll", path, MAX_PATH);
        HMODULE m = nullptr;
        if (n && n < MAX_PATH) m = LoadLibraryExW(path, nullptr, LOAD_WITH_ALTERED_SEARCH_PATH);
        if (m) return m;
        HKEY key;
        if (RegOpenKeyExW(HKEY_LOCAL_MACHINE,
                          L"SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Uninstall\\PawnIO", 0,
                          KEY_READ | KEY_WOW64_64KEY, &key) == ERROR_SUCCESS) {
            wchar_t dir[MAX_PATH] = {};
            DWORD bytes = sizeof(dir) - sizeof(wchar_t);
            if (RegQueryValueExW(key, L"InstallLocation", nullptr, nullptr,
                                 reinterpret_cast<BYTE*>(dir), &bytes) == ERROR_SUCCESS && dir[0]) {
                size_t len = wcslen(dir);
                if (len && dir[len - 1] != L'\\') wcscat_s(dir, L"\\");
                wcscat_s(dir, L"PawnIOLib.dll");
                m = LoadLibraryExW(dir, nullptr, LOAD_WITH_ALTERED_SEARCH_PATH);
            }
            RegCloseKey(key);
        }
        return m;
    }

    bool Call(PCSTR fn, ULONG64 in, ULONG64& out) {
        SIZE_T got = 0;
        ULONG64 result = 0;
        if (FAILED(exec(pawn, fn, &in, 1, &result, 1, &got)) || got < 1) return false;
        out = result;
        return true;
    }

    bool Msr(uint32_t msr, uint64_t& v) {
        ULONG64 out;
        if (!Call("ioctl_read_msr", msr, out)) return false;
        v = out;
        return true;
    }

    bool Smn(uint32_t offset, uint32_t& v) {
        // Every SMN user on the PC (HWiNFO, FanControl, Ryzen Master)
        // shares this mutex, or reads land in the middle of each other.
        if (pciMutex) {
            DWORD w = WaitForSingleObject(pciMutex, 20);
            if (w != WAIT_OBJECT_0 && w != WAIT_ABANDONED) return false;
        }
        ULONG64 out;
        bool ok = Call("ioctl_read_smn", offset, out);
        if (pciMutex) ReleaseMutex(pciMutex);
        if (ok) v = static_cast<uint32_t>(out);
        return ok;
    }

    void MapCores() {
        DWORD bytes = 0;
        GetLogicalProcessorInformationEx(RelationProcessorCore, nullptr, &bytes);
        if (!bytes) return;
        BYTE* buf = static_cast<BYTE*>(HeapAlloc(GetProcessHeap(), 0, bytes));
        if (!buf) return;
        if (GetLogicalProcessorInformationEx(
                RelationProcessorCore,
                reinterpret_cast<PSYSTEM_LOGICAL_PROCESSOR_INFORMATION_EX>(buf), &bytes)) {
            for (DWORD off = 0; off < bytes && coreCount < kMaxCores;) {
                auto* info = reinterpret_cast<PSYSTEM_LOGICAL_PROCESSOR_INFORMATION_EX>(buf + off);
                if (info->Relationship == RelationProcessorCore && info->Processor.GroupCount) {
                    KAFFINITY mask = info->Processor.GroupMask[0].Mask;
                    coreGroup[coreCount] = info->Processor.GroupMask[0].Group;
                    coreMask[coreCount] = mask & (~mask + 1);  // first thread of the core
                    ++coreCount;
                }
                off += info->Size;
            }
        }
        HeapFree(GetProcessHeap(), 0, buf);
    }

    bool Open() {
        failed = true;
        if (!CpuIsAmdZen(family, model)) return false;
        lib = LoadPawnLib();
        if (!lib) return false;
        auto open = reinterpret_cast<PawnOpenFn>(GetProcAddress(lib, "pawnio_open"));
        auto load = reinterpret_cast<PawnLoadFn>(GetProcAddress(lib, "pawnio_load"));
        exec = reinterpret_cast<PawnExecFn>(GetProcAddress(lib, "pawnio_execute"));
        close = reinterpret_cast<PawnCloseFn>(GetProcAddress(lib, "pawnio_close"));
        if (!open || !load || !exec || !close || FAILED(open(&pawn)) || !pawn) {
            Close();
            return false;
        }
        if (FAILED(load(pawn, kAmdFamily17Blob, sizeof(kAmdFamily17Blob)))) {
            Close();
            return false;
        }
        pciMutex = OpenMutexW(SYNCHRONIZE | MUTEX_MODIFY_STATE, FALSE, L"Global\\Access_PCI");
        if (!pciMutex) pciMutex = CreateMutexW(nullptr, FALSE, L"Global\\Access_PCI");
        uint64_t unit;
        if (Msr(0xC0010299, unit)) energyUnit = 1.0 / static_cast<double>(1ull << ((unit >> 8) & 0x1F));
        // SVI2 telemetry planes: Zen 2 desktop and Zen 3 desktop keep the
        // core rail at +0x10 and SoC at +0xC; first Zen at +0xC / +0x10.
        const uint32_t svi = 0x0005A000;
        if ((family == 0x17 && (model == 0x31 || model == 0x71)) ||
            (family == 0x19 && (model == 0x21 || model == 0x01 || model == 0x08))) {
            svi0 = svi + 0x10;
            svi1 = svi + 0xC;
        } else if (family == 0x17) {
            svi0 = svi + 0xC;
            svi1 = svi + 0x10;
        }
        // CCD sensors exist on chiplet parts (Zen 2/3 desktop, server).
        if ((family == 0x17 && (model == 0x31 || model == 0x71)) ||
            (family == 0x19 && (model == 0x21 || model == 0x01 || model == 0x08)))
            ccdCount = kMaxCcds;
        // THM_HTC: trust it only when it is switched on and its limit
        // (52 C plus half a degree a step) looks like a real one.
        uint32_t htc = 0;
        if (Smn(0x00059804, htc)) {
            double limit = 52.0 + 0.5 * ((htc >> 16) & 0x7F);
            htcOk = (htc & 1) && limit >= 60.0 && limit <= 116.0;  // 115.5 = the top step, seen on a 5800X
        }
        MapCores();
        failed = false;
        return true;
    }

    void Close() {
        if (pawn && close) close(pawn);
        pawn = nullptr;
        if (pciMutex) CloseHandle(pciMutex);
        pciMutex = nullptr;
        if (lib) FreeLibrary(lib);
        lib = nullptr;
        exec = nullptr;
        close = nullptr;
        havePkg = false;
        for (auto& c : core) c.have = false;
    }

    void Sample(Snapshot& s) {
        if (!pawn) return;
        bool any = false;
        uint32_t v;
        if (Smn(0x00059800, v)) {  // THM_TCON_CUR_TMP
            double t = static_cast<double>((v >> 21) & 0x7FF) / 8.0;
            if (v & 0x80000) t -= 49.0;
            if (t > -20 && t < 150) {
                s.cpuTemp = t;
                any = true;
            }
        }
        // THM_HTC: bit 0 enabled, bit 4 active (the chip is slowing itself for heat).
        if (htcOk && Smn(0x00059804, v)) s.cpuThermalThrottle = (v & 0x10) ? 1.0 : 0.0;
        uint32_t ccds = 0;
        for (uint32_t i = 0; i < ccdCount; ++i) {
            if (!Smn(0x00059954 + i * 4, v)) break;
            uint32_t raw = v & 0xFFF;
            double t = (static_cast<double>(raw) * 125.0 - 305000.0) / 1000.0;
            if (raw > 0 && t > 0 && t < 125) {
                s.cpuCcdTemp[i] = t;
                ccds = i + 1;
            }
        }
        s.ccdCount = ccds;
        if (svi0 && Smn(svi0, v)) {
            double volts = 1.55 - 0.00625 * static_cast<double>((v >> 16) & 0xFF);
            if (volts > 0.2 && volts < 2.0) s.cpuCoreVoltage = volts;
        }
        if (svi1 && Smn(svi1, v)) {
            double volts = 1.55 - 0.00625 * static_cast<double>((v >> 16) & 0xFF);
            if (volts > 0.2 && volts < 2.0) {
                s.cpuSocVoltage = volts;
                // SVI2 current is the low byte. Amps per step depend on the
                // board's power stages; 0.4248 matches HWiNFO on the tower's
                // ASUS board (zenpower's generic 0.2943 read a third low there).
                double amps = 0.4248 * static_cast<double>(v & 0xFF);
                if (amps >= 0 && amps < 100) s.cpuSocPower = volts * amps;
            }
        }
        uint64_t m;
        double now = QpcSeconds();
        if (energyUnit > 0 && Msr(0xC001029B, m)) {
            uint64_t e = m & 0xFFFFFFFFull;
            if (havePkg && now > pkgTime) {
                uint64_t d = e >= pkgEnergy ? e - pkgEnergy : e + 0x100000000ull - pkgEnergy;
                double w = static_cast<double>(d) * energyUnit / (now - pkgTime);
                if (w >= 0 && w < 1000) s.cpuPackagePower = w;
            }
            pkgEnergy = e;
            pkgTime = now;
            havePkg = true;
            any = true;
        }
        // Per-core reads run on that core: pin this thread for a moment.
        HANDLE self = GetCurrentThread();
        GROUP_AFFINITY old = {};
        bool haveOld = GetThreadGroupAffinity(self, &old) != FALSE;
        double clockSum = 0, clockMax = 0, effSum = 0, powerSum = 0;
        uint32_t clockN = 0, effN = 0, powerN = 0;
        for (uint32_t i = 0; i < coreCount; ++i) {
            GROUP_AFFINITY ga = {};
            ga.Group = coreGroup[i];
            ga.Mask = coreMask[i];
            if (!SetThreadGroupAffinity(self, &ga, nullptr)) continue;
            double t = QpcSeconds();
            uint64_t ps, aperf, ce;
            if (Msr(0xC0010293, ps)) {  // hardware P-state status
                double fid = static_cast<double>(ps & 0xFF);
                double did = static_cast<double>((ps >> 8) & 0x3F);
                if (did > 0) {
                    double mhz = fid / did * 200.0;
                    if (mhz > 100 && mhz < 10000) {
                        s.cpuCoreClock[i] = mhz;
                        clockSum += mhz;
                        if (mhz > clockMax) clockMax = mhz;
                        ++clockN;
                    }
                }
            }
            bool haveA = Msr(0xC00000E8, aperf);
            bool haveE = energyUnit > 0 && Msr(0xC001029A, ce);
            CoreState& c = core[i];
            if (c.have && t > c.time) {
                double dt = t - c.time;
                if (haveA && aperf >= c.aperf) {
                    double mhz = static_cast<double>(aperf - c.aperf) / dt / 1e6;
                    if (mhz >= 0 && mhz < 10000) {
                        s.cpuCoreEffectiveClock[i] = mhz;
                        effSum += mhz;
                        ++effN;
                    }
                }
                if (haveE) {
                    uint64_t e = ce & 0xFFFFFFFFull;
                    uint64_t d = e >= c.energy ? e - c.energy : e + 0x100000000ull - c.energy;
                    double w = static_cast<double>(d) * energyUnit / dt;
                    if (w >= 0 && w < 500) {
                        powerSum += w;
                        ++powerN;
                    }
                }
            }
            c.aperf = haveA ? aperf : 0;
            c.energy = haveE ? (ce & 0xFFFFFFFFull) : 0;
            c.time = t;
            c.have = haveA || haveE;
        }
        if (haveOld) SetThreadGroupAffinity(self, &old, nullptr);
        s.physicalCores = coreCount;
        if (clockN) {
            s.cpuClockAvg = clockSum / clockN;
            s.cpuClockMax = clockMax;
            any = true;
        }
        if (effN) s.cpuEffectiveClockAvg = effSum / effN;
        if (powerN && powerN == coreCount) s.cpuCoresPower = powerSum;
        if (any) s.sources |= kSrcPawnIO;
    }
};

// ------------------------------------------------------------- GPU: NVAPI

struct Nvapi {
    using QueryFn = void*(__cdecl*)(uint32_t);
    using InitFn = int(__cdecl*)();
    using EnumFn = int(__cdecl*)(void**, uint32_t*);
    using GpuU32Fn = int(__cdecl*)(void*, uint32_t*);
    using GpuPtrFn = int(__cdecl*)(void*, void*);
    using ThermalFn = int(__cdecl*)(void*, uint32_t, void*);
    using NameFn = int(__cdecl*)(void*, char*);

    struct ThermalSettings {  // NV_GPU_THERMAL_SETTINGS_V2
        uint32_t version, count;
        struct { int32_t controller, defaultMin, defaultMax, current, target; } sensor[3];
    };
    struct PstatesEx {  // NV_GPU_DYNAMIC_PSTATES_INFO_EX
        uint32_t version, flags;
        struct { uint32_t present, percentage; } utilization[8];
    };
    struct Clocks {  // NV_GPU_CLOCK_FREQUENCIES_V2
        uint32_t version, typeAndReserved;
        struct { uint32_t present, kHz; } domain[32];
    };
    struct MemoryInfo {  // NV_DISPLAY_DRIVER_MEMORY_INFO_V3, KB
        uint32_t version, dedicated, availableDedicated, system, sharedSystem,
            curAvailableDedicated, evictionsSize, evictionCount;
    };
    struct ThermalSensors {  // undocumented, LibreHardwareMonitor layout
        uint32_t version, mask;
        int32_t reserved[8];
        int32_t temperatures[32];
    };
    struct FanCoolers {  // undocumented, LibreHardwareMonitor layout
        uint32_t version, count;
        uint32_t reserved[8];
        struct { uint32_t coolerId, rpm, minLevel, maxLevel, level, reserved[8]; } item[32];
    };

    HMODULE lib = nullptr;
    void* gpu = nullptr;
    ThermalFn thermal = nullptr;
    GpuPtrFn pstates = nullptr, clocks = nullptr, memory = nullptr, sensors = nullptr, fans = nullptr;
    GpuU32Fn tach = nullptr;
    uint32_t sensorMask = 0;
    uint32_t pciBus = kUnknownBus;
    wchar_t name[64] = {};

    static uint32_t Ver(uint32_t size, uint32_t v) { return size | (v << 16); }

    bool Open() {
        wchar_t path[MAX_PATH];
        UINT n = GetSystemDirectoryW(path, MAX_PATH);
        if (!n || n > MAX_PATH - 16) return false;
        wcscat_s(path, L"\\nvapi64.dll");
        lib = LoadLibraryExW(path, nullptr, 0);
        if (!lib) return false;
        auto qi = reinterpret_cast<QueryFn>(GetProcAddress(lib, "nvapi_QueryInterface"));
        if (!qi) return Fail();
        auto init = reinterpret_cast<InitFn>(qi(0x0150E828));
        auto enumGpus = reinterpret_cast<EnumFn>(qi(0xE5AC921F));
        if (!init || !enumGpus || init() != 0) return Fail();
        void* handles[64] = {};
        uint32_t count = 0;
        if (enumGpus(handles, &count) != 0 || count == 0) return Fail();
        gpu = handles[0];
        thermal = reinterpret_cast<ThermalFn>(qi(0xE3640A56));
        pstates = reinterpret_cast<GpuPtrFn>(qi(0x60DED2ED));
        clocks = reinterpret_cast<GpuPtrFn>(qi(0xDCB616C3));
        memory = reinterpret_cast<GpuPtrFn>(qi(0x07F9B368));
        sensors = reinterpret_cast<GpuPtrFn>(qi(0x65FE3AAD));
        fans = reinterpret_cast<GpuPtrFn>(qi(0x35AED5E8));
        tach = reinterpret_cast<GpuU32Fn>(qi(0x5F608315));
        if (auto busId = reinterpret_cast<GpuU32Fn>(qi(0x1BE0B8E5))) {
            uint32_t bus = 0;
            if (busId(gpu, &bus) == 0) pciBus = bus;
        }
        if (auto fullName = reinterpret_cast<NameFn>(qi(0xCEEE8E9F))) {
            char raw[64] = {};
            if (fullName(gpu, raw) == 0) CopyAnsiName(name, 64, raw, 63);
        }
        if (sensors) {
            // Find how many sensor slots this card answers for.
            for (uint32_t bit = 0; bit < 32; ++bit) {
                ThermalSensors t = {};
                t.version = Ver(sizeof(t), 2);
                t.mask = sensorMask | (1u << bit);
                if (sensors(gpu, &t) != 0) break;
                sensorMask = t.mask;
            }
            if (!sensorMask) sensors = nullptr;
        }
        return true;
    }

    bool Fail() {
        if (lib) FreeLibrary(lib);
        lib = nullptr;
        gpu = nullptr;
        return false;
    }

    void Close() {
        // NvAPI_Unload only when this was the last user; skipping it is safe.
        if (lib) FreeLibrary(lib);
        lib = nullptr;
        gpu = nullptr;
    }

    void Sample(Snapshot& s) {
        if (!gpu) return;
        bool any = false;
        if (thermal) {
            ThermalSettings t = {};
            t.version = Ver(sizeof(t), 2);
            if (thermal(gpu, 15 /* all */, &t) == 0 && t.count > 0) {
                s.gpuTemp = t.sensor[0].current;
                any = true;
            }
        }
        if (sensors) {
            ThermalSensors t = {};
            t.version = Ver(sizeof(t), 2);
            t.mask = sensorMask;
            if (sensors(gpu, &t) == 0) {
                if (sensorMask & (1u << 1)) {
                    double h = t.temperatures[1] / 256.0;
                    if (h > 0 && h < 150) s.gpuHotspot = h;
                }
                // Memory junction is the last slot: 9 on cards that answer ten,
                // 7 on Ada cards that answer eight (matches HWiNFO on an RTX 4070).
                int jIdx = (sensorMask & (1u << 9)) ? 9 : (sensorMask & (1u << 7)) ? 7 : -1;
                if (jIdx >= 0) {
                    double j = t.temperatures[jIdx] / 256.0;
                    if (j > 0 && j < 150) s.gpuMemJunction = j;
                }
            }
        }
        if (pstates) {
            PstatesEx p = {};
            p.version = Ver(sizeof(p), 1);
            if (pstates(gpu, &p) == 0 && (p.utilization[0].present & 1)) {
                s.gpuUsage = p.utilization[0].percentage;
                any = true;
            }
        }
        if (clocks) {
            Clocks c = {};
            c.version = Ver(sizeof(c), 2);
            if (clocks(gpu, &c) == 0) {
                if (c.domain[0].present & 1) s.gpuClock = c.domain[0].kHz / 1000.0;
                // Afterburner's "memory clock" figure. Double it for the effective
                // data rate (Afterburner's "effective memory clock"); HWiNFO shows it / 8.
                if (c.domain[4].present & 1) s.gpuMemClock = c.domain[4].kHz / 1000.0;
                any = true;
            }
        }
        if (memory) {
            MemoryInfo m = {};
            m.version = Ver(sizeof(m), 3);
            if (memory(gpu, &m) == 0 && m.dedicated) {
                s.gpuVramTotalMB = m.dedicated / 1024.0;
                s.gpuVramUsedMB = (m.dedicated - m.curAvailableDedicated) / 1024.0;
                any = true;
            }
        }
        if (fans) {
            FanCoolers f = {};
            f.version = Ver(sizeof(f), 1);
            if (fans(gpu, &f) == 0 && f.count > 0 && f.count <= 32) {
                s.gpuFanPercent = f.item[0].level;
                s.gpuFanRpm = f.item[0].rpm;
            }
        }
        if (tach && !IsValid(s.gpuFanRpm)) {
            uint32_t rpm = 0;
            if (tach(gpu, &rpm) == 0) s.gpuFanRpm = rpm;
        }
        if (name[0]) wcscpy_s(s.gpuName, name);
        s.gpuPciBus = pciBus;
        s.gpuVendorId = 0x10DE;
        if (any) s.sources |= kSrcNvapi;
    }
};

// -------------------------------------------------------------- GPU: NVML

struct Nvml {
    using InitFn = int(__cdecl*)();
    using HandleFn = int(__cdecl*)(unsigned, void**);
    using U32Fn = int(__cdecl*)(void*, unsigned*);
    using TempFn = int(__cdecl*)(void*, int, unsigned*);
    using ClockFn = int(__cdecl*)(void*, int, unsigned*);
    using NameFn = int(__cdecl*)(void*, char*, unsigned);
    struct Util { unsigned gpu, memory; };
    using UtilFn = int(__cdecl*)(void*, Util*);
    struct Mem { unsigned long long total, free, used; };
    using MemFn = int(__cdecl*)(void*, Mem*);
    using ReasonFn = int(__cdecl*)(void*, unsigned long long*);
    using DriverFn = int(__cdecl*)(char*, unsigned);

    HMODULE lib = nullptr;
    void* dev = nullptr;
    InitFn shutdown = nullptr;
    U32Fn power = nullptr, fan = nullptr;
    TempFn temp = nullptr;
    ClockFn clock = nullptr;
    UtilFn util = nullptr;
    MemFn mem = nullptr;
    ReasonFn reasons = nullptr;
    wchar_t name[64] = {};
    wchar_t driver[32] = {};

    bool Open() {
        wchar_t path[MAX_PATH];
        UINT n = GetSystemDirectoryW(path, MAX_PATH);
        if (!n || n > MAX_PATH - 16) return false;
        wcscat_s(path, L"\\nvml.dll");
        lib = LoadLibraryExW(path, nullptr, LOAD_LIBRARY_SEARCH_SYSTEM32);
        if (!lib) return false;
        auto init = reinterpret_cast<InitFn>(GetProcAddress(lib, "nvmlInit_v2"));
        auto handle = reinterpret_cast<HandleFn>(GetProcAddress(lib, "nvmlDeviceGetHandleByIndex_v2"));
        shutdown = reinterpret_cast<InitFn>(GetProcAddress(lib, "nvmlShutdown"));
        power = reinterpret_cast<U32Fn>(GetProcAddress(lib, "nvmlDeviceGetPowerUsage"));
        fan = reinterpret_cast<U32Fn>(GetProcAddress(lib, "nvmlDeviceGetFanSpeed"));
        temp = reinterpret_cast<TempFn>(GetProcAddress(lib, "nvmlDeviceGetTemperature"));
        clock = reinterpret_cast<ClockFn>(GetProcAddress(lib, "nvmlDeviceGetClockInfo"));
        util = reinterpret_cast<UtilFn>(GetProcAddress(lib, "nvmlDeviceGetUtilizationRates"));
        mem = reinterpret_cast<MemFn>(GetProcAddress(lib, "nvmlDeviceGetMemoryInfo"));
        reasons = reinterpret_cast<ReasonFn>(GetProcAddress(lib, "nvmlDeviceGetCurrentClocksEventReasons"));
        if (!reasons)
            reasons = reinterpret_cast<ReasonFn>(GetProcAddress(lib, "nvmlDeviceGetCurrentClocksThrottleReasons"));
        if (!init || !handle || !shutdown || init() != 0) {
            FreeLibrary(lib);
            lib = nullptr;
            return false;
        }
        if (handle(0, &dev) != 0 || !dev) {
            Close();
            return false;
        }
        if (auto getName = reinterpret_cast<NameFn>(GetProcAddress(lib, "nvmlDeviceGetName"))) {
            char raw[96] = {};
            if (getName(dev, raw, sizeof(raw)) == 0) CopyAnsiName(name, 64, raw, 95);
        }
        if (auto getDriver = reinterpret_cast<DriverFn>(GetProcAddress(lib, "nvmlSystemGetDriverVersion"))) {
            char raw[80] = {};
            if (getDriver(raw, sizeof(raw)) == 0) CopyAnsiName(driver, 32, raw, 31);
        }
        return true;
    }

    void Close() {
        if (lib) {
            if (shutdown) shutdown();
            FreeLibrary(lib);
        }
        lib = nullptr;
        dev = nullptr;
    }

    // Watts always come from here; the rest only fills what NVAPI left.
    void Sample(Snapshot& s) {
        if (!dev) return;
        bool any = false;
        unsigned v = 0;
        if (power && power(dev, &v) == 0 && v < 2000000) {
            s.gpuPower = v / 1000.0;
            any = true;
        }
        if (!IsValid(s.gpuTemp) && temp && temp(dev, 0, &v) == 0) s.gpuTemp = v, any = true;
        if (!IsValid(s.gpuUsage) && util) {
            Util u = {};
            if (util(dev, &u) == 0) s.gpuUsage = u.gpu, any = true;
        }
        if (!IsValid(s.gpuClock) && clock && clock(dev, 0, &v) == 0) s.gpuClock = v, any = true;
        if (!IsValid(s.gpuMemClock) && clock && clock(dev, 2, &v) == 0) s.gpuMemClock = v;
        if (!IsValid(s.gpuVramUsedMB) && mem) {
            Mem m = {};
            if (mem(dev, &m) == 0 && m.total) {
                s.gpuVramTotalMB = m.total / (1024.0 * 1024.0);
                s.gpuVramUsedMB = m.used / (1024.0 * 1024.0);
                any = true;
            }
        }
        if (!IsValid(s.gpuFanPercent) && fan && fan(dev, &v) == 0) s.gpuFanPercent = v;
        if (!s.gpuName[0] && name[0]) wcscpy_s(s.gpuName, name);
        if (driver[0]) wcscpy_s(s.gpuDriver, driver);
        // Why the card is not boosting: 0x20/0x40 heat (driver or hardware),
        // 0x04/0x80 power limit or power brake. Idle (0x01) is neither.
        unsigned long long r = 0;
        if (reasons && reasons(dev, &r) == 0) {
            s.gpuThermalThrottle = (r & 0x60ull) ? 1.0 : 0.0;
            s.gpuPowerThrottle = (r & 0x84ull) ? 1.0 : 0.0;
        }
        if (any) s.sources |= kSrcNvml;
    }
};

}  // namespace detail

// --------------------------------------------------------------- Collector
// Reads every source in this process. Not thread safe: one thread samples.
// An elevated process gets the PawnIO CPU numbers; any process gets the rest.
namespace detail {

// LUID of the first adapter from this vendor, so readers can match their own
// DXGI adapter. dxgi.dll is loaded here and freed again: no link needed.
inline bool FindAdapterLuid(uint32_t vendor, LUID& luid) {
    HMODULE dxgi = LoadLibraryExW(L"dxgi.dll", nullptr, LOAD_LIBRARY_SEARCH_SYSTEM32);
    if (!dxgi) return false;
    using CreateFn = HRESULT(WINAPI*)(REFIID, void**);
    auto create = reinterpret_cast<CreateFn>(GetProcAddress(dxgi, "CreateDXGIFactory1"));
    bool found = false;
    IDXGIFactory1* factory = nullptr;
    if (create && SUCCEEDED(create(__uuidof(IDXGIFactory1), reinterpret_cast<void**>(&factory)))) {
        IDXGIAdapter1* a = nullptr;
        for (UINT i = 0; !found && factory->EnumAdapters1(i, &a) == S_OK; ++i) {
            DXGI_ADAPTER_DESC1 d = {};
            if (SUCCEEDED(a->GetDesc1(&d)) && d.VendorId == vendor && !(d.Flags & DXGI_ADAPTER_FLAG_SOFTWARE)) {
                luid = d.AdapterLuid;
                found = true;
            }
            a->Release();
        }
        factory->Release();
    }
    FreeLibrary(dxgi);
    return found;
}

}  // namespace detail

class Collector {
public:
    bool Open() {
        if (open_) return true;
        cpu_.Open();
        disk_.Open();
        pawnOk_ = pawn_.Open();
        nvapiOk_ = nvapi_.Open();
        nvmlOk_ = nvml_.Open();
        if (nvapiOk_ || nvmlOk_) haveLuid_ = detail::FindAdapterLuid(0x10DE, luid_);
        detail::ReadCpuName(cpuName_, 64);
        cpuVendor_ = detail::ReadCpuVendor();
        detail::ReadRamSpeed(ramMts_, ramModules_);
        open_ = true;
        return true;
    }

    void Close() {
        if (!open_) return;
        disk_.Close();
        pawn_.Close();
        nvapi_.Close();
        nvml_.Close();
        pawnOk_ = nvapiOk_ = nvmlOk_ = false;
        open_ = false;
    }

    // Fills a fresh snapshot. The first call primes the rate counters, so
    // load, power and network show from the second call on.
    void Sample(Snapshot& s) {
        if (!open_) Open();
        ResetSnapshot(s);
        cpu_.Sample(s);
        detail::SampleMemory(s);
        disk_.Sample(s);
        net_.Sample(s);
        if (pawnOk_) pawn_.Sample(s);
        if (nvapiOk_) nvapi_.Sample(s);
        if (nvmlOk_) nvml_.Sample(s);
        wcscpy_s(s.cpuName, cpuName_);
        s.cpuVendorId = cpuVendor_;
        s.ramModules = ramModules_;
        if (ramMts_) {
            s.ramSpeedMTs = ramMts_;
            s.ramClockMHz = ramMts_ / 2.0;
        }
        if (haveLuid_) {
            s.gpuLuidLow = luid_.LowPart;
            s.gpuLuidHigh = luid_.HighPart;
            s.gpuVendorId = 0x10DE;
        }
        s.tick = GetTickCount64();
        s.sequence = ++sequence_;
    }

    bool HasPawnIO() const { return pawnOk_; }
    bool HasNvapi() const { return nvapiOk_; }
    bool HasNvml() const { return nvmlOk_; }

private:
    bool open_ = false, pawnOk_ = false, nvapiOk_ = false, nvmlOk_ = false, haveLuid_ = false;
    LUID luid_ = {};
    uint32_t sequence_ = 0;
    wchar_t cpuName_[64] = {};
    uint32_t cpuVendor_ = 0, ramMts_ = 0, ramModules_ = 0;
    detail::CpuLoad cpu_;
    detail::DiskPdh disk_;
    detail::Network net_;
    detail::AmdPawn pawn_;
    detail::Nvapi nvapi_;
    detail::Nvml nvml_;
};

// ----------------------------------------------------- publisher / reader

struct PublisherOptions {
    uint32_t intervalMs = 1000;   // sample period while someone reads
    uint32_t idleAfterMs = 5000;  // stop sampling this long after the last read
};

enum class ReadResult {
    Ok,           // fresh numbers
    Stale,        // a publisher is alive but woke from idle; numbers are old
    NoPublisher,  // nobody publishes: show dashes, or call StartPublisher()
};

enum class PublisherMode { Stopped, Waiting, Global, Local };

namespace detail {

inline bool MakeSd(PCWSTR sddl, SECURITY_ATTRIBUTES& sa, PSECURITY_DESCRIPTOR& sd) {
    sd = nullptr;
    if (!ConvertStringSecurityDescriptorToSecurityDescriptorW(sddl, SDDL_REVISION_1, &sd, nullptr))
        return false;
    sa.nLength = sizeof(sa);
    sa.lpSecurityDescriptor = sd;
    sa.bInheritHandle = FALSE;
    return true;
}

struct State {
    SRWLOCK lock = SRWLOCK_INIT;
    Snapshot local = {};
    std::atomic<int> mode{static_cast<int>(PublisherMode::Stopped)};
    std::atomic<bool> idle{true};
    std::atomic<uint64_t> localDemandTick{0};
    std::atomic<uint32_t> intervalMs{1000};
    uint32_t idleAfterMs = 5000;
    HANDLE thread = nullptr;
    HANDLE stopEvent = nullptr;
    HANDLE localWake = nullptr;

    // Reader side of the shared block.
    SRWLOCK readerLock = SRWLOCK_INIT;
    HANDLE readerMap = nullptr;
    SharedBlock* readerView = nullptr;
    HANDLE readerDemand = nullptr;
    uint64_t readerRetryTick = 0;
};

inline State& G() {
    static State s;
    return s;
}

inline bool ProcessIsElevated() {
    HANDLE token = nullptr;
    if (!OpenProcessToken(GetCurrentProcess(), TOKEN_QUERY, &token)) return false;
    TOKEN_ELEVATION e = {};
    DWORD got = 0;
    bool ok = GetTokenInformation(token, TokenElevation, &e, sizeof(e), &got) && e.TokenIsElevated;
    CloseHandle(token);
    return ok;
}

inline bool HeartbeatFresh(const SharedBlock* b, uint64_t now) {
    uint64_t hb = static_cast<uint64_t>(b->header.heartbeatTick);
    uint32_t iv = b->header.intervalMs ? b->header.intervalMs : 1000;
    uint64_t limit = iv * 3ull > 5000 ? iv * 3ull : 5000;
    return hb && now >= hb && now - hb <= limit;
}

inline bool CopyShared(const SharedBlock* b, Snapshot& out) {
    for (int attempt = 0; attempt < 50; ++attempt) {
        LONG s1 = b->header.seq;
        if (s1 & 1) {
            YieldProcessor();
            continue;
        }
        std::atomic_thread_fence(std::memory_order_acquire);
        uint32_t size = b->header.snapshotSize;
        if (size > sizeof(Snapshot)) size = sizeof(Snapshot);
        ResetSnapshot(out);
        std::memcpy(&out, &b->snapshot, size);
        std::atomic_thread_fence(std::memory_order_acquire);
        if (b->header.seq == s1) {
            out.size = sizeof(Snapshot);
            return true;
        }
    }
    return false;
}

inline bool EnsureReaderView(State& g, uint64_t now) {
    if (g.readerView) return true;
    if (now < g.readerRetryTick) return false;
    g.readerRetryTick = now + 2000;
    g.readerMap = OpenFileMappingW(FILE_MAP_READ, FALSE, kMappingName);
    if (!g.readerMap) return false;
    g.readerView = static_cast<SharedBlock*>(MapViewOfFile(g.readerMap, FILE_MAP_READ, 0, 0, sizeof(SharedBlock)));
    if (!g.readerView || g.readerView->header.magic != kMagic || g.readerView->header.layout != kLayoutVersion) {
        if (g.readerView) UnmapViewOfFile(g.readerView);
        CloseHandle(g.readerMap);
        g.readerView = nullptr;
        g.readerMap = nullptr;
        return false;
    }
    if (!g.readerDemand) g.readerDemand = OpenEventW(EVENT_MODIFY_STATE, FALSE, kDemandEventName);
    return true;
}

inline void PublishLocal(State& g, const Snapshot& s) {
    AcquireSRWLockExclusive(&g.lock);
    g.local = s;
    ReleaseSRWLockExclusive(&g.lock);
}

inline void WriteShared(SharedBlock* b, const Snapshot& s) {
    InterlockedIncrement(&b->header.seq);  // odd: writing
    std::atomic_thread_fence(std::memory_order_release);
    std::memcpy(&b->snapshot, &s, sizeof(Snapshot));
    std::atomic_thread_fence(std::memory_order_release);
    InterlockedIncrement(&b->header.seq);  // even: done
}

inline bool GlobalPublisherAlive(uint64_t now) {
    HANDLE m = OpenFileMappingW(FILE_MAP_READ, FALSE, kMappingName);
    if (!m) return false;
    bool alive = false;
    if (auto* b = static_cast<SharedBlock*>(MapViewOfFile(m, FILE_MAP_READ, 0, 0, sizeof(SharedBlock)))) {
        alive = b->header.magic == kMagic && b->header.publisherPid != GetCurrentProcessId() &&
                HeartbeatFresh(b, now);
        UnmapViewOfFile(b);
    }
    CloseHandle(m);
    return alive;
}

// One loop for both modes. Global: owns the mutex and the shared block.
// Local: cannot create Global objects (not elevated), samples only for
// this process and only while no global publisher is alive.
inline DWORD WINAPI PublisherThread(LPVOID) {
    State& g = G();
    SECURITY_ATTRIBUTES saMutex, saMap, saEvent;
    PSECURITY_DESCRIPTOR sdMutex = nullptr, sdMap = nullptr, sdEvent = nullptr;
    // Only SYSTEM and elevated admins may hold the publisher mutex.
    MakeSd(L"D:(A;;GA;;;SY)(A;;GA;;;BA)", saMutex, sdMutex);
    // Everyone at medium integrity or above may read the block and ask for data.
    MakeSd(L"D:(A;;GA;;;SY)(A;;GA;;;BA)(A;;0x5;;;WD)S:(ML;;NW;;;ME)", saMap, sdMap);
    MakeSd(L"D:(A;;GA;;;SY)(A;;GA;;;BA)(A;;0x100002;;;WD)S:(ML;;NW;;;ME)", saEvent, sdEvent);

    Collector collector;
    HANDLE mutex = nullptr, map = nullptr, demand = nullptr;
    SharedBlock* view = nullptr;
    bool owner = false;
    uint64_t lastDemand = GetTickCount64();
    uint64_t lastSample = 0;
    // Only an elevated process may own the shared block; anything else
    // samples for itself, so a normal-rights program can never squat it.
    const bool elevated = ProcessIsElevated();
    uint64_t nextOwnerTry = elevated ? 0 : UINT64_MAX;

    auto releaseGlobal = [&] {
        if (view) {
            view->header.heartbeatTick = 0;
            UnmapViewOfFile(view);
        }
        view = nullptr;
        if (map) CloseHandle(map);
        map = nullptr;
        if (demand) CloseHandle(demand);
        demand = nullptr;
        if (owner) ReleaseMutex(mutex);
        owner = false;
    };

    for (;;) {
        uint64_t now = GetTickCount64();
        // Try to become (or stay) the one global publisher.
        if (!owner && now >= nextOwnerTry) {
            nextOwnerTry = now + 2000;
            if (!mutex) mutex = CreateMutexW(sdMutex ? &saMutex : nullptr, FALSE, kPublisherMutexName);
            if (mutex) {
                DWORD w = WaitForSingleObject(mutex, 0);
                if (w == WAIT_OBJECT_0 || w == WAIT_ABANDONED) {
                    owner = true;
                    map = CreateFileMappingW(INVALID_HANDLE_VALUE, sdMap ? &saMap : nullptr, PAGE_READWRITE, 0,
                                             static_cast<DWORD>(kMappingSize), kMappingName);
                    if (map) view = static_cast<SharedBlock*>(MapViewOfFile(map, FILE_MAP_ALL_ACCESS, 0, 0, sizeof(SharedBlock)));
                    demand = CreateEventW(sdEvent ? &saEvent : nullptr, FALSE, FALSE, kDemandEventName);
                    if (!view) {
                        releaseGlobal();
                    } else {
                        view->header.magic = 0;
                        view->header.layout = kLayoutVersion;
                        view->header.snapshotSize = sizeof(Snapshot);
                        view->header.coreRev = SENSOR_CORE_REV;
                        view->header.publisherPid = GetCurrentProcessId();
                        view->header.intervalMs = g.intervalMs.load();
                        if (view->header.seq & 1) InterlockedIncrement(&view->header.seq);
                        std::atomic_thread_fence(std::memory_order_release);
                        view->header.magic = kMagic;
                        view->header.heartbeatTick = static_cast<LONG64>(now);
                    }
                }
            }
        }
        g.mode.store(static_cast<int>(owner ? PublisherMode::Global : PublisherMode::Local));

        // Who wants numbers?
        if (demand && WaitForSingleObject(demand, 0) == WAIT_OBJECT_0) lastDemand = now;
        uint64_t localTick = g.localDemandTick.load();
        if (localTick > lastDemand) lastDemand = localTick;
        bool otherGlobal = !owner && GlobalPublisherAlive(now);
        bool active = now - lastDemand < g.idleAfterMs && !otherGlobal;
        uint32_t interval = g.intervalMs.load();
        if (view) {
            view->header.intervalMs = interval;
            view->header.heartbeatTick = static_cast<LONG64>(now);
        }

        if (active && now - lastSample + 15 >= interval) {
            Snapshot s;
            collector.Sample(s);
            lastSample = s.tick;
            PublishLocal(g, s);
            if (view) WriteShared(view, s);
            g.idle.store(false);
        } else if (!active && !g.idle.load()) {
            g.idle.store(true);
        }

        // Sleep until the next sample, or wake on demand while idle.
        DWORD wait;
        if (active) {
            uint64_t since = GetTickCount64() - lastSample;
            wait = since >= interval ? 1 : static_cast<DWORD>(interval - since);
        } else {
            wait = 2000;  // heartbeat and ownership retry
        }
        HANDLE handles[3] = {g.stopEvent, g.localWake, demand};
        DWORD count = active ? 1 : (demand ? 3 : 2);
        DWORD r = WaitForMultipleObjects(count, handles, FALSE, wait);
        if (r == WAIT_OBJECT_0) break;
        if (r == WAIT_OBJECT_0 + 2) lastDemand = GetTickCount64();
    }

    releaseGlobal();
    if (mutex) CloseHandle(mutex);
    collector.Close();
    if (sdMutex) LocalFree(sdMutex);
    if (sdMap) LocalFree(sdMap);
    if (sdEvent) LocalFree(sdEvent);
    g.mode.store(static_cast<int>(PublisherMode::Stopped));
    return 0;
}

}  // namespace detail

// Starts the background thread that samples and shares the numbers. Call
// it from an elevated process to get the CPU temperature, power, clocks and
// voltage. If another process already publishes, this one waits and takes
// over when that one stops. Safe to call more than once.
inline bool StartPublisher(const PublisherOptions& options = {}) {
    detail::State& g = detail::G();
    if (g.thread) return true;
    g.intervalMs.store(options.intervalMs < 100 ? 100 : options.intervalMs);
    g.idleAfterMs = options.idleAfterMs < 1000 ? 1000 : options.idleAfterMs;
    g.stopEvent = CreateEventW(nullptr, TRUE, FALSE, nullptr);
    g.localWake = CreateEventW(nullptr, FALSE, FALSE, nullptr);
    if (!g.stopEvent || !g.localWake) return false;
    g.mode.store(static_cast<int>(PublisherMode::Waiting));
    g.thread = CreateThread(nullptr, 0, detail::PublisherThread, nullptr, 0, nullptr);
    return g.thread != nullptr;
}

// Stops the thread (waits at most timeoutMs) and gives up the shared block.
inline void StopPublisher(DWORD timeoutMs = 5000) {
    detail::State& g = detail::G();
    if (g.thread) {
        SetEvent(g.stopEvent);
        if (WaitForSingleObject(g.thread, timeoutMs) != WAIT_OBJECT_0) {
            // Still sampling a slow driver: leave it, it exits on its own.
            CloseHandle(g.thread);
            g.thread = nullptr;
            return;
        }
        CloseHandle(g.thread);
        g.thread = nullptr;
    }
    if (g.stopEvent) CloseHandle(g.stopEvent);
    if (g.localWake) CloseHandle(g.localWake);
    g.stopEvent = g.localWake = nullptr;
}

inline void SetInterval(uint32_t ms) {
    detail::G().intervalMs.store(ms < 100 ? 100 : ms);
}

inline PublisherMode Mode() {
    return static_cast<PublisherMode>(detail::G().mode.load());
}

// Latest numbers from the best place: this process's own publisher if it
// owns the shared block, else the shared block, else this process's local
// sampler. Every call also tells the publisher someone is reading, which
// wakes it from idle. Cheap: call it once per refresh.
inline ReadResult Read(Snapshot& out, uint32_t maxAgeMs = 0) {
    detail::State& g = detail::G();
    uint64_t now = GetTickCount64();
    PublisherMode mode = Mode();
    uint32_t interval = g.intervalMs.load();
    if (!maxAgeMs) maxAgeMs = interval * 2 + 1500;

    auto readLocal = [&]() -> ReadResult {
        g.localDemandTick.store(now);
        if (g.idle.load() && g.localWake) SetEvent(g.localWake);
        AcquireSRWLockShared(&g.lock);
        out = g.local;
        ReleaseSRWLockShared(&g.lock);
        if (!out.tick) {
            ResetSnapshot(out);
            return ReadResult::Stale;
        }
        return now - out.tick <= maxAgeMs ? ReadResult::Ok : ReadResult::Stale;
    };

    if (mode == PublisherMode::Global) return readLocal();

    AcquireSRWLockExclusive(&g.readerLock);
    ReadResult result = ReadResult::NoPublisher;
    bool got = false;
    if (detail::EnsureReaderView(g, now) && detail::HeartbeatFresh(g.readerView, now)) {
        if (!g.readerDemand) g.readerDemand = OpenEventW(EVENT_MODIFY_STATE, FALSE, kDemandEventName);
        if (g.readerDemand) SetEvent(g.readerDemand);
        if (detail::CopyShared(g.readerView, out)) {
            got = true;
            uint32_t iv = g.readerView->header.intervalMs ? g.readerView->header.intervalMs : interval;
            uint32_t limit = maxAgeMs > iv * 2 + 1500 ? maxAgeMs : iv * 2 + 1500;
            result = out.tick && now - out.tick <= limit ? ReadResult::Ok : ReadResult::Stale;
        }
    } else if (g.readerView && !detail::HeartbeatFresh(g.readerView, now)) {
        // Publisher gone: drop the view so a new one is picked up.
        UnmapViewOfFile(g.readerView);
        CloseHandle(g.readerMap);
        g.readerView = nullptr;
        g.readerMap = nullptr;
        g.readerRetryTick = 0;
    }
    ReleaseSRWLockExclusive(&g.readerLock);
    if (got) return result;

    if (mode == PublisherMode::Local || mode == PublisherMode::Waiting) return readLocal();
    ResetSnapshot(out);
    return ReadResult::NoPublisher;
}

// Frees the reader's handles. Call on unload after StopPublisher().
inline void CloseReader() {
    detail::State& g = detail::G();
    AcquireSRWLockExclusive(&g.readerLock);
    if (g.readerView) UnmapViewOfFile(g.readerView);
    if (g.readerMap) CloseHandle(g.readerMap);
    if (g.readerDemand) CloseHandle(g.readerDemand);
    g.readerView = nullptr;
    g.readerMap = nullptr;
    g.readerDemand = nullptr;
    g.readerRetryTick = 0;
    ReleaseSRWLockExclusive(&g.readerLock);
}

}  // namespace seamless_sensors

#endif  // SEAMLESS_SENSORS_CORE_INC
// ---- End of sensor core ----

#include <windhawk_utils.h>
#include <windows.h>
#include <windowsx.h>
#include <commctrl.h>
#include <dwmapi.h>
#include <psapi.h>
#include <shellapi.h>
#include <shlwapi.h>
#include <uxtheme.h>
#include <evntrace.h>
#include <evntcons.h>
#include <d2d1.h>
#include <d2d1_1.h>
#include <d2d1helper.h>
#include <dwrite.h>
#include <wincodec.h>
#include <imm.h>
#include <dispatcherqueue.h>
#include <winrt/Windows.Foundation.h>
#include <winrt/Windows.System.h>
#include <winrt/Windows.Graphics.Effects.h>
#include <winrt/Windows.UI.Composition.h>
#include <winrt/Windows.UI.Composition.Desktop.h>

#include <algorithm>
#include <atomic>
#include <cmath>
#include <cstdint>
#include <cstring>
#include <cwchar>
#include <cwctype>
#include <map>
#include <memory>
#include <mutex>
#include <set>
#include <string>
#include <vector>

#include <windhawk_tool_mod.h>

// The settings window and the tray menu come from the shared settings engine (sfoset, at the
// end of this file).
namespace sfoset {
void OpenSettingsWindow();
void CloseSettingsWindow();
struct TrayRow {
    int id = 0;
    std::wstring glyph, label, hint;
    bool checked = false, disabled = false, separator = false;
    std::vector<TrayRow> sub;
};
int ShowTrayMenu(HWND owner, const POINT* at, const std::vector<TrayRow>& rows);
extern std::atomic<HWND> g_settingsWnd;
}  // namespace sfoset
std::wstring Hotkey_Format(UINT mods, UINT vk);

#ifndef WDA_NONE
#define WDA_NONE 0x00000000
#endif

namespace {

constexpr wchar_t kCtrlClass[] = L"SeamlessFpsOverlay_Control_v1";
constexpr wchar_t kOverlayClass[] = L"SeamlessFpsOverlay_Overlay_v1";
constexpr wchar_t kGlassClass[] = L"SeamlessFpsOverlay_Glass_v1";
constexpr wchar_t kTrayTip[] = L"Seamless FPS Overlay";
constexpr wchar_t kSessionName[] = L"SeamlessFpsOverlay";

constexpr UINT WM_APP_RELOAD_SETTINGS = WM_APP + 101;
constexpr UINT WM_APP_TRAY_CALLBACK = WM_APP + 102;
constexpr UINT WM_APP_FOREGROUND = WM_APP + 103;
// Test hook: wParam = a process id to follow as if it were in front (0 = back to the front window).
// Lets a proof run show the overlay over a test app without taking focus from the owner.
constexpr UINT WM_APP_PIN_TARGET = WM_APP + 104;

constexpr UINT_PTR TIMER_TICK = 1;
constexpr UINT_PTR TIMER_ANIM = 2;
constexpr UINT_PTR TIMER_HOTKEY_RETRY = 3;
constexpr UINT_PTR TIMER_GFX = 4;  // the moving parts: fans, flames, dials

constexpr int HK_TOGGLE = 1;
constexpr int HK_PRESET = 2;

enum Preset { kFpsOnly = 0, kCompact, kBenchmark, kVertical };
enum Corner { kTopLeft = 0, kTopRight, kBottomLeft, kBottomRight };
enum Background { kGlass = 0, kTint, kSolid, kNone };
enum ColourStyle { kStyleGradient = 0, kStyleBlue, kStyleMauve, kStyleText, kStyleCustom };
enum ShowWhen { kInGames = 0, kAlways, kListed };

}  // namespace

// ============================================================================
// Small helpers
// ============================================================================

static std::wstring Trim(const std::wstring& s) {
    size_t a = s.find_first_not_of(L" \t\r\n");
    if (a == std::wstring::npos) return L"";
    size_t b = s.find_last_not_of(L" \t\r\n");
    return s.substr(a, b - a + 1);
}

static std::wstring Lower(std::wstring s) {
    for (auto& c : s) c = (wchar_t)towlower(c);
    return s;
}

static bool IsProcessElevated() {
    HANDLE token = nullptr;
    if (!OpenProcessToken(GetCurrentProcess(), TOKEN_QUERY, &token)) return false;
    TOKEN_ELEVATION elev{};
    DWORD len = 0;
    bool ok = GetTokenInformation(token, TokenElevation, &elev, sizeof(elev), &len) && elev.TokenIsElevated != 0;
    CloseHandle(token);
    return ok;
}

static std::vector<std::wstring> SplitList(const std::wstring& text) {
    std::vector<std::wstring> out;
    size_t start = 0;
    while (start <= text.size()) {
        size_t comma = text.find_first_of(L",;", start);
        std::wstring part = Lower(Trim(text.substr(start, comma == std::wstring::npos ? std::wstring::npos : comma - start)));
        if (!part.empty()) {
            size_t slash = part.find_last_of(L"\\/");
            if (slash != std::wstring::npos) part = part.substr(slash + 1);
            if (part.find(L'.') == std::wstring::npos) part += L".exe";
            out.push_back(part);
        }
        if (comma == std::wstring::npos) break;
        start = comma + 1;
    }
    return out;
}

static std::wstring StrSetting(PCWSTR name) {
    PCWSTR p = Wh_GetStringSetting(name);
    std::wstring s = p ? p : L"";
    if (p) Wh_FreeStringSetting(p);
    return s;
}

static bool ParseHexColour(const std::wstring& text, D2D1_COLOR_F& out) {
    std::wstring s = Trim(text);
    if (!s.empty() && s[0] == L'#') s = s.substr(1);
    if (s.size() != 6 && s.size() != 8) return false;
    for (wchar_t c : s)
        if (!iswxdigit(c)) return false;
    unsigned v = wcstoul(s.c_str(), nullptr, 16);
    if (s.size() == 6) {
        out = D2D1::ColorF(((v >> 16) & 0xFF) / 255.f, ((v >> 8) & 0xFF) / 255.f, (v & 0xFF) / 255.f, 1.f);
    } else {
        out = D2D1::ColorF(((v >> 24) & 0xFF) / 255.f, ((v >> 16) & 0xFF) / 255.f, ((v >> 8) & 0xFF) / 255.f,
                           (v & 0xFF) / 255.f);
    }
    return true;
}

static D2D1_COLOR_F Rgb(uint32_t rgb, float a = 1.f) {
    return D2D1::ColorF(((rgb >> 16) & 0xFF) / 255.f, ((rgb >> 8) & 0xFF) / 255.f, (rgb & 0xFF) / 255.f, a);
}

namespace mocha {
constexpr uint32_t kText = 0xCDD6F4, kSubtext = 0xA6ADC8, kOverlay = 0x6C7086, kSurface1 = 0x45475A;
constexpr uint32_t kSurface0 = 0x313244, kSurface2 = 0x585B70;
constexpr uint32_t kBase = 0x1E1E2E, kMantle = 0x181825, kCrust = 0x11111B;
constexpr uint32_t kBlue = 0x89B4FA, kMauve = 0xCBA6F7, kLavender = 0xB4BEFE, kSapphire = 0x74C7EC;
constexpr uint32_t kSky = 0x89DCEB, kTeal = 0x94E2D5, kGreen = 0xA6E3A1, kYellow = 0xF9E2AF;
constexpr uint32_t kPeach = 0xFAB387, kPink = 0xF5C2E7, kRed = 0xF38BA8;
}  // namespace mocha

// The colour list every colour choice uses. kPalGradient is the blue to mauve gradient,
// kPalSame follows the label colour, kPalCustom is the user's own colour.
enum Pal { kPalSame = -1, kPalGradient = 0, kPalBlue, kPalMauve, kPalLavender, kPalSapphire, kPalSky, kPalTeal,
           kPalGreen, kPalYellow, kPalPeach, kPalPink, kPalRed, kPalWhite, kPalCustom };
static const uint32_t kPalRgb[] = {0,           mocha::kBlue,  mocha::kMauve, mocha::kLavender, mocha::kSapphire,
                                   mocha::kSky, mocha::kTeal,  mocha::kGreen, mocha::kYellow,   mocha::kPeach,
                                   mocha::kPink, mocha::kRed,  mocha::kText,  0};
static int PalIndex(const std::wstring& v, int fallback) {
    static const wchar_t* names[] = {L"gradient", L"blue", L"mauve", L"lavender", L"sapphire", L"sky", L"teal",
                                     L"green",    L"yellow", L"peach", L"pink",   L"red",      L"white", L"custom"};
    if (_wcsicmp(v.c_str(), L"same") == 0) return kPalSame;
    if (_wcsicmp(v.c_str(), L"text") == 0) return kPalWhite;
    for (int i = 0; i < (int)ARRAYSIZE(names); i++)
        if (_wcsicmp(v.c_str(), names[i]) == 0) return i;
    return fallback;
}

// The Benchmark layout's blocks, in their default order.
enum Block { kBlkName = 0, kBlkFrames, kBlkInfo, kBlkCores, kBlkMemory, kBlkCard, kBlkVram, kBlkProcessor, kBlkCount };
// Widest content each block has needed since the settings last changed. It only grows, so the
// panel does not twitch when a number gains a digit.
static float g_blkNeed[kBlkCount] = {};
static const wchar_t* const kBlockKey[kBlkCount] = {L"Name",   L"Frames", L"Info", L"Cores",
                                                    L"Memory", L"Card",   L"Vram", L"Processor"};

// ============================================================================
// Settings
// ============================================================================

struct OverlaySettings {
    int preset = kBenchmark;
    bool showOnStart = true, showGpuName = true;
    int updateMs = 500;
    bool fps = true, frameTime = true, low1 = true, low01 = true, avgFps = true, frameGraph = true;
    bool gpuUsage = true, gpuTemp = true, gpuHotspot = true, gpuPower = true, gpuClock = true,
         gpuMemClock = false, vram = true, gpuFan = true;
    bool cpuUsage = true, cpuTemp = true, cpuPower = false, cpuClock = false, ram = true;
    int corner = kTopLeft, offsetX = 16, offsetY = 16;
    bool monitorPrimary = false;
    int scale = 100;
    int background = kGlass, opacity = 100;
    bool rounded = true;
    int cornerRadius = 12;
    bool border = true, borderGradient = true;
    D2D1_COLOR_F borderColour = Rgb(mocha::kSurface1);
    std::wstring fontFace = L"FiraCode Nerd Font";
    int fontWeight = 700;
    int labelStyle = kStyleGradient, valueStyle = kStyleText;
    D2D1_COLOR_F customColour = Rgb(0xF5C2E7);
    bool flipGradient = false;
    int showWhen = kInGames;
    std::vector<std::wstring> gameList, hideList;
    std::wstring toggleHotkey = L"Ctrl+Alt+Shift+]", presetHotkey;
    bool trayIcon = true, flyoutAnimation = true;
    int animationSpeed = 0;

    // Readings only the Benchmark layout has.
    bool jitter = true, latency = false, api = true, session = true, driver = true, cpuName = true,
         coreBars = true, coreThreads = false, ramUsed = true, ramSpeed = true, ramClock = true, gpuArt = true,
         vramUsed = true, vramTemp = true, cpuArt = true, cpuBusyClock = true;
    // Blocks: shown, column (0 left, 1 right), order, size in percent, colour.
    bool blockOn[kBlkCount] = {true, true, true, true, true, true, true, true};
    int blockColumn[kBlkCount] = {0, 0, 0, 0, 0, 1, 1, 1};
    int blockOrder[kBlkCount] = {1, 2, 3, 4, 5, 1, 2, 3};
    int blockSize[kBlkCount] = {100, 100, 100, 100, 100, 100, 100, 100};
    int blockColour[kBlkCount] = {kPalSame, kPalSame, kPalSame, kPalSame, kPalSame, kPalSame, kPalSame, kPalSame};
    std::map<std::wstring, std::wstring> labels;  // label key -> the user's own wording
    bool cards = false, capitals = true;
    int textSize = 100, bgStrength = 100, blockGap = 6;
    // Warnings
    int warnColour = kPalRed;
    int gpuTempWarn = 83, hotspotWarn = 95, cpuTempWarn = 85, vramWarn = 95, ramWarn = 90, fpsWarn = 0;
    bool throttleWarn = true;
    // Graph
    int graphStyle = 0, graphSeconds = 3, graphHeight = 36, graphTopMs = 50;
    bool spikeMarks = true;
    // Moving parts
    bool animations = true, fanSpin = true, flames = true, binaryCode = true, smoothDials = true,
         throttlePulse = true;
    int fanSpeed = 100, flameAt = 97, animFps = 30, gpuGaugeMax = 3000, cpuGaugeMax = 6000;
};

static OverlaySettings g_set;
static int g_presetOverride = -1;  // A layout picked from the tray or the shortcut, until the next save.

static int ChoiceIndex(const std::wstring& v, std::initializer_list<const wchar_t*> names, int fallback) {
    int i = 0;
    for (auto n : names) {
        if (_wcsicmp(v.c_str(), n) == 0) return i;
        i++;
    }
    return fallback;
}

// A setting that was never written (a key that is new in this version, or an install from the
// command line) reads as its default, not as 0 or empty.
static bool SettingStored(PCWSTR name) {
    static const wchar_t* kIds[] = {L"local@seamless-fps-overlay", L"seamless-fps-overlay"};
    bool anyKey = false;
    for (PCWSTR id : kIds) {
        std::wstring path = std::wstring(L"SOFTWARE\\Windhawk\\Engine\\Mods\\") + id + L"\\Settings";
        HKEY k = nullptr;
        if (RegOpenKeyExW(HKEY_LOCAL_MACHINE, path.c_str(), 0, KEY_QUERY_VALUE | KEY_WOW64_64KEY, &k) != ERROR_SUCCESS)
            continue;
        anyKey = true;
        bool has = RegQueryValueExW(k, name, nullptr, nullptr, nullptr, nullptr) == ERROR_SUCCESS;
        RegCloseKey(k);
        if (has) return true;
    }
    return !anyKey;  // settings kept somewhere we cannot see: trust Windhawk
}

static int IntSet(const std::wstring& name, int def) {
    return SettingStored(name.c_str()) ? Wh_GetIntSetting(name.c_str()) : def;
}
static bool BoolSet(const std::wstring& name, bool def) { return IntSet(name, def ? 1 : 0) != 0; }
static std::wstring TextSet(const std::wstring& name, const std::wstring& def) {
    return SettingStored(name.c_str()) ? StrSetting(name.c_str()) : def;
}

// Label keys and their wording when the user leaves the box empty.
struct LabelDef {
    const wchar_t* key;
    const wchar_t* text;
};
static const LabelDef kLabelDefs[] = {
    {L"lblFps", L"FPS"},            {L"lbl01", L"0.1%"},           {L"lbl1", L"1%"},
    {L"lblAvg", L"AVG"},            {L"lblJitter", L"JITTER"},     {L"lblFrame", L"FRAME TIME"},
    {L"lblLatency", L"LATENCY"},    {L"lblApi", L"API"},           {L"lblTime", L"PLAY TIME"},
    {L"lblDriver", L"DRIVER"},      {L"lblRam", L"RAM"},           {L"lblRamUsed", L"USED"},
    {L"lblRamSpeed", L"SPEED"},     {L"lblRamClock", L"CLOCK"},    {L"lblGpuLoad", L"LOAD"},
    {L"lblGpuPower", L"POWER"},     {L"lblGpuClock", L"CLOCK"},    {L"lblFan", L"FAN"},
    {L"lblGpuTemp", L"TEMP"},       {L"lblHotspot", L"HOT SPOT"},  {L"lblVram", L"VRAM"},
    {L"lblVramUsed", L"USED"},      {L"lblVramTemp", L"TEMP"},     {L"lblVramClock", L"CLOCK"},
    {L"lblCpuLoad", L"LOAD"},       {L"lblCpuPower", L"POWER"},    {L"lblCpuBoost", L"BOOST"},
    {L"lblCpuBusy", L"BUSY CLOCK"}, {L"lblCpuTemp", L"TEMP"},
};

static void LoadSettings() {
    OverlaySettings s;
    s.preset = ChoiceIndex(StrSetting(L"preset"), {L"fps", L"compact", L"benchmark", L"vertical"}, kBenchmark);
    s.showOnStart = Wh_GetIntSetting(L"showOnStart") != 0;
    s.showGpuName = Wh_GetIntSetting(L"showGpuName") != 0;
    s.updateMs = std::clamp(_wtoi(StrSetting(L"updateRate").c_str()), 250, 1000);
    if (s.updateMs != 250 && s.updateMs != 500 && s.updateMs != 1000) s.updateMs = 500;
    s.fps = Wh_GetIntSetting(L"fps") != 0;
    s.frameTime = Wh_GetIntSetting(L"frameTime") != 0;
    s.low1 = Wh_GetIntSetting(L"low1") != 0;
    s.low01 = Wh_GetIntSetting(L"low01") != 0;
    s.avgFps = Wh_GetIntSetting(L"avgFps") != 0;
    s.frameGraph = Wh_GetIntSetting(L"frameGraph") != 0;
    s.gpuUsage = Wh_GetIntSetting(L"gpuUsage") != 0;
    s.gpuTemp = Wh_GetIntSetting(L"gpuTemp") != 0;
    s.gpuHotspot = Wh_GetIntSetting(L"gpuHotspot") != 0;
    s.gpuPower = Wh_GetIntSetting(L"gpuPower") != 0;
    s.gpuClock = Wh_GetIntSetting(L"gpuClock") != 0;
    s.gpuMemClock = Wh_GetIntSetting(L"gpuMemClock") != 0;
    s.vram = Wh_GetIntSetting(L"vram") != 0;
    s.gpuFan = Wh_GetIntSetting(L"gpuFan") != 0;
    s.cpuUsage = Wh_GetIntSetting(L"cpuUsage") != 0;
    s.cpuTemp = Wh_GetIntSetting(L"cpuTemp") != 0;
    s.cpuPower = Wh_GetIntSetting(L"cpuPower") != 0;
    s.cpuClock = Wh_GetIntSetting(L"cpuClock") != 0;
    s.ram = Wh_GetIntSetting(L"ram") != 0;
    s.corner = ChoiceIndex(StrSetting(L"corner"), {L"topLeft", L"topRight", L"bottomLeft", L"bottomRight"}, kTopLeft);
    s.offsetX = std::clamp(Wh_GetIntSetting(L"offsetX"), 0, 2000);
    s.offsetY = std::clamp(Wh_GetIntSetting(L"offsetY"), 0, 2000);
    s.monitorPrimary = _wcsicmp(StrSetting(L"monitor").c_str(), L"primary") == 0;
    s.scale = std::clamp(Wh_GetIntSetting(L"scale"), 50, 300);
    s.background = ChoiceIndex(StrSetting(L"background"), {L"glass", L"tint", L"solid", L"none"}, kGlass);
    s.opacity = std::clamp(Wh_GetIntSetting(L"opacity"), 20, 100);
    s.rounded = Wh_GetIntSetting(L"rounded") != 0;
    s.cornerRadius = std::clamp(Wh_GetIntSetting(L"cornerRadius"), 0, 40);
    s.border = Wh_GetIntSetting(L"border") != 0;
    std::wstring bc = Lower(Trim(StrSetting(L"borderColour")));
    s.borderGradient = bc.empty() || bc == L"gradient";
    if (!s.borderGradient && !ParseHexColour(bc, s.borderColour)) s.borderGradient = true;
    s.fontFace = Trim(StrSetting(L"fontFace"));
    if (s.fontFace.empty()) s.fontFace = L"FiraCode Nerd Font";
    s.fontWeight = 400 + 100 * ChoiceIndex(StrSetting(L"fontWeight"), {L"normal", L"medium", L"semibold", L"bold", L"heavy"}, 3);
    s.labelStyle = ChoiceIndex(StrSetting(L"labelStyle"), {L"gradient", L"blue", L"mauve", L"text", L"custom"}, kStyleGradient);
    int vs = ChoiceIndex(StrSetting(L"valueStyle"), {L"text", L"gradient", L"custom"}, 0);
    s.valueStyle = vs == 1 ? kStyleGradient : vs == 2 ? kStyleCustom : kStyleText;
    if (!ParseHexColour(StrSetting(L"customColour"), s.customColour)) s.customColour = Rgb(0xF5C2E7);
    s.flipGradient = Wh_GetIntSetting(L"flipGradient") != 0;
    s.showWhen = ChoiceIndex(StrSetting(L"showWhen"), {L"games", L"always", L"listed"}, kInGames);
    s.gameList = SplitList(StrSetting(L"gameList"));
    s.hideList = SplitList(StrSetting(L"hideList"));
    s.toggleHotkey = Trim(StrSetting(L"toggleHotkey"));
    s.presetHotkey = Trim(StrSetting(L"presetHotkey"));
    s.trayIcon = Wh_GetIntSetting(L"settingsTrayIcon") != 0;
    s.flyoutAnimation = Wh_GetIntSetting(L"flyoutAnimation") != 0;
    s.animationSpeed =
        ChoiceIndex(StrSetting(L"animationSpeed"), {L"global", L"veryQuick", L"quick", L"normal", L"relaxed", L"slow"}, 0);
    // These three are on by default from 1.1; a stored choice still wins.
    s.gpuMemClock = BoolSet(L"gpuMemClock", true);
    s.cpuPower = BoolSet(L"cpuPower", true);
    s.cpuClock = BoolSet(L"cpuClock", true);

    s.jitter = BoolSet(L"jitter", true);
    s.latency = BoolSet(L"latency", false);
    s.api = BoolSet(L"api", true);
    s.session = BoolSet(L"session", true);
    s.driver = BoolSet(L"driver", true);
    s.cpuName = BoolSet(L"cpuName", true);
    s.coreBars = BoolSet(L"coreBars", true);
    s.coreThreads = TextSet(L"coreBarsEach", L"core") == L"thread";
    s.ramUsed = BoolSet(L"ramUsed", true);
    s.ramSpeed = BoolSet(L"ramSpeed", true);
    s.ramClock = BoolSet(L"ramClock", true);
    s.gpuArt = BoolSet(L"gpuArt", true);
    s.vramUsed = BoolSet(L"vramUsed", true);
    s.vramTemp = BoolSet(L"vramTemp", true);
    s.cpuArt = BoolSet(L"cpuArt", true);
    s.cpuBusyClock = BoolSet(L"cpuBusyClock", true);

    for (int b = 0; b < kBlkCount; b++) {
        const std::wstring k = kBlockKey[b];
        const bool right = b >= kBlkCard;
        s.blockOn[b] = BoolSet(L"show" + k, true);
        s.blockColumn[b] = ChoiceIndex(TextSet(L"column" + k, right ? L"right" : L"left"), {L"left", L"right"}, right);
        s.blockOrder[b] = std::clamp(IntSet(L"order" + k, right ? b - kBlkCard + 1 : b + 1), 1, 9);
        s.blockSize[b] = std::clamp(IntSet(L"size" + k, 100), 50, 200);
        s.blockColour[b] = PalIndex(TextSet(L"colour" + k, L"same"), kPalSame);
    }
    for (const auto& d : kLabelDefs) {
        std::wstring v = Trim(TextSet(d.key, L""));
        if (!v.empty()) s.labels[d.key] = v;
    }
    s.cards = TextSet(L"panels", L"one") == L"cards";
    s.capitals = BoolSet(L"capitals", true);
    s.textSize = std::clamp(IntSet(L"textSize", 100), 60, 200);
    s.bgStrength = std::clamp(IntSet(L"bgStrength", 100), 0, 150);
    s.blockGap = std::clamp(IntSet(L"blockGap", 6), 0, 40);

    s.warnColour = PalIndex(TextSet(L"warnColour", L"red"), kPalRed);
    if (s.warnColour < kPalBlue || s.warnColour > kPalWhite) s.warnColour = kPalRed;
    s.gpuTempWarn = std::clamp(IntSet(L"gpuTempWarn", 83), 0, 150);
    s.hotspotWarn = std::clamp(IntSet(L"hotspotWarn", 95), 0, 150);
    s.cpuTempWarn = std::clamp(IntSet(L"cpuTempWarn", 85), 0, 150);
    s.vramWarn = std::clamp(IntSet(L"vramWarn", 95), 0, 100);
    s.ramWarn = std::clamp(IntSet(L"ramWarn", 90), 0, 100);
    s.fpsWarn = std::clamp(IntSet(L"fpsWarn", 0), 0, 1000);
    s.throttleWarn = BoolSet(L"throttleWarn", true);

    s.graphStyle = ChoiceIndex(TextSet(L"graphStyle", L"line"), {L"line", L"area", L"bars"}, 0);
    s.graphSeconds = std::clamp(IntSet(L"graphSeconds", 3), 1, 10);
    s.graphHeight = std::clamp(IntSet(L"graphHeight", 36), 16, 120);
    switch (ChoiceIndex(TextSet(L"graphTop", L"50"), {L"auto", L"33", L"50", L"100"}, 2)) {
        case 0: s.graphTopMs = 0; break;
        case 1: s.graphTopMs = 33; break;
        case 3: s.graphTopMs = 100; break;
        default: s.graphTopMs = 50; break;
    }
    s.spikeMarks = BoolSet(L"spikeMarks", true);

    s.animations = BoolSet(L"animations", true);
    s.fanSpin = BoolSet(L"fanSpin", true);
    s.fanSpeed = std::clamp(IntSet(L"fanSpeed", 100), 10, 300);
    s.flames = BoolSet(L"flames", true);
    s.flameAt = std::clamp(IntSet(L"flameAt", 97), 1, 100);
    s.binaryCode = BoolSet(L"binaryCode", true);
    s.smoothDials = BoolSet(L"smoothDials", true);
    s.throttlePulse = BoolSet(L"throttlePulse", true);
    switch (ChoiceIndex(TextSet(L"animFps", L"30"), {L"15", L"30", L"60"}, 1)) {
        case 0: s.animFps = 15; break;
        case 2: s.animFps = 60; break;
        default: s.animFps = 30; break;
    }
    s.gpuGaugeMax = std::clamp(IntSet(L"gpuGaugeMax", 3000), 500, 5000);
    s.cpuGaugeMax = std::clamp(IntSet(L"cpuGaugeMax", 6000), 1000, 8000);
    g_set = std::move(s);
    for (float& n : g_blkNeed) n = 0;
}

static std::wstring Label(const wchar_t* key) {
    auto it = g_set.labels.find(key);
    std::wstring t;
    if (it != g_set.labels.end()) t = it->second;
    else
        for (const auto& d : kLabelDefs)
            if (!wcscmp(d.key, key)) t = d.text;
    if (g_set.capitals)
        for (auto& c : t) c = (wchar_t)towupper(c);
    return t;
}

static int ActivePreset() { return g_presetOverride >= 0 && g_presetOverride < 4 ? g_presetOverride : g_set.preset; }

// ============================================================================
// Hotkeys (the same parser as every DavidHiFi tool mod)
// ============================================================================

struct KeyName {
    UINT vk;
    const wchar_t* name;
};
// Canonical names first; later entries for the same key are accepted aliases.
static const KeyName kKeyNames[] = {
    {VK_SPACE, L"Space"},   {VK_TAB, L"Tab"},         {VK_RETURN, L"Enter"},   {VK_ESCAPE, L"Esc"},
    {VK_INSERT, L"Insert"}, {VK_DELETE, L"Delete"},   {VK_HOME, L"Home"},      {VK_END, L"End"},
    {VK_PRIOR, L"PageUp"},  {VK_NEXT, L"PageDown"},   {VK_UP, L"Up"},          {VK_DOWN, L"Down"},
    {VK_LEFT, L"Left"},     {VK_RIGHT, L"Right"},     {VK_OEM_3, L"`"},        {VK_OEM_MINUS, L"-"},
    {VK_OEM_PLUS, L"="},    {VK_OEM_4, L"["},         {VK_OEM_6, L"]"},        {VK_OEM_5, L"\\"},
    {VK_OEM_1, L";"},       {VK_OEM_7, L"'"},         {VK_OEM_COMMA, L","},    {VK_OEM_PERIOD, L"."},
    {VK_OEM_2, L"/"},       {VK_PAUSE, L"Pause"},     {VK_SNAPSHOT, L"PrintScreen"},
    {VK_RETURN, L"Return"}, {VK_ESCAPE, L"Escape"},   {VK_INSERT, L"Ins"},     {VK_DELETE, L"Del"},
    {VK_PRIOR, L"PgUp"},    {VK_NEXT, L"PgDn"},
};

static UINT KeyFromName(const std::wstring& n) {
    if (n.size() == 1) {
        wchar_t c = (wchar_t)towupper(n[0]);
        if ((c >= L'A' && c <= L'Z') || (c >= L'0' && c <= L'9')) return c;
    }
    if (n.size() >= 2 && (n[0] == L'F' || n[0] == L'f') && iswdigit(n[1])) {
        int f = _wtoi(n.c_str() + 1);
        if (f >= 1 && f <= 24 && std::to_wstring(f) == n.substr(1)) return VK_F1 + f - 1;
        return 0;
    }
    if (n.size() == 7 && !_wcsnicmp(n.c_str(), L"Numpad", 6) && iswdigit(n[6])) return VK_NUMPAD0 + (n[6] - L'0');
    for (const auto& k : kKeyNames)
        if (!_wcsicmp(n.c_str(), k.name)) return k.vk;
    return 0;
}

bool Hotkey_Parse(const std::wstring& text, UINT& mods, UINT& vk) {
    mods = 0;
    vk = 0;
    std::vector<std::wstring> parts;
    size_t start = 0;
    while (true) {
        size_t plus = text.find(L'+', start);
        parts.push_back(Trim(text.substr(start, plus == std::wstring::npos ? std::wstring::npos : plus - start)));
        if (plus == std::wstring::npos) break;
        start = plus + 1;
    }
    for (size_t i = 0; i + 1 < parts.size(); i++) {
        const wchar_t* p = parts[i].c_str();
        if (!_wcsicmp(p, L"Ctrl") || !_wcsicmp(p, L"Control")) mods |= MOD_CONTROL;
        else if (!_wcsicmp(p, L"Alt")) mods |= MOD_ALT;
        else if (!_wcsicmp(p, L"Shift")) mods |= MOD_SHIFT;
        else if (!_wcsicmp(p, L"Win") || !_wcsicmp(p, L"Windows")) mods |= MOD_WIN;
        else return (mods = 0), false;
    }
    vk = parts.back().empty() ? 0 : KeyFromName(parts.back());
    if (!vk) mods = 0;
    return vk != 0;
}

std::wstring Hotkey_Format(UINT mods, UINT vk) {
    std::wstring key;
    if ((vk >= 'A' && vk <= 'Z') || (vk >= '0' && vk <= '9')) key = std::wstring(1, (wchar_t)vk);
    else if (vk >= VK_F1 && vk <= VK_F24) key = L"F" + std::to_wstring(vk - VK_F1 + 1);
    else if (vk >= VK_NUMPAD0 && vk <= VK_NUMPAD9) key = L"Numpad" + std::to_wstring(vk - VK_NUMPAD0);
    else
        for (const auto& k : kKeyNames)
            if (k.vk == vk) {
                key = k.name;
                break;
            }
    if (key.empty()) return {};
    std::wstring out;
    if (mods & MOD_CONTROL) out += L"Ctrl+";
    if (mods & MOD_ALT) out += L"Alt+";
    if (mods & MOD_SHIFT) out += L"Shift+";
    if (mods & MOD_WIN) out += L"Win+";
    return out + key;
}

static bool g_hotkeyMissing = false;
static bool g_hotkeyLogged[3] = {};

// Afterburner may still hold the same keys; a failed one is tried again every 15 seconds.
static void RegisterHotkeys(HWND hwnd, bool quiet) {
    UnregisterHotKey(hwnd, HK_TOGGLE);
    UnregisterHotKey(hwnd, HK_PRESET);
    g_hotkeyMissing = false;
    auto reg = [&](int id, const std::wstring& text, const wchar_t* label) {
        UINT mods = 0, vk = 0;
        if (text.empty() || !Hotkey_Parse(text, mods, vk)) return;
        if (!RegisterHotKey(hwnd, id, mods | MOD_NOREPEAT, vk)) {
            g_hotkeyMissing = true;
            if (!quiet || !g_hotkeyLogged[id]) {
                Wh_Log(L"Shortcut %s (%s) is taken by another app; trying again later.", label, text.c_str());
                g_hotkeyLogged[id] = true;
            }
        } else if (g_hotkeyLogged[id]) {
            Wh_Log(L"Shortcut %s (%s) is ours now.", label, text.c_str());
            g_hotkeyLogged[id] = false;
        }
    };
    reg(HK_TOGGLE, g_set.toggleHotkey, L"show or hide");
    reg(HK_PRESET, g_set.presetHotkey, L"next layout");
    if (g_hotkeyMissing) SetTimer(hwnd, TIMER_HOTKEY_RETRY, 15000, nullptr);
    else KillTimer(hwnd, TIMER_HOTKEY_RETRY);
}

// Open and close motion. The mod's own switch, the switch every DavidHiFi mod follows
// (HKCU\Software\DavidHiFi\Motion, written by Seamless Workshop) and Windows "Animation effects"
// all have to allow it. scale stretches the time: 2 = twice as long.
static bool FoMotion(double* scale) {
    static constexpr double kLevels[] = {1.0, 0.5, 0.75, 1.0, 1.5, 2.0};
    bool globalOn = true;
    double globalScale = 1.0;
    HKEY key = nullptr;
    if (RegOpenKeyExW(HKEY_CURRENT_USER, L"Software\\DavidHiFi\\Motion", 0, KEY_QUERY_VALUE, &key) == ERROR_SUCCESS) {
        DWORD value = 0, type = 0, size = sizeof(value);
        if (RegQueryValueExW(key, L"Enabled", nullptr, &type, (BYTE*)&value, &size) == ERROR_SUCCESS && type == REG_DWORD)
            globalOn = value != 0;
        WCHAR text[32] = {};
        size = sizeof(text) - sizeof(WCHAR);
        if (RegQueryValueExW(key, L"Speed", nullptr, &type, (BYTE*)text, &size) == ERROR_SUCCESS) {
            if (type == REG_DWORD) {
                globalScale = std::clamp((double)*(DWORD*)text, 25.0, 400.0) / 100.0;
            } else if (type == REG_SZ) {
                static const wchar_t* kNames[] = {L"", L"veryQuick", L"quick", L"normal", L"relaxed", L"slow"};
                for (int i = 1; i < 6; i++)
                    if (_wcsicmp(text, kNames[i]) == 0) globalScale = kLevels[i];
            }
        }
        RegCloseKey(key);
    }
    int level = g_set.animationSpeed;
    if (scale) *scale = (level > 0 && level < 6) ? kLevels[level] : globalScale;
    BOOL anim = TRUE;
    if (!SystemParametersInfoW(SPI_GETCLIENTAREAANIMATION, 0, &anim, 0)) anim = TRUE;
    return g_set.flyoutAnimation && globalOn && anim;
}

// ============================================================================
// Frame times from Windows' own event tracing (the way PresentMon does it). Nothing is put
// into the game: Windows reports every present call, and only the app in front is counted.
// ============================================================================

namespace frames {

// {CA11C036-0102-4A2D-A6AD-F03CFED5D3C9}
static const GUID kDxgi = {0xCA11C036, 0x0102, 0x4A2D, {0xA6, 0xAD, 0xF0, 0x3C, 0xFE, 0xD5, 0xD3, 0xC9}};
// {783ACA0A-790E-4D7F-8451-AA850511C6B9}
static const GUID kD3d9 = {0x783ACA0A, 0x790E, 0x4D7F, {0x84, 0x51, 0xAA, 0x85, 0x05, 0x11, 0xC6, 0xB9}};
// {802EC45A-1E99-4B83-9920-87C98277BA9D}
static const GUID kDxgKrnl = {0x802EC45A, 0x1E99, 0x4B83, {0x99, 0x20, 0x87, 0xC9, 0x82, 0x77, 0xBA, 0x9D}};

// The SDK's filter structures, written out so the build doesn't depend on which MinGW has them.
struct FilterDesc {
    ULONGLONG Ptr;
    ULONG Size;
    ULONG Type;
};
struct EnableParams {
    ULONG Version;
    ULONG EnableProperty;
    ULONG ControlFlags;
    GUID SourceId;
    FilterDesc* EnableFilterDesc;
    ULONG FilterDescCount;
};
constexpr ULONG kFilterTypeEventId = 0x80000200;
constexpr ULONG kUseMsFlushTimer = 0x00000010;

enum Source { kSrcNone = 0, kSrcDxgi, kSrcD3d9, kSrcBlit, kSrcFlip, kSrcPresentInfo, kSrcCount };

constexpr size_t kRing = 32768;

struct Tracker {
    SRWLOCK lock = SRWLOCK_INIT;
    std::atomic<DWORD> pid{0};
    int64_t ring[kRing];
    size_t head = 0, count = 0;
    int active = kSrcNone;
    int64_t lastSeen[kSrcCount] = {};
    uint32_t cur[kSrcCount] = {}, prev[kSrcCount] = {};
    int64_t windowStart = 0;
    struct Chain {
        uint64_t ptr;
        uint32_t cur, prev;
    } chains[8] = {};
    uint64_t dominant = 0;
    int64_t freq = 1;
};

static Tracker* g_t = nullptr;
static TRACEHANDLE g_session = 0;
static TRACEHANDLE g_trace = INVALID_PROCESSTRACE_HANDLE;
static HANDLE g_thread = nullptr;
static std::vector<BYTE> g_props;

static void ResetLocked(Tracker& t) {
    t.head = t.count = 0;
    t.active = kSrcNone;
    memset(t.lastSeen, 0, sizeof(t.lastSeen));
    memset(t.cur, 0, sizeof(t.cur));
    memset(t.prev, 0, sizeof(t.prev));
    memset(t.chains, 0, sizeof(t.chains));
    t.windowStart = 0;
    t.dominant = 0;
}

static void SetTarget(DWORD pid) {
    if (!g_t || g_t->pid.load() == pid) return;
    AcquireSRWLockExclusive(&g_t->lock);
    g_t->pid.store(pid);
    ResetLocked(*g_t);
    ReleaseSRWLockExclusive(&g_t->lock);
}

// Which stream the frames come from right now (kSrc...).
static int ActiveSource() { return g_t ? g_t->active : kSrcNone; }

static void Push(Tracker& t, int src, int64_t ts, uint64_t chain) {
    // Once a second: the busiest swap chain and the busiest kernel stream win.
    if (!t.windowStart) t.windowStart = ts;
    if (ts - t.windowStart >= t.freq) {
        for (int i = 0; i < kSrcCount; i++) {
            t.prev[i] = t.cur[i];
            t.cur[i] = 0;
        }
        uint32_t best = 0;
        t.dominant = 0;
        for (auto& c : t.chains) {
            c.prev = c.cur;
            c.cur = 0;
            if (c.ptr && c.prev > best) {
                best = c.prev;
                t.dominant = c.ptr;
            }
            if (c.ptr && !c.prev) c.ptr = 0;  // Gone quiet: frees the slot.
        }
        t.windowStart = ts;
    }
    t.cur[src]++;
    t.lastSeen[src] = ts;
    if (chain && (src == kSrcDxgi || src == kSrcD3d9)) {
        Tracker::Chain* slot = nullptr;
        for (auto& c : t.chains)
            if (c.ptr == chain) slot = &c;
        if (!slot)
            for (auto& c : t.chains)
                if (!c.ptr) {
                    slot = &c;
                    slot->ptr = chain;
                    slot->cur = slot->prev = 0;
                    break;
                }
        if (slot) slot->cur++;
    }

    // The app's own present calls win; the kernel streams are for apps that skip DXGI and D3D9
    // (OpenGL, Vulkan).
    int pick;
    if (t.lastSeen[kSrcDxgi] && ts - t.lastSeen[kSrcDxgi] < t.freq) pick = kSrcDxgi;
    else if (t.lastSeen[kSrcD3d9] && ts - t.lastSeen[kSrcD3d9] < t.freq) pick = kSrcD3d9;
    else {
        pick = kSrcFlip;
        uint32_t best = 0;
        for (int s : {kSrcFlip, kSrcPresentInfo, kSrcBlit}) {
            uint32_t n = std::max(t.prev[s], t.cur[s]);
            if (n > best) best = n, pick = s;
        }
    }
    if (src != pick) return;
    if (pick == kSrcDxgi || pick == kSrcD3d9) {
        if (t.dominant && chain && chain != t.dominant) return;
    }
    if (t.active != pick) {
        t.active = pick;
        t.head = t.count = 0;
    }
    t.ring[t.head] = ts;
    t.head = (t.head + 1) % kRing;
    if (t.count < kRing) t.count++;
}

static VOID WINAPI OnEvent(PEVENT_RECORD r) {
    Tracker* t = g_t;
    if (!t || !r) return;
    DWORD pid = t->pid.load(std::memory_order_relaxed);
    if (!pid || r->EventHeader.ProcessId != pid) return;
    const GUID& p = r->EventHeader.ProviderId;
    USHORT id = r->EventHeader.EventDescriptor.Id;
    int src = kSrcNone;
    if (IsEqualGUID(p, kDxgi)) {
        if (id == 42) src = kSrcDxgi;
    } else if (IsEqualGUID(p, kD3d9)) {
        if (id == 1) src = kSrcD3d9;
    } else if (IsEqualGUID(p, kDxgKrnl)) {
        if (id == 166) src = kSrcBlit;
        else if (id == 168) src = kSrcFlip;
        else if (id == 184 || id == 252) src = kSrcPresentInfo;
    }
    if (src == kSrcNone) return;
    uint64_t chain = 0;
    if ((src == kSrcDxgi || src == kSrcD3d9) && r->UserData) {
        bool p32 = (r->EventHeader.Flags & EVENT_HEADER_FLAG_32_BIT_HEADER) != 0;
        if (p32 && r->UserDataLength >= 4) chain = *(const uint32_t*)r->UserData;
        else if (!p32 && r->UserDataLength >= 8) chain = *(const uint64_t*)r->UserData;
    }
    AcquireSRWLockExclusive(&t->lock);
    if (t->pid.load(std::memory_order_relaxed) == pid) Push(*t, src, r->EventHeader.TimeStamp.QuadPart, chain);
    ReleaseSRWLockExclusive(&t->lock);
}

static DWORD WINAPI TraceThread(LPVOID) {
    TRACEHANDLE h = g_trace;
    ULONG rc = ProcessTrace(&h, 1, nullptr, nullptr);
    if (rc != ERROR_SUCCESS && rc != ERROR_CANCELLED) Wh_Log(L"Frame tracing stopped: %lu", rc);
    return 0;
}

static EVENT_TRACE_PROPERTIES* Props() {
    const size_t size = sizeof(EVENT_TRACE_PROPERTIES) + sizeof(kSessionName) + 16;
    g_props.assign(size, 0);
    auto* p = (EVENT_TRACE_PROPERTIES*)g_props.data();
    p->Wnode.BufferSize = (ULONG)size;
    p->Wnode.Flags = WNODE_FLAG_TRACED_GUID;
    p->Wnode.ClientContext = 1;  // QPC time stamps
    p->LoggerNameOffset = sizeof(EVENT_TRACE_PROPERTIES);
    return p;
}

static void StopStale() {
    auto* p = Props();
    ControlTraceW(0, kSessionName, p, EVENT_TRACE_CONTROL_STOP);
}

static void EnableProvider(const GUID& guid, UCHAR level, ULONGLONG any, std::initializer_list<USHORT> ids) {
    // EVENT_FILTER_EVENT_ID: FilterIn, Reserved, Count, then the ids.
    std::vector<BYTE> filter(4 + ids.size() * sizeof(USHORT), 0);
    filter[0] = 1;
    *(USHORT*)&filter[2] = (USHORT)ids.size();
    size_t i = 0;
    for (USHORT id : ids) ((USHORT*)&filter[4])[i++] = id;
    FilterDesc desc{(ULONGLONG)(ULONG_PTR)filter.data(), (ULONG)filter.size(), kFilterTypeEventId};
    EnableParams params{};
    params.Version = 2;
    params.EnableFilterDesc = &desc;
    params.FilterDescCount = 1;
    ULONG rc = EnableTraceEx2(g_session, &guid, EVENT_CONTROL_CODE_ENABLE_PROVIDER, level, any, 0, 0,
                              (PENABLE_TRACE_PARAMETERS)&params);
    if (rc != ERROR_SUCCESS) {
        // Older builds without event id filters: take the provider whole.
        rc = EnableTraceEx2(g_session, &guid, EVENT_CONTROL_CODE_ENABLE_PROVIDER, level, any, 0, 0, nullptr);
        if (rc != ERROR_SUCCESS) Wh_Log(L"Couldn't follow a frame source: %lu", rc);
    }
}

static bool Running() { return g_thread != nullptr; }

static bool Start() {
    if (g_thread) return true;
    if (!g_t) {
        g_t = new (std::nothrow) Tracker();
        if (!g_t) return false;
        LARGE_INTEGER f;
        QueryPerformanceFrequency(&f);
        g_t->freq = f.QuadPart ? f.QuadPart : 1;
    }
    StopStale();  // A session left by a crashed run.
    auto* p = Props();
    p->BufferSize = 64;  // KB
    p->MinimumBuffers = 4;
    p->MaximumBuffers = 16;
    p->LogFileMode = EVENT_TRACE_REAL_TIME_MODE | kUseMsFlushTimer;
    p->FlushTimer = 200;  // ms
    ULONG rc = StartTraceW(&g_session, kSessionName, p);
    if (rc == ERROR_ALREADY_EXISTS) {
        StopStale();
        p = Props();
        p->BufferSize = 64;
        p->MinimumBuffers = 4;
        p->MaximumBuffers = 16;
        p->LogFileMode = EVENT_TRACE_REAL_TIME_MODE | kUseMsFlushTimer;
        p->FlushTimer = 200;
        rc = StartTraceW(&g_session, kSessionName, p);
    }
    if (rc != ERROR_SUCCESS) {
        Wh_Log(L"Couldn't start frame tracing: %lu", rc);
        g_session = 0;
        return false;
    }
    EnableProvider(kDxgi, TRACE_LEVEL_VERBOSE, 0x8000000000000002ull, {42});
    EnableProvider(kD3d9, TRACE_LEVEL_VERBOSE, 0x8000000000000002ull, {1});
    EnableProvider(kDxgKrnl, TRACE_LEVEL_VERBOSE, 0x8000000ull, {166, 168, 184, 252});

    EVENT_TRACE_LOGFILEW log{};
    log.LoggerName = (LPWSTR)kSessionName;
    log.ProcessTraceMode = PROCESS_TRACE_MODE_REAL_TIME | PROCESS_TRACE_MODE_EVENT_RECORD | PROCESS_TRACE_MODE_RAW_TIMESTAMP;
    log.EventRecordCallback = OnEvent;
    g_trace = OpenTraceW(&log);
    if (g_trace == INVALID_PROCESSTRACE_HANDLE) {
        Wh_Log(L"Couldn't read frame tracing: %lu", GetLastError());
        ControlTraceW(g_session, nullptr, Props(), EVENT_TRACE_CONTROL_STOP);
        g_session = 0;
        return false;
    }
    g_thread = CreateThread(nullptr, 0, TraceThread, nullptr, 0, nullptr);
    if (!g_thread) {
        CloseTrace(g_trace);
        g_trace = INVALID_PROCESSTRACE_HANDLE;
        ControlTraceW(g_session, nullptr, Props(), EVENT_TRACE_CONTROL_STOP);
        g_session = 0;
        return false;
    }
    Wh_Log(L"Frame tracing on.");
    return true;
}

static void Stop() {
    if (g_session) {
        ControlTraceW(g_session, nullptr, Props(), EVENT_TRACE_CONTROL_STOP);
        g_session = 0;
    }
    if (g_trace != INVALID_PROCESSTRACE_HANDLE) {
        CloseTrace(g_trace);
        g_trace = INVALID_PROCESSTRACE_HANDLE;
    }
    if (g_thread) {
        WaitForSingleObject(g_thread, 3000);
        CloseHandle(g_thread);
        g_thread = nullptr;
        Wh_Log(L"Frame tracing off.");
    }
    if (g_t) {
        AcquireSRWLockExclusive(&g_t->lock);
        ResetLocked(*g_t);
        ReleaseSRWLockExclusive(&g_t->lock);
    }
}

static void Free() {
    Stop();
    delete g_t;
    g_t = nullptr;
}

struct Stats {
    bool live = false;        // presents in the last two seconds
    bool gameLike = false;    // a steady stream for the last 1.5 seconds
    bool recent3s = false;    // anything in the last three seconds
    double fps = NAN, frameMs = NAN, low1 = NAN, low01 = NAN, avg = NAN;
    double jitter = NAN;       // how much one frame differs from the next, on average, ms
    std::vector<float> graph;  // the last few seconds of frame times, ms (spikes kept)
};

static double QpcNow() {
    LARGE_INTEGER c;
    QueryPerformanceCounter(&c);
    return (double)c.QuadPart;
}

static Stats Compute(int periodMs, int graphSeconds = 3) {
    Stats st;
    if (!g_t) return st;
    std::vector<int64_t> ts;
    const double freq = (double)g_t->freq;
    AcquireSRWLockShared(&g_t->lock);
    size_t n = g_t->count;
    if (n) {
        int64_t newest = g_t->ring[(g_t->head + kRing - 1) % kRing];
        int64_t floor = newest - (int64_t)(20.0 * freq);
        ts.reserve(std::min<size_t>(n, 24000));
        for (size_t i = 0; i < n; i++) {
            int64_t v = g_t->ring[(g_t->head + kRing - n + i) % kRing];
            if (v >= floor) ts.push_back(v);
        }
    }
    ReleaseSRWLockShared(&g_t->lock);
    if (ts.size() < 2) {
        if (!ts.empty()) st.recent3s = (QpcNow() - (double)ts.back()) / freq < 3.0;
        return st;
    }
    const double now = QpcNow();
    const double age = (now - (double)ts.back()) / freq;
    st.recent3s = age < 3.0;
    st.live = age < 2.0;
    if (!st.live) return st;

    std::vector<double> d;
    d.reserve(ts.size());
    for (size_t i = 1; i < ts.size(); i++) {
        double ms = (double)(ts[i] - ts[i - 1]) * 1000.0 / freq;
        if (ms > 0 && ms < 1000.0) d.push_back(ms);
    }
    if (d.empty()) return st;

    // Steady stream: the last 1.5 seconds covered with no gap over 300 ms.
    {
        const int64_t span = (int64_t)(1.5 * freq);
        const int64_t from = ts.back() - span;
        bool covered = ts.front() <= from;
        double maxGap = 0;
        int count = 0;
        for (size_t i = ts.size() - 1; i > 0 && ts[i] >= from; i--) {
            maxGap = std::max(maxGap, (double)(ts[i] - ts[i - 1]) / freq);
            count++;
        }
        st.gameLike = covered && count >= 12 && maxGap <= 0.3 && age < 0.8;
    }

    // FPS from the mean frame time of the last second.
    {
        const int64_t from = ts.back() - (int64_t)freq;
        size_t i = ts.size() - 1;
        while (i > 0 && ts[i - 1] >= from) i--;
        size_t frames = ts.size() - 1 - i;
        if (frames >= 1) st.fps = frames * freq / (double)(ts.back() - ts[i]);
    }
    // Frame time: the mean over the last update period.
    {
        const int64_t from = ts.back() - (int64_t)(periodMs / 1000.0 * freq);
        size_t i = ts.size() - 1;
        while (i > 0 && ts[i - 1] >= from) i--;
        size_t frames = ts.size() - 1 - i;
        st.frameMs = frames >= 1 ? (double)(ts.back() - ts[i]) * 1000.0 / freq / frames : d.back();
    }
    double sum = 0;
    for (double v : d) sum += v;
    st.avg = 1000.0 / (sum / d.size());
    std::vector<double> sorted = d;
    auto pct = [&](double q) {
        size_t k = std::min(sorted.size() - 1, (size_t)std::floor(q * (sorted.size() - 1) + 0.5));
        std::nth_element(sorted.begin(), sorted.begin() + k, sorted.end());
        return sorted[k];
    };
    if (d.size() >= 20) {
        st.low1 = 1000.0 / pct(0.99);
        st.low01 = 1000.0 / pct(0.999);
    }
    // Jitter: the mean change from one frame to the next over the last second.
    {
        const int64_t from = ts.back() - (int64_t)freq;
        double acc = 0;
        int k = 0;
        for (size_t i = 2; i < ts.size(); i++) {
            if (ts[i - 2] < from) continue;
            double a = (double)(ts[i] - ts[i - 1]) * 1000.0 / freq, b = (double)(ts[i - 1] - ts[i - 2]) * 1000.0 / freq;
            acc += std::fabs(a - b);
            k++;
        }
        if (k >= 3) st.jitter = acc / k;
    }
    const int64_t graphFrom = ts.back() - (int64_t)(std::clamp(graphSeconds, 1, 20) * freq);
    std::vector<float> g;
    for (size_t i = 1; i < ts.size(); i++) {
        if (ts[i] < graphFrom) continue;
        double ms = (double)(ts[i] - ts[i - 1]) * 1000.0 / freq;
        g.push_back((float)std::min(ms, 250.0));
    }
    // At most 400 points: each keeps the slowest frame of its slice so a spike never vanishes.
    constexpr size_t kMaxPts = 400;
    if (g.size() > kMaxPts) {
        st.graph.resize(kMaxPts);
        for (size_t b = 0; b < kMaxPts; b++) {
            size_t a0 = b * g.size() / kMaxPts, a1 = std::max(a0 + 1, (b + 1) * g.size() / kMaxPts);
            float m = 0;
            for (size_t i = a0; i < a1 && i < g.size(); i++) m = std::max(m, g[i]);
            st.graph[b] = m;
        }
    } else {
        st.graph = std::move(g);
    }
    return st;
}

}  // namespace frames

// ============================================================================
// Glass behind the overlay: Windows' own blur, in a click-through window just under it.
// The same recipe as Seamless Crosshair's pop-up.
// ============================================================================

struct SfoCompositorDesktopInterop : ::IUnknown {
    virtual HRESULT __stdcall CreateDesktopWindowTarget(HWND window, BOOL isTopmost, void** target) = 0;
    virtual HRESULT __stdcall EnsureOnThread(DWORD threadId) = 0;
};
template <>
inline constexpr winrt::guid winrt::impl::guid_v<SfoCompositorDesktopInterop>{
    0x29E691FA, 0x4567, 0x4DCA, {0xB3, 0x19, 0xD0, 0xF2, 0x07, 0xEB, 0x68, 0x07}};

struct SfoEffectD2D1Interop : ::IUnknown {
    virtual HRESULT __stdcall GetEffectId(GUID* id) = 0;
    virtual HRESULT __stdcall GetNamedPropertyMapping(LPCWSTR name, UINT* index, int* mapping) = 0;
    virtual HRESULT __stdcall GetPropertyCount(UINT* count) = 0;
    virtual HRESULT __stdcall GetProperty(UINT index, void** value) = 0;
    virtual HRESULT __stdcall GetSource(UINT index, void** source) = 0;
    virtual HRESULT __stdcall GetSourceCount(UINT* count) = 0;
};
template <>
inline constexpr winrt::guid winrt::impl::guid_v<SfoEffectD2D1Interop>{
    0x2FC57384, 0xA068, 0x44D7, {0xA3, 0x31, 0x30, 0x98, 0x2F, 0xCF, 0x71, 0x77}};

struct SfoGlassBlur : winrt::implements<SfoGlassBlur, winrt::Windows::Graphics::Effects::IGraphicsEffect,
                                        winrt::Windows::Graphics::Effects::IGraphicsEffectSource,
                                        SfoEffectD2D1Interop> {
    SfoGlassBlur(float sigma, winrt::Windows::Graphics::Effects::IGraphicsEffectSource source)
        : m_sigma(sigma), m_source(std::move(source)) {}
    winrt::hstring Name() { return m_name; }
    void Name(winrt::hstring const& name) { m_name = name; }
    HRESULT __stdcall GetEffectId(GUID* id) override {
        *id = {0x1FEB6D69, 0x2FE6, 0x4AC9, {0x8C, 0x58, 0x1D, 0x7F, 0x93, 0xE7, 0xA6, 0xA5}};  // Gaussian blur
        return S_OK;
    }
    HRESULT __stdcall GetNamedPropertyMapping(LPCWSTR, UINT*, int*) override { return E_INVALIDARG; }
    HRESULT __stdcall GetPropertyCount(UINT* count) override {
        *count = 3;
        return S_OK;
    }
    HRESULT __stdcall GetProperty(UINT index, void** value) override {
        using winrt::Windows::Foundation::PropertyValue;
        winrt::Windows::Foundation::IInspectable v;
        switch (index) {
            case 0: v = PropertyValue::CreateSingle(m_sigma); break;
            case 1: v = PropertyValue::CreateUInt32(1 /* BALANCED */); break;
            case 2: v = PropertyValue::CreateUInt32(1 /* BORDER_MODE_HARD */); break;
            default: return E_INVALIDARG;
        }
        *value = winrt::detach_abi(v.as<winrt::Windows::Foundation::IPropertyValue>());
        return S_OK;
    }
    HRESULT __stdcall GetSource(UINT index, void** source) override {
        if (index != 0) return E_INVALIDARG;
        winrt::Windows::Graphics::Effects::IGraphicsEffectSource copy = m_source;
        *source = winrt::detach_abi(copy);
        return S_OK;
    }
    HRESULT __stdcall GetSourceCount(UINT* count) override {
        *count = 1;
        return S_OK;
    }

   private:
    winrt::hstring m_name = L"GlassBlur";
    float m_sigma;
    winrt::Windows::Graphics::Effects::IGraphicsEffectSource m_source;
};

namespace sfoglass {

static bool GlassAvailable() {
    DWORD transparency = 1, size = sizeof(transparency);
    RegGetValueW(HKEY_CURRENT_USER, L"Software\\Microsoft\\Windows\\CurrentVersion\\Themes\\Personalize",
                 L"EnableTransparency", RRF_RT_REG_DWORD, nullptr, &transparency, &size);
    SYSTEM_POWER_STATUS power{};
    const bool saver = GetSystemPowerStatus(&power) && power.SystemStatusFlag == 1;
    return transparency != 0 && !saver;
}

static LRESULT CALLBACK GlassWndProc(HWND hwnd, UINT msg, WPARAM wp, LPARAM lp) {
    if (msg == WM_NCHITTEST) return HTTRANSPARENT;
    return DefWindowProcW(hwnd, msg, wp, lp);
}

class Glass {
   public:
    // `cards` are the panels in window pixels; empty means one panel over the whole window.
    bool Show(HWND owner, int x, int y, int w, int h, const std::vector<D2D1_RECT_F>& cards, float radius,
              float opacity) {
        namespace Composition = winrt::Windows::UI::Composition;
        if (m_failed) return false;
        try {
            if (!Ensure()) {
                m_failed = true;
                return false;
            }
            if (!m_visible || x != m_x || y != m_y || w != m_w || h != m_h || GetWindow(owner, GW_HWNDNEXT) != m_hwnd) {
                SetWindowPos(m_hwnd, owner, x, y, w, h, SWP_NOACTIVATE | SWP_SHOWWINDOW);
                m_x = x, m_y = y, m_w = w, m_h = h;
            }
            std::vector<D2D1_RECT_F> rects = cards;
            if (rects.empty()) rects.push_back(D2D1::RectF(0, 0, (float)w, (float)h));
            while (m_cards.size() < rects.size()) {
                Composition::SpriteVisual v = m_compositor.CreateSpriteVisual();
                v.Brush(m_brush);
                Composition::CompositionRoundedRectangleGeometry shape = m_compositor.CreateRoundedRectangleGeometry();
                v.Clip(m_compositor.CreateGeometricClip(shape));
                m_root.Children().InsertAtTop(v);
                m_cards.push_back(v);
                m_shapes.push_back(shape);
            }
            for (size_t i = 0; i < m_cards.size(); i++) {
                if (i >= rects.size()) {
                    m_cards[i].IsVisible(false);
                    continue;
                }
                const D2D1_RECT_F& r = rects[i];
                const winrt::Windows::Foundation::Numerics::float2 extent{std::max(1.f, r.right - r.left),
                                                                          std::max(1.f, r.bottom - r.top)};
                m_cards[i].Offset({r.left, r.top, 0});
                m_cards[i].Size(extent);
                m_shapes[i].Size(extent);
                const float rr = std::clamp(radius, 0.0f, std::min(extent.x, extent.y) / 2);
                m_shapes[i].CornerRadius({rr, rr});
                m_cards[i].Opacity(std::clamp(opacity, 0.0f, 1.0f));
                m_cards[i].IsVisible(true);
            }
            m_visible = true;
            return true;
        } catch (winrt::hresult_error const& e) {
            Wh_Log(L"Overlay glass unavailable: %08X", (unsigned)e.code());
            m_failed = true;
            Hide();
            return false;
        }
    }
    void Hide() {
        if (m_hwnd && m_visible) ShowWindow(m_hwnd, SW_HIDE);
        m_visible = false;
    }
    bool Failed() const { return m_failed; }
    HWND Hwnd() const { return m_hwnd; }
    // On the UI thread, before it ends.
    void Destroy() {
        m_cards.clear();
        m_shapes.clear();
        m_brush = nullptr;
        m_root = nullptr;
        m_target = nullptr;
        if (m_hwnd) DestroyWindow(m_hwnd);
        m_hwnd = nullptr;
        m_visible = false;
        m_compositor = nullptr;
        if (m_queue) {
            auto queue = std::move(m_queue);
            try {
                const auto shutdown = queue.ShutdownQueueAsync();
                for (int i = 0; i < 100 && shutdown.Status() == winrt::Windows::Foundation::AsyncStatus::Started; i++) {
                    MsgWaitForMultipleObjects(0, nullptr, FALSE, 10, QS_ALLINPUT);
                    MSG msg;
                    while (PeekMessageW(&msg, nullptr, 0, 0, PM_REMOVE)) DispatchMessageW(&msg);
                }
            } catch (winrt::hresult_error const& e) {
                Wh_Log(L"Ending the overlay glass queue failed: %08X", (unsigned)e.code());
            }
        }
        if (m_registered) UnregisterClassW(kGlassClass, (HINSTANCE)windhawk_tool_mod::GetCurrentModuleHandle());
        m_registered = false;
        m_failed = false;
    }

   private:
    bool Ensure() {
        namespace Composition = winrt::Windows::UI::Composition;
        if (m_root) return true;
        if (!m_queue) {
            using CreateController_t = HRESULT(WINAPI*)(DispatcherQueueOptions, void**);
            static const HMODULE messaging = LoadLibraryExW(L"CoreMessaging.dll", nullptr, LOAD_LIBRARY_SEARCH_SYSTEM32);
            const auto create =
                messaging ? (CreateController_t)(void*)GetProcAddress(messaging, "CreateDispatcherQueueController")
                          : nullptr;
            if (!create) return false;
            const DispatcherQueueOptions options{sizeof(options), DQTYPE_THREAD_CURRENT, DQTAT_COM_STA};
            winrt::check_hresult(create(options, winrt::put_abi(m_queue)));
        }
        if (!m_compositor) m_compositor = Composition::Compositor();
        const HINSTANCE inst = (HINSTANCE)windhawk_tool_mod::GetCurrentModuleHandle();
        if (!m_registered) {
            WNDCLASSW wc{};
            wc.lpfnWndProc = GlassWndProc;
            wc.hInstance = inst;
            wc.lpszClassName = kGlassClass;
            m_registered = RegisterClassW(&wc) != 0;
        }
        m_hwnd = CreateWindowExW(WS_EX_NOREDIRECTIONBITMAP | WS_EX_LAYERED | WS_EX_TRANSPARENT | WS_EX_TOPMOST |
                                     WS_EX_TOOLWINDOW | WS_EX_NOACTIVATE,
                                 kGlassClass, L"", WS_POPUP, 0, 0, 0, 0, nullptr, nullptr, inst, nullptr);
        if (!m_hwnd) return false;
        SetLayeredWindowAttributes(m_hwnd, 0, 255, LWA_ALPHA);
        const BOOL hostBackdrop = TRUE;  // DWMWA_USE_HOSTBACKDROPBRUSH
        winrt::check_hresult(DwmSetWindowAttribute(m_hwnd, 17, &hostBackdrop, sizeof(hostBackdrop)));
        auto interop = m_compositor.as<SfoCompositorDesktopInterop>();
        winrt::check_hresult(interop->CreateDesktopWindowTarget(m_hwnd, TRUE, winrt::put_abi(m_target)));
        Composition::ContainerVisual root = m_compositor.CreateContainerVisual();
        root.RelativeSizeAdjustment({1, 1});
        m_target.Root(root);
        try {
            const auto effect =
                winrt::make<SfoGlassBlur>(18.0f, Composition::CompositionEffectSourceParameter(L"Backdrop"));
            const auto brush = m_compositor.CreateEffectFactory(effect).CreateBrush();
            brush.SetSourceParameter(L"Backdrop", m_compositor.CreateHostBackdropBrush());
            m_brush = brush;
        } catch (winrt::hresult_error const& e) {
            Wh_Log(L"Extra overlay blur unavailable: %08X", (unsigned)e.code());
            m_brush = m_compositor.CreateHostBackdropBrush();
        }
        m_root = root;
        return true;
    }

    HWND m_hwnd = nullptr;
    bool m_failed = false, m_visible = false, m_registered = false;
    int m_x = 0, m_y = 0, m_w = 0, m_h = 0;
    winrt::Windows::System::DispatcherQueueController m_queue{nullptr};
    winrt::Windows::UI::Composition::Compositor m_compositor{nullptr};
    winrt::Windows::UI::Composition::Desktop::DesktopWindowTarget m_target{nullptr};
    winrt::Windows::UI::Composition::ContainerVisual m_root{nullptr};
    winrt::Windows::UI::Composition::CompositionBrush m_brush{nullptr};
    std::vector<winrt::Windows::UI::Composition::SpriteVisual> m_cards;
    std::vector<winrt::Windows::UI::Composition::CompositionRoundedRectangleGeometry> m_shapes;
};

}  // namespace sfoglass

// ============================================================================
// The overlay
// ============================================================================

static HWND g_ctrl = nullptr;      // hidden window: tray, shortcuts, timers
static HWND g_overlay = nullptr;   // the layered, click-through overlay
static sfoglass::Glass g_glass;
static HANDLE g_uiThread = nullptr, g_uiReady = nullptr;
static DWORD g_uiThreadId = 0;
static HWINEVENTHOOK g_fgHook = nullptr;
static UINT g_wmTaskbarCreated = 0;
static NOTIFYICONDATAW g_nid{};
static bool g_trayAdded = false;

static bool g_enabled = false;     // the shortcut's state: off means no tracing and no drawing
static bool g_wantVisible = false; // the rules say show it now
static DWORD g_targetPid = 0;
static DWORD g_pinnedPid = 0;  // WM_APP_PIN_TARGET
static std::wstring g_targetExe;
static bool g_targetSkip = false;
static ULONGLONG g_lastGameTick = 0;  // the last tick the target drew like a game
static ULONGLONG g_gameSince = 0;     // start of the current unbroken game-like run
static bool g_isGame = false;         // the target has passed the game test
static bool g_sensorsStarted = false;

// Drawing
static ID2D1Factory* g_d2d = nullptr;
static IDWriteFactory* g_dw = nullptr;
static ID2D1DCRenderTarget* g_rt = nullptr;
static HDC g_memDc = nullptr;
static HBITMAP g_dib = nullptr;
static HGDIOBJ g_oldBmp = nullptr;
static int g_dibW = 0, g_dibH = 0;
static std::wstring g_lastSig;
static int g_w = 0, g_h = 0;         // overlay size in pixels
static POINT g_pos{};                // resting top-left
static RECT g_monitorRc{};

// Animation
static bool g_shown = false;        // on screen (or animating in)
static bool g_animating = false;
static bool g_animIn = true;
static double g_animFrom = 0, g_animT = 0, g_animDurMs = 0;
static double g_animStartQpc = 0, g_qpcFreq = 1;
static double g_alpha = 0;           // 0..1

enum Font { kFontLabel = 0, kFontValue, kFontUnit, kFontBig, kFontName, kFontTiny, kFontSmall, kFontHuge, kFontCount };
static IDWriteTextFormat* g_fmt[kFontCount] = {};
static float g_lineH[kFontCount] = {};
static std::wstring g_fmtKey;

template <class T>
static void SafeRelease(T*& p) {
    if (p) {
        p->Release();
        p = nullptr;
    }
}

static float MonitorScale(HMONITOR mon) {
    using GetDpiForMonitor_t = HRESULT(WINAPI*)(HMONITOR, int, UINT*, UINT*);
    static GetDpiForMonitor_t fn = []() -> GetDpiForMonitor_t {
        HMODULE shcore = LoadLibraryExW(L"shcore.dll", nullptr, LOAD_LIBRARY_SEARCH_SYSTEM32);
        return shcore ? (GetDpiForMonitor_t)(void*)GetProcAddress(shcore, "GetDpiForMonitor") : nullptr;
    }();
    UINT x = 96, y = 96;
    if (fn && mon && SUCCEEDED(fn(mon, 0, &x, &y)) && x) return x / 96.0f;
    return 1.0f;
}

static std::wstring PickFontFamily(const std::wstring& want) {
    IDWriteFontCollection* fonts = nullptr;
    std::wstring pick = L"Segoe UI";
    if (g_dw && SUCCEEDED(g_dw->GetSystemFontCollection(&fonts, TRUE)) && fonts) {
        for (const std::wstring& name : {want, std::wstring(L"Segoe UI Variable Display"), std::wstring(L"Segoe UI")}) {
            UINT32 idx = 0;
            BOOL exists = FALSE;
            if (!name.empty() && SUCCEEDED(fonts->FindFamilyName(name.c_str(), &idx, &exists)) && exists) {
                pick = name;
                break;
            }
        }
        fonts->Release();
    }
    return pick;
}

static void EnsureFormats(float px) {
    wchar_t key[160];
    swprintf_s(key, L"%s|%d|%.2f|%d", g_set.fontFace.c_str(), g_set.fontWeight, px, g_set.textSize);
    if (g_fmtKey == key && g_fmt[0]) return;
    for (auto& f : g_fmt) SafeRelease(f);
    g_fmtKey = key;
    if (!g_dw) return;
    std::wstring family = PickFontFamily(g_set.fontFace);
    const DWRITE_FONT_WEIGHT weight = (DWRITE_FONT_WEIGHT)std::clamp(g_set.fontWeight, 100, 900);
    const float ts = std::clamp(g_set.textSize, 60, 200) / 100.0f;
    float sizes[kFontCount] = {12.5f, 15.0f, 11.0f, 34.0f, 12.5f, 8.5f, 10.5f, 46.0f};
    for (float& f : sizes) f *= ts;
    for (int i = 0; i < kFontCount; i++) {
        DWRITE_FONT_WEIGHT w = (i == kFontUnit || i == kFontTiny) ? (DWRITE_FONT_WEIGHT)std::max(400, (int)weight - 200) : weight;
        g_dw->CreateTextFormat(family.c_str(), nullptr, w, DWRITE_FONT_STYLE_NORMAL, DWRITE_FONT_STRETCH_NORMAL,
                               sizes[i] * px, L"en-us", &g_fmt[i]);
        if (g_fmt[i]) {
            g_fmt[i]->SetWordWrapping(DWRITE_WORD_WRAPPING_NO_WRAP);
            IDWriteTextLayout* layout = nullptr;
            g_lineH[i] = sizes[i] * px * 1.25f;
            if (SUCCEEDED(g_dw->CreateTextLayout(L"0Ag", 3, g_fmt[i], 1000, 1000, &layout)) && layout) {
                DWRITE_TEXT_METRICS m{};
                if (SUCCEEDED(layout->GetMetrics(&m))) g_lineH[i] = m.height;
                layout->Release();
            }
        }
    }
}

static float TextW(int font, const std::wstring& s) {
    if (s.empty() || !g_fmt[font]) return 0;
    IDWriteTextLayout* layout = nullptr;
    float w = 0;
    if (SUCCEEDED(g_dw->CreateTextLayout(s.c_str(), (UINT32)s.size(), g_fmt[font], 4000, 1000, &layout)) && layout) {
        DWRITE_TEXT_METRICS m{};
        if (SUCCEEDED(layout->GetMetrics(&m))) w = m.widthIncludingTrailingWhitespace;
        layout->Release();
    }
    return w;
}

// ---- Values -----------------------------------------------------------------

struct Readings {
    frames::Stats f;
    seamless_sensors::Snapshot s{};
    bool sensorsOk = false;
};

static const std::wstring kDash = L"\u2013";

static std::wstring Num(double v, int decimals = 0) {
    if (!seamless_sensors::IsValid(v) || v < 0) return kDash;
    wchar_t b[32];
    swprintf_s(b, decimals ? L"%.1f" : L"%.0f", v);
    return b;
}

static double SensorVal(const Readings& r, double v) { return r.sensorsOk ? v : NAN; }

// ---- Layout -----------------------------------------------------------------

enum BrushKind { kBrushLabel = 0, kBrushValue, kBrushDim };

// What an op draws. Everything but text and the graph is our own vector art.
enum Shape { kShText = 0, kShGraph, kShRing, kShBolt, kShGauge, kShFan, kShThermo, kShDie, kShBar, kShChips,
             kShGpuArt, kShCpuArt, kShBinary, kShCores, kShRamStick, kShWave, kShLine };

struct Op {
    bool graph = false;  // the frame time graph (same as shape == kShGraph)
    int shape = kShText;
    int font = kFontLabel, brush = kBrushLabel;
    float x = 0, y = 0, w = 0, h = 0;
    std::wstring text;
    float v = 0, v2 = 0;          // the reading as 0..1 (and a second one some shapes use)
    int id = -1;                  // slot for smooth dial movement, -1 = jump straight there
    bool warn = false, pulse = false;
    int blk = -1;                 // the Benchmark block it belongs to, -1 = none
    std::vector<float> series;    // graph, wave and core bar values
};

// Where a Benchmark block sits: its corner, its size factor and its colour.
struct Place {
    float x = 0, y = 0, k = 1, w = 0, h = 0;
    int colour = kPalSame;
};

struct Layout {
    std::vector<Op> ops;
    float w = 0, h = 0;
    std::vector<float> graph;
    Place places[kBlkCount];
    std::vector<D2D1_RECT_F> cards;  // one panel per block; empty = one panel for everything
    std::vector<D2D1_RECT_F> dividers;  // thin lines between sections inside the one panel (x1,y1,x2,y2)
    bool animated = false;           // has moving parts
    double fanRate = 0;              // fan turns per second, 0 = still
};

struct Item {
    std::wstring label, value, unit;
};

static void AddText(Layout& L, int font, int brush, float x, float y, const std::wstring& s) {
    if (s.empty()) return;
    Op o;
    o.font = font;
    o.brush = brush;
    o.x = x;
    o.y = y;
    o.text = s;
    o.w = TextW(font, s);
    o.h = g_lineH[font];
    L.ops.push_back(std::move(o));
}

static std::vector<Item> FrameItems(const Readings& r, bool withFps) {
    std::vector<Item> v;
    const auto& f = r.f;
    if (withFps && g_set.fps) v.push_back({L"FPS", Num(f.fps), L""});
    if (g_set.frameTime) v.push_back({L"Frame", Num(f.frameMs, 1), L"ms"});
    if (g_set.low1) v.push_back({L"1%", Num(f.low1), L""});
    if (g_set.low01) v.push_back({L"0.1%", Num(f.low01), L""});
    if (g_set.avgFps) v.push_back({L"AVG", Num(f.avg), L""});
    return v;
}

static std::wstring VramPct(const Readings& r) {
    double used = SensorVal(r, r.s.gpuVramUsedMB), total = SensorVal(r, r.s.gpuVramTotalMB);
    if (!seamless_sensors::IsValid(used) || !seamless_sensors::IsValid(total) || total <= 0) return kDash;
    return Num(used / total * 100.0);
}

static std::vector<Item> GpuItems(const Readings& r, bool shortNames) {
    std::vector<Item> v;
    const auto& s = r.s;
    if (g_set.gpuUsage) v.push_back({shortNames ? L"GPU" : L"Load", Num(SensorVal(r, s.gpuUsage)), L"%"});
    if (g_set.gpuTemp) v.push_back({L"Temp", Num(SensorVal(r, s.gpuTemp)), L"\u00B0C"});
    if (g_set.gpuHotspot) v.push_back({L"Hot spot", Num(SensorVal(r, s.gpuHotspot)), L"\u00B0C"});
    if (g_set.gpuPower) v.push_back({L"Power", Num(SensorVal(r, s.gpuPower)), L"W"});
    if (g_set.gpuClock) v.push_back({L"Clock", Num(SensorVal(r, s.gpuClock)), L"MHz"});
    if (g_set.gpuMemClock) v.push_back({L"Memory", Num(SensorVal(r, s.gpuMemClock)), L"MHz"});
    if (g_set.vram) v.push_back({L"VRAM", VramPct(r), L"%"});
    if (g_set.gpuFan) {
        std::wstring rpm = Num(SensorVal(r, s.gpuFanRpm));
        std::wstring pct = Num(SensorVal(r, s.gpuFanPercent));
        v.push_back({L"Fan", rpm, L"RPM"});
        if (pct != kDash) v.back().unit = L"RPM  " + pct + L"%";
    }
    return v;
}

static std::vector<Item> CpuItems(const Readings& r) {
    std::vector<Item> v;
    const auto& s = r.s;
    if (g_set.cpuUsage) v.push_back({L"CPU", Num(SensorVal(r, s.cpuUsage)), L"%"});
    if (g_set.cpuTemp) v.push_back({L"CPU temp", Num(SensorVal(r, s.cpuTemp)), L"\u00B0C"});
    if (g_set.cpuPower) v.push_back({L"CPU power", Num(SensorVal(r, s.cpuPackagePower)), L"W"});
    if (g_set.cpuClock) v.push_back({L"CPU clock", Num(SensorVal(r, s.cpuEffectiveClockAvg)), L"MHz"});
    if (g_set.ram) v.push_back({L"RAM", Num(SensorVal(r, s.ramLoad)), L"%"});
    return v;
}

// A label on the left and the number (and unit) right-aligned at `right`.
static void AddRow(Layout& L, float x, float right, float y, const Item& it, float px) {
    AddText(L, kFontLabel, kBrushLabel, x, y + (g_lineH[kFontValue] - g_lineH[kFontLabel]) / 2, it.label);
    float uw = it.unit.empty() ? 0 : TextW(kFontUnit, it.unit) + 3 * px;
    float vw = TextW(kFontValue, it.value);
    AddText(L, kFontValue, kBrushValue, right - uw - vw, y, it.value);
    if (!it.unit.empty())
        AddText(L, kFontUnit, kBrushDim, right - uw + 3 * px, y + g_lineH[kFontValue] - g_lineH[kFontUnit] - 1 * px,
                it.unit);
}

static float RowWidth(const Item& it, float px, float gap) {
    float uw = it.unit.empty() ? 0 : TextW(kFontUnit, it.unit) + 3 * px;
    return TextW(kFontLabel, it.label) + gap + TextW(kFontValue, it.value) + uw;
}

// Inline pieces for the compact line: "FPS 144  6.9 ms  GPU 54 % 61 C".
static float AddInline(Layout& L, float x, float y, const Item& it, float px, bool label) {
    float lineH = g_lineH[kFontValue];
    if (label && !it.label.empty()) {
        AddText(L, kFontLabel, kBrushLabel, x, y + (lineH - g_lineH[kFontLabel]) / 2, it.label);
        x += TextW(kFontLabel, it.label) + 5 * px;
    }
    AddText(L, kFontValue, kBrushValue, x, y, it.value);
    x += TextW(kFontValue, it.value);
    if (!it.unit.empty()) {
        x += 2 * px;
        AddText(L, kFontUnit, kBrushDim, x, y + lineH - g_lineH[kFontUnit] - 1 * px, it.unit);
        x += TextW(kFontUnit, it.unit);
    }
    return x;
}

// ---- The Benchmark layout ------------------------------------------------------
// Blocks laid out like the RivaTuner overlay it replaces: frames, info, cores and memory on the
// left; the card, its memory and the processor on the right. Each block is built at its own
// origin; Render moves and sizes it.

static std::wstring g_apiName;        // "DX11", "Vulkan", ... for the current game
static ULONGLONG g_sessionStart = 0;  // when the current game started drawing

static double Frac(double v, double max) {
    if (!seamless_sensors::IsValid(v) || v < 0 || max <= 0) return 0;
    return std::clamp(v / max, 0.0, 1.0);
}
static bool Over(double v, int limit) { return limit > 0 && seamless_sensors::IsValid(v) && v >= limit; }

static std::wstring Fixed(double v, int decimals) {
    if (!seamless_sensors::IsValid(v) || v < 0) return kDash;
    wchar_t b[32];
    swprintf_s(b, L"%.*f", decimals, v);
    return b;
}

static void EraseAll(std::wstring& s, const wchar_t* what) {
    const size_t n = wcslen(what);
    for (size_t at; (at = s.find(what)) != std::wstring::npos;) s.erase(at, n);
}
static std::wstring Squash(const std::wstring& s) {
    std::wstring out;
    for (wchar_t c : s)
        if (c != L' ' || (!out.empty() && out.back() != L' ')) out += c;
    while (!out.empty() && out.back() == L' ') out.pop_back();
    return out;
}

static std::wstring ShortGpuName(const wchar_t* n) {
    std::wstring s = n;
    for (const wchar_t* drop : {L"NVIDIA ", L"GeForce ", L"AMD ", L"Radeon ", L"Intel(R) ", L"(TM)", L"(R)"})
        EraseAll(s, drop);
    return Squash(s);
}

static std::wstring ShortCpuName(const wchar_t* n) {
    std::wstring s = n;
    for (const wchar_t* drop : {L"(R)", L"(TM)", L" Processor", L"AMD ", L"Intel ", L" with Radeon Graphics",
                                L" CPU", L"Core "})
        EraseAll(s, drop);
    // "16-Core" adds nothing the bars do not show.
    for (size_t at; (at = s.find(L"-Core")) != std::wstring::npos;) {
        size_t start = at;
        while (start > 0 && iswdigit(s[start - 1])) start--;
        s.erase(start, at + 5 - start);
    }
    size_t at = s.find(L'@');
    if (at != std::wstring::npos) s.erase(at);
    return Squash(s);
}

struct Bench {
    Layout* L;
    const Readings* r;
    int blk = 0;
    float u = 1, P = 7, W = 150;  // one design unit, the inner padding and the content width
    int slot = 0;                 // next smoothing slot in this block
    float need = 0;               // widest row seen, so a long name never runs into its number
};

static Op& BOp(Bench& b, int shape, float x, float y, float w, float h) {
    Op o;
    o.shape = shape;
    o.graph = shape == kShGraph;
    o.x = x, o.y = y, o.w = w, o.h = h;
    o.blk = b.blk;
    b.L->ops.push_back(std::move(o));
    return b.L->ops.back();
}

static void BText(Bench& b, int font, int brush, float x, float y, const std::wstring& s, bool warn = false,
                  bool pulse = false) {
    const size_t n = b.L->ops.size();
    AddText(*b.L, font, brush, x, y, s);
    if (b.L->ops.size() == n) return;
    Op& o = b.L->ops.back();
    o.blk = b.blk;
    o.warn = warn;
    o.pulse = pulse;
}

// A number and its unit, right-aligned at `right`, top at `y`.
static float BValue(Bench& b, float right, float y, const std::wstring& value, const std::wstring& unit, bool warn) {
    const float u = b.u;
    const float uw = unit.empty() ? 0 : TextW(kFontUnit, unit) + 3 * u;
    const float vw = TextW(kFontValue, value);
    BText(b, kFontValue, kBrushValue, right - uw - vw, y, value, warn);
    if (!unit.empty())
        BText(b, kFontUnit, kBrushDim, right - uw + 3 * u, y + g_lineH[kFontValue] - g_lineH[kFontUnit] - 1 * u, unit);
    return uw + vw;
}

// One reading: an optional picture, its name, and the number at the right edge. Returns its height.
static float BRow(Bench& b, float y, int icon, float v, float v2, const std::wstring& label, const std::wstring& value,
                  const std::wstring& unit, bool warn = false) {
    const float u = b.u;
    const float iconSz = 24 * u;
    const float rowH = icon >= 0 ? std::max(30 * u, g_lineH[kFontValue] + 6 * u) : g_lineH[kFontValue] + 3 * u;
    float lx = b.P;
    if (icon >= 0) {
        Op& o = BOp(b, icon, b.P, y + (rowH - iconSz) / 2, iconSz, iconSz);
        o.v = v;
        o.v2 = v2;
        o.warn = warn;
        o.id = b.blk * 16 + b.slot++;
        lx = b.P + iconSz + 8 * u;
    }
    BText(b, kFontSmall, kBrushLabel, lx, y + (rowH - g_lineH[kFontSmall]) / 2, label);
    const float vw = BValue(b, b.P + b.W, y + (rowH - g_lineH[kFontValue]) / 2, value, unit, warn);
    b.need = std::max(b.need, (lx - b.P) + TextW(kFontSmall, label) + 10 * u + vw);
    return rowH;
}

static void BLine(Bench& b, float y) { BOp(b, kShLine, b.P, y, b.W, 0); }

static void BBar(Bench& b, float y, float h, float v, bool warn) {
    Op& o = BOp(b, kShBar, b.P, y, b.W, h);
    o.v = v;
    o.warn = warn;
    o.id = b.blk * 16 + b.slot++;
}

static std::wstring GbPair(double usedMB, double totalMB) {
    if (!seamless_sensors::IsValid(usedMB) || usedMB < 0) return kDash;
    std::wstring s = Fixed(usedMB / 1024.0, 1);
    if (seamless_sensors::IsValid(totalMB) && totalMB > 0) s += L" / " + Fixed(totalMB / 1024.0, 0);
    return s;
}

static std::wstring PlayTime(bool live) {
    if (!g_sessionStart || !live) return kDash;
    const ULONGLONG secs = (GetTickCount64() - g_sessionStart) / 1000;
    wchar_t t[32];
    if (secs >= 3600) swprintf_s(t, L"%llu:%02llu:%02llu", secs / 3600, secs / 60 % 60, secs % 60);
    else swprintf_s(t, L"%llu:%02llu", secs / 60, secs % 60);
    return t;
}

static float BuildBlock(Bench& b) {
    const Readings& r = *b.r;
    const auto& s = r.s;
    const auto& f = r.f;
    const float u = b.u, P = b.P, W = b.W;
    float y = P;
    bool any = false;
    auto sv = [&](double v) { return SensorVal(r, v); };
    const bool flamesOn = g_set.animations && g_set.flames;
    switch (b.blk) {
        case kBlkName: {
            std::wstring name = g_set.showGpuName && r.sensorsOk && s.gpuName[0] ? ShortGpuName(s.gpuName) : L"";
            std::wstring slow;
            if (g_set.throttleWarn && r.sensorsOk) {
                if (s.gpuThermalThrottle == 1.0) slow = L"HEAT LIMIT";
                else if (s.gpuPowerThrottle == 1.0) slow = L"POWER LIMIT";
            }
            if (name.empty() && slow.empty()) return 0;
            const int font = TextW(kFontName, name) > W * 0.7f && !slow.empty() ? kFontSmall : kFontName;
            BText(b, font, kBrushLabel, P, y, name);
            if (!slow.empty())
                BText(b, kFontTiny, kBrushValue, P + W - TextW(kFontTiny, slow),
                      y + (g_lineH[font] - g_lineH[kFontTiny]) / 2, slow, true, g_set.throttlePulse);
            y += g_lineH[font];
            any = true;
            break;
        }
        case kBlkFrames: {
            if (g_set.fps) {
                const std::wstring v = Num(f.fps), lbl = Label(L"lblFps");
                const bool warn = g_set.fpsWarn > 0 && f.fps > 0 && f.fps < g_set.fpsWarn;
                const float right = P + W * 100.f / 150.f;
                const float top = y - 6 * u;
                BText(b, kFontHuge, kBrushValue, right - TextW(kFontHuge, v), top, v, warn);
                BText(b, kFontLabel, kBrushLabel, right + 6 * u, top + g_lineH[kFontHuge] * 0.80f - g_lineH[kFontLabel],
                      lbl);
                y += g_lineH[kFontHuge] - 10 * u;
                any = true;
            }
            if (g_set.low01 || g_set.low1 || g_set.avgFps) {
                struct Col {
                    bool on;
                    double v;
                    const wchar_t* key;
                    float centre;
                } cols[3] = {{g_set.low01, f.low01, L"lbl01", 24.f},
                             {g_set.low1, f.low1, L"lbl1", 75.5f},
                             {g_set.avgFps, f.avg, L"lblAvg", 126.5f}};
                for (auto& c : cols) {
                    if (!c.on) continue;
                    const float cx = P + W * c.centre / 150.f;
                    const std::wstring v = Num(c.v), l = Label(c.key);
                    BText(b, kFontValue, kBrushValue, cx - TextW(kFontValue, v) / 2, y, v);
                    BText(b, kFontTiny, kBrushLabel, cx - TextW(kFontTiny, l) / 2, y + g_lineH[kFontValue], l);
                }
                y += g_lineH[kFontValue] + g_lineH[kFontTiny] + 5 * u;
                any = true;
            }
            if (g_set.jitter) {
                const float rowH = g_lineH[kFontValue] + 3 * u;
                BText(b, kFontSmall, kBrushLabel, P, y + (rowH - g_lineH[kFontSmall]) / 2, Label(L"lblJitter"));
                Op& w = BOp(b, kShWave, P + W * 0.36f, y + 3 * u, W * 0.30f, rowH - 6 * u);
                const size_t take = std::min<size_t>(f.graph.size(), 48);
                w.series.assign(f.graph.end() - take, f.graph.end());
                BValue(b, P + W, y + 1.5f * u, Fixed(f.live ? f.jitter : NAN, 1), L"ms", false);
                y += rowH;
                any = true;
            }
            if (g_set.frameTime) {
                y += BRow(b, y, -1, 0, 0, Label(L"lblFrame"), Fixed(f.live ? f.frameMs : NAN, 1), L"ms");
                any = true;
            }
            if (g_set.frameGraph) {
                y += 3 * u;
                Op& g = BOp(b, kShGraph, P, y, W, std::clamp(g_set.graphHeight, 16, 120) * u);
                g.series = f.graph;
                y += g.h + 2 * u;
                any = true;
            }
            break;
        }
        case kBlkInfo: {
            struct Line {
                bool on;
                const wchar_t* key;
                std::wstring value, unit;
            } lines[] = {{g_set.latency, L"lblLatency", kDash, L"ms"},
                         {g_set.api, L"lblApi", g_apiName.empty() ? kDash : g_apiName, L""},
                         {g_set.session, L"lblTime", PlayTime(f.live), L""},
                         {g_set.driver, L"lblDriver", r.sensorsOk && s.gpuDriver[0] ? std::wstring(s.gpuDriver) : kDash,
                          L""}};
            for (auto& l : lines) {
                if (!l.on) continue;
                if (any) BLine(b, y);
                any = true;
                y += BRow(b, y, -1, 0, 0, Label(l.key), l.value, l.unit);
            }
            break;
        }
        case kBlkCores: {
            if (g_set.cpuName && r.sensorsOk && s.cpuName[0]) {
                const std::wstring n = ShortCpuName(s.cpuName);
                const int font = TextW(kFontName, n) > W ? kFontSmall : kFontName;
                BText(b, font, kBrushLabel, P, y, n);
                y += g_lineH[font] + 3 * u;
                any = true;
            }
            if (g_set.coreBars && r.sensorsOk && s.logicalCores) {
                Op& o = BOp(b, kShCores, P, y, W, 46 * u);
                const uint32_t n = std::min<uint32_t>(s.logicalCores, seamless_sensors::kMaxCores);
                const bool pairs = !g_set.coreThreads && s.physicalCores && n == s.physicalCores * 2;
                for (uint32_t i = 0; i < n; i += pairs ? 2 : 1) {
                    double v = s.cpuCoreUsage[i];
                    if (pairs) v = std::max(v, s.cpuCoreUsage[i + 1]);
                    o.series.push_back((float)Frac(v, 100));
                }
                y += o.h + 2 * u;
                any = true;
            }
            break;
        }
        case kBlkMemory: {
            if (g_set.ram) {
                const double load = sv(s.ramLoad);
                const bool warn = Over(load, g_set.ramWarn);
                y += BRow(b, y, -1, 0, 0, Label(L"lblRam"), Num(load), L"%", warn);
                Op& stick = BOp(b, kShRamStick, P, y + 1 * u, W, 30 * u);
                stick.v = (float)Frac(load, 100);
                stick.id = b.blk * 16 + b.slot++;
                y += 34 * u;
                BBar(b, y, 4 * u, (float)Frac(load, 100), warn);
                y += 8 * u;
                any = true;
            }
            if (g_set.ramUsed) {
                y += BRow(b, y, -1, 0, 0, Label(L"lblRamUsed"), GbPair(sv(s.ramUsedMB), sv(s.ramTotalMB)), L"GB");
                any = true;
            }
            if (g_set.ramSpeed) {
                y += BRow(b, y, -1, 0, 0, Label(L"lblRamSpeed"), Num(sv(s.ramSpeedMTs)), L"MT/s");
                any = true;
            }
            if (g_set.ramClock) {
                y += BRow(b, y, -1, 0, 0, Label(L"lblRamClock"), Num(sv(s.ramClockMHz)), L"MHz");
                any = true;
            }
            break;
        }
        case kBlkCard: {
            if (g_set.gpuArt) {
                Op& art = BOp(b, kShGpuArt, P, y, W, W * 40.f / 128.f);
                art.v = (float)Frac(sv(s.gpuUsage), 100);
                y += art.h + 4 * u;
                any = true;
            }
            const double use = sv(s.gpuUsage);
            if (g_set.gpuUsage) {
                y += BRow(b, y, kShRing, (float)Frac(use, 100), flamesOn && Over(use, g_set.flameAt) ? 1.f : 0.f,
                          Label(L"lblGpuLoad"), Num(use), L"%");
                any = true;
            }
            if (g_set.gpuPower) {
                y += BRow(b, y, kShBolt, 0, 0, Label(L"lblGpuPower"), Num(sv(s.gpuPower)), L"W");
                any = true;
            }
            if (g_set.gpuClock) {
                y += BRow(b, y, kShGauge, (float)Frac(sv(s.gpuClock), g_set.gpuGaugeMax), 0, Label(L"lblGpuClock"),
                          Num(sv(s.gpuClock)), L"MHz");
                any = true;
            }
            if (g_set.gpuFan) {
                const double rpm = sv(s.gpuFanRpm), pct = sv(s.gpuFanPercent);
                const bool hasPct = seamless_sensors::IsValid(pct) && pct >= 0;
                const bool hasRpm = seamless_sensors::IsValid(rpm) && rpm >= 0;
                const float spin = (float)(hasPct ? Frac(pct, 100) : Frac(rpm, 3000));
                y += BRow(b, y, kShFan, spin, spin, Label(L"lblFan"), hasRpm ? Num(rpm) : Num(pct),
                          hasRpm || !hasPct ? L"RPM" : L"%");
                any = true;
            }
            if (g_set.gpuTemp) {
                const double t = sv(s.gpuTemp);
                y += BRow(b, y, kShThermo, (float)Frac(t, 100), 0, Label(L"lblGpuTemp"), Num(t), L"\u00B0C",
                          Over(t, g_set.gpuTempWarn));
                any = true;
            }
            if (g_set.gpuHotspot) {
                const double t = sv(s.gpuHotspot);
                y += BRow(b, y, kShDie, (float)Frac(t, 110), 0, Label(L"lblHotspot"), Num(t), L"\u00B0C",
                          Over(t, g_set.hotspotWarn));
                any = true;
            }
            break;
        }
        case kBlkVram: {
            const double used = sv(s.gpuVramUsedMB), total = sv(s.gpuVramTotalMB);
            const double pct =
                seamless_sensors::IsValid(used) && seamless_sensors::IsValid(total) && total > 0 ? used / total * 100.0
                                                                                                  : NAN;
            if (g_set.vram) {
                const bool warn = Over(pct, g_set.vramWarn);
                const float rowH = g_lineH[kFontValue] + 3 * u;
                const std::wstring l = Label(L"lblVram");
                BText(b, kFontSmall, kBrushLabel, P, y + (rowH - g_lineH[kFontSmall]) / 2, l);
                const float cx = P + TextW(kFontSmall, l) + 8 * u;
                const float cw = W - (cx - P) - 46 * u;
                if (cw > 20 * u) {
                    Op& chips = BOp(b, kShChips, cx, y + rowH / 2 - 4 * u, cw, 8 * u);
                    chips.v = (float)Frac(pct, 100);
                    chips.v2 = 8;
                    chips.warn = warn;
                }
                BValue(b, P + W, y + 1.5f * u, Num(pct), L"%", warn);
                y += rowH + 1 * u;
                BBar(b, y, 4 * u, (float)Frac(pct, 100), warn);
                y += 7 * u;
                any = true;
            }
            if (g_set.vramUsed) {
                y += BRow(b, y, -1, 0, 0, Label(L"lblVramUsed"), GbPair(used, total), L"GB");
                any = true;
            }
            if (g_set.vramTemp) {
                const double t = sv(s.gpuMemJunction);
                const bool warn = Over(t, g_set.hotspotWarn);
                y += 2 * u;
                BBar(b, y, 4 * u, (float)Frac(t, 110), warn);
                y += 6 * u;
                y += BRow(b, y, -1, 0, 0, Label(L"lblVramTemp"), Num(t), L"\u00B0C", warn);
                any = true;
            }
            if (g_set.gpuMemClock) {
                y += BRow(b, y, -1, 0, 0, Label(L"lblVramClock"), Num(sv(s.gpuMemClock)), L"MHz");
                any = true;
            }
            break;
        }
        case kBlkProcessor: {
            if (g_set.cpuArt) {
                Op& chip = BOp(b, kShCpuArt, P, y, 40 * u, 40 * u);
                chip.text = !r.sensorsOk ? L"CPU" : s.cpuVendorId == 0x1022 ? L"AMD" : s.cpuVendorId == 0x8086 ? L"INTEL"
                                                                                                                 : L"CPU";
                Op& bin = BOp(b, kShBinary, P + 48 * u, y + 2 * u, W - 48 * u, 36 * u);
                bin.v = (float)Frac(sv(s.cpuUsage), 100);
                if (g_set.throttleWarn && r.sensorsOk && s.cpuThermalThrottle == 1.0) {
                    const std::wstring slow = L"HEAT LIMIT";
                    BText(b, kFontTiny, kBrushValue, P + W - TextW(kFontTiny, slow), y + 40 * u - g_lineH[kFontTiny],
                          slow, true, g_set.throttlePulse);
                }
                y += 46 * u;
                any = true;
            }
            const double use = sv(s.cpuUsage);
            if (g_set.cpuUsage) {
                y += BRow(b, y, kShRing, (float)Frac(use, 100), flamesOn && Over(use, g_set.flameAt) ? 1.f : 0.f,
                          Label(L"lblCpuLoad"), Num(use), L"%");
                any = true;
            }
            if (g_set.cpuPower) {
                y += BRow(b, y, kShBolt, 0, 0, Label(L"lblCpuPower"), Num(sv(s.cpuPackagePower)), L"W");
                any = true;
            }
            if (g_set.cpuClock) {
                const double mhz = sv(s.cpuClockMax);
                y += BRow(b, y, kShGauge, (float)Frac(mhz, g_set.cpuGaugeMax), 0, Label(L"lblCpuBoost"),
                          Fixed(seamless_sensors::IsValid(mhz) ? mhz / 1000.0 : NAN, 2), L"GHz");
                any = true;
            }
            if (g_set.cpuBusyClock) {
                const double mhz = sv(s.cpuEffectiveClockAvg);
                y += BRow(b, y, kShGauge, (float)Frac(mhz, g_set.cpuGaugeMax), 0, Label(L"lblCpuBusy"), Num(mhz),
                          L"MHz");
                any = true;
            }
            if (g_set.cpuTemp) {
                const double t = sv(s.cpuTemp);
                y += BRow(b, y, kShThermo, (float)Frac(t, 100), 0, Label(L"lblCpuTemp"), Num(t), L"\u00B0C",
                          Over(t, g_set.cpuTempWarn));
                any = true;
            }
            break;
        }
    }
    return any ? y + P - 2 * u : 0;
}

static Layout BuildBench(const Readings& r, float px) {
    Layout L;
    const float u = px;
    const float ts = std::max(1.0f, std::clamp(g_set.textSize, 60, 200) / 100.0f);
    const float P = 8 * u, gap = std::clamp(g_set.blockGap, 0, 40) * u;
    const float design[2] = {150 * u * ts, 128 * u * ts};

    // Blocks per column, in the chosen order.
    std::vector<int> cols[2];
    for (int i = 0; i < kBlkCount; i++)
        if (g_set.blockOn[i]) cols[std::clamp(g_set.blockColumn[i], 0, 1)].push_back(i);
    for (auto& c : cols)
        std::stable_sort(c.begin(), c.end(), [](int a, int b) { return g_set.blockOrder[a] < g_set.blockOrder[b]; });

    // One panel (the default): no gaps, sections split by thin lines, both columns end level.
    const bool one = !g_set.cards;
    const float blockGap = one ? 0.f : gap, colGap = one ? 0.f : std::max(gap, 6 * u);
    float colX = 0, totalH = 0;
    struct ColInfo { float x = 0, w = 0, h = 0; std::vector<int> blocks; };
    std::vector<ColInfo> built;
    for (int c = 0; c < 2; c++) {
        if (cols[c].empty()) continue;
        float colW = 0;
        for (int i : cols[c]) {
            const float k = std::clamp(g_set.blockSize[i], 50, 200) / 100.f;
            // Dry run at the design width to learn how wide this block's longest row is.
            Bench probe{&L, &r, i, u, P, design[c]};
            const size_t first = L.ops.size();
            BuildBlock(probe);
            L.ops.resize(first);
            g_blkNeed[i] = std::max(g_blkNeed[i], probe.need);
            colW = std::max(colW, (std::max(design[c], g_blkNeed[i]) + 2 * P) * k);
        }
        float y = 0;
        ColInfo col;
        col.x = colX, col.w = colW;
        for (int i : cols[c]) {
            const float k = std::clamp(g_set.blockSize[i], 50, 200) / 100.f;
            Bench b{&L, &r, i, u, P, colW / k - 2 * P};
            const size_t first = L.ops.size();
            const float h = BuildBlock(b);
            if (h <= 0) {
                L.ops.resize(first);
                continue;
            }
            if (!col.blocks.empty()) y += blockGap;
            Place& pl = L.places[i];
            pl.x = colX, pl.y = y, pl.k = k, pl.w = colW / k, pl.h = h;
            pl.colour = g_set.blockColour[i];
            if (g_set.cards) L.cards.push_back(D2D1::RectF(colX, y, colX + colW, y + h * k));
            y += h * k;
            col.blocks.push_back(i);
        }
        if (col.blocks.empty()) continue;
        col.h = y;
        totalH = std::max(totalH, y);
        built.push_back(col);
        colX += colW + colGap;
    }
    if (one && !built.empty()) {
        // Share the spare height of a shorter column out between its sections, each section's
        // rows centred in its slot, so the lines and the bottom edge line up across the panel.
        for (auto& col : built) {
            const float extra = totalH - col.h, each = extra / col.blocks.size();
            float shift = 0;
            for (size_t n = 0; n < col.blocks.size(); n++) {
                Place& pl = L.places[col.blocks[n]];
                const float top = pl.y + shift;
                pl.y = top + each / 2;
                shift += each;
                const float bottom = top + pl.h * pl.k + each;
                if (n + 1 < col.blocks.size())
                    L.dividers.push_back(D2D1::RectF(col.x + P, bottom, col.x + col.w - P, bottom));
            }
        }
        for (size_t c = 1; c < built.size(); c++)
            L.dividers.push_back(D2D1::RectF(built[c].x, P, built[c].x, totalH - P));
    }
    if (L.ops.empty()) return L;
    L.w = std::max(1.f, colX - colGap);
    L.h = std::max(1.f, totalH);
    L.graph = r.f.graph;
    L.animated = g_set.animations;
    if (g_set.animations && g_set.fanSpin && r.sensorsOk) {
        const double pct = r.s.gpuFanPercent, rpm = r.s.gpuFanRpm;
        double turns = 0;
        if (seamless_sensors::IsValid(pct) && pct > 0) turns = pct / 100.0 * 1.5;
        else if (seamless_sensors::IsValid(rpm) && rpm > 0) turns = rpm / 3000.0 * 1.5;
        L.fanRate = turns * std::clamp(g_set.fanSpeed, 10, 300) / 100.0;
    }
    return L;
}

static Layout BuildLayout(const Readings& r, float px) {
    Layout L;
    const float pad = 10 * px, gap = 14 * px, rowGap = 2 * px;
    const int preset = ActivePreset();
    const float rowH = g_lineH[kFontValue] + rowGap;

    if (preset == kFpsOnly) {
        std::wstring v = Num(r.f.fps);
        AddText(L, kFontBig, kBrushValue, pad, pad - 2 * px, v);
        float x = pad + TextW(kFontBig, v) + 5 * px;
        float y = pad - 2 * px + g_lineH[kFontBig] - g_lineH[kFontLabel] - 6 * px;
        AddText(L, kFontLabel, kBrushLabel, x, y, L"FPS");
        L.w = x + TextW(kFontLabel, L"FPS") + pad;
        L.h = pad - 2 * px + g_lineH[kFontBig] + pad - 4 * px;
        return L;
    }

    if (preset == kCompact) {
        float x = pad, y = pad - 2 * px;
        auto sep = [&]() { x += gap; };
        bool first = true;
        for (const Item& it : FrameItems(r, true)) {
            if (!first) x += 9 * px;
            x = AddInline(L, x, y, it, px, it.label != L"Frame");
            first = false;
        }
        auto group = [&](const wchar_t* title, const std::vector<Item>& items) {
            if (items.empty()) return;
            if (!first) sep();
            AddText(L, kFontLabel, kBrushLabel, x, y + (g_lineH[kFontValue] - g_lineH[kFontLabel]) / 2, title);
            x += TextW(kFontLabel, title) + 5 * px;
            for (size_t i = 0; i < items.size(); i++) {
                if (i) x += 7 * px;
                x = AddInline(L, x, y, items[i], px, false);
            }
            first = false;
        };
        std::vector<Item> gpu = GpuItems(r, true);
        group(L"GPU", gpu);
        std::vector<Item> cpu;
        for (auto& it : CpuItems(r))
            if (it.label != L"RAM") cpu.push_back(it);
        group(L"CPU", cpu);
        if (g_set.ram) group(L"RAM", {Item{L"", Num(SensorVal(r, r.s.ramLoad)), L"%"}});
        float h = g_lineH[kFontValue];
        if (g_set.frameGraph && !r.f.graph.empty()) {
            if (!first) x += gap;
            Op g;
            g.graph = true;
            g.x = x;
            g.y = y + 2 * px;
            g.w = 90 * px;
            g.h = h - 4 * px;
            L.ops.push_back(g);
            x += g.w;
            L.graph = r.f.graph;
        }
        L.w = x + pad;
        L.h = y + h + pad - 4 * px;
        return L;
    }

    if (preset == kVertical) {
        std::vector<Item> items = FrameItems(r, true);
        for (auto& it : GpuItems(r, true)) {
            if (it.label != L"GPU") it.label = L"GPU " + Lower(it.label);
            if (it.label == L"GPU vram") it.label = L"VRAM";
            items.push_back(it);
        }
        for (auto& it : CpuItems(r)) items.push_back(it);
        float colW = 120 * px;
        for (auto& it : items) colW = std::max(colW, RowWidth(it, px, gap));
        float y = pad - 2 * px;
        for (auto& it : items) {
            AddRow(L, pad, pad + colW, y, it, px);
            y += rowH;
        }
        if (g_set.frameGraph && !r.f.graph.empty()) {
            Op g;
            g.graph = true;
            g.x = pad;
            g.y = y + 3 * px;
            g.w = colW;
            g.h = 26 * px;
            L.ops.push_back(g);
            y += g.h + 5 * px;
            L.graph = r.f.graph;
        }
        L.w = pad * 2 + colW;
        L.h = y + pad - rowGap - 2 * px;
        return L;
    }

    return BuildBench(r, px);
}

// ---- Rendering --------------------------------------------------------------

static bool EnsureDevice() {
    if (!g_d2d && FAILED(D2D1CreateFactory(D2D1_FACTORY_TYPE_SINGLE_THREADED, &g_d2d))) return false;
    if (!g_dw && FAILED(DWriteCreateFactory(DWRITE_FACTORY_TYPE_SHARED, __uuidof(IDWriteFactory), (IUnknown**)&g_dw)))
        return false;
    if (!g_rt) {
        D2D1_RENDER_TARGET_PROPERTIES p = D2D1::RenderTargetProperties(
            D2D1_RENDER_TARGET_TYPE_DEFAULT, D2D1::PixelFormat(DXGI_FORMAT_B8G8R8A8_UNORM, D2D1_ALPHA_MODE_PREMULTIPLIED),
            96, 96);
        if (FAILED(g_d2d->CreateDCRenderTarget(&p, &g_rt))) return false;
        g_rt->SetTextAntialiasMode(D2D1_TEXT_ANTIALIAS_MODE_GRAYSCALE);
    }
    if (!g_memDc) g_memDc = CreateCompatibleDC(nullptr);
    return g_memDc != nullptr;
}

static bool EnsureDib(int w, int h) {
    if (g_dib && w == g_dibW && h == g_dibH) return true;
    if (g_dib) {
        SelectObject(g_memDc, g_oldBmp);
        DeleteObject(g_dib);
        g_dib = nullptr;
    }
    BITMAPINFO bi{};
    bi.bmiHeader.biSize = sizeof(bi.bmiHeader);
    bi.bmiHeader.biWidth = w;
    bi.bmiHeader.biHeight = -h;
    bi.bmiHeader.biPlanes = 1;
    bi.bmiHeader.biBitCount = 32;
    void* bits = nullptr;
    g_dib = CreateDIBSection(g_memDc, &bi, DIB_RGB_COLORS, &bits, nullptr, 0);
    if (!g_dib) return false;
    g_oldBmp = SelectObject(g_memDc, g_dib);
    g_dibW = w;
    g_dibH = h;
    return true;
}

static int EffectiveBackground() {
    if (g_set.background == kGlass && (!sfoglass::GlassAvailable() || g_glass.Failed())) return kSolid;
    return g_set.background;
}

static D2D1_COLOR_F StyleColour(int style) {
    switch (style) {
        case kStyleBlue: return Rgb(mocha::kBlue);
        case kStyleMauve: return Rgb(mocha::kMauve);
        case kStyleText: return Rgb(mocha::kText);
        case kStyleCustom: return g_set.customColour;
        default: return Rgb(mocha::kText);
    }
}

// ---- Moving parts -------------------------------------------------------------

static double g_fanAngle = 0;    // degrees, all fans
static double g_flamePhase = 0;  // seconds of flame flicker
static double g_pulsePhase = 0;  // seconds of the "limit" pulse
static double g_binClock = 0;
static int g_binFrame = 0;       // which of the 8 binary code frames shows
static std::map<int, float> g_smooth;  // dial slot -> where its needle is now
static Layout g_lastLayout;
static float g_lastPx = 1;
static bool g_gfxOn = false;
static double g_gfxLastQpc = 0;
static ID2D1StrokeStyle* g_roundStroke = nullptr;
static std::vector<D2D1_RECT_F> g_cards;  // panels of the last frame, for the glass

static float OpVal(const Op& o) {
    if (o.id < 0 || !g_set.animations || !g_set.smoothDials) return o.v;
    auto it = g_smooth.find(o.id);
    return it == g_smooth.end() ? o.v : it->second;
}

struct Paint {
    ID2D1RenderTarget* rt = nullptr;
    ID2D1SolidColorBrush* solid = nullptr;     // scratch colour
    ID2D1SolidColorBrush* accSolid = nullptr;  // the block colour when it is not the gradient
    ID2D1LinearGradientBrush* grad = nullptr;
    ID2D1Brush* accent = nullptr;              // the block colour, gradient or solid
    D2D1_COLOR_F warn{};
    D2D1_MATRIX_3X2_F world = D2D1::Matrix3x2F::Identity();
    float u = 1;
};

static D2D1::Matrix3x2F M(const D2D1_MATRIX_3X2_F& m) {
    return D2D1::Matrix3x2F(m._11, m._12, m._21, m._22, m._31, m._32);
}

// The gradient is laid over the whole overlay, so inside a moved or turned shape it is
// counter-moved to stay put.
static void World(Paint& p, const D2D1_MATRIX_3X2_F& m) {
    p.rt->SetTransform(m);
    if (!p.grad) return;
    const float det = m._11 * m._22 - m._12 * m._21;
    if (std::fabs(det) < 1e-6f) return;
    const float i11 = m._22 / det, i12 = -m._12 / det, i21 = -m._21 / det, i22 = m._11 / det;
    const float i31 = -(m._31 * i11 + m._32 * i21), i32 = -(m._31 * i12 + m._32 * i22);
    p.grad->SetTransform(D2D1::Matrix3x2F(i11, i12, i21, i22, i31, i32));
}

static ID2D1Brush* Col(Paint& p, uint32_t rgb, float a = 1.f) {
    p.solid->SetColor(Rgb(rgb, a));
    return p.solid;
}
static ID2D1Brush* Accent(Paint& p, bool warn) {
    if (!warn) return p.accent;
    p.solid->SetColor(p.warn);
    return p.solid;
}

static D2D1_POINT_2F Polar(D2D1_POINT_2F c, float r, float deg) {
    const float a = deg * 3.14159265f / 180.f;
    return D2D1::Point2F(c.x + r * std::sin(a), c.y - r * std::cos(a));
}

// An arc from a0 to a1 degrees, clockwise, 0 = straight up.
static void Arc(Paint& p, D2D1_POINT_2F c, float r, float a0, float a1, ID2D1Brush* b, float width) {
    if (a1 - a0 < 0.5f) return;
    if (a1 - a0 >= 359.5f) {
        p.rt->DrawEllipse(D2D1::Ellipse(c, r, r), b, width);
        return;
    }
    ID2D1PathGeometry* g = nullptr;
    ID2D1GeometrySink* s = nullptr;
    if (SUCCEEDED(g_d2d->CreatePathGeometry(&g)) && SUCCEEDED(g->Open(&s))) {
        s->BeginFigure(Polar(c, r, a0), D2D1_FIGURE_BEGIN_HOLLOW);
        s->AddArc(D2D1::ArcSegment(Polar(c, r, a1), D2D1::SizeF(r, r), 0, D2D1_SWEEP_DIRECTION_CLOCKWISE,
                                   a1 - a0 > 180 ? D2D1_ARC_SIZE_LARGE : D2D1_ARC_SIZE_SMALL));
        s->EndFigure(D2D1_FIGURE_END_OPEN);
        s->Close();
        p.rt->DrawGeometry(g, b, width, g_roundStroke);
    }
    SafeRelease(s);
    SafeRelease(g);
}

static void Poly(Paint& p, const D2D1_POINT_2F* pts, int n, ID2D1Brush* fill, ID2D1Brush* line = nullptr,
                 float width = 1, bool closed = true) {
    ID2D1PathGeometry* g = nullptr;
    ID2D1GeometrySink* s = nullptr;
    if (n >= 2 && SUCCEEDED(g_d2d->CreatePathGeometry(&g)) && SUCCEEDED(g->Open(&s))) {
        s->BeginFigure(pts[0], fill ? D2D1_FIGURE_BEGIN_FILLED : D2D1_FIGURE_BEGIN_HOLLOW);
        for (int i = 1; i < n; i++) s->AddLine(pts[i]);
        s->EndFigure(closed ? D2D1_FIGURE_END_CLOSED : D2D1_FIGURE_END_OPEN);
        s->Close();
        if (fill) p.rt->FillGeometry(g, fill);
        if (line) p.rt->DrawGeometry(g, line, width, g_roundStroke);
    }
    SafeRelease(s);
    SafeRelease(g);
}

static D2D1_ROUNDED_RECT RR(float l, float t, float r, float b, float rad) {
    return D2D1_ROUNDED_RECT{D2D1::RectF(l, t, r, b), rad, rad};
}

// Fan blades turned by `angle` around c.
static void Rotor(Paint& p, D2D1_POINT_2F c, float r, float angle, int blades, ID2D1Brush* b) {
    const D2D1_MATRIX_3X2_F base = p.world;
    for (int i = 0; i < blades; i++) {
        const float a = angle + i * 360.f / blades;
        // A curved blade: a slim ellipse leaning off the spoke.
        const D2D1_POINT_2F mid = D2D1::Point2F(c.x + r * 0.12f, c.y - r * 0.52f);
        World(p, D2D1::Matrix3x2F::Rotation(24, mid) * D2D1::Matrix3x2F::Rotation(a, c) * M(base));
        p.rt->FillEllipse(D2D1::Ellipse(mid, r * 0.2f, r * 0.42f), b);
    }
    World(p, base);
}

static void Flames(Paint& p, D2D1_POINT_2F c, float r) {
    const float u = p.u;
    static const uint32_t kFire[3] = {mocha::kPeach, mocha::kRed, mocha::kYellow};
    for (int i = 0; i < 10; i++) {
        const float a = i * 36.f + 8.f * (float)std::sin(g_flamePhase * 5.0 + i);
        const float flick = 0.5f + 0.5f * (float)std::sin(g_flamePhase * 17.0 + i * 1.9);
        const float len = (2.5f + 3.5f * flick) * u;
        D2D1_POINT_2F pts[3] = {Polar(c, r + 0.5f * u, a - 11), Polar(c, r + len, a + 4 * flick),
                                Polar(c, r + 0.5f * u, a + 11)};
        Poly(p, pts, 3, Col(p, kFire[i % 3], 0.55f + 0.4f * flick));
    }
}

static void DrawShape(Paint& p, const Op& o) {
    const float u = p.u;
    const float v = std::clamp(OpVal(o), 0.f, 1.f);
    const D2D1_POINT_2F c = D2D1::Point2F(o.x + o.w / 2, o.y + o.h / 2);
    const float r = std::min(o.w, o.h) / 2;
    switch (o.shape) {
        case kShRing: {
            const float rr = r - 2 * u;
            if (o.v2 > 0 && g_set.animations && g_set.flames) Flames(p, c, rr + 1 * u);
            p.rt->DrawEllipse(D2D1::Ellipse(c, rr, rr), Col(p, mocha::kSurface1, 0.9f), 3 * u);
            Arc(p, c, rr, 0, v * 360.f, Accent(p, o.warn), 3 * u);
            p.rt->FillEllipse(D2D1::Ellipse(c, rr * 0.38f, rr * 0.38f), Col(p, mocha::kSurface1, 0.8f));
            break;
        }
        case kShBolt: {
            const float x = o.x + o.w * 0.18f, y = o.y + 1 * u, w = o.w * 0.64f, h = o.h - 2 * u;
            const float n[][2] = {{0.62f, 0}, {0.08f, 0.56f}, {0.44f, 0.56f}, {0.32f, 1}, {0.92f, 0.40f},
                                  {0.56f, 0.40f}, {0.74f, 0}};
            D2D1_POINT_2F pts[7];
            for (int i = 0; i < 7; i++) pts[i] = D2D1::Point2F(x + n[i][0] * w, y + n[i][1] * h);
            Poly(p, pts, 7, Accent(p, o.warn));
            break;
        }
        case kShGauge: {
            const float rr = r - 2 * u;
            const D2D1_POINT_2F gc = D2D1::Point2F(c.x, c.y + 2 * u);
            Arc(p, gc, rr, -115, 115, Col(p, mocha::kSurface1, 0.9f), 2.6f * u);
            Arc(p, gc, rr, -115, -115 + 230 * v, Accent(p, o.warn), 2.6f * u);
            const D2D1_POINT_2F tip = Polar(gc, rr * 0.78f, -115 + 230 * v);
            p.rt->DrawLine(gc, tip, Col(p, mocha::kText), 1.6f * u, g_roundStroke);
            p.rt->FillEllipse(D2D1::Ellipse(gc, 2.2f * u, 2.2f * u), Col(p, mocha::kText));
            break;
        }
        case kShFan: {
            const float rr = r - 1.5f * u;
            p.rt->DrawEllipse(D2D1::Ellipse(c, rr, rr), Col(p, mocha::kSurface1, 0.9f), 1.6f * u);
            Arc(p, c, rr, 0, v * 360.f, Accent(p, o.warn), 1.8f * u);
            Rotor(p, c, rr - 2 * u, (float)g_fanAngle, 5, Col(p, mocha::kSubtext, 0.9f));
            p.rt->FillEllipse(D2D1::Ellipse(c, rr * 0.2f, rr * 0.2f), Col(p, mocha::kSurface2));
            break;
        }
        case kShThermo: {
            const float tw = 6 * u, bulb = 5 * u;
            const float top = o.y + 1 * u, bottomY = o.y + o.h - bulb;
            const float x0 = c.x - tw / 2, x1 = c.x + tw / 2;
            p.rt->FillRoundedRectangle(RR(x0, top, x1, bottomY, tw / 2), Col(p, mocha::kSurface1, 0.9f));
            p.rt->FillEllipse(D2D1::Ellipse(D2D1::Point2F(c.x, bottomY), bulb, bulb), Col(p, mocha::kSurface1, 0.9f));
            ID2D1Brush* fill = Accent(p, o.warn);
            const float level = top + (bottomY - top) * (1 - v);
            if (bottomY - level > 1) p.rt->FillRoundedRectangle(RR(x0 + 1.2f * u, level, x1 - 1.2f * u, bottomY, tw / 2), fill);
            p.rt->FillEllipse(D2D1::Ellipse(D2D1::Point2F(c.x, bottomY), bulb - 1.6f * u, bulb - 1.6f * u), fill);
            break;
        }
        case kShDie: {
            const float s = r * 0.62f;
            ID2D1Brush* pins = Col(p, mocha::kSurface2);
            for (int i = 0; i < 3; i++) {
                const float t = -s * 0.55f + i * s * 0.55f;
                p.rt->DrawLine(D2D1::Point2F(c.x + t, c.y - s - 3 * u), D2D1::Point2F(c.x + t, c.y - s), pins, 1.4f * u);
                p.rt->DrawLine(D2D1::Point2F(c.x + t, c.y + s), D2D1::Point2F(c.x + t, c.y + s + 3 * u), pins, 1.4f * u);
                p.rt->DrawLine(D2D1::Point2F(c.x - s - 3 * u, c.y + t), D2D1::Point2F(c.x - s, c.y + t), pins, 1.4f * u);
                p.rt->DrawLine(D2D1::Point2F(c.x + s, c.y + t), D2D1::Point2F(c.x + s + 3 * u, c.y + t), pins, 1.4f * u);
            }
            p.rt->FillRoundedRectangle(RR(c.x - s, c.y - s, c.x + s, c.y + s, 2 * u), Col(p, mocha::kSurface0));
            p.rt->DrawRoundedRectangle(RR(c.x - s, c.y - s, c.x + s, c.y + s, 2 * u), Accent(p, o.warn), 1.2f * u);
            // The hot centre goes green, then yellow, then red as it heats up.
            const uint32_t heat = v < 0.6f ? mocha::kGreen : v < 0.8f ? mocha::kYellow : mocha::kRed;
            const float hs = s * (0.35f + 0.3f * v);
            p.rt->FillRoundedRectangle(RR(c.x - hs, c.y - hs, c.x + hs, c.y + hs, 1.5f * u), Col(p, heat, 0.9f));
            break;
        }
        case kShBar: {
            const float rad = o.h / 2;
            p.rt->FillRoundedRectangle(RR(o.x, o.y, o.x + o.w, o.y + o.h, rad), Col(p, mocha::kSurface0, 0.9f));
            if (v > 0) p.rt->FillRoundedRectangle(RR(o.x, o.y, o.x + std::max(o.h, o.w * v), o.y + o.h, rad), Accent(p, o.warn));
            break;
        }
        case kShChips: {
            const int n = std::max(1, (int)o.v2);
            const float gap = 2 * u, cw = (o.w - gap * (n - 1)) / n;
            const int lit = (int)std::lround(v * n);
            for (int i = 0; i < n; i++) {
                const float x = o.x + i * (cw + gap);
                p.rt->FillRoundedRectangle(RR(x, o.y, x + cw, o.y + o.h, 1.2f * u),
                                           i < lit ? Accent(p, o.warn) : Col(p, mocha::kSurface1, 0.9f));
            }
            break;
        }
        case kShGpuArt: {
            const float bodyR = o.x + o.w * 0.95f, top = o.y + o.h * 0.06f, bot = o.y + o.h * 0.80f;
            // Gold contacts under the card, then the bracket at its end.
            ID2D1Brush* gold = Col(p, mocha::kYellow, 0.75f);
            for (float x = o.x + o.w * 0.24f; x < o.x + o.w * 0.66f; x += 3 * u)
                p.rt->FillRectangle(D2D1::RectF(x, bot, x + 1.8f * u, o.y + o.h * 0.94f), gold);
            p.rt->FillRoundedRectangle(RR(bodyR + 1 * u, o.y, o.x + o.w, o.y + o.h * 0.88f, 1 * u), Col(p, mocha::kSurface2));
            p.rt->FillRoundedRectangle(RR(o.x, top, bodyR, bot, 4 * u), Col(p, mocha::kSurface0, 0.92f));
            p.rt->DrawRoundedRectangle(RR(o.x, top, bodyR, bot, 4 * u), p.accent, 1.2f * u);
            // A light strip along the top that glows brighter with load.
            p.solid->SetOpacity(1);
            p.accent->SetOpacity(0.35f + 0.65f * v);
            p.rt->DrawLine(D2D1::Point2F(o.x + 6 * u, top + 2.5f * u), D2D1::Point2F(bodyR - 6 * u, top + 2.5f * u), p.accent,
                           1.6f * u, g_roundStroke);
            p.accent->SetOpacity(1);
            const float fr = std::min((bot - top) * 0.40f, (bodyR - o.x) * 0.15f);
            const float cy = (top + bot) / 2 + 1.5f * u;
            for (int i = 0; i < 3; i++) {
                const D2D1_POINT_2F fc = D2D1::Point2F(o.x + (bodyR - o.x) * (0.18f + 0.32f * i), cy);
                p.rt->FillEllipse(D2D1::Ellipse(fc, fr, fr), Col(p, mocha::kCrust, 0.7f));
                p.rt->DrawEllipse(D2D1::Ellipse(fc, fr, fr), Col(p, mocha::kSurface2), 1.2f * u);
                const float a = (float)g_fanAngle * (i == 1 ? -1.f : 1.f) + i * 17.f;
                Rotor(p, fc, fr - 1.5f * u, a, 7, Col(p, mocha::kSubtext, 0.85f));
                p.rt->FillEllipse(D2D1::Ellipse(fc, fr * 0.26f, fr * 0.26f), Col(p, mocha::kSurface2));
                p.rt->FillEllipse(D2D1::Ellipse(fc, fr * 0.12f, fr * 0.12f), p.accent);
            }
            break;
        }
        case kShCpuArt: {
            ID2D1Brush* pins = Col(p, mocha::kSurface2);
            const float in = 5 * u;
            for (int i = 0; i < 5; i++) {
                const float t = o.x + in + 3 * u + i * (o.w - 2 * in - 6 * u) / 4;
                const float t2 = o.y + in + 3 * u + i * (o.h - 2 * in - 6 * u) / 4;
                p.rt->DrawLine(D2D1::Point2F(t, o.y), D2D1::Point2F(t, o.y + in), pins, 1.5f * u);
                p.rt->DrawLine(D2D1::Point2F(t, o.y + o.h - in), D2D1::Point2F(t, o.y + o.h), pins, 1.5f * u);
                p.rt->DrawLine(D2D1::Point2F(o.x, t2), D2D1::Point2F(o.x + in, t2), pins, 1.5f * u);
                p.rt->DrawLine(D2D1::Point2F(o.x + o.w - in, t2), D2D1::Point2F(o.x + o.w, t2), pins, 1.5f * u);
            }
            const D2D1_ROUNDED_RECT body = RR(o.x + in, o.y + in, o.x + o.w - in, o.y + o.h - in, 3 * u);
            p.rt->FillRoundedRectangle(body, Col(p, mocha::kSurface0, 0.95f));
            p.rt->DrawRoundedRectangle(body, p.accent, 1.2f * u);
            p.rt->DrawRoundedRectangle(RR(o.x + in + 4 * u, o.y + in + 4 * u, o.x + o.w - in - 4 * u, o.y + o.h - in - 4 * u, 2 * u),
                                       Col(p, mocha::kOverlay, 0.6f), 1 * u);
            if (g_fmt[kFontTiny] && !o.text.empty()) {
                const float tw = TextW(kFontTiny, o.text);
                const D2D1_RECT_F tr = D2D1::RectF(c.x - tw / 2, c.y - g_lineH[kFontTiny] / 2, c.x + tw / 2 + 4,
                                                   c.y + g_lineH[kFontTiny] / 2 + 2);
                p.rt->DrawText(o.text.c_str(), (UINT32)o.text.size(), g_fmt[kFontTiny], tr, p.accent);
            }
            break;
        }
        case kShBinary: {
            if (!g_fmt[kFontTiny]) break;
            const float cw = std::max(1.f, TextW(kFontTiny, L"0")) + 1.2f * u;
            const int cols = std::max(1, (int)(o.w / cw)), rows = 3;
            const float rowH = o.h / rows;
            ID2D1Brush* dim = Col(p, mocha::kOverlay, 0.55f);
            for (int row = 0; row < rows; row++) {
                for (int col = 0; col < cols; col++) {
                    uint32_t hsh = (uint32_t)(g_binFrame * 7919 + row * 104729 + col * 1299709);
                    hsh ^= hsh >> 13;
                    hsh *= 0x5BD1E995u;
                    hsh ^= hsh >> 15;
                    const wchar_t ch = (hsh & 1) ? L'1' : L'0';
                    const bool lit = ((hsh >> 8) & 0xFF) < (uint32_t)(64 + 150 * v);
                    const D2D1_RECT_F tr = D2D1::RectF(o.x + col * cw, o.y + row * rowH, o.x + (col + 1) * cw + 2,
                                                       o.y + row * rowH + g_lineH[kFontTiny] + 2);
                    p.rt->DrawText(&ch, 1, g_fmt[kFontTiny], tr, lit ? p.accent : dim);
                }
            }
            break;
        }
        case kShCores: {
            const int n = (int)o.series.size();
            if (!n) break;
            const float gap = n > 24 ? 1 * u : 2 * u, bw = (o.w - gap * (n - 1)) / n;
            for (int i = 0; i < n; i++) {
                const float x = o.x + i * (bw + gap);
                p.rt->FillRoundedRectangle(RR(x, o.y, x + bw, o.y + o.h, 1 * u), Col(p, mocha::kSurface0, 0.9f));
                const float fv = std::clamp(o.series[i], 0.f, 1.f);
                if (fv > 0.01f)
                    p.rt->FillRoundedRectangle(RR(x, o.y + o.h * (1 - fv), x + bw, o.y + o.h, 1 * u), p.accent);
            }
            break;
        }
        case kShRamStick: {
            const float boardB = o.y + o.h * 0.76f;
            ID2D1Brush* gold = Col(p, mocha::kYellow, 0.75f);
            const float notch = o.x + o.w * 0.42f;
            for (float x = o.x + 3 * u; x < o.x + o.w - 3 * u; x += 2.6f * u)
                if (x < notch - 2 * u || x > notch + 3 * u)
                    p.rt->FillRectangle(D2D1::RectF(x, boardB, x + 1.4f * u, o.y + o.h), gold);
            const D2D1_ROUNDED_RECT board = RR(o.x, o.y, o.x + o.w, boardB, 2 * u);
            p.rt->FillRoundedRectangle(board, Col(p, mocha::kSurface0, 0.95f));
            p.rt->DrawRoundedRectangle(board, p.accent, 1.1f * u);
            const int n = 8;
            const float gap = 3 * u, cw = (o.w - 8 * u - gap * (n - 1)) / n;
            const int lit = (int)std::ceil(v * n - 0.01f);
            for (int i = 0; i < n; i++) {
                const float x = o.x + 4 * u + i * (cw + gap);
                p.rt->FillRoundedRectangle(RR(x, o.y + 4 * u, x + cw, boardB - 4 * u, 1 * u),
                                           i < lit ? p.accent : Col(p, mocha::kSurface2, 0.9f));
            }
            break;
        }
        case kShWave: {
            const size_t n = o.series.size();
            if (n < 2) break;
            double mean = 0, spread = 0;
            for (float s : o.series) mean += s;
            mean /= n;
            for (float s : o.series) spread = std::max(spread, std::fabs(s - mean));
            spread = std::max(spread, 2.0);
            std::vector<D2D1_POINT_2F> pts(n);
            for (size_t i = 0; i < n; i++)
                pts[i] = D2D1::Point2F(o.x + o.w * i / (n - 1),
                                       c.y - (float)((o.series[i] - mean) / spread) * (o.h / 2));
            Poly(p, pts.data(), (int)n, nullptr, p.accent, 1.3f * u, false);
            break;
        }
        case kShLine:
            p.rt->DrawLine(D2D1::Point2F(o.x, o.y), D2D1::Point2F(o.x + o.w, o.y), Col(p, mocha::kOverlay, 0.3f), 1 * u);
            break;
    }
}

static void DrawGraph(Paint& p, const Op& o, const std::vector<float>& data) {
    const float u = p.u;
    if (data.size() < 2) return;
    double sum = 0, mx = 0;
    for (float v : data) sum += v, mx = std::max(mx, (double)v);
    const double mean = sum / data.size();
    const double top = g_set.graphTopMs > 0 ? (double)g_set.graphTopMs : std::max({mx * 1.1, mean * 2.0, 20.0});
    p.rt->DrawLine(D2D1::Point2F(o.x, o.y + o.h), D2D1::Point2F(o.x + o.w, o.y + o.h), Col(p, mocha::kOverlay, 0.35f),
                   u);
    if (o.blk >= 0 && g_fmt[kFontTiny]) {
        wchar_t t[24];
        swprintf_s(t, L"%.0f ms", top);
        const float tw = TextW(kFontTiny, t);
        p.rt->DrawText(t, (UINT32)wcslen(t), g_fmt[kFontTiny],
                       D2D1::RectF(o.x + o.w - tw, o.y - 1 * u, o.x + o.w + 4, o.y + g_lineH[kFontTiny]),
                       Col(p, mocha::kOverlay, 0.9f));
    }
    const size_t n = data.size();
    auto X = [&](size_t i) { return o.x + o.w * (float)i / (float)(n - 1); };
    auto Y = [&](float v) { return o.y + o.h - (float)std::min(1.0, v / top) * o.h; };
    ID2D1Brush* b = p.accent;
    if (g_set.graphStyle == 2) {
        const float bw = std::max(0.6f * u, o.w / n - 0.4f * u);
        for (size_t i = 0; i < n; i++) p.rt->FillRectangle(D2D1::RectF(X(i), Y(data[i]), X(i) + bw, o.y + o.h), b);
    } else {
        std::vector<D2D1_POINT_2F> pts;
        pts.reserve(n + 2);
        for (size_t i = 0; i < n; i++) pts.push_back(D2D1::Point2F(X(i), Y(data[i])));
        if (g_set.graphStyle == 1) {
            std::vector<D2D1_POINT_2F> area = pts;
            area.push_back(D2D1::Point2F(o.x + o.w, o.y + o.h));
            area.push_back(D2D1::Point2F(o.x, o.y + o.h));
            b->SetOpacity(0.28f);
            Poly(p, area.data(), (int)area.size(), b);
            b->SetOpacity(1);
        }
        Poly(p, pts.data(), (int)n, nullptr, b, 1.4f * u, false);
    }
    if (g_set.spikeMarks) {
        std::vector<float> sorted = data;
        std::nth_element(sorted.begin(), sorted.begin() + n / 2, sorted.end());
        const double median = sorted[n / 2];
        const double limit = std::max(median * 2.0, median + 8.0);
        p.solid->SetColor(p.warn);
        for (size_t i = 0; i < n; i++)
            if (data[i] > limit)
                p.rt->DrawLine(D2D1::Point2F(X(i), o.y + o.h), D2D1::Point2F(X(i), Y(data[i])), p.solid, 1.4f * u);
    }
}

static void Render(const Layout& L, float px) {
    const int w = std::max(1, (int)std::ceil(L.w)), h = std::max(1, (int)std::ceil(L.h));
    if (!EnsureDib(w, h)) return;
    RECT rc{0, 0, w, h};
    if (FAILED(g_rt->BindDC(g_memDc, &rc))) return;
    if (!g_roundStroke)
        g_d2d->CreateStrokeStyle(D2D1::StrokeStyleProperties(D2D1_CAP_STYLE_ROUND, D2D1_CAP_STYLE_ROUND,
                                                             D2D1_CAP_STYLE_ROUND, D2D1_LINE_JOIN_ROUND),
                                 nullptr, 0, &g_roundStroke);
    g_rt->BeginDraw();
    g_rt->SetTransform(D2D1::Matrix3x2F::Identity());
    g_rt->Clear(D2D1::ColorF(0, 0, 0, 0));

    // One gradient across the whole overlay, top left to bottom right (swapped when flipped).
    D2D1_GRADIENT_STOP stops[2] = {{0.f, Rgb(mocha::kBlue)}, {1.f, Rgb(mocha::kMauve)}};
    if (g_set.flipGradient) std::swap(stops[0].color, stops[1].color);
    ID2D1GradientStopCollection* coll = nullptr;
    ID2D1LinearGradientBrush* grad = nullptr;
    g_rt->CreateGradientStopCollection(stops, 2, &coll);
    if (coll)
        g_rt->CreateLinearGradientBrush(D2D1::LinearGradientBrushProperties(D2D1::Point2F(0, 0), D2D1::Point2F((float)w, (float)h)),
                                        coll, &grad);
    ID2D1SolidColorBrush* solid = nullptr;
    ID2D1SolidColorBrush* acc = nullptr;
    g_rt->CreateSolidColorBrush(Rgb(mocha::kText), &solid);
    g_rt->CreateSolidColorBrush(Rgb(mocha::kBlue), &acc);
    if (!solid || !acc) {
        g_rt->EndDraw();
        SafeRelease(solid);
        SafeRelease(acc);
        SafeRelease(grad);
        SafeRelease(coll);
        return;
    }
    Paint p;
    p.rt = g_rt;
    p.solid = solid;
    p.accSolid = acc;
    p.grad = grad;
    p.u = px;
    p.warn = g_set.warnColour >= 0 && g_set.warnColour < kPalCustom && g_set.warnColour != kPalGradient
                 ? Rgb(kPalRgb[g_set.warnColour])
                 : Rgb(mocha::kRed);

    const int bg = EffectiveBackground();
    const float radius = g_set.rounded ? g_set.cornerRadius * px : 0.f;
    const float strength = std::clamp(g_set.bgStrength, 0, 200) / 100.f;
    const float fillA = std::min(1.f, (bg == kGlass ? 0.42f : bg == kTint ? 0.55f : 0.96f) * strength);
    const uint32_t fillRgb = bg == kSolid ? mocha::kMantle : mocha::kBase;
    // Box edges are 2 px at 100% scale, drawn half a stroke in so the outside of the line sits
    // exactly on the box's own rounded corner and the curve is as thick as the sides.
    const float edgeW = std::max(1.f, std::round(2.f * px));
    const float half = edgeW / 2;
    std::vector<D2D1_ROUNDED_RECT> panels;  // outer shapes
    if (!L.cards.empty()) {
        for (const auto& c : L.cards) {
            const float cr = std::min(radius, std::min(c.right - c.left, c.bottom - c.top) / 2);
            panels.push_back(D2D1_ROUNDED_RECT{c, cr, cr});
        }
    } else {
        panels.push_back(D2D1_ROUNDED_RECT{D2D1::RectF(0, 0, (float)w, (float)h), radius, radius});
    }
    if (bg != kNone) {
        solid->SetColor(Rgb(fillRgb, fillA));
        for (const auto& pr : panels) g_rt->FillRoundedRectangle(pr, solid);
    }

    auto setAccent = [&](int blk) {
        int colour = blk >= 0 ? L.places[blk].colour : kPalSame;
        if (colour == kPalSame) {
            switch (g_set.labelStyle) {
                case kStyleBlue: colour = kPalBlue; break;
                case kStyleMauve: colour = kPalMauve; break;
                case kStyleText: colour = kPalWhite; break;
                case kStyleCustom: colour = kPalCustom; break;
                default: colour = kPalGradient; break;
            }
        }
        if (colour == kPalGradient && grad) {
            p.accent = grad;
            return;
        }
        acc->SetColor(colour == kPalCustom ? g_set.customColour
                      : colour > kPalGradient && colour < kPalCustom ? Rgb(kPalRgb[colour])
                                                                       : Rgb(mocha::kBlue));
        p.accent = acc;
    };
    auto brushFor = [&](const Op& o) -> ID2D1Brush* {
        if (o.warn) {
            solid->SetColor(p.warn);
            return solid;
        }
        if (o.brush == kBrushLabel) return p.accent;
        if (o.brush == kBrushValue) {
            if (g_set.valueStyle == kStyleGradient && grad) return grad;
            solid->SetColor(StyleColour(g_set.valueStyle));
            return solid;
        }
        solid->SetColor(Rgb(mocha::kSubtext));
        return solid;
    };
    const float pulse = 0.85f + 0.15f * (float)(0.5 + 0.5 * std::cos(g_pulsePhase * 2 * 3.14159265 / 0.8));

    int curBlk = -2;
    for (const Op& o : L.ops) {
        if (o.blk != curBlk) {
            curBlk = o.blk;
            if (curBlk >= 0) {
                const Place& pl = L.places[curBlk];
                p.world = D2D1::Matrix3x2F::Scale(pl.k, pl.k) * D2D1::Matrix3x2F::Translation(pl.x, pl.y);
                p.u = px;
            } else {
                p.world = D2D1::Matrix3x2F::Identity();
            }
            World(p, p.world);
            setAccent(curBlk);
        }
        if (o.graph || o.shape == kShGraph) {
            DrawGraph(p, o, o.series.empty() ? L.graph : o.series);
            continue;
        }
        if (o.shape != kShText) {
            DrawShape(p, o);
            continue;
        }
        if (!g_fmt[o.font]) continue;
        const D2D1_RECT_F r = D2D1::RectF(o.x, o.y, o.x + o.w + 4, o.y + o.h + 2);
        if (bg == kNone) {
            // No background: a soft shadow keeps the text readable on bright scenes.
            solid->SetColor(D2D1::ColorF(0, 0, 0, 0.75f));
            const D2D1_RECT_F s = D2D1::RectF(r.left + px, r.top + px, r.right + px, r.bottom + px);
            g_rt->DrawText(o.text.c_str(), (UINT32)o.text.size(), g_fmt[o.font], s, solid, D2D1_DRAW_TEXT_OPTIONS_NONE);
        }
        ID2D1Brush* b = brushFor(o);
        if (o.pulse && g_set.animations) b->SetOpacity(pulse);
        g_rt->DrawText(o.text.c_str(), (UINT32)o.text.size(), g_fmt[o.font], r, b, D2D1_DRAW_TEXT_OPTIONS_NONE);
        b->SetOpacity(1);
    }

    p.world = D2D1::Matrix3x2F::Identity();
    World(p, p.world);
    if (!L.dividers.empty() && bg != kNone) {
        // 1 px lines between sections, on whole pixels so they stay sharp.
        const float lw = std::max(1.f, std::round(px));
        solid->SetColor(Rgb(mocha::kSurface1));
        for (const auto& d : L.dividers) {
            const float o = std::fmod(lw, 2.f) / 2;
            const float x1 = std::round(d.left) + o, y1 = std::round(d.top) + o;
            const float x2 = std::round(d.right) + o, y2 = std::round(d.bottom) + o;
            g_rt->DrawLine(D2D1::Point2F(x1, y1), D2D1::Point2F(x2, y2), solid, lw);
        }
    }
    if (g_set.border) {
        ID2D1Brush* b = solid;
        if (g_set.borderGradient && grad) b = grad;
        else solid->SetColor(g_set.borderColour);
        for (const auto& pr : panels) {
            D2D1_ROUNDED_RECT e = pr;
            e.rect = D2D1::RectF(e.rect.left + half, e.rect.top + half, e.rect.right - half, e.rect.bottom - half);
            e.radiusX = e.radiusY = std::max(0.f, pr.radiusX - half);
            g_rt->DrawRoundedRectangle(e, b, edgeW);
        }
    }
    g_rt->EndDraw();
    SafeRelease(solid);
    SafeRelease(acc);
    SafeRelease(grad);
    SafeRelease(coll);
    g_w = w;
    g_h = h;
    g_cards = L.cards;
}

static void UpdateGfxTimer();

// Where the overlay rests, and how far it slides from.
static void RestingPos(POINT& p) {
    const RECT& m = g_monitorRc;
    const float px = MonitorScale(MonitorFromRect(&m, MONITOR_DEFAULTTOPRIMARY));
    const int ox = (int)(g_set.offsetX * px), oy = (int)(g_set.offsetY * px);
    const bool right = g_set.corner == kTopRight || g_set.corner == kBottomRight;
    const bool bottom = g_set.corner == kBottomLeft || g_set.corner == kBottomRight;
    p.x = right ? m.right - ox - g_w : m.left + ox;
    p.y = bottom ? m.bottom - oy - g_h : m.top + oy;
    p.x = std::clamp<LONG>(p.x, m.left, std::max(m.left, m.right - g_w));
    p.y = std::clamp<LONG>(p.y, m.top, std::max(m.top, m.bottom - g_h));
}

static void Push() {
    if (!g_overlay || !g_w || !g_h) return;
    const float px = MonitorScale(MonitorFromRect(&g_monitorRc, MONITOR_DEFAULTTOPRIMARY));
    const bool bottom = g_set.corner == kBottomLeft || g_set.corner == kBottomRight;
    const double slide = (1.0 - g_alpha) * 10.0 * px * (bottom ? 1 : -1);
    POINT dst{g_pos.x, g_pos.y + (LONG)std::lround(slide)};
    POINT src{0, 0};
    SIZE size{g_w, g_h};
    const double a = std::clamp(g_alpha, 0.0, 1.0) * g_set.opacity / 100.0;
    BLENDFUNCTION blend{AC_SRC_OVER, 0, (BYTE)std::lround(a * 255), AC_SRC_ALPHA};
    UpdateLayeredWindow(g_overlay, nullptr, &dst, &size, g_memDc, &src, 0, &blend, ULW_ALPHA);
    if (!IsWindowVisible(g_overlay)) ShowWindow(g_overlay, SW_SHOWNOACTIVATE);
    if (EffectiveBackground() == kGlass) {
        const float radius = g_set.rounded ? g_set.cornerRadius * px * g_set.scale / 100.f : 0.f;
        if (!g_glass.Show(g_overlay, dst.x, dst.y, g_w, g_h, g_cards, radius, (float)a)) g_lastSig.clear();
    } else {
        g_glass.Hide();
    }
}

static void KeepOnTop() {
    if (!g_overlay || !g_shown) return;
    SetWindowPos(g_overlay, HWND_TOPMOST, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE | SWP_NOACTIVATE | SWP_NOOWNERZORDER);
    if (g_glass.Hwnd() && IsWindowVisible(g_glass.Hwnd()))
        SetWindowPos(g_glass.Hwnd(), g_overlay, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE | SWP_NOACTIVATE);
}

static void StartAnim(bool in) {
    double scale = 1.0;
    const bool motion = FoMotion(&scale);
    g_animIn = in;
    if (!motion) {
        g_alpha = in ? 1.0 : 0.0;
        g_animating = false;
        KillTimer(g_ctrl, TIMER_ANIM);
        if (in) Push();
        return;
    }
    LARGE_INTEGER c;
    QueryPerformanceCounter(&c);
    g_animStartQpc = (double)c.QuadPart;
    g_animFrom = g_alpha;
    g_animDurMs = (in ? 200.0 : 150.0) * scale * std::max(0.15, in ? 1.0 - g_alpha : g_alpha);
    g_animating = true;
    SetTimer(g_ctrl, TIMER_ANIM, 10, nullptr);
}

static void HideNow() {
    if (g_overlay) ShowWindow(g_overlay, SW_HIDE);
    g_glass.Hide();
    g_shown = false;
    g_alpha = 0;
    UpdateGfxTimer();
}

static void AnimStep() {
    LARGE_INTEGER c;
    QueryPerformanceCounter(&c);
    double t = ((double)c.QuadPart - g_animStartQpc) * 1000.0 / g_qpcFreq / std::max(1.0, g_animDurMs);
    t = std::clamp(t, 0.0, 1.0);
    const double e = 1.0 - std::pow(1.0 - t, 3.0);  // ease out
    g_alpha = g_animIn ? g_animFrom + (1.0 - g_animFrom) * e : g_animFrom * (1.0 - e);
    if (t >= 1.0) {
        g_animating = false;
        KillTimer(g_ctrl, TIMER_ANIM);
        g_alpha = g_animIn ? 1.0 : 0.0;
    }
    if (!g_animIn && g_alpha <= 0.0) {
        HideNow();
        return;
    }
    Push();
}

// ---- Moving parts: one quick timer while something moves ----------------------

// Steps every moving part by dt seconds. Returns whether anything on screen changed.
static bool AnimAdvance(double dt) {
    const Layout& L = g_lastLayout;
    bool moved = false;
    if (g_set.fanSpin && L.fanRate > 0) {
        g_fanAngle = std::fmod(g_fanAngle + std::min(L.fanRate * 360.0 * dt, 20.0), 360.0);
        moved = true;
    }
    bool flames = false, pulse = false, binary = false;
    for (const Op& o : L.ops) {
        if (o.shape == kShRing && o.v2 > 0) flames = true;
        if (o.pulse) pulse = true;
        if (o.shape == kShBinary) binary = true;
    }
    if (flames && g_set.flames) {
        g_flamePhase += dt;
        moved = true;
    }
    if (pulse && g_set.throttlePulse) {
        g_pulsePhase += dt;
        moved = true;
    }
    if (binary && g_set.binaryCode) {
        g_binClock += dt;
        if (g_binClock >= 0.3) {
            g_binClock = std::fmod(g_binClock, 0.3);
            g_binFrame = (g_binFrame + 1) % 8;
            moved = true;
        }
    }
    if (g_set.smoothDials) {
        const float k = (float)(1.0 - std::exp(-dt / 0.25));
        for (const Op& o : L.ops) {
            if (o.id < 0) continue;
            auto it = g_smooth.find(o.id);
            if (it == g_smooth.end()) {
                g_smooth[o.id] = o.v;
                continue;
            }
            float& cur = it->second;
            if (std::fabs(o.v - cur) < 0.002f) {
                if (cur != o.v) cur = o.v, moved = true;
                continue;
            }
            cur += (o.v - cur) * k;
            moved = true;
        }
    }
    return moved;
}

static void GfxStep() {
    LARGE_INTEGER c;
    QueryPerformanceCounter(&c);
    const double now = (double)c.QuadPart;
    double dt = g_gfxLastQpc ? (now - g_gfxLastQpc) / g_qpcFreq : 0.0;
    g_gfxLastQpc = now;
    dt = std::clamp(dt, 0.0, 0.25);
    if (!g_shown || !g_overlay || g_lastLayout.ops.empty()) return;
    if (!AnimAdvance(dt)) return;
    Render(g_lastLayout, g_lastPx);
    if (!g_animating) Push();
}

// Runs the quick timer only while the overlay shows something that moves, so a hidden
// overlay costs nothing.
static void UpdateGfxTimer() {
    const bool want = g_ctrl && g_shown && g_enabled && g_set.animations && g_lastLayout.animated;
    if (want == g_gfxOn) return;
    g_gfxOn = want;
    if (want) {
        g_gfxLastQpc = 0;
        SetTimer(g_ctrl, TIMER_GFX, 1000 / std::clamp(g_set.animFps, 10, 60), nullptr);
    } else {
        KillTimer(g_ctrl, TIMER_GFX);
    }
}

// Which graphics API the game draws with, from the modules it has loaded.
static DWORD g_apiPid = 0;
static ULONGLONG g_apiTried = 0;
static void DetectApi(DWORD pid) {
    if (!pid) return;
    if (pid != g_apiPid) {
        g_apiPid = pid;
        g_apiName.clear();
        g_apiTried = 0;
    }
    if (!g_apiName.empty()) return;
    const ULONGLONG now = GetTickCount64();
    if (g_apiTried && now - g_apiTried < 5000) return;
    g_apiTried = now;
    if (frames::ActiveSource() == frames::kSrcD3d9) {
        g_apiName = L"DX9";
        return;
    }
    HANDLE p = OpenProcess(PROCESS_QUERY_INFORMATION | PROCESS_VM_READ, FALSE, pid);
    if (!p) return;
    HMODULE mods[1024];
    DWORD bytes = 0;
    bool d3d12 = false, d3d11 = false, d3d10 = false, d3d9 = false, vulkan = false, gl = false;
    if (K32EnumProcessModulesEx(p, mods, sizeof(mods), &bytes, LIST_MODULES_ALL)) {
        const DWORD n = std::min<DWORD>(bytes / sizeof(HMODULE), ARRAYSIZE(mods));
        for (DWORD i = 0; i < n; i++) {
            wchar_t name[MAX_PATH];
            if (!K32GetModuleBaseNameW(p, mods[i], name, MAX_PATH)) continue;
            const std::wstring m = Lower(name);
            if (m == L"d3d12.dll") d3d12 = true;
            else if (m == L"d3d11.dll") d3d11 = true;
            else if (m == L"d3d10.dll" || m == L"d3d10_1.dll") d3d10 = true;
            else if (m == L"d3d9.dll") d3d9 = true;
            else if (m == L"vulkan-1.dll") vulkan = true;
            else if (m == L"opengl32.dll") gl = true;
        }
    }
    CloseHandle(p);
    // Vulkan games often load the DirectX files too, through the driver's overlay layers, so
    // Vulkan wins only when no DirectX 12 is there.
    if (vulkan && !d3d12) g_apiName = L"Vulkan";
    else if (d3d12) g_apiName = L"DX12";
    else if (d3d11) g_apiName = L"DX11";
    else if (d3d10) g_apiName = L"DX10";
    else if (d3d9) g_apiName = L"DX9";
    else if (gl) g_apiName = L"OpenGL";
}

// ---- Who is in front --------------------------------------------------------

static std::wstring ExeOf(DWORD pid, std::wstring* fullPath) {
    std::wstring name;
    HANDLE p = OpenProcess(PROCESS_QUERY_LIMITED_INFORMATION, FALSE, pid);
    if (!p) return name;
    wchar_t path[MAX_PATH * 2];
    DWORD len = ARRAYSIZE(path);
    if (QueryFullProcessImageNameW(p, 0, path, &len)) {
        if (fullPath) *fullPath = path;
        const wchar_t* slash = wcsrchr(path, L'\\');
        name = Lower(slash ? slash + 1 : path);
    }
    CloseHandle(p);
    return name;
}

// Apps that draw their own frames but are not games: the shell, browsers and Electron apps.
static bool BuiltInSkip(const std::wstring& exe, const std::wstring& path) {
    static const wchar_t* kSkip[] = {
        L"explorer.exe", L"dwm.exe", L"windhawk.exe", L"windhawk-mod.exe", L"windhawk-mod-elevated.exe",
        L"searchhost.exe", L"startmenuexperiencehost.exe", L"shellexperiencehost.exe", L"applicationframehost.exe",
        L"textinputhost.exe", L"lockapp.exe", L"systemsettings.exe", L"taskmgr.exe", L"chrome.exe", L"msedge.exe",
        L"firefox.exe", L"brave.exe", L"opera.exe", L"opera_gx.exe", L"vivaldi.exe", L"msedgewebview2.exe",
        L"discord.exe", L"spotify.exe", L"steamwebhelper.exe", L"steam.exe", L"obs64.exe", L"code.exe",
        L"windowsterminal.exe", L"flow.launcher.exe", L"rtss.exe", L"msiafterburner.exe", L"hwinfo64.exe",
        L"yapfast.exe", L"thunderbird.exe", L"mpc-hc64.exe", L"vlc.exe", L"powershell.exe", L"pwsh.exe", L"cmd.exe", L"conhost.exe",
        L"notepad.exe", L"mspaint.exe", L"photos.exe", L"snippingtool.exe", L"screenclippinghost.exe",
    };
    for (auto s : kSkip)
        if (exe == s) return true;
    // Electron and other web shells keep their page in resources\app.asar.
    if (!path.empty()) {
        std::wstring dir = path.substr(0, path.find_last_of(L'\\'));
        if (GetFileAttributesW((dir + L"\\resources\\app.asar").c_str()) != INVALID_FILE_ATTRIBUTES) return true;
    }
    return false;
}

static bool InList(const std::vector<std::wstring>& list, const std::wstring& exe) {
    return std::find(list.begin(), list.end(), exe) != list.end();
}

// The pinned test app's biggest visible window, or null.
struct PinFind { DWORD pid; HWND best; LONG area; };
static BOOL CALLBACK PinFindProc(HWND h, LPARAM lp) {
    auto* f = (PinFind*)lp;
    DWORD pid = 0;
    GetWindowThreadProcessId(h, &pid);
    RECT r;
    if (pid == f->pid && IsWindowVisible(h) && GetWindowRect(h, &r)) {
        LONG a = (r.right - r.left) * (r.bottom - r.top);
        if (a > f->area) { f->area = a; f->best = h; }
    }
    return TRUE;
}
static HWND PinnedWindow() {
    PinFind f{g_pinnedPid, nullptr, 0};
    EnumWindows(PinFindProc, (LPARAM)&f);
    return f.best;
}

static HWND TargetWindow() {
    if (g_pinnedPid) {
        if (HWND h = PinnedWindow()) return h;
        g_pinnedPid = 0;  // the test app closed
    }
    return GetForegroundWindow();
}

static void UpdateTarget() {
    HWND fg = TargetWindow();
    DWORD pid = 0;
    if (fg) GetWindowThreadProcessId(fg, &pid);
    if (pid == GetCurrentProcessId()) return;  // our own settings window or menu: keep the game
    if (pid == g_targetPid) return;
    g_targetPid = pid;
    std::wstring path;
    g_targetExe = pid ? ExeOf(pid, &path) : L"";
    g_targetSkip = g_targetExe.empty() || BuiltInSkip(g_targetExe, path);
    wchar_t cls[64]{};
    if (fg) GetClassNameW(fg, cls, 64);
    if (!wcscmp(cls, L"Progman") || !wcscmp(cls, L"WorkerW") || !wcscmp(cls, L"Shell_TrayWnd")) g_targetSkip = true;
    g_lastGameTick = 0;
    g_gameSince = 0;
    g_isGame = false;
    g_sessionStart = 0;
    g_apiName.clear();
    g_apiPid = 0;
    frames::SetTarget(pid);
}

static void PickMonitor() {
    HMONITOR mon = nullptr;
    if (!g_set.monitorPrimary) {
        HWND fg = TargetWindow();
        DWORD pid = 0;
        if (fg) GetWindowThreadProcessId(fg, &pid);
        if (fg && pid == g_targetPid) mon = MonitorFromWindow(fg, MONITOR_DEFAULTTOPRIMARY);
    }
    if (!mon) {
        if (!g_set.monitorPrimary && g_monitorRc.right > g_monitorRc.left) return;  // keep the last one
        POINT zero{0, 0};
        mon = MonitorFromPoint(zero, MONITOR_DEFAULTTOPRIMARY);
    }
    MONITORINFO mi{sizeof(mi)};
    if (GetMonitorInfoW(mon, &mi)) g_monitorRc = mi.rcMonitor;
}

// ---- The tick -----------------------------------------------------------------

static void EnsureSensors() {
    if (g_sensorsStarted) return;
    seamless_sensors::PublisherOptions o;
    o.intervalMs = (uint32_t)std::max(500, g_set.updateMs);
    o.idleAfterMs = 5000;
    g_sensorsStarted = seamless_sensors::StartPublisher(o);
}

static std::wstring Signature(const Layout& L) {
    std::wstring s;
    s.reserve(256);
    wchar_t b[64];
    swprintf_s(b, L"%.0f,%.0f|%d|", L.w, L.h, EffectiveBackground());
    s += b;
    for (const Op& o : L.ops) {
        s += o.text;
        if (o.shape != kShText) {
            swprintf_s(b, L"#%d:%.2f,%.2f,%d", o.shape, o.v, o.v2, o.warn ? 1 : 0);
            s += b;
            for (float v : o.series) {
                swprintf_s(b, L"%.2f,", v);
                s += b;
            }
        }
        s += L'|';
    }
    for (float v : L.graph) {
        swprintf_s(b, L"%.1f,", v);
        s += b;
    }
    return s;
}

// Another mod (the taskbar) may share the readings from an older copy that leaves out the memory
// speed and the driver. Both only change with a reboot or a driver update, so read them once here.
static void FillOlderPublisherGaps(seamless_sensors::Snapshot& s) {
    static bool read = false;
    static uint32_t mts = 0, modules = 0;
    static wchar_t driver[32] = {};
    if (!read) {
        read = true;
        seamless_sensors::detail::ReadRamSpeed(mts, modules);
        seamless_sensors::detail::Nvml nv;
        if (nv.Open()) wcscpy_s(driver, nv.driver);
        nv.Close();
    }
    if (std::isnan(s.ramSpeedMTs) && mts) {
        s.ramSpeedMTs = mts;
        s.ramClockMHz = mts / 2.0;
    }
    if (!s.ramModules) s.ramModules = modules;
    if (!s.gpuDriver[0] && driver[0]) wcscpy_s(s.gpuDriver, driver);
}

static void Tick(bool force) {
    if (!g_enabled) return;
    UpdateTarget();
    frames::Stats st = frames::Compute(g_set.updateMs, g_set.graphSeconds);
    const bool listed = InList(g_set.gameList, g_targetExe);
    const bool hidden = InList(g_set.hideList, g_targetExe);
    bool want = false;
    if (g_set.showWhen == kAlways) {
        want = !hidden;
    } else if (g_set.showWhen == kListed) {
        want = listed && !hidden;
    } else {
        if (!hidden && (listed || !g_targetSkip)) {
            // A game draws a steady stream for 4 seconds straight. Apps that only redraw while
            // you scroll or type (chat apps, mail) never get that far.
            const ULONGLONG now = GetTickCount64();
            if (st.gameLike || (listed && st.live)) {
                g_lastGameTick = now;
                if (!g_gameSince) g_gameSince = now;
                if (listed || now - g_gameSince >= 4000) g_isGame = true;
            } else {
                g_gameSince = 0;
                // Fifteen seconds without a steady stream: no longer a game.
                if (g_isGame && now - g_lastGameTick > 15000) g_isGame = false;
            }
            // Keep it up through a short load or hitch.
            want = g_isGame && (st.recent3s || now - g_lastGameTick < 3000);
        }
    }
    if (!want) {
        if (g_shown && !(g_animating && !g_animIn)) StartAnim(false);
        g_wantVisible = false;
        UpdateGfxTimer();
        return;
    }
    g_wantVisible = true;

    EnsureSensors();
    // One line every 5 s while shown, for the mod's log (silent unless logging is on).
    static ULONGLONG lastLog = 0;
    if (GetTickCount64() - lastLog >= 5000) {
        lastLog = GetTickCount64();
        Wh_Log(L"Stats %s pid %lu: fps %.1f, frame %.2f ms, 1%% low %.1f, avg %.1f", g_targetExe.c_str(), g_targetPid,
               st.fps, st.frameMs, st.low1, st.avg);
    }
    if (st.live && !g_sessionStart) g_sessionStart = GetTickCount64();
    DetectApi(g_targetPid);
    Readings r;
    r.f = std::move(st);
    r.sensorsOk = seamless_sensors::Read(r.s) == seamless_sensors::ReadResult::Ok;
    if (!r.sensorsOk) seamless_sensors::ResetSnapshot(r.s);
    if (r.sensorsOk) FillOlderPublisherGaps(r.s);

    PickMonitor();
    if (!EnsureDevice()) return;
    const float px = MonitorScale(MonitorFromRect(&g_monitorRc, MONITOR_DEFAULTTOPRIMARY)) * g_set.scale / 100.0f;
    EnsureFormats(px);
    Layout L = BuildLayout(r, px);
    std::wstring sig = Signature(L);
    g_lastLayout = L;
    g_lastPx = px;
    bool redrawn = false;
    if (force || sig != g_lastSig) {
        Render(L, px);
        g_lastSig = sig;
        redrawn = true;
    }
    POINT p;
    RestingPos(p);
    const bool moved = p.x != g_pos.x || p.y != g_pos.y;
    g_pos = p;
    if (!g_shown) {
        g_shown = true;
        g_alpha = 0;
        Push();
        KeepOnTop();
        StartAnim(true);
    } else if (g_animating && !g_animIn) {
        StartAnim(true);
    } else if ((redrawn || moved) && !g_animating) {
        Push();
    }
    UpdateGfxTimer();
}

static void SetEnabled(bool on) {
    if (on == g_enabled) return;
    g_enabled = on;
    if (on) {
        frames::Start();
        g_targetPid = (DWORD)-1;
        UpdateTarget();
        g_lastSig.clear();
        SetTimer(g_ctrl, TIMER_TICK, g_set.updateMs, nullptr);
        Tick(true);
    } else {
        KillTimer(g_ctrl, TIMER_TICK);
        frames::Stop();
        g_targetPid = 0;
        if (g_shown) StartAnim(false);
        UpdateGfxTimer();
    }
    if (g_trayAdded) {
        wcscpy_s(g_nid.szTip, on ? L"Seamless FPS Overlay: on" : L"Seamless FPS Overlay: off");
        g_nid.uFlags = NIF_TIP | NIF_SHOWTIP;
        Shell_NotifyIconW(NIM_MODIFY, &g_nid);
        g_nid.uFlags = NIF_MESSAGE | NIF_ICON | NIF_TIP | NIF_SHOWTIP;
    }
    Wh_Log(L"Overlay %s.", on ? L"on" : L"off");
}

// ============================================================================
// Tray
// ============================================================================

constexpr UINT TrayIconId() {
    UINT hash = 2166136261u;
    for (PCWSTR p = WH_MOD_ID; *p; p++) hash = (hash ^ (UINT)*p) * 16777619u;
    return hash | 0x80000000u;
}
constexpr UINT kTrayId = TrayIconId();

// The gauge glyph in the blue to mauve gradient on a clear background, drawn with GDI.
static HICON MakeBadgeIcon(int size) {
    if (size < 16) size = 16;
    BITMAPINFO bi{};
    bi.bmiHeader.biSize = sizeof(bi.bmiHeader);
    bi.bmiHeader.biWidth = size;
    bi.bmiHeader.biHeight = -size;
    bi.bmiHeader.biPlanes = 1;
    bi.bmiHeader.biBitCount = 32;
    void* bits = nullptr;
    void* glyphBits = nullptr;
    HDC screen = GetDC(nullptr);
    HBITMAP color = CreateDIBSection(screen, &bi, DIB_RGB_COLORS, &bits, nullptr, 0);
    HBITMAP glyph = CreateDIBSection(screen, &bi, DIB_RGB_COLORS, &glyphBits, nullptr, 0);
    ReleaseDC(nullptr, screen);
    if (!color || !glyph) {
        if (color) DeleteObject(color);
        if (glyph) DeleteObject(glyph);
        return nullptr;
    }
    HDC dc = CreateCompatibleDC(nullptr);
    HGDIOBJ old = SelectObject(dc, glyph);
    memset(glyphBits, 0, (size_t)size * size * 4);
    HFONT font = CreateFontW(-(int)(size * 0.84f), 0, 0, 0, FW_NORMAL, 0, 0, 0, DEFAULT_CHARSET, 0, 0,
                             ANTIALIASED_QUALITY, 0, L"Segoe Fluent Icons");
    HGDIOBJ oldFont = SelectObject(dc, font);
    WCHAR face[64]{};
    GetTextFaceW(dc, 64, face);
    if (_wcsicmp(face, L"Segoe Fluent Icons") != 0) {
        SelectObject(dc, oldFont);
        DeleteObject(font);
        font = CreateFontW(-(int)(size * 0.84f), 0, 0, 0, FW_NORMAL, 0, 0, 0, DEFAULT_CHARSET, 0, 0,
                           ANTIALIASED_QUALITY, 0, L"Segoe MDL2 Assets");
        oldFont = SelectObject(dc, font);
    }
    SetBkMode(dc, TRANSPARENT);
    SetTextColor(dc, RGB(255, 255, 255));
    RECT r{0, 0, size, size};
    WCHAR g[2] = {(WCHAR)0xEC4A, 0};
    DrawTextW(dc, g, 1, &r, DT_CENTER | DT_VCENTER | DT_SINGLELINE | DT_NOPREFIX);
    GdiFlush();
    SelectObject(dc, oldFont);
    DeleteObject(font);
    SelectObject(dc, old);
    DeleteDC(dc);

    const float c0[3] = {0x89 / 255.f, 0xB4 / 255.f, 0xFA / 255.f};
    const float c1[3] = {0xCB / 255.f, 0xA6 / 255.f, 0xF7 / 255.f};
    uint32_t* pxl = (uint32_t*)bits;
    const uint32_t* gp = (const uint32_t*)glyphBits;
    for (int y = 0; y < size; y++)
        for (int x = 0; x < size; x++) {
            float t = std::clamp((x + y) / (2.0f * (size - 1)), 0.0f, 1.0f);
            float cov = ((gp[y * size + x] >> 8) & 0xFF) / 255.0f;
            float rgb[3];
            for (int i = 0; i < 3; i++) rgb[i] = (c0[i] + (c1[i] - c0[i]) * t) * cov;
            pxl[y * size + x] = ((uint32_t)(cov * 255 + 0.5f) << 24) | ((uint32_t)(rgb[0] * 255 + 0.5f) << 16) |
                                ((uint32_t)(rgb[1] * 255 + 0.5f) << 8) | (uint32_t)(rgb[2] * 255 + 0.5f);
        }
    HBITMAP mask = CreateBitmap(size, size, 1, 1, nullptr);
    ICONINFO ii{TRUE, 0, 0, mask, color};
    HICON icon = CreateIconIndirect(&ii);
    DeleteObject(mask);
    DeleteObject(color);
    DeleteObject(glyph);
    return icon;
}

static void RemoveTrayIcon() {
    if (g_trayAdded) {
        Shell_NotifyIconW(NIM_DELETE, &g_nid);
        g_trayAdded = false;
    }
    if (g_nid.hIcon) {
        DestroyIcon(g_nid.hIcon);
        g_nid.hIcon = nullptr;
    }
}

static void AddTrayIcon(HWND hwnd) {
    if (!g_set.trayIcon) {
        RemoveTrayIcon();
        return;
    }
    if (g_trayAdded) return;
    if (g_nid.hIcon) DestroyIcon(g_nid.hIcon);
    g_nid = NOTIFYICONDATAW{};
    g_nid.cbSize = sizeof(g_nid);
    g_nid.hWnd = hwnd;
    g_nid.uID = kTrayId;
    g_nid.uFlags = NIF_MESSAGE | NIF_ICON | NIF_TIP | NIF_SHOWTIP;
    g_nid.uCallbackMessage = WM_APP_TRAY_CALLBACK;
    g_nid.hIcon = MakeBadgeIcon(GetSystemMetricsForDpi(SM_CXSMICON, GetDpiForWindow(hwnd)));
    if (!g_nid.hIcon) g_nid.hIcon = CopyIcon(LoadIconW(nullptr, IDI_APPLICATION));
    wcscpy_s(g_nid.szTip, g_enabled ? L"Seamless FPS Overlay: on" : L"Seamless FPS Overlay: off");
    Shell_NotifyIconW(NIM_DELETE, &g_nid);  // A copy left by a crashed run.
    if (Shell_NotifyIconW(NIM_ADD, &g_nid)) {
        g_trayAdded = true;
        g_nid.uVersion = NOTIFYICON_VERSION_4;
        Shell_NotifyIconW(NIM_SETVERSION, &g_nid);
    }
}

static void SetPresetOverride(int preset) {
    g_presetOverride = preset == g_set.preset ? -1 : preset;
    Wh_SetIntValue(L"presetOverride", g_presetOverride + 1);
    g_lastSig.clear();
    if (g_enabled) Tick(true);
}

static void ShowTrayMenu(HWND hwnd, POINT pt) {
    std::vector<sfoset::TrayRow> rows;
    sfoset::TrayRow r;
    r.id = 1;
    r.glyph = g_enabled ? L"\uED1A" : L"\uE7B3";
    r.label = g_enabled ? L"Hide the overlay" : L"Show the overlay";
    rows.push_back(r);
    r = {};
    r.separator = true;
    rows.push_back(r);
    r = {};
    r.glyph = L"\uE8A1";
    r.label = L"Layout";
    static const wchar_t* kNames[] = {L"FPS only", L"Compact line", L"Full benchmark layout", L"Vertical stack"};
    for (int i = 0; i < 4; i++) {
        sfoset::TrayRow s;
        s.id = 10 + i;
        s.label = kNames[i];
        s.checked = ActivePreset() == i;
        r.sub.push_back(s);
    }
    rows.push_back(r);
    r = {};
    r.id = 2;
    r.glyph = L"\uE713";
    r.label = L"Settings";
    rows.push_back(r);

    int cmd = sfoset::ShowTrayMenu(hwnd, &pt, rows);
    if (cmd == 1) SetEnabled(!g_enabled);
    else if (cmd == 2) sfoset::OpenSettingsWindow();
    else if (cmd >= 10 && cmd < 14) SetPresetOverride(cmd - 10);
}

// ============================================================================
// Windows and the UI thread
// ============================================================================

static LRESULT CALLBACK OverlayWndProc(HWND hwnd, UINT msg, WPARAM wp, LPARAM lp) {
    switch (msg) {
        case WM_NCHITTEST: return HTTRANSPARENT;
        case WM_MOUSEACTIVATE: return MA_NOACTIVATE;
    }
    return DefWindowProcW(hwnd, msg, wp, lp);
}

static void CALLBACK WinEventProc(HWINEVENTHOOK, DWORD event, HWND, LONG, LONG, DWORD, DWORD) {
    if (g_ctrl && (event == EVENT_SYSTEM_FOREGROUND || event == EVENT_SYSTEM_MINIMIZEEND))
        PostMessageW(g_ctrl, WM_APP_FOREGROUND, 0, 0);
}

static void ApplySettings() {
    LoadSettings();
    g_presetOverride = -1;
    Wh_SetIntValue(L"presetOverride", 0);
    RegisterHotkeys(g_ctrl, false);
    RemoveTrayIcon();
    AddTrayIcon(g_ctrl);
    seamless_sensors::SetInterval((uint32_t)std::max(500, g_set.updateMs));
    g_fmtKey.clear();
    g_lastSig.clear();
    KillTimer(g_ctrl, TIMER_GFX);
    g_gfxOn = false;
    g_smooth.clear();
    if (g_enabled) {
        SetTimer(g_ctrl, TIMER_TICK, g_set.updateMs, nullptr);
        g_targetPid = (DWORD)-1;  // the lists may have changed
        Tick(true);
    }
}

static LRESULT CALLBACK CtrlWndProc(HWND hwnd, UINT msg, WPARAM wp, LPARAM lp) {
    if (g_wmTaskbarCreated && msg == g_wmTaskbarCreated) {
        g_trayAdded = false;
        AddTrayIcon(hwnd);
        return 0;
    }
    switch (msg) {
        case WM_CREATE:
            g_wmTaskbarCreated = RegisterWindowMessageW(L"TaskbarCreated");
            if (g_wmTaskbarCreated) ChangeWindowMessageFilterEx(hwnd, g_wmTaskbarCreated, MSGFLT_ALLOW, nullptr);
            ChangeWindowMessageFilterEx(hwnd, WM_APP_TRAY_CALLBACK, MSGFLT_ALLOW, nullptr);
            ChangeWindowMessageFilterEx(hwnd, WM_APP_PIN_TARGET, MSGFLT_ALLOW, nullptr);
            return 0;
        case WM_HOTKEY:
            if (wp == HK_TOGGLE) SetEnabled(!g_enabled);
            else if (wp == HK_PRESET) SetPresetOverride((ActivePreset() + 1) % 4);
            return 0;
        case WM_TIMER:
            if (wp == TIMER_TICK) Tick(false);
            else if (wp == TIMER_ANIM) AnimStep();
            else if (wp == TIMER_GFX) GfxStep();
            else if (wp == TIMER_HOTKEY_RETRY) RegisterHotkeys(hwnd, true);
            return 0;
        case WM_APP_FOREGROUND:
            if (g_enabled) {
                Tick(false);
                KeepOnTop();
            }
            return 0;
        case WM_APP_RELOAD_SETTINGS:
            ApplySettings();
            return 0;
        case WM_APP_PIN_TARGET:
            g_pinnedPid = (DWORD)wp;
            Wh_Log(L"Following pid %lu", g_pinnedPid);
            g_targetPid = (DWORD)-1;
            g_lastSig.clear();
            if (g_enabled) {
                Tick(true);
                KeepOnTop();
            }
            return 0;
        case WM_APP_TRAY_CALLBACK:
            switch (LOWORD(lp)) {
                case NIN_SELECT:
                case NIN_KEYSELECT:
                    SetEnabled(!g_enabled);
                    break;
                case WM_CONTEXTMENU:
                    ShowTrayMenu(hwnd, POINT{GET_X_LPARAM(wp), GET_Y_LPARAM(wp)});
                    break;
            }
            return 0;
        case WM_DISPLAYCHANGE:
            g_lastSig.clear();
            return 0;
        case WM_CLOSE:
            DestroyWindow(hwnd);
            return 0;
        case WM_DESTROY:
            KillTimer(hwnd, TIMER_TICK);
            KillTimer(hwnd, TIMER_ANIM);
            KillTimer(hwnd, TIMER_GFX);
            g_gfxOn = false;
            KillTimer(hwnd, TIMER_HOTKEY_RETRY);
            UnregisterHotKey(hwnd, HK_TOGGLE);
            UnregisterHotKey(hwnd, HK_PRESET);
            frames::Free();
            RemoveTrayIcon();
            g_glass.Destroy();
            if (g_overlay) {
                DestroyWindow(g_overlay);
                g_overlay = nullptr;
            }
            PostQuitMessage(0);
            return 0;
    }
    return DefWindowProcW(hwnd, msg, wp, lp);
}

static DWORD WINAPI UiThreadProc(LPVOID) {
    winrt::init_apartment(winrt::apartment_type::single_threaded);
    SetThreadDpiAwarenessContext(DPI_AWARENESS_CONTEXT_PER_MONITOR_AWARE_V2);
    LARGE_INTEGER f;
    QueryPerformanceFrequency(&f);
    g_qpcFreq = f.QuadPart ? (double)f.QuadPart : 1.0;
    const HINSTANCE inst = (HINSTANCE)windhawk_tool_mod::GetCurrentModuleHandle();

    WNDCLASSEXW oc{sizeof(oc)};
    oc.lpfnWndProc = OverlayWndProc;
    oc.hInstance = inst;
    oc.lpszClassName = kOverlayClass;
    RegisterClassExW(&oc);
    WNDCLASSEXW cc{sizeof(cc)};
    cc.lpfnWndProc = CtrlWndProc;
    cc.hInstance = inst;
    cc.lpszClassName = kCtrlClass;
    RegisterClassExW(&cc);

    g_overlay = CreateWindowExW(WS_EX_LAYERED | WS_EX_TRANSPARENT | WS_EX_TOPMOST | WS_EX_TOOLWINDOW | WS_EX_NOACTIVATE,
                                kOverlayClass, L"Seamless FPS Overlay", WS_POPUP, 0, 0, 1, 1, nullptr, nullptr, inst,
                                nullptr);
    // Not a message-only window: the taskbar's "I restarted" broadcast has to reach it.
    g_ctrl = CreateWindowExW(WS_EX_TOOLWINDOW, kCtrlClass, L"Seamless FPS Overlay control", WS_POPUP, 0, 0, 0, 0,
                             nullptr, nullptr, inst, nullptr);
    if (g_ctrl) {
        RegisterHotkeys(g_ctrl, false);
        AddTrayIcon(g_ctrl);
        g_fgHook = SetWinEventHook(EVENT_SYSTEM_FOREGROUND, EVENT_SYSTEM_MINIMIZEEND, nullptr, WinEventProc, 0, 0,
                                   WINEVENT_OUTOFCONTEXT | WINEVENT_SKIPOWNPROCESS);
        if (g_set.showOnStart) SetEnabled(true);
    }
    if (g_uiReady) SetEvent(g_uiReady);

    MSG msg{};
    while (GetMessageW(&msg, nullptr, 0, 0) > 0) {
        TranslateMessage(&msg);
        DispatchMessageW(&msg);
    }

    if (g_fgHook) {
        UnhookWinEvent(g_fgHook);
        g_fgHook = nullptr;
    }
    for (auto& f : g_fmt) SafeRelease(f);
    if (g_dib) {
        SelectObject(g_memDc, g_oldBmp);
        DeleteObject(g_dib);
        g_dib = nullptr;
    }
    if (g_memDc) {
        DeleteDC(g_memDc);
        g_memDc = nullptr;
    }
    SafeRelease(g_roundStroke);
    SafeRelease(g_rt);
    SafeRelease(g_dw);
    SafeRelease(g_d2d);
    g_ctrl = nullptr;
    UnregisterClassW(kOverlayClass, inst);
    UnregisterClassW(kCtrlClass, inst);
    winrt::uninit_apartment();
    return 0;
}

// ---------------------------------------------------------------------------------------------
// Menu room: shared by Seamless Flyouts and the tool mods' menu look.
// - Every popup menu window in this process is caught as it is created, title bar (system)
//   menus included, which never pass through TrackPopupMenu.
// - Menus that Windows draws get 2 px more frame on every side, so the hover has the same room
//   from the border as in Explorer's own desktop menu (4 px at the sides, 6 px top and bottom).
//   Menus with owner-drawn rows (Explorer) already have it and are left alone.
// - A submenu opens touching its parent, and while the pointer heads for an open submenu the
//   parent ignores it, so rows crossed on the way don't swap the submenu (released after a
//   short rest, so stopping on a row still opens that row).
// - A menu too tall for its monitor gets shorter rows while it is open, so the last item
//   shows without scroll arrows. Windows reads row spacing once per process, so the spacing is
//   reloaded (FlushMenuThemes) when such a menu opens and again when the menu closes.
// ---------------------------------------------------------------------------------------------
#include <algorithm>
#include <atomic>
#include <mutex>
#include <vector>
#include <commctrl.h>

namespace SeamlessMenuRoom {

constexpr UINT_PTR kRoomId = 0x6D55;
constexpr INT kRowMargin = 6;                  // row top and bottom margin of the menu look
constexpr INT kMinRowMargin = 2;
static const WCHAR* const kPadProp = L"SeamlessMenuRoomPad";
static const WCHAR* const kSizeProp = L"SeamlessMenuRoomSize";
static const WCHAR* const kSeqProp = L"SeamlessMenuRoomSeq";   // creation order of menu windows
constexpr UINT kAimHoldMs = 250;               // how long the pointer may rest before a held move counts

static std::atomic<INT> g_rowMargin{kRowMargin};
static HWINEVENTHOOK g_createHook = nullptr, g_menuHook = nullptr;
static VOID (*g_onCreate)(HWND) = nullptr;
using Flush_t = VOID(WINAPI*)();
static Flush_t g_flush = nullptr;
static thread_local HHOOK t_loopHook = nullptr;
static thread_local INT t_trackDepth = 0;
static thread_local BOOL t_menuMode = FALSE;
static std::atomic<ULONG> g_seq{0};
static thread_local HHOOK t_aimHook = nullptr;
static thread_local POINT t_apex = {LONG_MIN, LONG_MIN};
static thread_local MSG t_held = {};
static thread_local UINT_PTR t_aimTimer = 0;
static thread_local DWORD t_holdStart = 0;
constexpr DWORD kAimMaxMs = 700;               // a hold never lasts longer than this

// Row top and bottom margin to report for Menu part 27 / POPUPITEM, property 10000.
static INT RowMargin() { return g_rowMargin.load(); }

static UINT DpiOf(HWND h)
{
    UINT d = h ? GetDpiForWindow(h) : 0;
    if (!d) d = GetDpiForSystem();
    return d ? d : USER_DEFAULT_SCREEN_DPI;
}

static BOOL IsPopupMenuWindow(HWND h)
{
    WCHAR cls[16];
    return h && GetClassNameW(h, cls, ARRAYSIZE(cls)) && wcscmp(cls, L"#32768") == 0;
}

static BOOL HasOwnerDraw(HMENU m)
{
    INT n = GetMenuItemCount(m);
    for (INT i = 0; i < n; i++) {
        MENUITEMINFOW mii = {sizeof(mii), MIIM_FTYPE};
        if (GetMenuItemInfoW(m, i, TRUE, &mii) && (mii.fType & MFT_OWNERDRAW)) return TRUE;
    }
    return FALSE;
}

// The nearest visible menu window of this thread made before (parent) or after (child) h.
struct RelativeFind { HWND self; ULONG_PTR seq; BOOL child; HWND best; ULONG_PTR bestSeq; };
static BOOL CALLBACK FindRelative(HWND h, LPARAM l)
{
    auto* f = reinterpret_cast<RelativeFind*>(l);
    if (h == f->self || !IsWindowVisible(h) || !IsPopupMenuWindow(h)) return TRUE;
    ULONG_PTR s = (ULONG_PTR)GetPropW(h, kSeqProp);
    if (!s) return TRUE;
    BOOL better = f->child ? (s > f->seq && (!f->best || s < f->bestSeq))
                           : (s < f->seq && (!f->best || s > f->bestSeq));
    if (better) { f->best = h; f->bestSeq = s; }
    return TRUE;
}
static HWND RelativeMenu(HWND h, BOOL child)
{
    RelativeFind f = {h, (ULONG_PTR)GetPropW(h, kSeqProp), child, nullptr, 0};
    if (!f.seq) return nullptr;
    EnumThreadWindows(GetCurrentThreadId(), FindRelative, reinterpret_cast<LPARAM>(&f));
    return f.best;
}

// Pull a submenu in so it touches its parent (never pushes it further away or off screen).
static VOID SnapToParent(HWND h, WINDOWPOS* wp)
{
    HWND parent = RelativeMenu(h, FALSE);
    RECT pr;
    if (!parent || !GetWindowRect(parent, &pr)) return;
    INT cx = wp->cx;
    if ((wp->flags & SWP_NOSIZE) || cx <= 0) {
        RECT r;
        if (!GetWindowRect(h, &r)) return;
        cx = r.right - r.left;
    }
    LONG mid = (pr.left + pr.right) / 2;
    if (wp->x >= mid) {
        if (pr.right < wp->x) wp->x = pr.right;
    } else if (wp->x + cx <= mid) {
        if (pr.left - cx > wp->x) wp->x = pr.left - cx;
    }
}

static BOOL InTriangle(POINT p, POINT a, POINT b, POINT c)
{
    auto side = [](POINT o, POINT u, POINT v) {
        return (LONGLONG)(u.x - o.x) * (v.y - o.y) - (LONGLONG)(u.y - o.y) * (v.x - o.x);
    };
    LONGLONG d1 = side(p, a, b), d2 = side(p, b, c), d3 = side(p, c, a);
    BOOL neg = d1 < 0 || d2 < 0 || d3 < 0, pos = d1 > 0 || d2 > 0 || d3 > 0;
    return !(neg && pos);
}

static VOID DropHeld()
{
    if (t_aimTimer) KillTimer(nullptr, t_aimTimer);
    t_aimTimer = 0;
    t_held = {};
}

// The pointer rested: let the last held move through, from where it stopped. The timer has no
// callback (a pending one could outlive the mod's unload); AimProc sees its WM_TIMER.
static VOID AimRelease()
{
    MSG m = t_held;
    DropHeld();
    if (m.hwnd && IsWindow(m.hwnd)) {
        t_apex = m.pt;
        PostMessageW(m.hwnd, m.message, m.wParam, m.lParam);
    }
}

// TRUE: hold this move, the pointer is on its way to the open submenu.
static BOOL HoldForSubmenu(const MSG* m)
{
    POINT p = m->pt;
    HWND under = WindowFromPoint(p);
    HWND sub = nullptr;
    if (under && IsPopupMenuWindow(under) && GetWindowThreadProcessId(under, nullptr) == GetCurrentThreadId())
        sub = RelativeMenu(under, TRUE);
    RECT sr, pr;
    if (!sub || !GetWindowRect(sub, &sr) || !GetWindowRect(under, &pr) || t_apex.x == LONG_MIN ||
        (p.x == t_apex.x && p.y == t_apex.y)) {
        DropHeld();
        t_apex = p;
        return FALSE;
    }
    LONG edge = sr.left >= (pr.left + pr.right) / 2 ? sr.left : sr.right;
    INT slack = MulDiv(6, DpiOf(under), USER_DEFAULT_SCREEN_DPI);
    POINT b = {edge, sr.top - slack}, c = {edge, sr.bottom + slack};
    if (!InTriangle(p, t_apex, b, c)) {
        DropHeld();
        t_apex = p;
        return FALSE;
    }
    if (!t_held.hwnd) t_holdStart = GetTickCount();
    else if (GetTickCount() - t_holdStart > kAimMaxMs) {
        DropHeld();
        t_apex = p;
        return FALSE;
    }
    t_held = *m;
    if (t_aimTimer) KillTimer(nullptr, t_aimTimer);
    t_aimTimer = SetTimer(nullptr, 0, kAimHoldMs, nullptr);
    if (!t_aimTimer) { t_held = {}; t_apex = p; return FALSE; }
    return TRUE;
}

static LRESULT CALLBACK AimProc(INT code, WPARAM w, LPARAM l)
{
    if (code == MSGF_MENU && l) {
        auto* m = reinterpret_cast<MSG*>(l);
        if (m->message == WM_TIMER && !m->hwnd && t_aimTimer && m->wParam == t_aimTimer) {
            AimRelease();
            return TRUE;
        }
        if (m->message == WM_MOUSEMOVE || m->message == WM_NCMOUSEMOVE) {
            if (HoldForSubmenu(m)) return TRUE;
        } else if ((m->message >= WM_LBUTTONDOWN && m->message <= WM_MBUTTONDBLCLK) ||
                   (m->message >= WM_NCLBUTTONDOWN && m->message <= WM_NCMBUTTONDBLCLK) ||
                   m->message == WM_KEYDOWN) {
            DropHeld();
            t_apex = {LONG_MIN, LONG_MIN};
        }
    }
    return CallNextHookEx(nullptr, code, w, l);
}

static LRESULT CALLBACK RoomProc(HWND h, UINT msg, WPARAM w, LPARAM l, UINT_PTR, DWORD_PTR)
{
    if (msg == WM_WINDOWPOSCHANGING && l) {
        auto* wp = reinterpret_cast<WINDOWPOS*>(l);
        // Grow only the size Windows asks for, never a size this proc already produced.
        if (!(wp->flags & SWP_NOSIZE) && wp->cx > 0 && wp->cy > 0 &&
            (DWORD)MAKELONG(wp->cx, wp->cy) != (DWORD)(ULONG_PTR)GetPropW(h, kSizeProp)) {
            HMENU m = (HMENU)SendMessageW(h, MN_GETHMENU, 0, 0);
            INT pad = (m && !HasOwnerDraw(m)) ? MulDiv(2, DpiOf(h), USER_DEFAULT_SCREEN_DPI) : 0;
            SetPropW(h, kPadProp, (HANDLE)(INT_PTR)pad);
            if (pad) {
                wp->cx += 2 * pad;
                wp->cy += 2 * pad;
                if (!(wp->flags & SWP_NOMOVE)) {
                    RECT r = {wp->x, wp->y, wp->x + wp->cx, wp->y + wp->cy};
                    MONITORINFO mi = {sizeof(mi)};
                    if (GetMonitorInfoW(MonitorFromRect(&r, MONITOR_DEFAULTTONEAREST), &mi)) {
                        if (r.right > mi.rcMonitor.right) wp->x = std::max(mi.rcMonitor.left, wp->x - (r.right - mi.rcMonitor.right));
                        if (r.bottom > mi.rcMonitor.bottom) wp->y = std::max(mi.rcMonitor.top, wp->y - (r.bottom - mi.rcMonitor.bottom));
                    }
                }
            }
            SetPropW(h, kSizeProp, (HANDLE)(ULONG_PTR)(DWORD)MAKELONG(wp->cx, wp->cy));
        }
        if (!(wp->flags & SWP_NOMOVE)) SnapToParent(h, wp);
    }
    if (msg == WM_NCDESTROY) {
        RemovePropW(h, kPadProp);
        RemovePropW(h, kSizeProp);
        RemovePropW(h, kSeqProp);
        RemoveWindowSubclass(h, RoomProc, kRoomId);
        return DefSubclassProc(h, msg, w, l);
    }
    LRESULT result = DefSubclassProc(h, msg, w, l);
    if (msg == WM_NCCALCSIZE && l) {
        INT pad = (INT)(INT_PTR)GetPropW(h, kPadProp);
        if (pad > 0) InflateRect(reinterpret_cast<RECT*>(l), -pad, -pad);
    }
    return result;
}

static VOID ResetRows()
{
    if (g_rowMargin.exchange(kRowMargin) != kRowMargin && g_flush) g_flush();
}

// Picks the largest row margin (6 down to 2) at which the whole menu fits its monitor.
static VOID FitMenu(HMENU m, HWND owner)
{
    if (!m || !g_flush || HasOwnerDraw(m)) return;
    INT rows = 0, seps = 0, n = GetMenuItemCount(m);
    for (INT i = 0; i < n; i++) {
        MENUITEMINFOW mii = {sizeof(mii), MIIM_FTYPE};
        if (!GetMenuItemInfoW(m, i, TRUE, &mii)) continue;
        (mii.fType & MFT_SEPARATOR) ? seps++ : rows++;
    }
    MONITORINFO mi = {sizeof(mi)};
    if (!rows || !GetMonitorInfoW(MonitorFromWindow(owner, MONITOR_DEFAULTTONEAREST), &mi)) return;
    UINT dpi = DpiOf(owner);
    auto px = [dpi](INT v) { return MulDiv(v, dpi, USER_DEFAULT_SCREEN_DPI); };
    INT avail = mi.rcWork.bottom - mi.rcWork.top - px(8);
    INT pick = kRowMargin;
    for (; pick > kMinRowMargin; pick--) {
        INT cut = px(2 * (kRowMargin - pick));   // rows measure 29 px and separators 17 px at margin 6
        if (rows * (px(29) - cut) + seps * (px(17) - cut) + px(10) <= avail) break;
    }
    if (pick < g_rowMargin.load()) {
        g_rowMargin = pick;
        g_flush();
    }
}

static LRESULT CALLBACK LoopProc(INT code, WPARAM w, LPARAM l)
{
    if (code == HC_ACTION && l) {
        auto* c = reinterpret_cast<CWPSTRUCT*>(l);
        if (c->message == WM_INITMENUPOPUP) FitMenu((HMENU)c->wParam, c->hwnd);
        else if (c->message == WM_EXITMENULOOP) ResetRows();
    }
    return CallNextHookEx(nullptr, code, w, l);
}
// Every live loop hook, so Uninit can remove the ones other threads still hold.
static std::mutex g_hooksLock;
static std::vector<HHOOK> g_hooks;
static VOID SyncLoopHook()
{
    BOOL want = t_trackDepth > 0 || t_menuMode;
    if (want && !t_loopHook) {
        t_loopHook = SetWindowsHookExW(WH_CALLWNDPROC, LoopProc, nullptr, GetCurrentThreadId());
        if (t_loopHook) { std::lock_guard<std::mutex> g(g_hooksLock); g_hooks.push_back(t_loopHook); }
    } else if (!want && t_loopHook) {
        {
            std::lock_guard<std::mutex> g(g_hooksLock);
            auto it = std::find(g_hooks.begin(), g_hooks.end(), t_loopHook);
            if (it != g_hooks.end()) { g_hooks.erase(it); UnhookWindowsHookEx(t_loopHook); }
        }
        t_loopHook = nullptr;
        ResetRows();
    }
    if (want && !t_aimHook) {
        t_apex = {LONG_MIN, LONG_MIN};
        t_aimHook = SetWindowsHookExW(WH_MSGFILTER, AimProc, nullptr, GetCurrentThreadId());
        if (t_aimHook) { std::lock_guard<std::mutex> g(g_hooksLock); g_hooks.push_back(t_aimHook); }
    } else if (!want && t_aimHook) {
        {
            std::lock_guard<std::mutex> g(g_hooksLock);
            auto it = std::find(g_hooks.begin(), g_hooks.end(), t_aimHook);
            if (it != g_hooks.end()) { g_hooks.erase(it); UnhookWindowsHookEx(t_aimHook); }
        }
        t_aimHook = nullptr;
        DropHeld();
    }
}

// Wrap TrackPopupMenu(Ex) with these (menu-bar menus are covered by the menu events).
static VOID BeginTrack() { t_trackDepth++; SyncLoopHook(); }
static VOID EndTrack() { if (t_trackDepth > 0) t_trackDepth--; SyncLoopHook(); }

static VOID CALLBACK OnEvent(HWINEVENTHOOK, DWORD ev, HWND h, LONG obj, LONG child, DWORD, DWORD)
{
    if (ev == EVENT_OBJECT_CREATE) {
        if (obj != OBJID_WINDOW || child != CHILDID_SELF || !IsPopupMenuWindow(h) ||
            GetWindowThreadProcessId(h, nullptr) != GetCurrentThreadId())
            return;
        SetPropW(h, kSeqProp, (HANDLE)(ULONG_PTR)++g_seq);
        if (g_onCreate) g_onCreate(h);
        SetWindowSubclass(h, RoomProc, kRoomId, 0);
    } else if (ev == EVENT_SYSTEM_MENUSTART) {
        t_menuMode = TRUE;
        SyncLoopHook();
    } else if (ev == EVENT_SYSTEM_MENUEND) {
        t_menuMode = FALSE;
        SyncLoopHook();
    }
}

// onCreate (optional) runs for each new popup menu window, on its own thread, after creation.
static VOID Init(VOID (*onCreate)(HWND))
{
    g_onCreate = onCreate;
    HMODULE ux = GetModuleHandleW(L"uxtheme.dll");
    if (!ux) ux = LoadLibraryExW(L"uxtheme.dll", nullptr, LOAD_LIBRARY_SEARCH_SYSTEM32);
    g_flush = ux ? (Flush_t)GetProcAddress(ux, MAKEINTRESOURCEA(136)) : nullptr;
    HMODULE self = nullptr;
    GetModuleHandleExW(GET_MODULE_HANDLE_EX_FLAG_FROM_ADDRESS | GET_MODULE_HANDLE_EX_FLAG_UNCHANGED_REFCOUNT,
                       reinterpret_cast<LPCWSTR>(&OnEvent), &self);
    DWORD pid = GetCurrentProcessId();
    g_createHook = SetWinEventHook(EVENT_OBJECT_CREATE, EVENT_OBJECT_CREATE, self, OnEvent, pid, 0, WINEVENT_INCONTEXT);
    g_menuHook = SetWinEventHook(EVENT_SYSTEM_MENUSTART, EVENT_SYSTEM_MENUEND, self, OnEvent, pid, 0, WINEVENT_INCONTEXT);
}

static VOID Uninit()
{
    for (HWINEVENTHOOK* hk : {&g_createHook, &g_menuHook})
        if (*hk) { UnhookWinEvent(*hk); *hk = nullptr; }
    {
        std::lock_guard<std::mutex> g(g_hooksLock);
        for (HHOOK hk : g_hooks) UnhookWindowsHookEx(hk);
        g_hooks.clear();
    }
    ResetRows();
}

}  // namespace SeamlessMenuRoom
// ---------------------------------------------------------------------------------------------

// ---------------------------------------------------------------------------------------------
// Seamless menu look for this mod's own menus.
// Windhawk runs tool mods in their own process, where Seamless Flyouts cannot reach, so the
// menus this mod shows get the same look here: blurred Catppuccin Mocha body, rounded corners,
// roomy rows, separators that run to the border, the blue to mauve hover pill, and
// submenus that open beside their parent with a small gap. Only this process is touched.
// ---------------------------------------------------------------------------------------------
#include <d2d1.h>
#include <dwmapi.h>
#include <uxtheme.h>
#include <vssym32.h>
#include <commctrl.h>

// ---------------------------------------------------------------------------------------------
// Menu pill: the one hover look for every menu row, the same pill Seamless Clipboard Manager
// draws: a soft blue to mauve fill (16 %) and a 1 px blue to mauve ring (80 %), radius 8.
// Drawn at the row's real size each time, because a stretched nine-grid can't hold a gradient.
// ---------------------------------------------------------------------------------------------
namespace SeamlessMenuPill {

static BOOL Draw(ID2D1Factory* factory, HDC hdc, const RECT& r, UINT dpi)
{
    INT w = r.right - r.left, h = r.bottom - r.top;
    if (!factory || !hdc || w <= 2 || h <= 2) return FALSE;
    HDC dc = CreateCompatibleDC(hdc);
    if (!dc) return FALSE;
    BITMAPINFO bmi = {};
    bmi.bmiHeader = {sizeof(BITMAPINFOHEADER), w, -h, 1, 32, BI_RGB};
    VOID* bits = nullptr;
    HBITMAP bmp = CreateDIBSection(dc, &bmi, DIB_RGB_COLORS, &bits, nullptr, 0);
    if (!bmp) { DeleteDC(dc); return FALSE; }
    HGDIOBJ old = SelectObject(dc, bmp);
    auto props = D2D1::RenderTargetProperties(D2D1_RENDER_TARGET_TYPE_SOFTWARE,
        D2D1::PixelFormat(DXGI_FORMAT_B8G8R8A8_UNORM, D2D1_ALPHA_MODE_PREMULTIPLIED), 0, 0,
        D2D1_RENDER_TARGET_USAGE_GDI_COMPATIBLE, D2D1_FEATURE_LEVEL_DEFAULT);
    ID2D1DCRenderTarget* rt = nullptr;
    RECT rc = {0, 0, w, h};
    BOOL ok = FALSE;
    if (SUCCEEDED(factory->CreateDCRenderTarget(&props, &rt)) && SUCCEEDED(rt->BindDC(dc, &rc))) {
        FLOAT s = (dpi ? dpi : USER_DEFAULT_SCREEN_DPI) / (FLOAT)USER_DEFAULT_SCREEN_DPI;
        FLOAT ringW = s < 1.5f ? 1.f : 2.f;
        FLOAT rad = std::min(8.f * s, std::min((FLOAT)w, (FLOAT)h) / 2.f);
        D2D1_ROUNDED_RECT rr = {{ringW / 2, ringW / 2, w - ringW / 2, h - ringW / 2}, rad, rad};
        auto gradient = [&](FLOAT a) {
            ID2D1LinearGradientBrush* brush = nullptr;
            ID2D1GradientStopCollection* stops = nullptr;
            D2D1_GRADIENT_STOP st[2] = {{0.f, {137 / 255.f, 180 / 255.f, 250 / 255.f, a}},
                                        {1.f, {203 / 255.f, 166 / 255.f, 247 / 255.f, a}}};
            if (SUCCEEDED(rt->CreateGradientStopCollection(st, 2, &stops)))
                rt->CreateLinearGradientBrush(D2D1::LinearGradientBrushProperties({0, 0}, {(FLOAT)w, (FLOAT)h}),
                                              stops, &brush);
            if (stops) stops->Release();
            return brush;
        };
        rt->BeginDraw();
        rt->Clear({0, 0, 0, 0});
        ID2D1LinearGradientBrush* fill = gradient(0.16f);
        ID2D1LinearGradientBrush* ring = gradient(0.8f);
        if (fill) rt->FillRoundedRectangle(&rr, fill);
        if (ring) rt->DrawRoundedRectangle(&rr, ring, ringW);
        ok = SUCCEEDED(rt->EndDraw()) && fill && ring;
        if (fill) fill->Release();
        if (ring) ring->Release();
    }
    if (rt) rt->Release();
    if (ok) {
        BLENDFUNCTION bf = {AC_SRC_OVER, 0, 255, AC_SRC_ALPHA};
        ok = GdiAlphaBlend(hdc, r.left, r.top, w, h, dc, 0, 0, w, h, bf);
    }
    SelectObject(dc, old);
    DeleteObject(bmp);
    DeleteDC(dc);
    return ok;
}

}  // namespace SeamlessMenuPill

namespace SeamlessMenuSkin {

constexpr COLORREF kMenuTint = 0xA01B1111;        // Seamless Flyouts "MenuBlur" A011111B
constexpr UINT_PTR kSubclassId = 0x6D54;
constexpr UINT kAccentAcrylic = 4, kWcaAccentPolicy = 19;

struct AccentPolicy { DWORD state, flags, color, animation; };
struct CompositionData { DWORD attrib; PVOID data; SIZE_T size; };
using SetWca_t = BOOL(WINAPI*)(HWND, CompositionData*);
using GetThemeClass_t = HRESULT(WINAPI*)(HTHEME, LPWSTR, INT);

static ID2D1Factory* g_factory = nullptr;
static HDC g_hoverDC = nullptr, g_sepDC = nullptr;
static UINT g_edgesMsg = 0;

static decltype(&DrawThemeBackground) DrawThemeBackground_orig = nullptr;
static decltype(&DrawThemeBackgroundEx) DrawThemeBackgroundEx_orig = nullptr;
static decltype(&GetThemeColor) GetThemeColor_orig = nullptr;
static decltype(&GetThemeMargins) GetThemeMargins_orig = nullptr;
static decltype(&GetThemeFont) GetThemeFont_orig = nullptr;
static decltype(&DwmSetWindowAttribute) DwmSetWindowAttribute_orig = nullptr;
static decltype(&TrackPopupMenu) TrackPopupMenu_orig = nullptr;
static decltype(&TrackPopupMenuEx) TrackPopupMenuEx_orig = nullptr;

static UINT Dpi() { UINT d = GetDpiForSystem(); return d ? d : USER_DEFAULT_SCREEN_DPI; }

static BOOL IsMenuWindow(HWND hWnd)
{
    WCHAR cls[16];
    return hWnd && GetClassNameW(hWnd, cls, ARRAYSIZE(cls)) && wcscmp(cls, L"#32768") == 0;
}

static BOOL IsMenuTheme(HTHEME hTheme)
{
    static auto getClass = (GetThemeClass_t)GetProcAddress(GetModuleHandleW(L"uxtheme.dll"), MAKEINTRESOURCEA(74));
    WCHAR buf[64] = {};
    return getClass && SUCCEEDED(getClass(hTheme, buf, ARRAYSIZE(buf))) && wcscmp(buf, L"Menu") == 0;
}

static D2D1_COLOR_F Argb(BYTE a, BYTE r, BYTE g, BYTE b) { return {r / 255.f, g / 255.f, b / 255.f, a / 255.f}; }

// A small premultiplied 32-bit bitmap drawn once with Direct2D and stretched as a nine-grid.
static HDC MakeCache(INT w, INT h, BOOL separator)
{
    if (!g_factory) return nullptr;
    HDC dc = CreateCompatibleDC(nullptr);
    if (!dc) return nullptr;
    BITMAPINFO bmi = {};
    bmi.bmiHeader = {sizeof(BITMAPINFOHEADER), w, -h, 1, 32, BI_RGB};
    VOID* bits = nullptr;
    HBITMAP bmp = CreateDIBSection(dc, &bmi, DIB_RGB_COLORS, &bits, nullptr, 0);
    if (!bmp) { DeleteDC(dc); return nullptr; }
    SelectObject(dc, bmp);
    auto props = D2D1::RenderTargetProperties(D2D1_RENDER_TARGET_TYPE_SOFTWARE,
        D2D1::PixelFormat(DXGI_FORMAT_B8G8R8A8_UNORM, D2D1_ALPHA_MODE_PREMULTIPLIED), 0, 0,
        D2D1_RENDER_TARGET_USAGE_GDI_COMPATIBLE, D2D1_FEATURE_LEVEL_DEFAULT);
    ID2D1DCRenderTarget* rt = nullptr;
    RECT rc = {0, 0, w, h};
    if (FAILED(g_factory->CreateDCRenderTarget(&props, &rt)) || FAILED(rt->BindDC(dc, &rc))) {
        if (rt) rt->Release();
        DeleteDC(dc); DeleteObject(bmp);
        return nullptr;
    }
    ID2D1SolidColorBrush *a = nullptr, *b = nullptr;
    rt->BeginDraw();
    if (separator) {
        rt->CreateSolidColorBrush(Argb(255, 69, 71, 90), &a);
        if (a) rt->DrawLine({0, h / 2.f}, {(FLOAT)w, h / 2.f}, a);
    } else {
        auto r = D2D1::RoundedRect(D2D1::RectF(0.5f, 0.5f, w - 0.5f, h - 0.5f), 6.f, 6.f);
        rt->CreateSolidColorBrush(Argb(190, 69, 71, 90), &a);
        rt->CreateSolidColorBrush(Argb(255, 137, 180, 250), &b);
        if (a) rt->FillRoundedRectangle(&r, a);
        if (b) rt->DrawRoundedRectangle(&r, b, 1.f);
    }
    HRESULT hr = rt->EndDraw();
    if (a) a->Release();
    if (b) b->Release();
    rt->Release();
    if (FAILED(hr)) { DeleteDC(dc); DeleteObject(bmp); return nullptr; }
    return dc;
}

static VOID Blend(HDC dst, INT x, INT y, INT w, INT h, HDC src, INT sx, INT sy, INT sw, INT sh)
{
    if (w <= 0 || h <= 0 || sw <= 0 || sh <= 0) return;
    BLENDFUNCTION bf = {AC_SRC_OVER, 0, 255, AC_SRC_ALPHA};
    GdiAlphaBlend(dst, x, y, w, h, src, sx, sy, sw, sh, bf);
}

static VOID NineGrid(HDC hdc, HDC src, const RECT* d, INT l, INT t, INT r, INT b)
{
    BITMAP bm = {};
    GetObject(GetCurrentObject(src, OBJ_BITMAP), sizeof(bm), &bm);
    INT sw = bm.bmWidth, sh = bm.bmHeight, dw = d->right - d->left, dh = d->bottom - d->top;
    l = std::min(l, dw); r = std::min(r, dw - l); t = std::min(t, dh); b = std::min(b, dh - t);
    if (l + r >= sw || t + b >= sh) { Blend(hdc, d->left, d->top, dw, dh, src, 0, 0, sw, sh); return; }
    INT cw = dw - l - r, ch = dh - t - b, scw = sw - l - r, sch = sh - t - b;
    Blend(hdc, d->left + l, d->top + t, cw, ch, src, l, t, scw, sch);
    Blend(hdc, d->left, d->top, l, t, src, 0, 0, l, t);
    Blend(hdc, d->left + l, d->top, cw, t, src, l, 0, scw, t);
    Blend(hdc, d->right - r, d->top, r, t, src, sw - r, 0, r, t);
    Blend(hdc, d->left, d->top + t, l, ch, src, 0, t, l, sch);
    Blend(hdc, d->right - r, d->top + t, r, ch, src, sw - r, t, r, sch);
    Blend(hdc, d->left, d->bottom - b, l, b, src, 0, sh - b, l, b);
    Blend(hdc, d->left + l, d->bottom - b, cw, b, src, l, sh - b, scw, b);
    Blend(hdc, d->right - r, d->bottom - b, r, b, src, sw - r, sh - b, r, b);
}

static VOID ApplyEffects(HWND hWnd)
{
    static auto setWca = (SetWca_t)GetProcAddress(GetModuleHandleW(L"user32.dll"), "SetWindowCompositionAttribute");
    BOOL dark = TRUE;
    DwmSetWindowAttribute(hWnd, DWMWA_USE_IMMERSIVE_DARK_MODE, &dark, sizeof(dark));
    DWM_BLURBEHIND bb = {DWM_BB_ENABLE | DWM_BB_BLURREGION | DWM_BB_TRANSITIONONMAXIMIZED, TRUE, CreateRectRgn(0, 0, -1, -1), TRUE};
    DwmEnableBlurBehindWindow(hWnd, &bb);
    DeleteObject(bb.hRgnBlur);
    AccentPolicy ap = {kAccentAcrylic, 0, kMenuTint, 0};
    CompositionData data = {kWcaAccentPolicy, &ap, sizeof(ap)};
    if (setWca) setWca(hWnd, &data);
    UINT corner = DWMWCP_ROUND;
    DwmSetWindowAttribute(hWnd, DWMWA_WINDOW_CORNER_PREFERENCE, &corner, sizeof(corner));
}

// Separator lines stop at the client edge; copy each one across the thin menu frame so it
// meets the border.
static BOOL IsSeparatorPixel(COLORREF c)
{
    return abs(GetRValue(c) - 69) <= 8 && abs(GetGValue(c) - 71) <= 8 && abs(GetBValue(c) - 90) <= 8;
}
static VOID PaintSeparatorEdges(HWND hWnd)
{
    if (!g_sepDC || !IsWindowVisible(hWnd)) return;
    HMENU hMenu = (HMENU)SendMessageW(hWnd, MN_GETHMENU, 0, 0);
    if (!hMenu) return;
    RECT wr, cr;
    GetWindowRect(hWnd, &wr);
    GetClientRect(hWnd, &cr);
    POINT org = {0, 0};
    ClientToScreen(hWnd, &org);
    INT cl = org.x - wr.left, cw = cr.right, winW = wr.right - wr.left;
    if (cl <= 0 || cw <= 0) return;
    HDC wdc = GetWindowDC(hWnd);
    if (!wdc) return;
    INT count = GetMenuItemCount(hMenu);
    for (INT i = 0; i < count; i++) {
        MENUITEMINFOW mii = {sizeof(mii), MIIM_FTYPE};
        if (!GetMenuItemInfoW(hMenu, i, TRUE, &mii) || !(mii.fType & MFT_SEPARATOR)) continue;
        RECT ir;
        if (!GetMenuItemRect(hWnd, hMenu, i, &ir)) continue;
        for (INT y = ir.top - wr.top; y < ir.bottom - wr.top; y++) {
            if (!IsSeparatorPixel(GetPixel(wdc, cl, y)) || !IsSeparatorPixel(GetPixel(wdc, cl + cw - 1, y))) continue;
            RECT left = {0, y - 2, cl, y + 3}, right = {cl + cw, y - 2, winW, y + 3};
            NineGrid(wdc, g_sepDC, &left, 0, 5, 0, 0);
            NineGrid(wdc, g_sepDC, &right, 0, 5, 0, 0);
        }
    }
    ReleaseDC(hWnd, wdc);
}

struct ParentSearch { HWND self; RECT r; HWND parent; RECT pr; BOOL right; };
static BOOL CALLBACK FindParent(HWND hWnd, LPARAM lParam)
{
    auto* f = reinterpret_cast<ParentSearch*>(lParam);
    if (hWnd == f->self || !IsWindowVisible(hWnd) || !IsMenuWindow(hWnd)) return TRUE;
    RECT p;
    GetWindowRect(hWnd, &p);
    if (f->r.top >= p.bottom || f->r.bottom <= p.top) return TRUE;
    BOOL right = f->r.left > p.left && f->r.left < p.right + 2 && f->r.right > p.right;
    BOOL left = f->r.right < p.right && f->r.right > p.left - 2 && f->r.left < p.left;
    if (!right && !left) return TRUE;
    f->parent = hWnd; f->pr = p; f->right = right;
    return FALSE;
}
// Submenus open over the parent's edge; move them beside it with an 8 px gap.
static VOID PlaceSubmenu(HWND hWnd, WINDOWPOS* wp)
{
    RECT cur;
    GetWindowRect(hWnd, &cur);
    INT w = (wp->flags & SWP_NOSIZE) ? cur.right - cur.left : wp->cx;
    INT h = (wp->flags & SWP_NOSIZE) ? cur.bottom - cur.top : wp->cy;
    if (w <= 0 || h <= 0) return;
    ParentSearch f = {hWnd, {wp->x, wp->y, wp->x + w, wp->y + h}, nullptr, {}, FALSE};
    EnumThreadWindows(GetCurrentThreadId(), FindParent, reinterpret_cast<LPARAM>(&f));
    if (!f.parent) return;
    UINT dpi = GetDpiForWindow(hWnd);
    INT gap = MulDiv(8, dpi ? dpi : Dpi(), USER_DEFAULT_SCREEN_DPI);
    MONITORINFO mi = {sizeof(mi)};
    if (!GetMonitorInfoW(MonitorFromRect(&f.pr, MONITOR_DEFAULTTONEAREST), &mi)) return;
    INT toRight = f.pr.right + gap, toLeft = f.pr.left - gap - w;
    if (f.right)
        wp->x = (toRight + w <= mi.rcWork.right) ? toRight : (toLeft >= mi.rcWork.left ? toLeft : wp->x);
    else
        wp->x = (toLeft >= mi.rcWork.left) ? toLeft : (toRight + w <= mi.rcWork.right ? toRight : wp->x);
}

static LRESULT CALLBACK MenuProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam, UINT_PTR, DWORD_PTR)
{
    if (msg == g_edgesMsg && g_edgesMsg) { PaintSeparatorEdges(hWnd); return 0; }
    if (msg == WM_TIMER && wParam == kSubclassId) {
        KillTimer(hWnd, kSubclassId);
        PaintSeparatorEdges(hWnd);
        return 0;
    }
    if (msg == WM_NCDESTROY) {
        KillTimer(hWnd, kSubclassId);
        RemoveWindowSubclass(hWnd, MenuProc, kSubclassId);
        return DefSubclassProc(hWnd, msg, wParam, lParam);
    }
    if (msg == WM_WINDOWPOSCHANGING && lParam && !(reinterpret_cast<WINDOWPOS*>(lParam)->flags & SWP_NOMOVE))
        PlaceSubmenu(hWnd, reinterpret_cast<WINDOWPOS*>(lParam));
    if (msg == WM_NCPAINT)
        ApplyEffects(hWnd);
    LRESULT result = DefSubclassProc(hWnd, msg, wParam, lParam);
    if (msg == WM_CREATE)
        ApplyEffects(hWnd);
    if (msg == WM_NCPAINT || msg == WM_PAINT)
        PostMessageW(hWnd, g_edgesMsg, 0, 0);
    if (msg == WM_WINDOWPOSCHANGED && lParam && (reinterpret_cast<WINDOWPOS*>(lParam)->flags & SWP_SHOWWINDOW)) {
        PostMessageW(hWnd, g_edgesMsg, 0, 0);
        SetTimer(hWnd, kSubclassId, 150, nullptr);
    }
    return result;
}

// Every popup menu window of this process, title bar menus included (those never pass
// through TrackPopupMenu, so they used to keep a black, unblurred body).
static VOID OnMenuCreated(HWND hWnd)
{
    // The CBT hook and the create-event hook can both reach this window.
    static const WCHAR* const kSkinProp = L"SeamlessMenuSkinAttached";
    if (GetPropW(hWnd, kSkinProp)) return;
    SetPropW(hWnd, kSkinProp, (HANDLE)1);
    SetWindowSubclass(hWnd, MenuProc, kSubclassId, 0);
    ApplyEffects(hWnd);
}

// Delivered synchronously on this thread during the menu window's creation, before
// its first paint, so the black body never shows without the acrylic behind it.
static LRESULT CALLBACK MenuCbtProc(INT code, WPARAM w, LPARAM l)
{
    if (code == HCBT_CREATEWND) {
        HWND created = reinterpret_cast<HWND>(w);
        WCHAR cls[16];
        if (GetClassNameW(created, cls, ARRAYSIZE(cls)) &&
            wcscmp(cls, L"#32768") == 0)
            OnMenuCreated(created);
    }
    return CallNextHookEx(nullptr, code, w, l);
}
static HHOOK InstallMenuCbtHook()
{
    return SetWindowsHookExW(WH_CBT, MenuCbtProc, nullptr, GetCurrentThreadId());
}

static BOOL WINAPI TrackPopupMenu_hook(HMENU m, UINT f, INT x, INT y, INT r, HWND h, const RECT* rc)
{
    SeamlessMenuRoom::BeginTrack();
    HHOOK cbt = InstallMenuCbtHook();
    BOOL ret = TrackPopupMenu_orig(m, f, x, y, r, h, rc);
    if (cbt) UnhookWindowsHookEx(cbt);
    SeamlessMenuRoom::EndTrack();
    return ret;
}
static BOOL WINAPI TrackPopupMenuEx_hook(HMENU m, UINT f, INT x, INT y, HWND h, LPTPMPARAMS p)
{
    SeamlessMenuRoom::BeginTrack();
    HHOOK cbt = InstallMenuCbtHook();
    BOOL ret = TrackPopupMenuEx_orig(m, f, x, y, h, p);
    if (cbt) UnhookWindowsHookEx(cbt);
    SeamlessMenuRoom::EndTrack();
    return ret;
}
// Title bar menus are opened by DefWindowProc, never through TrackPopupMenu: wrap the
// messages that open one the same way, so the menu is skinned before its first paint.
static decltype(&DefWindowProcW) SysMenuDefProc_orig = nullptr;
static LRESULT WINAPI SysMenuDefProc_hook(HWND h, UINT msg, WPARAM w, LPARAM l)
{
    UINT sc = (UINT)(w & 0xFFF0);
    bool opens = (msg == WM_SYSCOMMAND && (sc == SC_KEYMENU || sc == SC_MOUSEMENU)) ||
                 msg == WM_CONTEXTMENU || msg == 0x0313 /* WM_POPUPSYSTEMMENU */;
    if (!opens) return SysMenuDefProc_orig(h, msg, w, l);
    SeamlessMenuRoom::BeginTrack();
    HHOOK cbt = InstallMenuCbtHook();
    LRESULT ret = SysMenuDefProc_orig(h, msg, w, l);
    if (cbt) UnhookWindowsHookEx(cbt);
    SeamlessMenuRoom::EndTrack();
    return ret;
}

// Returns TRUE when the menu part was drawn here.
static BOOL PaintMenuPart(HDC hdc, INT part, INT state, LPCRECT pRect, LPCRECT pClip)
{
    if (part == 26) { part = 27; state = 2; }                   // keyboard focus: same hover
    if ((part == 27 || part == MENU_POPUPITEM) && state == 2) {
        // Keep the same gap above and below as at the sides, so the first and last rows'
        // rounded hover stays clear of the menu's own rounded corners.
        RECT rc = *pRect;
        InflateRect(&rc, 0, -MulDiv(2, Dpi(), USER_DEFAULT_SCREEN_DPI));
        return SeamlessMenuPill::Draw(g_factory, hdc, rc, Dpi());
    }
    if (part == MENU_POPUPSEPARATOR) {
        if (!g_sepDC) g_sepDC = MakeCache(1, 5, TRUE);
        if (!g_sepDC) return FALSE;
        RECT rc = *pRect;
        INT reach = MulDiv(64, Dpi(), USER_DEFAULT_SCREEN_DPI);
        rc.left -= reach; rc.right += reach;
        NineGrid(hdc, g_sepDC, &rc, 1, 5, 0, 0);
        return TRUE;
    }
    if (part == MENU_POPUPBACKGROUND || part == MENU_POPUPBORDERS || part == MENU_POPUPGUTTER ||
        part == MENU_POPUPCHECKBACKGROUND || part == 27 || part == MENU_POPUPITEM) {
        RECT rc = *pRect;
        if (pClip) IntersectRect(&rc, pRect, pClip);
        FillRect(hdc, &rc, (HBRUSH)GetStockObject(BLACK_BRUSH));   // clear: the blur shows through
        return TRUE;
    }
    return FALSE;
}

static HRESULT WINAPI DrawThemeBackground_hook(HTHEME t, HDC hdc, INT part, INT state, LPCRECT r, LPCRECT clip)
{
    if (r && IsMenuTheme(t) && PaintMenuPart(hdc, part, state, r, clip)) return S_OK;
    return DrawThemeBackground_orig(t, hdc, part, state, r, clip);
}
static HRESULT WINAPI DrawThemeBackgroundEx_hook(HTHEME t, HDC hdc, INT part, INT state, LPCRECT r, const DTBGOPTS* o)
{
    LPCRECT clip = (o && (o->dwFlags & DTBG_CLIPRECT)) ? &o->rcClip : nullptr;
    if (r && IsMenuTheme(t) && PaintMenuPart(hdc, part, state, r, clip)) return S_OK;
    return DrawThemeBackgroundEx_orig(t, hdc, part, state, r, o);
}
static HRESULT WINAPI GetThemeColor_hook(HTHEME t, INT part, INT state, INT prop, COLORREF* c)
{
    HRESULT hr = GetThemeColor_orig(t, part, state, prop, c);
    if (!c || !IsMenuTheme(t)) return hr;
    if (prop == TMT_TEXTCOLOR && (part == MENU_POPUPITEM || part == 27) && state != 3 && state != 4) {
        *c = RGB(205, 214, 244);
        return S_OK;
    }
    if (prop == TMT_FILLCOLOR || prop == TMT_FILLCOLORHINT) { *c = RGB(0, 0, 0); return S_OK; }
    return hr;
}
static HRESULT WINAPI GetThemeMargins_hook(HTHEME t, HDC hdc, INT part, INT state, INT prop, LPRECT prc, MARGINS* m)
{
    HRESULT hr = GetThemeMargins_orig(t, hdc, part, state, prop, prc, m);
    if (m && IsMenuTheme(t) && (part == MENU_POPUPITEM || part == 27 || part == 26)) {
        if (prop == TMT_CONTENTMARGINS) *m = {2, 2, 8, 8};
        else if (prop == TMT_SIZINGMARGINS) *m = {10, 10, 10, 10};
        else if (prop == 10000) *m = {0, 0, SeamlessMenuRoom::RowMargin(), SeamlessMenuRoom::RowMargin()};
    }
    return hr;
}
static HRESULT WINAPI GetThemeFont_hook(HTHEME t, HDC hdc, INT part, INT state, INT prop, LOGFONTW* f)
{
    HRESULT hr = GetThemeFont_orig(t, hdc, part, state, prop, f);
    if (SUCCEEDED(hr) && f && prop == TMT_FONT && IsMenuTheme(t) && wcscmp(f->lfFaceName, L"Segoe UI") == 0) {
        wcscpy_s(f->lfFaceName, LF_FACESIZE, L"FiraCode Nerd Font Med");
        f->lfHeight = -MulDiv(14, Dpi(), USER_DEFAULT_SCREEN_DPI);
        f->lfWeight = 500;
        f->lfQuality = CLEARTYPE_QUALITY;
        f->lfPitchAndFamily = DEFAULT_PITCH;
    }
    return hr;
}
static HRESULT WINAPI DwmSetWindowAttribute_hook(HWND h, DWORD attr, LPCVOID v, DWORD cb)
{
    if (attr == DWMWA_WINDOW_CORNER_PREFERENCE && IsMenuWindow(h)) {
        UINT corner = DWMWCP_ROUND;
        return DwmSetWindowAttribute_orig(h, attr, &corner, sizeof(corner));
    }
    return DwmSetWindowAttribute_orig(h, attr, v, cb);
}

template <typename T>
static VOID Hook(HMODULE mod, LPCSTR name, T hook, T* orig)
{
    if (auto p = mod ? GetProcAddress(mod, name) : nullptr)
        Wh_SetFunctionHook((void*)p, (void*)hook, (void**)orig);
}

// Call from the mod's init, before it returns (hooks are applied when init finishes).
static VOID Init()
{
    D2D1CreateFactory(D2D1_FACTORY_TYPE_MULTI_THREADED, __uuidof(ID2D1Factory), nullptr, (void**)&g_factory);
    g_edgesMsg = RegisterWindowMessageW(L"SeamlessFlyouts_MenuSeparatorEdges");
    HMODULE ux = LoadLibraryExW(L"uxtheme.dll", nullptr, LOAD_LIBRARY_SEARCH_SYSTEM32);
    HMODULE dwm = LoadLibraryExW(L"dwmapi.dll", nullptr, LOAD_LIBRARY_SEARCH_SYSTEM32);
    HMODULE u32 = GetModuleHandleW(L"user32.dll");
    // Dark menus in this process (SetPreferredAppMode ForceDark, then FlushMenuThemes).
    using SetMode_t = INT(WINAPI*)(INT);
    using Flush_t = VOID(WINAPI*)();
    if (auto setMode = ux ? (SetMode_t)GetProcAddress(ux, MAKEINTRESOURCEA(135)) : nullptr) setMode(2);
    if (auto flush = ux ? (Flush_t)GetProcAddress(ux, MAKEINTRESOURCEA(136)) : nullptr) flush();
    Hook(ux, "DrawThemeBackground", DrawThemeBackground_hook, &DrawThemeBackground_orig);
    Hook(ux, "DrawThemeBackgroundEx", DrawThemeBackgroundEx_hook, &DrawThemeBackgroundEx_orig);
    Hook(ux, "GetThemeColor", GetThemeColor_hook, &GetThemeColor_orig);
    Hook(ux, "GetThemeMargins", GetThemeMargins_hook, &GetThemeMargins_orig);
    Hook(ux, "GetThemeFont", GetThemeFont_hook, &GetThemeFont_orig);
    Hook(dwm, "DwmSetWindowAttribute", DwmSetWindowAttribute_hook, &DwmSetWindowAttribute_orig);
    Hook(u32, "TrackPopupMenu", TrackPopupMenu_hook, &TrackPopupMenu_orig);
    Hook(u32, "TrackPopupMenuEx", TrackPopupMenuEx_hook, &TrackPopupMenuEx_orig);
    Hook(u32, "DefWindowProcW", SysMenuDefProc_hook, &SysMenuDefProc_orig);
    SeamlessMenuRoom::Init(OnMenuCreated);
}

static VOID Uninit()
{
    SeamlessMenuRoom::Uninit();
    for (HDC* dc : {&g_hoverDC, &g_sepDC})
        if (*dc) {
            HGDIOBJ bmp = GetCurrentObject(*dc, OBJ_BITMAP);
            DeleteDC(*dc);
            DeleteObject(bmp);
            *dc = nullptr;
        }
    if (g_factory) { g_factory->Release(); g_factory = nullptr; }
}

}  // namespace SeamlessMenuSkin

BOOL WhTool_ModInit() {
    SeamlessMenuSkin::Init();
    LoadSettings();
    g_presetOverride = Wh_GetIntValue(L"presetOverride", 0) - 1;
    g_uiReady = CreateEventW(nullptr, TRUE, FALSE, nullptr);
    g_uiThread = CreateThread(nullptr, 0, UiThreadProc, nullptr, 0, &g_uiThreadId);
    if (!g_uiThread) {
        if (g_uiReady) CloseHandle(g_uiReady);
        g_uiReady = nullptr;
        return FALSE;
    }
    if (g_uiReady) {
        WaitForSingleObject(g_uiReady, 5000);
        CloseHandle(g_uiReady);
        g_uiReady = nullptr;
    }
    Wh_Log(L"Seamless FPS Overlay started.");
    return TRUE;
}

void WhTool_ModSettingsChanged() {
    if (sfoset::g_settingsWnd) PostMessageW(sfoset::g_settingsWnd.load(), WM_APP + 1 /* WM_APP_SETTINGS_RELOAD */, 0, 0);
    if (g_ctrl) PostMessageW(g_ctrl, WM_APP_RELOAD_SETTINGS, 0, 0);
}

void WhTool_ModUninit() {
    sfoset::CloseSettingsWindow();
    if (g_ctrl) PostMessageW(g_ctrl, WM_CLOSE, 0, 0);
    else if (g_uiThreadId) PostThreadMessageW(g_uiThreadId, WM_QUIT, 0, 0);
    // Keep this short. Windhawk starts the next copy while this one closes, and that copy gives
    // up after about 400 ms if this one still holds the tool mutex. The frame trace left behind
    // by a cut-short close is stopped by name when the next copy starts.
    if (g_uiThread) {
        WaitForSingleObject(g_uiThread, 1500);
        CloseHandle(g_uiThread);
        g_uiThread = nullptr;
    }
    seamless_sensors::StopPublisher(500);
    seamless_sensors::CloseReader();
    Wh_Log(L"Seamless FPS Overlay stopped cleanly.");
    SeamlessMenuSkin::Uninit();
}

// The frame counter needs administrator rights, so only an elevated Windhawk process starts
// the tool process. That launcher also keeps watch: if the tool process is gone (a reload where
// the new copy lost the race with the old one, or a crash), it starts it again, waiting longer
// each time so a copy that keeps failing cannot loop fast.
static HANDLE g_watchStop;
static HANDLE g_watchThread;

static bool ToolProcessRunning() {
    HANDLE m = OpenMutexW(SYNCHRONIZE, FALSE, L"windhawk-tool-mod_" WH_MOD_ID);
    if (!m) return GetLastError() == ERROR_ACCESS_DENIED;
    CloseHandle(m);
    return true;
}

static DWORD WINAPI WatchToolProcess(LPVOID) {
    DWORD wait = 20000, backoff = 30000;
    int missing = 0;
    while (WaitForSingleObject(g_watchStop, wait) == WAIT_TIMEOUT) {
        wait = 15000;
        if (ToolProcessRunning()) {
            missing = 0;
            continue;
        }
        if (++missing < 2) continue;
        Wh_Log(L"Overlay process missing, starting it again");
        windhawk_tool_mod::LaunchToolModProcess();
        missing = 0;
        wait = backoff;
        if (backoff < 600000) backoff *= 2;
    }
    return 0;
}

BOOL WhToolLauncher_ModInit(BOOL* bLaunch) {
    if (!IsProcessElevated()) return FALSE;  // nothing to do in a normal-rights helper
    *bLaunch = TRUE;
    return TRUE;
}

void WhToolLauncher_ModAfterInit() {
    g_watchStop = CreateEventW(nullptr, TRUE, FALSE, nullptr);
    if (g_watchStop) g_watchThread = CreateThread(nullptr, 0, WatchToolProcess, nullptr, 0, nullptr);
}

void WhToolLauncher_ModBeforeUninit() {
    if (g_watchStop) SetEvent(g_watchStop);
    if (g_watchThread) {
        WaitForSingleObject(g_watchThread, 2000);
        CloseHandle(g_watchThread);
        g_watchThread = nullptr;
    }
}

void WhToolLauncher_ModUninit() {
    WhToolLauncher_ModBeforeUninit();
    if (g_watchStop) {
        CloseHandle(g_watchStop);
        g_watchStop = nullptr;
    }
}

// ===========================================================================
// Settings window: the Seamless Launchpad settings GUI, the standard for every
// DavidHiFi mod. Generated by work\2026-11-26-fps-suite\overlay\gen.py.
// ===========================================================================
extern "C" IMAGE_DOS_HEADER __ImageBase;
namespace sfoset {
// The settings window, from the tray icon. It shows the same settings as
// Windhawk's page for this mod and saves them through windhawk-cli, so the two
// stay in step. Writing a mod's settings takes admin rights, so the save runs
// the CLI elevated (silently where UAC prompts are off).

constexpr WCHAR kSettingsClass[] = L"WindhawkSeamlessFpsOverlaySettings";
constexpr UINT WM_APP_SETTINGS_RELOAD = WM_APP + 1, WM_APP_SETTINGS_ACTIVATE = WM_APP + 2;
HANDLE g_settingsThread = nullptr;
std::atomic<HWND> g_settingsWnd;
std::atomic<bool> g_settingsStop;
void Settings_Close();
static std::wstring GetStringSetting(PCWSTR name) {
    PCWSTR p = Wh_GetStringSetting(name);
    std::wstring s = p ? p : L"";
    if (p) Wh_FreeStringSetting(p);
    return s;
}
// SetForegroundWindow works when this process had the last input; an empty SendInput gives it.
static void ForceForeground(HWND hwnd) {
    INPUT input{};
    SendInput(1, &input, sizeof(INPUT));
    SetForegroundWindow(hwnd);
    SetFocus(hwnd);
}
static float SystemCornerRadius(bool) { return 8; }
static int GetState(PCWSTR key, int fallback) { return Wh_GetIntValue(key, fallback); }
static void SetState(PCWSTR key, int value) { Wh_SetIntValue(key, value); }
static std::wstring StateKey(PCWSTR window, PCWSTR field) { return std::wstring(window)+L"_"+field; }
static void ApplyDarkWindow(HWND hwnd) { BOOL dark=TRUE; DwmSetWindowAttribute(hwnd,20,&dark,sizeof(dark)); }
namespace mocha {
constexpr UINT32 base = 0x1E1E2E, mantle = 0x181825, crust = 0x11111B,
                 surface0 = 0x313244, surface1 = 0x45475A, surface2 = 0x585B70,
                 overlay0 = 0x6C7086, overlay1 = 0x7F849C, overlay2 = 0x9399B2,
                 subtext0 = 0xA6ADC8, subtext1 = 0xBAC2DE, text = 0xCDD6F4,
                 lavender = 0xB4BEFE, blue = 0x89B4FA, sapphire = 0x74C7EC,
                 sky = 0x89DCEB, teal = 0x94E2D5, green = 0xA6E3A1,
                 yellow = 0xF9E2AF, peach = 0xFAB387, maroon = 0xEBA0AC,
                 red = 0xF38BA8, mauve = 0xCBA6F7, pink = 0xF5C2E7,
                 flamingo = 0xF2CDCD, rosewater = 0xF5E0DC;
}  // namespace mocha
inline D2D1_COLOR_F D2DColor(UINT32 rgb, float a = 1.0f) {
    return D2D1::ColorF(((rgb >> 16) & 0xFF) / 255.0f, ((rgb >> 8) & 0xFF) / 255.0f,
                        (rgb & 0xFF) / 255.0f, a);
}
inline D2D1_COLOR_F D2DColorRef(COLORREF c, float a = 1.0f) {
    return D2D1::ColorF(GetRValue(c) / 255.0f, GetGValue(c) / 255.0f, GetBValue(c) / 255.0f, a);
}
inline COLORREF RefFromRgb(UINT32 rgb) { return RGB((rgb >> 16) & 0xFF, (rgb >> 8) & 0xFF, rgb & 0xFF); }

COLORREF ParseColorRef(const std::wstring& text, COLORREF fallback) {
    std::wstring hex = !text.empty() && text[0] == L'#' ? text.substr(1) : text;
    if (hex.size() != 6 || hex.find_first_not_of(L"0123456789abcdefABCDEF") !=
                               std::wstring::npos) {
        return fallback;
    }
    UINT rgb = wcstoul(hex.c_str(), nullptr, 16);
    return RGB(rgb >> 16, (rgb >> 8) & 0xFF, rgb & 0xFF);
}

// ---------------------------------------------------------------------------
// 50-settings.cpp : the mod's own settings window. A sidebar of pages, grouped
// cards, toggles, dropdowns, sliders, key boxes and colour chips, all drawn
// with Direct2D in the style of Seamless Dictate's settings. It shows the same
// settings as Windhawk's page for this mod and saves them with one elevated
// windhawk-cli call, so the two stay in step. Windhawk then calls
// WhTool_ModSettingsChanged by itself.
//
// One window, one Direct2D target that fills the whole client rect (the window
// edge is rounded by DWM, never by us). Text typed into a number, text or colour
// box goes through one small native EDIT that sits on top of the box while it is
// edited. Key boxes read WM_KEYDOWN themselves.
// ---------------------------------------------------------------------------

template <class T>
class SetCom {
   public:
    T* p = nullptr;
    SetCom() = default;
    SetCom(const SetCom& o) : p(o.p) {
        if (p) p->AddRef();
    }
    SetCom& operator=(const SetCom& o) {
        if (o.p) o.p->AddRef();
        reset();
        p = o.p;
        return *this;
    }
    ~SetCom() { reset(); }
    void reset() {
        if (p) p->Release();
        p = nullptr;
    }
    T** put() {
        reset();
        return &p;
    }
    T* get() const { return p; }
    T* operator->() const { return p; }
    explicit operator bool() const { return p != nullptr; }
};

// One row of a tray menu (Set_TrayMenu). Every mod's tray menu is a list of these.
struct SetMenuItem {
    int id = 0;                    // What Set_TrayMenu returns when this row is picked.
    std::wstring glyph;            // FiraCode Nerd Font glyph for the leading column.
    std::wstring label;
    std::wstring hint;             // Grey text on the right, such as a hotkey.
    bool checked = false;          // Accent check mark on the right.
    bool separator = false;
    bool disabled = false;
    std::vector<SetMenuItem> sub;  // A submenu, drawn by the same renderer.
};

// One open level of a tray menu: its own popup window and Direct2D target.
struct SetMenuLevel {
    const std::vector<SetMenuItem>* items = nullptr;
    HWND hwnd = nullptr;
    SetCom<ID2D1HwndRenderTarget> rt;
    float scale = 1, wDip = 0, hDip = 0, itemH = 30, hintW = 0;
    std::vector<float> top, height;  // Per row, DIPs inside the window.
    int hover = -1;                  // Highlighted row.
    int open = -1;                   // Row whose submenu is the next level.
};

// A running tray menu. It owns its factories, so it runs on whatever thread owns the tray icon.
struct SetMenuSession {
    SetCom<ID2D1Factory> d2d;
    SetCom<IDWriteFactory> dw;
    SetCom<IDWriteTextFormat> fText, fHint, fGlyph, fGlyphS;
    std::vector<std::unique_ptr<SetMenuLevel>> levels;
    HINSTANCE inst = nullptr;
    std::wstring cls;
    float radius = 8;
    int result = 0;
    bool done = false;
    bool pressed = false;  // A button went down inside the menu; only then does a release pick a row.
    bool wasActive = false;
    float alpha = 1;
    ULONGLONG fadeStart = 0;
    int pendingLevel = -1, pendingItem = -1;  // Hover timer: open (item >= 0) or close a submenu after a delay.
};

struct SetField {
    enum Kind { Choice, Number, Text, Hotkey, Check, Color };
    Kind kind;
    PCWSTR key;
    PCWSTR label;
    PCWSTR desc = nullptr;
    PCWSTR def = L"";                                // The schema default ("Reset to suggested").
    std::vector<std::pair<PCWSTR, PCWSTR>> options;  // Value, label.
    int min = 0, max = 0;
    int page = 0;        // Which sidebar page shows it.
    PCWSTR group = L"";  // Heading above it on that page.
    std::wstring value;  // As loaded, so a save writes only what changed.
    std::wstring cur;    // What the window shows now.
    float fitW = 0;      // Box width that fits the text (Set_FitBoxes); 0 until measured.
    float fitText = -1;  // Measured text width behind fitW.
    std::wstring fitFor; // The text that was measured.
};

// Names, descriptions and option labels match the ==WindhawkModSettings== block word for word.
// Generated by work\2026-11-26-fps-suite\overlay\gen.py from spec.py.
static std::vector<SetField> Set_MakeFields() {
    using K = SetField;
    return {
{K::Choice, L"preset", L"Layout", L"Benchmark is the two-column layout from your old RivaTuner setup, with the moving pictures. FPS only shows one number. One line puts the main numbers in a single row. Tall list puts each number on its own line.", L"benchmark", {{L"benchmark", L"Benchmark (your RivaTuner layout)"}, {L"fps", L"FPS only"}, {L"compact", L"One line"}, {L"vertical", L"Tall list"}}, 0, 100, 0, L"Layout"},
{K::Check, L"showOnStart", L"Show when the mod starts", L"Off, the overlay waits until you press the shortcut or click the tray icon.", L"1", {}, 0, 100, 0, L"Layout"},
{K::Choice, L"showWhen", L"Show the overlay", L"In games shows it over any program that draws its own frames, the way games do. Always keeps it up everywhere, desktop included. Only listed games uses the list on the Games and keys page.", L"games", {{L"games", L"In games"}, {L"always", L"Always"}, {L"listed", L"Only listed games"}}, 0, 100, 0, L"Layout"},
{K::Hotkey, L"toggleHotkey", L"Show or hide shortcut", L"The same keys your Afterburner used. Click the box and press the keys. Backspace clears it.", L"Ctrl+Alt+Shift+]", {}, 0, 100, 0, L"Layout"},
{K::Choice, L"corner", L"Corner", L"Which corner of the screen the overlay sits in.", L"topLeft", {{L"topLeft", L"Top left"}, {L"topRight", L"Top right"}, {L"bottomLeft", L"Bottom left"}, {L"bottomRight", L"Bottom right"}}, 0, 100, 0, L"Where and how big"},
{K::Number, L"scale", L"Size", L"In percent. 100 is the normal size.", L"100", {}, 50, 300, 0, L"Where and how big"},
{K::Choice, L"background", L"Background", L"Blurred glass blurs the game behind each box. See-through tint is a light dark wash. Solid dark is the easiest to read. None leaves only the text, with a soft shadow.", L"glass", {{L"glass", L"Blurred glass"}, {L"tint", L"See-through tint"}, {L"solid", L"Solid dark"}, {L"none", L"None"}}, 0, 100, 0, L"Look"},
{K::Number, L"opacity", L"Opacity", L"How solid the whole overlay is, in percent.", L"100", {}, 20, 100, 0, L"Look"},
{K::Number, L"cornerRadius", L"Corner roundness", L"How round the box corners are, in pixels. 0 gives square corners.", L"12", {}, 0, 40, 0, L"Look"},
{K::Check, L"flipGradient", L"Flip the gradient", L"Off, blue sits at the top left and mauve at the bottom right. On, they swap.", L"0", {}, 0, 100, 0, L"Look"},
{K::Check, L"animations", L"Moving pictures", L"The spinning fan, the flames on a busy chip and the running code on the processor. They stop while the overlay is hidden.", L"1", {}, 0, 100, 0, L"Look"},
{K::Choice, L"updateRate", L"Update speed", L"How often the numbers change. Slower is easier to read and a little lighter on the PC.", L"500", {{L"250", L"Four times a second"}, {L"500", L"Twice a second"}, {L"1000", L"Once a second"}}, 0, 100, 0, L"Look"},
{K::Check, L"showGpuName", L"Graphics card name", L"The line across the top.", L"1", {}, 0, 100, 1, L"Card name"},
{K::Check, L"throttleWarn", L"Slow-down note", L"Shows HEAT LIMIT or POWER LIMIT when a chip slows itself down.", L"1", {}, 0, 100, 1, L"Card name"},
{K::Check, L"fps", L"FPS", L"Frames per second right now.", L"1", {}, 0, 100, 1, L"Frame rate"},
{K::Check, L"low01", L"Worst moments (slowest 0.1% of frames)", L"The frame rate during the very worst moments of the last 20 seconds.", L"1", {}, 0, 100, 1, L"Frame rate"},
{K::Check, L"low1", L"Bad moments (slowest 1% of frames)", L"The frame rate during the slowest moments of the last 20 seconds.", L"1", {}, 0, 100, 1, L"Frame rate"},
{K::Check, L"avgFps", L"Average FPS", L"Over the last 20 seconds.", L"1", {}, 0, 100, 1, L"Frame rate"},
{K::Check, L"jitter", L"Smoothness", L"How much the time between frames jumps around, in milliseconds. Lower feels smoother.", L"1", {}, 0, 100, 1, L"Frame rate"},
{K::Check, L"frameTime", L"Frame time", L"How long each frame takes, in milliseconds.", L"1", {}, 0, 100, 1, L"Frame rate"},
{K::Check, L"frameGraph", L"Frame time graph", L"A line of the last few seconds of frame times. Tall spikes are stutters.", L"1", {}, 0, 100, 1, L"Frame rate"},
{K::Check, L"latency", L"Input delay", L"This mod cannot measure it yet, so it shows a dash. Off by default.", L"0", {}, 0, 100, 1, L"Game info"},
{K::Check, L"api", L"Graphics engine", L"Whether the game draws with DirectX 9, 11, 12, OpenGL or Vulkan.", L"1", {}, 0, 100, 1, L"Game info"},
{K::Check, L"session", L"Play time", L"How long the game in front has been running.", L"1", {}, 0, 100, 1, L"Game info"},
{K::Check, L"driver", L"Driver version", L"The graphics driver version.", L"1", {}, 0, 100, 1, L"Game info"},
{K::Check, L"cpuName", L"Processor name", L"", L"1", {}, 0, 100, 1, L"Processor cores"},
{K::Check, L"coreBars", L"Load bar for each core", L"", L"1", {}, 0, 100, 1, L"Processor cores"},
{K::Choice, L"coreBarsEach", L"One bar for each", L"Threads gives twice as many bars on processors that run two threads per core.", L"core", {{L"core", L"Core"}, {L"thread", L"Thread"}}, 0, 100, 1, L"Processor cores"},
{K::Check, L"ram", L"Memory in use", L"In percent.", L"1", {}, 0, 100, 1, L"System memory"},
{K::Check, L"ramUsed", L"Memory in use, in GB", L"Used and total.", L"1", {}, 0, 100, 1, L"System memory"},
{K::Check, L"ramSpeed", L"Memory speed", L"In MT/s, the number on the memory box.", L"1", {}, 0, 100, 1, L"System memory"},
{K::Check, L"ramClock", L"Memory clock", L"In MHz, half the speed above.", L"1", {}, 0, 100, 1, L"System memory"},
{K::Check, L"gpuArt", L"Graphics card picture", L"The card drawing with its fan.", L"1", {}, 0, 100, 1, L"Graphics card"},
{K::Check, L"gpuUsage", L"Load", L"How busy the card is, in percent.", L"1", {}, 0, 100, 1, L"Graphics card"},
{K::Check, L"gpuPower", L"Power", L"In watts.", L"1", {}, 0, 100, 1, L"Graphics card"},
{K::Check, L"gpuClock", L"Clock", L"In MHz.", L"1", {}, 0, 100, 1, L"Graphics card"},
{K::Check, L"gpuFan", L"Fan speed", L"In RPM, with the percent next to it.", L"1", {}, 0, 100, 1, L"Graphics card"},
{K::Check, L"gpuTemp", L"Temperature", L"", L"1", {}, 0, 100, 1, L"Graphics card"},
{K::Check, L"gpuHotspot", L"Hot spot", L"The hottest point on the chip.", L"1", {}, 0, 100, 1, L"Graphics card"},
{K::Check, L"vram", L"How full", L"In percent of the card's memory.", L"1", {}, 0, 100, 1, L"Video memory"},
{K::Check, L"vramUsed", L"Used, in GB", L"Used and total.", L"1", {}, 0, 100, 1, L"Video memory"},
{K::Check, L"vramTemp", L"Temperature", L"Some cards do not report it. Then it shows a dash.", L"1", {}, 0, 100, 1, L"Video memory"},
{K::Check, L"gpuMemClock", L"Clock", L"In MHz.", L"1", {}, 0, 100, 1, L"Video memory"},
{K::Check, L"cpuArt", L"Processor picture", L"The chip drawing with its running code.", L"1", {}, 0, 100, 1, L"Processor"},
{K::Check, L"cpuUsage", L"Load", L"How busy the processor is, in percent.", L"1", {}, 0, 100, 1, L"Processor"},
{K::Check, L"cpuPower", L"Power", L"In watts. Needs the PawnIO driver, or it shows a dash.", L"1", {}, 0, 100, 1, L"Processor"},
{K::Check, L"cpuClock", L"Boost clock", L"The fastest core right now, in GHz.", L"1", {}, 0, 100, 1, L"Processor"},
{K::Check, L"cpuBusyClock", L"Busy clock", L"The average clock while the cores are working, in MHz.", L"1", {}, 0, 100, 1, L"Processor"},
{K::Check, L"cpuTemp", L"Temperature", L"Needs the PawnIO driver, or it shows a dash.", L"1", {}, 0, 100, 1, L"Processor"},
{K::Check, L"showName", L"Show this box", L"The graphics card name across the top, with a note when the card slows down to stay cool or within its power limit.", L"1", {}, 0, 100, 2, L"Card name"},
{K::Choice, L"columnName", L"Side", L"", L"left", {{L"left", L"Left column"}, {L"right", L"Right column"}}, 0, 100, 2, L"Card name"},
{K::Number, L"orderName", L"Place in its column", L"1 is the top. Boxes with the same number keep their usual order.", L"1", {}, 1, 9, 2, L"Card name"},
{K::Number, L"sizeName", L"Size", L"In percent of the overlay size.", L"100", {}, 50, 200, 2, L"Card name"},
{K::Choice, L"colourName", L"Name colour", L"The colour of the words and pictures in this box.", L"same", {{L"same", L"Same as the names"}, {L"gradient", L"Blue to mauve"}, {L"blue", L"Blue"}, {L"mauve", L"Mauve"}, {L"lavender", L"Lavender"}, {L"sapphire", L"Sapphire"}, {L"sky", L"Sky"}, {L"teal", L"Teal"}, {L"green", L"Green"}, {L"yellow", L"Yellow"}, {L"peach", L"Peach"}, {L"pink", L"Pink"}, {L"red", L"Red"}, {L"white", L"White"}, {L"custom", L"My own colour"}}, 0, 100, 2, L"Card name"},
{K::Check, L"showFrames", L"Show this box", L"FPS, the worst moments, the average, smoothness and the frame time graph.", L"1", {}, 0, 100, 2, L"Frame rate"},
{K::Choice, L"columnFrames", L"Side", L"", L"left", {{L"left", L"Left column"}, {L"right", L"Right column"}}, 0, 100, 2, L"Frame rate"},
{K::Number, L"orderFrames", L"Place in its column", L"1 is the top. Boxes with the same number keep their usual order.", L"2", {}, 1, 9, 2, L"Frame rate"},
{K::Number, L"sizeFrames", L"Size", L"In percent of the overlay size.", L"100", {}, 50, 200, 2, L"Frame rate"},
{K::Choice, L"colourFrames", L"Name colour", L"The colour of the words and pictures in this box.", L"same", {{L"same", L"Same as the names"}, {L"gradient", L"Blue to mauve"}, {L"blue", L"Blue"}, {L"mauve", L"Mauve"}, {L"lavender", L"Lavender"}, {L"sapphire", L"Sapphire"}, {L"sky", L"Sky"}, {L"teal", L"Teal"}, {L"green", L"Green"}, {L"yellow", L"Yellow"}, {L"peach", L"Peach"}, {L"pink", L"Pink"}, {L"red", L"Red"}, {L"white", L"White"}, {L"custom", L"My own colour"}}, 0, 100, 2, L"Frame rate"},
{K::Check, L"showInfo", L"Show this box", L"Which DirectX or Vulkan the game uses, how long you have played and the driver version.", L"1", {}, 0, 100, 2, L"Game info"},
{K::Choice, L"columnInfo", L"Side", L"", L"left", {{L"left", L"Left column"}, {L"right", L"Right column"}}, 0, 100, 2, L"Game info"},
{K::Number, L"orderInfo", L"Place in its column", L"1 is the top. Boxes with the same number keep their usual order.", L"3", {}, 1, 9, 2, L"Game info"},
{K::Number, L"sizeInfo", L"Size", L"In percent of the overlay size.", L"100", {}, 50, 200, 2, L"Game info"},
{K::Choice, L"colourInfo", L"Name colour", L"The colour of the words and pictures in this box.", L"same", {{L"same", L"Same as the names"}, {L"gradient", L"Blue to mauve"}, {L"blue", L"Blue"}, {L"mauve", L"Mauve"}, {L"lavender", L"Lavender"}, {L"sapphire", L"Sapphire"}, {L"sky", L"Sky"}, {L"teal", L"Teal"}, {L"green", L"Green"}, {L"yellow", L"Yellow"}, {L"peach", L"Peach"}, {L"pink", L"Pink"}, {L"red", L"Red"}, {L"white", L"White"}, {L"custom", L"My own colour"}}, 0, 100, 2, L"Game info"},
{K::Check, L"showCores", L"Show this box", L"The processor name and a small load bar for each core.", L"1", {}, 0, 100, 2, L"Processor cores"},
{K::Choice, L"columnCores", L"Side", L"", L"left", {{L"left", L"Left column"}, {L"right", L"Right column"}}, 0, 100, 2, L"Processor cores"},
{K::Number, L"orderCores", L"Place in its column", L"1 is the top. Boxes with the same number keep their usual order.", L"4", {}, 1, 9, 2, L"Processor cores"},
{K::Number, L"sizeCores", L"Size", L"In percent of the overlay size.", L"100", {}, 50, 200, 2, L"Processor cores"},
{K::Choice, L"colourCores", L"Name colour", L"The colour of the words and pictures in this box.", L"same", {{L"same", L"Same as the names"}, {L"gradient", L"Blue to mauve"}, {L"blue", L"Blue"}, {L"mauve", L"Mauve"}, {L"lavender", L"Lavender"}, {L"sapphire", L"Sapphire"}, {L"sky", L"Sky"}, {L"teal", L"Teal"}, {L"green", L"Green"}, {L"yellow", L"Yellow"}, {L"peach", L"Peach"}, {L"pink", L"Pink"}, {L"red", L"Red"}, {L"white", L"White"}, {L"custom", L"My own colour"}}, 0, 100, 2, L"Processor cores"},
{K::Check, L"showMemory", L"Show this box", L"How much memory is in use, and its speed.", L"1", {}, 0, 100, 2, L"System memory"},
{K::Choice, L"columnMemory", L"Side", L"", L"left", {{L"left", L"Left column"}, {L"right", L"Right column"}}, 0, 100, 2, L"System memory"},
{K::Number, L"orderMemory", L"Place in its column", L"1 is the top. Boxes with the same number keep their usual order.", L"5", {}, 1, 9, 2, L"System memory"},
{K::Number, L"sizeMemory", L"Size", L"In percent of the overlay size.", L"100", {}, 50, 200, 2, L"System memory"},
{K::Choice, L"colourMemory", L"Name colour", L"The colour of the words and pictures in this box.", L"same", {{L"same", L"Same as the names"}, {L"gradient", L"Blue to mauve"}, {L"blue", L"Blue"}, {L"mauve", L"Mauve"}, {L"lavender", L"Lavender"}, {L"sapphire", L"Sapphire"}, {L"sky", L"Sky"}, {L"teal", L"Teal"}, {L"green", L"Green"}, {L"yellow", L"Yellow"}, {L"peach", L"Peach"}, {L"pink", L"Pink"}, {L"red", L"Red"}, {L"white", L"White"}, {L"custom", L"My own colour"}}, 0, 100, 2, L"System memory"},
{K::Check, L"showCard", L"Show this box", L"The card picture with its spinning fan, load, power, clock, fan and temperatures.", L"1", {}, 0, 100, 2, L"Graphics card"},
{K::Choice, L"columnCard", L"Side", L"", L"right", {{L"left", L"Left column"}, {L"right", L"Right column"}}, 0, 100, 2, L"Graphics card"},
{K::Number, L"orderCard", L"Place in its column", L"1 is the top. Boxes with the same number keep their usual order.", L"1", {}, 1, 9, 2, L"Graphics card"},
{K::Number, L"sizeCard", L"Size", L"In percent of the overlay size.", L"100", {}, 50, 200, 2, L"Graphics card"},
{K::Choice, L"colourCard", L"Name colour", L"The colour of the words and pictures in this box.", L"same", {{L"same", L"Same as the names"}, {L"gradient", L"Blue to mauve"}, {L"blue", L"Blue"}, {L"mauve", L"Mauve"}, {L"lavender", L"Lavender"}, {L"sapphire", L"Sapphire"}, {L"sky", L"Sky"}, {L"teal", L"Teal"}, {L"green", L"Green"}, {L"yellow", L"Yellow"}, {L"peach", L"Peach"}, {L"pink", L"Pink"}, {L"red", L"Red"}, {L"white", L"White"}, {L"custom", L"My own colour"}}, 0, 100, 2, L"Graphics card"},
{K::Check, L"showVram", L"Show this box", L"The memory on the graphics card: how full, how hot and its clock.", L"1", {}, 0, 100, 2, L"Video memory"},
{K::Choice, L"columnVram", L"Side", L"", L"right", {{L"left", L"Left column"}, {L"right", L"Right column"}}, 0, 100, 2, L"Video memory"},
{K::Number, L"orderVram", L"Place in its column", L"1 is the top. Boxes with the same number keep their usual order.", L"2", {}, 1, 9, 2, L"Video memory"},
{K::Number, L"sizeVram", L"Size", L"In percent of the overlay size.", L"100", {}, 50, 200, 2, L"Video memory"},
{K::Choice, L"colourVram", L"Name colour", L"The colour of the words and pictures in this box.", L"same", {{L"same", L"Same as the names"}, {L"gradient", L"Blue to mauve"}, {L"blue", L"Blue"}, {L"mauve", L"Mauve"}, {L"lavender", L"Lavender"}, {L"sapphire", L"Sapphire"}, {L"sky", L"Sky"}, {L"teal", L"Teal"}, {L"green", L"Green"}, {L"yellow", L"Yellow"}, {L"peach", L"Peach"}, {L"pink", L"Pink"}, {L"red", L"Red"}, {L"white", L"White"}, {L"custom", L"My own colour"}}, 0, 100, 2, L"Video memory"},
{K::Check, L"showProcessor", L"Show this box", L"The chip picture, load, power, clocks and temperature.", L"1", {}, 0, 100, 2, L"Processor"},
{K::Choice, L"columnProcessor", L"Side", L"", L"right", {{L"left", L"Left column"}, {L"right", L"Right column"}}, 0, 100, 2, L"Processor"},
{K::Number, L"orderProcessor", L"Place in its column", L"1 is the top. Boxes with the same number keep their usual order.", L"3", {}, 1, 9, 2, L"Processor"},
{K::Number, L"sizeProcessor", L"Size", L"In percent of the overlay size.", L"100", {}, 50, 200, 2, L"Processor"},
{K::Choice, L"colourProcessor", L"Name colour", L"The colour of the words and pictures in this box.", L"same", {{L"same", L"Same as the names"}, {L"gradient", L"Blue to mauve"}, {L"blue", L"Blue"}, {L"mauve", L"Mauve"}, {L"lavender", L"Lavender"}, {L"sapphire", L"Sapphire"}, {L"sky", L"Sky"}, {L"teal", L"Teal"}, {L"green", L"Green"}, {L"yellow", L"Yellow"}, {L"peach", L"Peach"}, {L"pink", L"Pink"}, {L"red", L"Red"}, {L"white", L"White"}, {L"custom", L"My own colour"}}, 0, 100, 2, L"Processor"},
{K::Check, L"capitals", L"Names in capitals", L"Off, the names show the way you typed them.", L"1", {}, 0, 100, 3, L"All names"},
{K::Text, L"lblFps", L"FPS", L"", L"FPS", {}, 0, 100, 3, L"Frame rate"},
{K::Text, L"lbl01", L"Worst moments", L"", L"0.1%", {}, 0, 100, 3, L"Frame rate"},
{K::Text, L"lbl1", L"Bad moments", L"", L"1%", {}, 0, 100, 3, L"Frame rate"},
{K::Text, L"lblAvg", L"Average", L"", L"AVG", {}, 0, 100, 3, L"Frame rate"},
{K::Text, L"lblJitter", L"Smoothness", L"", L"JITTER", {}, 0, 100, 3, L"Frame rate"},
{K::Text, L"lblFrame", L"Frame time", L"", L"FRAME TIME", {}, 0, 100, 3, L"Frame rate"},
{K::Text, L"lblLatency", L"Input delay", L"", L"LATENCY", {}, 0, 100, 3, L"Game info"},
{K::Text, L"lblApi", L"Graphics engine", L"", L"API", {}, 0, 100, 3, L"Game info"},
{K::Text, L"lblTime", L"Play time", L"", L"PLAY TIME", {}, 0, 100, 3, L"Game info"},
{K::Text, L"lblDriver", L"Driver version", L"", L"DRIVER", {}, 0, 100, 3, L"Game info"},
{K::Text, L"lblRam", L"Box name", L"", L"RAM", {}, 0, 100, 3, L"System memory"},
{K::Text, L"lblRamUsed", L"In use", L"", L"USED", {}, 0, 100, 3, L"System memory"},
{K::Text, L"lblRamSpeed", L"Speed", L"", L"SPEED", {}, 0, 100, 3, L"System memory"},
{K::Text, L"lblRamClock", L"Clock", L"", L"CLOCK", {}, 0, 100, 3, L"System memory"},
{K::Text, L"lblGpuLoad", L"Load", L"", L"LOAD", {}, 0, 100, 3, L"Graphics card"},
{K::Text, L"lblGpuPower", L"Power", L"", L"POWER", {}, 0, 100, 3, L"Graphics card"},
{K::Text, L"lblGpuClock", L"Clock", L"", L"CLOCK", {}, 0, 100, 3, L"Graphics card"},
{K::Text, L"lblFan", L"Fan", L"", L"FAN", {}, 0, 100, 3, L"Graphics card"},
{K::Text, L"lblGpuTemp", L"Temperature", L"", L"TEMP", {}, 0, 100, 3, L"Graphics card"},
{K::Text, L"lblHotspot", L"Hot spot", L"", L"HOT SPOT", {}, 0, 100, 3, L"Graphics card"},
{K::Text, L"lblVram", L"Box name", L"", L"VRAM", {}, 0, 100, 3, L"Video memory"},
{K::Text, L"lblVramUsed", L"Used", L"", L"USED", {}, 0, 100, 3, L"Video memory"},
{K::Text, L"lblVramTemp", L"Temperature", L"", L"TEMP", {}, 0, 100, 3, L"Video memory"},
{K::Text, L"lblVramClock", L"Clock", L"", L"CLOCK", {}, 0, 100, 3, L"Video memory"},
{K::Text, L"lblCpuLoad", L"Load", L"", L"LOAD", {}, 0, 100, 3, L"Processor"},
{K::Text, L"lblCpuPower", L"Power", L"", L"POWER", {}, 0, 100, 3, L"Processor"},
{K::Text, L"lblCpuBoost", L"Boost clock", L"", L"BOOST", {}, 0, 100, 3, L"Processor"},
{K::Text, L"lblCpuBusy", L"Busy clock", L"", L"BUSY CLOCK", {}, 0, 100, 3, L"Processor"},
{K::Text, L"lblCpuTemp", L"Temperature", L"", L"TEMP", {}, 0, 100, 3, L"Processor"},
{K::Choice, L"warnColour", L"Warning colour", L"A number past its limit turns this colour.", L"red", {{L"gradient", L"Blue to mauve"}, {L"blue", L"Blue"}, {L"mauve", L"Mauve"}, {L"lavender", L"Lavender"}, {L"sapphire", L"Sapphire"}, {L"sky", L"Sky"}, {L"teal", L"Teal"}, {L"green", L"Green"}, {L"yellow", L"Yellow"}, {L"peach", L"Peach"}, {L"pink", L"Pink"}, {L"red", L"Red"}, {L"white", L"White"}, {L"custom", L"My own colour"}}, 0, 100, 4, L"Colour"},
{K::Number, L"gpuTempWarn", L"Graphics card hotter than", L"In \u00B0C.", L"83", {}, 40, 110, 4, L"Limits"},
{K::Number, L"hotspotWarn", L"Hot spot or video memory hotter than", L"In \u00B0C.", L"95", {}, 40, 120, 4, L"Limits"},
{K::Number, L"cpuTempWarn", L"Processor hotter than", L"In \u00B0C.", L"85", {}, 40, 110, 4, L"Limits"},
{K::Number, L"vramWarn", L"Video memory fuller than", L"In percent.", L"95", {}, 10, 100, 4, L"Limits"},
{K::Number, L"ramWarn", L"System memory fuller than", L"In percent.", L"90", {}, 10, 100, 4, L"Limits"},
{K::Number, L"fpsWarn", L"FPS lower than", L"0 turns this warning off.", L"0", {}, 0, 1000, 4, L"Limits"},
{K::Choice, L"graphStyle", L"Graph style", L"", L"line", {{L"line", L"Line"}, {L"area", L"Filled"}, {L"bars", L"Bars"}}, 0, 100, 5, L"Frame time graph"},
{K::Number, L"graphSeconds", L"Graph length", L"How many seconds the graph shows.", L"3", {}, 1, 10, 5, L"Frame time graph"},
{K::Number, L"graphHeight", L"Graph height", L"In pixels, before the overlay size.", L"36", {}, 16, 120, 5, L"Frame time graph"},
{K::Choice, L"graphTop", L"Top of the graph", L"The frame time at the top edge. Fit to the frames picks it from what is on screen.", L"50", {{L"auto", L"Fit to the frames"}, {L"33", L"33 ms (30 FPS)"}, {L"50", L"50 ms (20 FPS)"}, {L"100", L"100 ms (10 FPS)"}}, 0, 100, 5, L"Frame time graph"},
{K::Check, L"spikeMarks", L"Mark stutters", L"A small mark above each big spike.", L"1", {}, 0, 100, 5, L"Frame time graph"},
{K::Check, L"fanSpin", L"Spinning fan", L"Spins as fast as the real fan, scaled down.", L"1", {}, 0, 100, 5, L"Moving pictures"},
{K::Number, L"fanSpeed", L"Fan spin speed", L"In percent. 100 follows the real fan.", L"100", {}, 10, 300, 5, L"Moving pictures"},
{K::Check, L"flames", L"Flames on a busy chip", L"Small flames around a load ring that is nearly full.", L"1", {}, 0, 100, 5, L"Moving pictures"},
{K::Number, L"flameAt", L"Flames start at", L"Load in percent.", L"97", {}, 1, 100, 5, L"Moving pictures"},
{K::Check, L"binaryCode", L"Running code", L"The ones and zeros on the processor picture.", L"1", {}, 0, 100, 5, L"Moving pictures"},
{K::Check, L"smoothDials", L"Smooth dials", L"Rings and needles glide to a new number.", L"1", {}, 0, 100, 5, L"Moving pictures"},
{K::Check, L"throttlePulse", L"Pulse the slow-down note", L"HEAT LIMIT and POWER LIMIT gently pulse.", L"1", {}, 0, 100, 5, L"Moving pictures"},
{K::Choice, L"animFps", L"Picture frame rate", L"How often the moving pictures redraw. Lower costs less.", L"30", {{L"15", L"15 a second"}, {L"30", L"30 a second"}, {L"60", L"60 a second"}}, 0, 100, 5, L"Moving pictures"},
{K::Number, L"gpuGaugeMax", L"Graphics clock dial ends at", L"In MHz.", L"3000", {}, 500, 5000, 5, L"Dials"},
{K::Number, L"cpuGaugeMax", L"Processor clock dial ends at", L"In MHz.", L"6000", {}, 1000, 8000, 5, L"Dials"},
{K::Number, L"offsetX", L"Distance from the side", L"In pixels.", L"16", {}, 0, 2000, 6, L"Position"},
{K::Number, L"offsetY", L"Distance from the top or bottom", L"In pixels.", L"16", {}, 0, 2000, 6, L"Position"},
{K::Choice, L"monitor", L"Screen", L"Follow the game moves the overlay to whichever screen the game is on.", L"game", {{L"game", L"Follow the game"}, {L"primary", L"Main screen"}}, 0, 100, 6, L"Position"},
{K::Choice, L"panels", L"Boxes", L"One panel puts every section in a single box, split by thin lines. Separate boxes gives each section its own box, like RivaTuner.", L"one", {{L"one", L"One panel"}, {L"cards", L"Separate boxes"}}, 0, 100, 6, L"Boxes"},
{K::Number, L"blockGap", L"Gap between boxes", L"Only used with separate boxes. In pixels.", L"6", {}, 0, 40, 6, L"Boxes"},
{K::Number, L"bgStrength", L"Background strength", L"How dark the box fill is, in percent. 0 leaves only the blur.", L"100", {}, 0, 150, 6, L"Boxes"},
{K::Check, L"rounded", L"Rounded corners", L"Off gives square corners at any roundness.", L"1", {}, 0, 100, 6, L"Boxes"},
{K::Check, L"border", L"Edge", L"A thin line around each box.", L"1", {}, 0, 100, 6, L"Boxes"},
{K::Text, L"borderColour", L"Edge colour", L"Type gradient for the blue to mauve edge, or a colour like #45475A.", L"gradient", {}, 0, 100, 6, L"Boxes"},
{K::Text, L"fontFace", L"Font", L"Any font installed on this PC. If it is missing, Segoe UI is used.", L"FiraCode Nerd Font", {}, 0, 100, 6, L"Text"},
{K::Choice, L"fontWeight", L"Thickness", L"", L"bold", {{L"normal", L"Normal"}, {L"medium", L"Medium"}, {L"semibold", L"Semibold"}, {L"bold", L"Bold"}, {L"heavy", L"Heavy"}}, 0, 100, 6, L"Text"},
{K::Number, L"textSize", L"Text size", L"In percent, on top of the overlay size.", L"100", {}, 60, 200, 6, L"Text"},
{K::Choice, L"labelStyle", L"Name colour", L"The colour of the names, like GPU and FPS, and of the pictures.", L"gradient", {{L"gradient", L"Blue to mauve"}, {L"blue", L"Blue"}, {L"mauve", L"Mauve"}, {L"text", L"White"}, {L"custom", L"My own colour"}}, 0, 100, 6, L"Text"},
{K::Choice, L"valueStyle", L"Number colour", L"The colour of the numbers.", L"text", {{L"text", L"White"}, {L"gradient", L"Blue to mauve"}, {L"custom", L"My own colour"}}, 0, 100, 6, L"Text"},
{K::Color, L"customColour", L"My own colour", L"Used wherever a colour is set to My own colour.", L"#F5C2E7", {}, 0, 100, 6, L"Text"},
{K::Text, L"gameList", L"Listed games", L"Used when Show the overlay is set to Only listed games. Program names split by commas, like cs2.exe, plutonium-bootstrapper-win32.exe.", L"", {}, 0, 100, 7, L"Lists"},
{K::Text, L"hideList", L"Never show over", L"Program names split by commas. The overlay stays hidden over these.", L"", {}, 0, 100, 7, L"Lists"},
{K::Hotkey, L"presetHotkey", L"Next layout shortcut", L"Steps through the four layouts. Empty means no shortcut.", L"", {}, 0, 100, 7, L"Shortcuts"},
{K::Check, L"settingsTrayIcon", L"Tray icon", L"Click it to show or hide the overlay. Right-click it for layouts and settings.", L"1", {}, 0, 100, 8, L"Tray icon"},
{K::Check, L"settingsGlass", L"Blurred settings window", L"On, the settings window is see-through glass with Windows acrylic behind it. Off, it is solid. Applies when you save.", L"1", {}, 0, 100, 8, L"Settings window"},
{K::Check, L"nativeSettingsTitleBar", L"Native Windows title bar", L"Use the Windows title bar and window buttons for this settings window. Applies when you save.", L"0", {}, 0, 100, 8, L"Settings window"},
{K::Check, L"flyoutAnimation", L"Show and hide animation", L"The overlay fades and slides in when it shows, and out when it hides. It stays still when Windows animation effects are off.", L"1", {}, 0, 100, 8, L"Motion"},
{K::Choice, L"animationSpeed", L"Animation speed", L"Follow the global speed uses the one speed shared by all DavidHiFi mods.", L"global", {{L"global", L"Follow the global speed"}, {L"veryQuick", L"Very quick"}, {L"quick", L"Quick"}, {L"normal", L"Normal"}, {L"relaxed", L"Relaxed"}, {L"slow", L"Slow"}}, 0, 100, 8, L"Motion"}
    };
}

struct SetPageInfo {
    PCWSTR name, intro;
    WCHAR glyph;
};
static const SetPageInfo kSetPages[] = {
{L"Overlay", L"The settings most people change. Everything else is one page down.", 0xEC4A},
{L"Readings", L"Turn each number and picture on or off.", 0xE9D9},
{L"Blocks", L"The boxes of the Benchmark layout: which side, what order, how big, what colour.", 0xE80A},
{L"Names", L"The words in front of each number. Leave a box empty to get the usual name back.", 0xE8D2},
{L"Warnings", L"When a number turns to the warning colour.", 0xE7BA},
{L"Graph and motion", L"The frame time graph and the moving pictures.", 0xE9D2},
{L"Position and style", L"Fine control over where the overlay sits and how it looks.", 0xE790},
{L"Games and keys", L"Which programs get the overlay, and the extra shortcut.", 0xE7FC},
{L"Look", L"The tray icon, the show and hide animation and this settings window.", 0xE771},
{L"About", L"Version, credits, support and links.", 0xE946},
};
constexpr int kSetPageCount = (int)(sizeof(kSetPages) / sizeof(kSetPages[0]));
// About sits apart at the end of the sidebar, as in Seamless Dictate.
constexpr int kSetAboutPage = kSetPageCount - 1;
constexpr float kSetAboutGap = 17;
constexpr int kSetDropMax = 9;  // A dropdown with more options than this scrolls.

// All sizes are DIPs; the render target does the scaling.
constexpr float kSetPadX = 40, kSetMaxW = 720, kSetRowMin = 56, kSetRowGap = 8, kSetBoxH = 32, kSetRowPad = 16,
                kSetDropItem = 32, kSetRailTop = 76, kSetRailItem = 36, kSetRailPitch = 40;
// The sidebar is a floating dock: dragged between min and max, or collapsed to an icon rail.
constexpr float kSetDockGap = 10, kSetRailDef = 232, kSetRailMin = 200, kSetRailMax = 380, kSetRailMini = 60,
                kSetRailSnap = 130, kSetEdgeGrab = 5;
// The footer is a floating pill dock at the bottom right of the page.
constexpr float kSetFootBtnH = 36, kSetFootPad = 8, kSetFootH = kSetFootBtnH + 2 * kSetFootPad, kSetFootGap = 14;
// The glass tint is one layer over the whole window, title bar included, so the two always match.
constexpr float kSetGlassTint = 0.55f, kSetNativeFade = 56;
constexpr int kSetChipCount = 10;
constexpr UINT32 kSetChips[kSetChipCount] = {mocha::blue,   mocha::sapphire, mocha::teal, mocha::green, mocha::yellow,
                                             mocha::peach,  mocha::red,      mocha::pink, mocha::mauve, mocha::lavender};
constexpr UINT_PTR kSetTimerId = 1;
constexpr float kSetAutoDead = 10, kSetAutoR = 18, kSetAutoGain = 0.14f, kSetAutoMax = 56;
constexpr PCWSTR kSetAutoProp = L"SeamlessOwnAutoscroll";  // Seamless Autoscroll skips this window.
constexpr PCWSTR kSetKofiUrl = L"https://ko-fi.com/DavidHiFi";
constexpr PCWSTR kSetAuthorUrl = L"https://github.com/DavidHiFi";
constexpr PCWSTR kSetDittoUrl = L"https://pawnio.eu";
constexpr PCWSTR kSetKsUrl = L"https://github.com/namazso/PawnIO.Modules";
constexpr PCWSTR kSetRepoUrl = L"https://github.com/DavidHiFi/davids-windhawk-mods";
constexpr PCWSTR kSetBugUrl =
    L"https://github.com/DavidHiFi/davids-windhawk-mods/issues/new?title=%5BSeamless%20FPS%20Overlay%5D%20";
constexpr PCWSTR kSetTitle = L"Seamless FPS Overlay";
// The self-drawn title bar. Everything below it is laid out as before, in "content" DIPs.
static float kSetCapH = 40;
constexpr float kSetCapBtnW = 46, kSetHoverMs = 120;
constexpr float kSetMenuPad = 6, kSetMenuIconW = 22, kSetMenuSepH = 9, kSetMenuOverlap = 3, kSetMenuMinW = 190, kSetMenuMaxW = 640, kSetMenuBorderW = 2;
constexpr UINT kSetMenuSubDelayMs = 200, kSetMenuFadeMs = 90, kSetMenuTimerSub = 0x5E71, kSetMenuTimerFade = 0x5E72, kSetMenuTimerPoll = 0x5E73;

struct SetItem {
    enum Type { Group, Row, Banner, About, Link, Support } type = Row;
    int field = -1;  // Row: index into fields.
    float y = 0, h = 0;
    std::wstring text, sub, url;
};

// What the pointer is over. id picks the hover glow.
struct SetHit {
    enum Kind { None, Rail, Row, Control, Slider, Clear, Chip, Footer, Drop, Link, Scroll, Popup, Caption, RailToggle, RailEdge } kind = None;
    int a = -1, b = -1;
    int id = -1;
};

struct SetWindow {
    HWND hwnd = nullptr, edit = nullptr, owner = nullptr;
    HFONT editFont = nullptr;
    HBRUSH editBrush = nullptr;
    std::vector<SetField> fields = Set_MakeFields();
    std::vector<SetItem> items;
    UINT dpi = 96;
    float cw = 980, ch = 700;  // Content size in DIPs: the client area below the title bar.
    HICON iconSmall = nullptr, iconBig = nullptr;
    int capDown = 0;  // Title bar button held down: 1 minimize, 2 maximize, 3 close.
    bool capTracking = false, active = true;
    bool nativeTitle = false;  // Windows draws the title bar and its buttons.
    bool nativeButtons = false;  // Own title bar, but Windows draws minimize, maximize and close.
    bool glass = false;        // Acrylic behind the window; the page is drawn see-through.
    ULONGLONG lastTick = 0;
    int page = 0, recording = -1, editing = -1, focus = -1, openSel = -1;
    bool kbd = false;  // Show the focus ring (after a Tab).
    D2D1_RECT_F dropRect{};
    int dropHover = -1, dropTop = 0;  // dropTop: first option shown when the dropdown scrolls.
    bool frameApplied = false;        // Set_ApplyFrame has run once.
    float scrollY = 0, scrollTarget = 0, contentH = 0, contentX = 0, contentW = 720, pageT = 1;
    SetHit hover;
    int dragSlider = -1;
    bool dragScroll = false, tracking = false, timer = false;
    float dragOff = 0;
    bool autoScroll = false, autoMoved = false;
    float autoX = 0, autoY = 0, autoA = 0, autoDir = 0;
    // Sidebar dock: railW is the chosen open width, railCur the drawn width (eased toward
    // kSetRailMini when collapsed). railGlow / footGlow ease the dock borders on hover.
    float railW = kSetRailDef, railCur = kSetRailDef, railGlow = 0, footGlow = 0;
    bool railCollapsed = false, dragRail = false;
    float mouseX = -1, mouseY = -1;
    std::map<int, float> glow;  // Eased hover amount by hit id.
    std::map<int, float> knob;  // Eased toggle position by field.
    std::wstring status;
    bool statusError = false;
    bool saving = false, destroyed = false, render = false;
    SetCom<ID2D1HwndRenderTarget> rt;
    SetCom<ID2D1BitmapRenderTarget> layer;  // The page, drawn off screen so the footer can blur it.
    D2D1_SIZE_F layerSize{};
    std::wstring family, iconFamily;
    SetCom<IDWriteTextFormat> fLabel, fHint, fTitle, fIntro, fSection, fValue, fValueC, fButton, fIcon, fIconS,
        fIconL, fBig, fSmall, fStatusLine, fCap, fCapGlyph, fRailName;
    RECT normalRect{};  // Last restored-state rect, remembered on close.
    COLORREF customColors[16] = {};
};

static std::shared_ptr<SetWindow> g_setWin;
static UINT g_setForceDpi;  // Harness renders at a chosen scale.
static SetCom<ID2D1Factory> g_setD2d;
static SetCom<IDWriteFactory> g_setDw;
static SetCom<IWICImagingFactory> g_setWic;
#ifdef SCM_HARNESS
static std::wstring g_setFakeKeyStatus;  // Lets the test render the hotkey warning line.
#endif

static std::wstring Set_WindowText(HWND hwnd) {
    std::wstring text(GetWindowTextLengthW(hwnd) + 1, L'\0');
    text.resize(GetWindowTextW(hwnd, text.data(), (int)text.size()));
    return text;
}

static std::wstring Set_KeyStatusText() {
#ifdef SCM_HARNESS
    if (!g_setFakeKeyStatus.empty()) return g_setFakeKeyStatus;
#endif
    return std::wstring();
}

// Quotes one argument the way CommandLineToArgvW reads it back.
static std::wstring Set_QuoteArg(const std::wstring& arg) {
    std::wstring out = L"\"";
    for (size_t i = 0;; i++) {
        size_t slashes = 0;
        while (i < arg.size() && arg[i] == L'\\') i++, slashes++;
        if (i == arg.size()) {
            out.append(slashes * 2, L'\\');
            break;
        }
        out.append(arg[i] == L'"' ? slashes * 2 + 1 : slashes, L'\\');
        out += arg[i];
    }
    return out + L"\"";
}

// windhawk-cli.exe sits three folders above the engine
// (<Windhawk>\Engine\<version>\<arch>\windhawk.dll), next to windhawk.exe.
static std::wstring Set_CliPath() {
    WCHAR path[MAX_PATH];
    if (HMODULE engine = GetModuleHandleW(L"windhawk.dll"); engine && GetModuleFileNameW(engine, path, MAX_PATH)) {
        std::wstring dir = path;
        for (int i = 0; i < 4 && dir.find_last_of(L'\\') != std::wstring::npos; i++) dir.resize(dir.find_last_of(L'\\'));
        dir += L"\\windhawk-cli.exe";
        if (GetFileAttributesW(dir.c_str()) != INVALID_FILE_ATTRIBUTES) return dir;
    }
    if (GetModuleFileNameW(nullptr, path, MAX_PATH)) {
        std::wstring dir = path;
        dir.resize(dir.find_last_of(L'\\'));
        dir += L"\\windhawk-cli.exe";
        if (GetFileAttributesW(dir.c_str()) != INVALID_FILE_ATTRIBUTES) return dir;
    }
    return {};
}

// ---- Factories and fonts ---------------------------------------------------

static bool Set_EnsureFactories() {
    if (!g_setD2d) {
        D2D1_FACTORY_OPTIONS o{};
        if (FAILED(D2D1CreateFactory(D2D1_FACTORY_TYPE_SINGLE_THREADED, __uuidof(ID2D1Factory), &o,
                                     (void**)g_setD2d.put())))
            return false;
    }
    if (!g_setDw && FAILED(DWriteCreateFactory(DWRITE_FACTORY_TYPE_SHARED, __uuidof(IDWriteFactory),
                                               (IUnknown**)g_setDw.put())))
        return false;
    if (!g_setWic && FAILED(CoCreateInstance(CLSID_WICImagingFactory, nullptr, CLSCTX_INPROC_SERVER,
                                             __uuidof(IWICImagingFactory), (void**)g_setWic.put())))
        return false;
    return true;
}

static void Set_ReleaseFactories() {
    g_setWic.reset();
    g_setDw.reset();
    g_setD2d.reset();
}

static bool Set_FamilyExists(const std::wstring& name) {
    SetCom<IDWriteFontCollection> sys;
    if (name.empty() || FAILED(g_setDw->GetSystemFontCollection(sys.put(), FALSE))) return false;
    UINT32 index = 0;
    BOOL exists = FALSE;
    return SUCCEEDED(sys->FindFamilyName(name.c_str(), &index, &exists)) && exists;
}

// The font setting, or its Nerd Font build ("Fira Code" is installed as
// "FiraCode Nerd Font"), or Segoe UI.
static std::wstring Set_ResolveFamily() {
    if (Set_FamilyExists(std::wstring(L"FiraCode Nerd Font"))) return std::wstring(L"FiraCode Nerd Font");
    std::wstring joined;
    for (WCHAR c : std::wstring(L"FiraCode Nerd Font"))
        if (c != L' ') joined += c;
    for (const std::wstring& face : {joined + L" Nerd Font", std::wstring(L"FiraCode Nerd Font") + L" Nerd Font", joined})
        if (Set_FamilyExists(face)) return face;
    return L"Segoe UI";
}

static float Set_TextW(IDWriteTextFormat* fmt, const std::wstring& text);

static SetCom<IDWriteTextFormat> Set_Fmt(const std::wstring& family, float size, int weight, bool wrap,
                                         DWRITE_TEXT_ALIGNMENT align = DWRITE_TEXT_ALIGNMENT_LEADING,
                                         bool vcenter = false) {
    SetCom<IDWriteTextFormat> f;
    if (FAILED(g_setDw->CreateTextFormat(family.c_str(), nullptr, (DWRITE_FONT_WEIGHT)weight, DWRITE_FONT_STYLE_NORMAL,
                                         DWRITE_FONT_STRETCH_NORMAL, size, L"en-us", f.put())))
        return f;
    f->SetWordWrapping(wrap ? DWRITE_WORD_WRAPPING_WRAP : DWRITE_WORD_WRAPPING_NO_WRAP);
    f->SetTextAlignment(align);
    f->SetParagraphAlignment(vcenter ? DWRITE_PARAGRAPH_ALIGNMENT_CENTER : DWRITE_PARAGRAPH_ALIGNMENT_NEAR);
    if (!wrap) {
        SetCom<IDWriteInlineObject> sign;
        g_setDw->CreateEllipsisTrimmingSign(f.get(), sign.put());
        DWRITE_TRIMMING t{DWRITE_TRIMMING_GRANULARITY_CHARACTER, 0, 0};
        f->SetTrimming(&t, sign.get());
    }
    return f;
}

// std::wstring(L"FiraCode Nerd Font") at 500; emphasis is one step heavier, never past bold.
static float Set_MenuCornerRadius() {
    float radius = 8.0f;
    HKEY key;
    if (RegOpenKeyExW(HKEY_LOCAL_MACHINE, L"SOFTWARE\\Windhawk\\Engine\\Mods\\custom-corner-radius", 0,
                      KEY_READ | KEY_WOW64_64KEY, &key) == ERROR_SUCCESS) {
        DWORD disabled = 0, size = sizeof(disabled);
        bool off = RegQueryValueExW(key, L"Disabled", nullptr, nullptr, (BYTE*)&disabled, &size) == ERROR_SUCCESS && disabled;
        DWORD value = 0;
        size = sizeof(value);
        if (!off && RegGetValueW(key, L"Settings", L"radius", RRF_RT_REG_DWORD, nullptr, &value, &size) == ERROR_SUCCESS &&
            value > 0 && value <= 64)
            radius = (float)value;
        RegCloseKey(key);
    }
    return radius;
}

static SetMenuItem Set_MenuRow(int id, PCWSTR glyph, PCWSTR label, bool checked = false, bool disabled = false,
                               PCWSTR hint = L"") {
    SetMenuItem m;
    m.id = id;
    m.glyph = glyph ? glyph : L"";
    m.label = label ? label : L"";
    m.hint = hint ? hint : L"";
    m.checked = checked;
    m.disabled = disabled;
    return m;
}

static SetMenuItem Set_MenuSub(PCWSTR glyph, PCWSTR label, std::vector<SetMenuItem> sub, bool disabled = false) {
    SetMenuItem m = Set_MenuRow(0, glyph, label, false, disabled);
    m.sub = std::move(sub);
    return m;
}

static SetMenuItem Set_MenuSep() {
    SetMenuItem m;
    m.separator = true;
    return m;
}

static SetMenuSession*& Set_MenuCur() {
    static thread_local SetMenuSession* session = nullptr;  // One menu per thread; History menus run on the settings thread.
    return session;
}

static bool Set_MenuSelectable(const SetMenuItem& m) { return !m.separator && !m.disabled; }

static float Set_MenuTextW(SetMenuSession& s, IDWriteTextFormat* f, const std::wstring& text) {
    SetCom<IDWriteTextLayout> layout;
    DWRITE_TEXT_METRICS m{};
    if (text.empty() || !f || FAILED(s.dw->CreateTextLayout(text.c_str(), (UINT32)text.size(), f, 10000, 1000, layout.put())) ||
        FAILED(layout->GetMetrics(&m)))
        return 0;
    return m.widthIncludingTrailingWhitespace;
}

static bool Set_MenuFormats(SetMenuSession& s) {
    if (!s.d2d && FAILED(D2D1CreateFactory(D2D1_FACTORY_TYPE_SINGLE_THREADED, __uuidof(ID2D1Factory), nullptr,
                                           (void**)s.d2d.put())))
        return false;
    if (!s.dw && FAILED(DWriteCreateFactory(DWRITE_FACTORY_TYPE_SHARED, __uuidof(IDWriteFactory), (IUnknown**)s.dw.put())))
        return false;
    std::wstring family = L"Segoe UI";
    SetCom<IDWriteFontCollection> sys;
    if (SUCCEEDED(s.dw->GetSystemFontCollection(sys.put(), FALSE))) {
        for (PCWSTR face : {L"FiraCode Nerd Font", L"FiraCodeNerdFont", L"FiraCode Nerd Font Mono"}) {
            UINT32 index = 0;
            BOOL exists = FALSE;
            if (SUCCEEDED(sys->FindFamilyName(face, &index, &exists)) && exists) {
                family = face;
                break;
            }
        }
    }
    auto make = [&](float size, DWRITE_TEXT_ALIGNMENT align, SetCom<IDWriteTextFormat>& out) {
        if (FAILED(s.dw->CreateTextFormat(family.c_str(), nullptr, DWRITE_FONT_WEIGHT_NORMAL, DWRITE_FONT_STYLE_NORMAL,
                                          DWRITE_FONT_STRETCH_NORMAL, size, L"en-us", out.put())))
            return false;
        out->SetWordWrapping(DWRITE_WORD_WRAPPING_NO_WRAP);
        out->SetTextAlignment(align);
        out->SetParagraphAlignment(DWRITE_PARAGRAPH_ALIGNMENT_CENTER);
        // Only a label wider than the widest menu (kSetMenuMaxW) is ever shortened, with an ellipsis.
        DWRITE_TRIMMING trim{DWRITE_TRIMMING_GRANULARITY_CHARACTER, 0, 0};
        SetCom<IDWriteInlineObject> sign;
        if (SUCCEEDED(s.dw->CreateEllipsisTrimmingSign(out.get(), sign.put()))) out->SetTrimming(&trim, sign.get());
        return true;
    };
    return make(13.5f, DWRITE_TEXT_ALIGNMENT_LEADING, s.fText) && make(12.5f, DWRITE_TEXT_ALIGNMENT_TRAILING, s.fHint) &&
           make(15, DWRITE_TEXT_ALIGNMENT_CENTER, s.fGlyph) && make(12, DWRITE_TEXT_ALIGNMENT_CENTER, s.fGlyphS);
}

static void Set_MenuLayout(SetMenuSession& s, SetMenuLevel& lv) {
    const auto& items = *lv.items;
    lv.itemH = 30;
    lv.top.assign(items.size(), 0);
    lv.height.assign(items.size(), 0);
    float textW = 0, hintW = 0, y = kSetMenuPad;
    for (size_t i = 0; i < items.size(); i++) {
        lv.top[i] = y;
        lv.height[i] = items[i].separator ? kSetMenuSepH : lv.itemH;
        y += lv.height[i];
        if (items[i].separator) continue;
        textW = std::max(textW, Set_MenuTextW(s, s.fText.get(), items[i].label));
        hintW = std::max(hintW, Set_MenuTextW(s, s.fHint.get(), items[i].hint));
    }
    lv.hintW = std::ceil(hintW);
    float w = kSetMenuPad * 2 + 8 + kSetMenuIconW + 10 + std::ceil(textW) + 2 + (hintW > 0 ? 24 + lv.hintW : 0) + 10 + 20 + 8;
    lv.wDip = std::ceil(std::clamp(w, kSetMenuMinW, kSetMenuMaxW));
    lv.hDip = std::ceil(y + kSetMenuPad);
}

static int Set_MenuItemAt(const SetMenuLevel& lv, float x, float y) {
    if (x < kSetMenuPad || x >= lv.wDip - kSetMenuPad) return -1;
    for (size_t i = 0; i < lv.top.size(); i++)
        if (y >= lv.top[i] && y < lv.top[i] + lv.height[i]) return (*lv.items)[i].separator ? -1 : (int)i;
    return -1;
}

static int Set_MenuNext(const SetMenuLevel& lv, int from, int dir) {
    int n = (int)lv.items->size();
    if (!n) return -1;
    int i = from < 0 ? (dir > 0 ? -1 : n) : from;
    for (int k = 0; k < n; k++) {
        i = ((i + dir) % n + n) % n;
        if (Set_MenuSelectable((*lv.items)[(size_t)i])) return i;
    }
    return -1;
}

static void Set_MenuPaint(SetMenuSession& s, SetMenuLevel& lv) {
    ID2D1RenderTarget* rt = lv.rt.get();
    SetCom<ID2D1SolidColorBrush> brush;
    if (FAILED(rt->CreateSolidColorBrush(D2DColor(mocha::text), brush.put()))) return;
    auto solid = [&](UINT32 rgb, float a) {
        brush->SetColor(D2DColor(rgb, a));
        return brush.get();
    };
    auto gradient = [&](D2D1_POINT_2F a, D2D1_POINT_2F b, D2D1_COLOR_F c1, D2D1_COLOR_F c2) {
        SetCom<ID2D1LinearGradientBrush> g;
        D2D1_GRADIENT_STOP stops[2] = {{0, c1}, {1, c2}};
        SetCom<ID2D1GradientStopCollection> coll;
        if (SUCCEEDED(rt->CreateGradientStopCollection(stops, 2, coll.put())))
            rt->CreateLinearGradientBrush(D2D1::LinearGradientBrushProperties(a, b), coll.get(), g.put());
        return g;
    };
    // Blue to mauve at 45 degrees across a rect, like Seamless Borders.
    auto accent = [&](const D2D1_RECT_F& r, float a) {
        float d = ((r.right - r.left) + (r.bottom - r.top)) / 2;
        return gradient({r.left, r.top}, {r.left + d, r.top + d}, D2DColor(mocha::blue, a), D2DColor(mocha::mauve, a));
    };
    const float w = lv.wDip, h = lv.hDip;
    rt->Clear(D2D1::ColorF(0, 0, 0, 0));
    SetCom<ID2D1Layer> layer;
    bool faded = s.alpha < 0.999f && SUCCEEDED(rt->CreateLayer(nullptr, layer.put()));
    if (faded)
        rt->PushLayer(D2D1::LayerParameters(D2D1::InfiniteRect(), nullptr, D2D1_ANTIALIAS_MODE_PER_PRIMITIVE,
                                            D2D1::IdentityMatrix(), std::max(0.0f, s.alpha)),
                      layer.get());
    // Dark Mocha over the acrylic blur; DWM rounds the window.
    auto tint = gradient({0, 0}, {0, h}, D2DColor(mocha::base, 0.80f), D2DColor(mocha::base, 0.84f));
    if (tint) rt->FillRectangle({0, 0, w, h}, tint.get());
    const auto& items = *lv.items;
    const float slotRight = w - kSetMenuPad - 8, slotLeft = slotRight - 20;
    for (size_t i = 0; i < items.size(); i++) {
        const SetMenuItem& m = items[i];
        D2D1_RECT_F r{kSetMenuPad, lv.top[i], w - kSetMenuPad, lv.top[i] + lv.height[i]};
        if (m.separator) {
            float y = std::floor((r.top + r.bottom) / 2);
            rt->FillRectangle({r.left + 8, y, r.right - 8, y + 1}, solid(mocha::surface1, 0.8f));
            continue;
        }
        bool hot = ((int)i == lv.hover || (int)i == lv.open) && !m.disabled;
        if (hot) {
            // The hover look of every card: a faint blue to mauve wash and a 1 px gradient ring.
            float rad = 8, ringW = 1;
            D2D1_ROUNDED_RECT rr{{r.left + ringW / 2, r.top + ringW / 2, r.right - ringW / 2, r.bottom - ringW / 2}, rad, rad};
            auto fill = gradient({r.left, r.top}, {r.right, r.bottom}, D2DColor(mocha::blue, 0.16f), D2DColor(mocha::mauve, 0.16f));
            if (fill) rt->FillRoundedRectangle(rr, fill.get());
            auto ring = accent(r, 0.8f);
            if (ring) rt->DrawRoundedRectangle(rr, ring.get(), ringW);
        }
        UINT32 col = m.disabled ? mocha::overlay0 : mocha::text;
        if (!m.glyph.empty())
            rt->DrawText(m.glyph.c_str(), (UINT32)m.glyph.size(), s.fGlyph.get(),
                         {r.left + 8, r.top, r.left + 8 + kSetMenuIconW, r.bottom}, solid(col, 1));
        float textX = r.left + 8 + kSetMenuIconW + 10;
        float hintRight = slotLeft - 10, hintLeft = hintRight - lv.hintW;
        float textRight = lv.hintW > 0 ? hintLeft - 12 : slotLeft - 4;
        if (!m.label.empty())
            rt->DrawText(m.label.c_str(), (UINT32)m.label.size(), s.fText.get(), {textX, r.top, textRight, r.bottom},
                         solid(col, 1));
        if (!m.hint.empty())
            rt->DrawText(m.hint.c_str(), (UINT32)m.hint.size(), s.fHint.get(), {hintLeft, r.top, hintRight, r.bottom},
                         solid(m.disabled ? mocha::overlay0 : mocha::subtext0, 1));
        if (!m.sub.empty()) {
            rt->DrawText(L"\uEAB6", 1, s.fGlyphS.get(), {slotLeft, r.top, slotRight, r.bottom}, solid(col, 1));  // chevron_right
        } else if (m.checked) {
            rt->DrawText(L"\uEAB2", 1, s.fGlyph.get(), {slotLeft, r.top, slotRight, r.bottom},  // check
                         solid(m.disabled ? mocha::overlay0 : mocha::blue, 1));
        }
    }
    // The edge on DWM's real corner curve: 2 px, blue to mauve, inset half the stroke.
    const float bw = kSetMenuBorderW;
    D2D1_RECT_F edge{bw / 2, bw / 2, w - bw / 2, h - bw / 2};
    auto border = accent({0, 0, w, h}, 1);
    float r2 = std::max(0.0f, s.radius - bw / 2);
    if (border) rt->DrawRoundedRectangle({edge, r2, r2}, border.get(), bw);
    if (faded) rt->PopLayer();
}

static int Set_MenuIndexOf(HWND hwnd) {
    if (SetMenuSession* s = Set_MenuCur())
        for (size_t i = 0; i < s->levels.size(); i++)
            if (s->levels[i]->hwnd == hwnd) return (int)i;
    return -1;
}

static void Set_MenuInvalidate() {
    if (SetMenuSession* s = Set_MenuCur())
        for (auto& lv : s->levels)
            if (lv->hwnd) InvalidateRect(lv->hwnd, nullptr, FALSE);
}

static void Set_MenuCloseFrom(size_t n) {
    SetMenuSession* s = Set_MenuCur();
    if (!s) return;
    while (s->levels.size() > n) {
        HWND h = s->levels.back()->hwnd;
        s->levels.back()->rt.reset();
        s->levels.pop_back();
        if (h) DestroyWindow(h);
    }
    if (n > 0 && !s->levels.empty()) s->levels.back()->open = -1;
    Set_MenuInvalidate();
}

static void Set_MenuFinish(int id) {
    SetMenuSession* s = Set_MenuCur();
    if (!s || s->done) return;
    s->result = id;
    s->done = true;
}

static void Set_MenuBackdrop(HWND hwnd) {
    BOOL dark = TRUE;
    DwmSetWindowAttribute(hwnd, 20 /* DWMWA_USE_IMMERSIVE_DARK_MODE */, &dark, sizeof(dark));
    int corner = 2;  // DWMWCP_ROUND
    DwmSetWindowAttribute(hwnd, 33 /* DWMWA_WINDOW_CORNER_PREFERENCE */, &corner, sizeof(corner));
    COLORREF none = 0xFFFFFFFE;  // DWMWA_COLOR_NONE: the menu draws its own edge.
    DwmSetWindowAttribute(hwnd, 34 /* DWMWA_BORDER_COLOR */, &none, sizeof(none));
    DwmSetWindowAttribute(hwnd, 35 /* DWMWA_CAPTION_COLOR */, &none, sizeof(none));
    int backdrop = 1;  // DWMSBT_NONE
    DwmSetWindowAttribute(hwnd, 38 /* DWMWA_SYSTEMBACKDROP_TYPE */, &backdrop, sizeof(backdrop));
    DWM_BLURBEHIND bb{};
    bb.dwFlags = DWM_BB_ENABLE | DWM_BB_BLURREGION;
    bb.fEnable = TRUE;
    bb.hRgnBlur = CreateRectRgn(0, 0, -1, -1);
    DwmEnableBlurBehindWindow(hwnd, &bb);
    if (bb.hRgnBlur) DeleteObject(bb.hRgnBlur);
    struct SetAccentPolicy { int state, flags, abgr, animation; };
    struct SetCompositionData { DWORD attribute; void* data; SIZE_T size; };
    using SetComposition_t = BOOL(WINAPI*)(HWND, SetCompositionData*);
    if (auto setComposition =
            (SetComposition_t)(void*)GetProcAddress(GetModuleHandleW(L"user32.dll"), "SetWindowCompositionAttribute")) {
        SetAccentPolicy policy{4 /* ACCENT_ENABLE_ACRYLICBLURBEHIND */, 2, (int)0x012E1E1E, 0};
        SetCompositionData data{19 /* WCA_ACCENT_POLICY */, &policy, sizeof(policy)};
        setComposition(hwnd, &data);
    }
}

static RECT Set_MenuWorkArea(POINT pt) {
    MONITORINFO mi{sizeof(mi)};
    GetMonitorInfoW(MonitorFromPoint(pt, MONITOR_DEFAULTTONEAREST), &mi);
    return mi.rcWork;
}

static bool Set_MenuCreateWindow(SetMenuSession& s, SetMenuLevel& lv, POINT at, const RECT* parent, int rowTopPx) {
    DWORD ex = WS_EX_TOOLWINDOW | WS_EX_TOPMOST | (parent ? WS_EX_NOACTIVATE : 0);
    HWND hwnd = CreateWindowExW(ex, s.cls.c_str(), L"", WS_POPUP, at.x, at.y, 1, 1, nullptr, nullptr, s.inst, nullptr);
    if (!hwnd) return false;
    lv.hwnd = hwnd;
    lv.scale = GetDpiForWindow(hwnd) / 96.0f;
    if (lv.scale <= 0) lv.scale = 1;
    Set_MenuLayout(s, lv);
    int w = (int)std::ceil(lv.wDip * lv.scale), h = (int)std::ceil(lv.hDip * lv.scale);
    RECT wa = Set_MenuWorkArea(parent ? POINT{parent->right, parent->top + rowTopPx} : at);
    int x = at.x, y = at.y;
    if (parent) {
        int overlap = (int)kSetMenuOverlap;
        x = parent->right - overlap;
        if (x + w > wa.right) x = parent->left - w + overlap;
        y = parent->top + rowTopPx - (int)(kSetMenuPad * lv.scale);
        if (y + h > wa.bottom) y = wa.bottom - h;
    } else {
        if (x + w > wa.right) x = at.x - w;
        if (y + h > wa.bottom) y = at.y - h;
    }
    x = std::clamp<int>(x, wa.left, std::max<int>(wa.left, wa.right - w));
    y = std::clamp<int>(y, wa.top, std::max<int>(wa.top, wa.bottom - h));
    Set_MenuBackdrop(hwnd);
    SetWindowPos(hwnd, HWND_TOPMOST, x, y, w, h, SWP_NOACTIVATE | SWP_FRAMECHANGED);
    D2D1_RENDER_TARGET_PROPERTIES props = D2D1::RenderTargetProperties(
        D2D1_RENDER_TARGET_TYPE_DEFAULT, D2D1::PixelFormat(DXGI_FORMAT_B8G8R8A8_UNORM, D2D1_ALPHA_MODE_PREMULTIPLIED),
        96 * lv.scale, 96 * lv.scale);
    s.d2d->CreateHwndRenderTarget(props, D2D1::HwndRenderTargetProperties(hwnd, D2D1::SizeU((UINT32)w, (UINT32)h)),
                                  lv.rt.put());
    return (bool)lv.rt;
}

static void Set_MenuOpenSub(size_t level, int item, bool keyboard) {
    SetMenuSession* s = Set_MenuCur();
    if (!s || level >= s->levels.size()) return;
    SetMenuLevel& parent = *s->levels[level];
    const SetMenuItem& m = (*parent.items)[(size_t)item];
    if (m.sub.empty() || m.disabled) return;
    Set_MenuCloseFrom(level + 1);
    auto lv = std::make_unique<SetMenuLevel>();
    lv->items = &m.sub;
    RECT pr{};
    GetWindowRect(parent.hwnd, &pr);
    SetMenuLevel* raw = lv.get();
    s->levels.push_back(std::move(lv));
    parent.open = item;
    if (!Set_MenuCreateWindow(*s, *raw, POINT{pr.right, pr.top}, &pr, (int)(parent.top[(size_t)item] * parent.scale))) {
        Set_MenuCloseFrom(level + 1);
        return;
    }
    if (keyboard) raw->hover = Set_MenuNext(*raw, -1, +1);
    ShowWindow(raw->hwnd, SW_SHOWNOACTIVATE);
    Set_MenuInvalidate();
}

static void Set_MenuActivate(size_t level, int item, bool keyboard) {
    SetMenuSession* s = Set_MenuCur();
    if (!s || level >= s->levels.size()) return;
    const SetMenuItem& m = (*s->levels[level]->items)[(size_t)item];
    if (!Set_MenuSelectable(m)) return;
    if (!m.sub.empty()) Set_MenuOpenSub(level, item, keyboard);
    else Set_MenuFinish(m.id);
}

static void Set_MenuHoverChanged(size_t level, int item) {
    SetMenuSession* s = Set_MenuCur();
    if (!s) return;
    SetMenuLevel& lv = *s->levels[level];
    HWND root = s->levels[0]->hwnd;
    KillTimer(root, kSetMenuTimerSub);
    s->pendingItem = -1;
    bool wantsSub = item >= 0 && Set_MenuSelectable((*lv.items)[(size_t)item]) && !(*lv.items)[(size_t)item].sub.empty();
    if (wantsSub && lv.open != item) {
        s->pendingLevel = (int)level;
        s->pendingItem = item;
        SetTimer(root, kSetMenuTimerSub, kSetMenuSubDelayMs, nullptr);
    } else if (!wantsSub && lv.open != -1 && s->levels.size() > level + 1) {
        s->pendingLevel = (int)level;
        s->pendingItem = -1;
        SetTimer(root, kSetMenuTimerSub, kSetMenuSubDelayMs, nullptr);
    }
}

static void Set_MenuKey(WPARAM vk) {
    SetMenuSession* s = Set_MenuCur();
    if (!s || s->levels.empty()) return;
    size_t li = s->levels.size() - 1;
    SetMenuLevel& cur = *s->levels[li];
    const auto& items = *cur.items;
    switch (vk) {
        case VK_DOWN: cur.hover = Set_MenuNext(cur, cur.hover, +1); break;
        case VK_UP: cur.hover = Set_MenuNext(cur, cur.hover, -1); break;
        case VK_HOME: cur.hover = Set_MenuNext(cur, -1, +1); break;
        case VK_END: cur.hover = Set_MenuNext(cur, (int)items.size(), -1); break;
        case VK_RIGHT:
            if (cur.hover >= 0 && !items[(size_t)cur.hover].sub.empty()) Set_MenuActivate(li, cur.hover, true);
            break;
        case VK_LEFT:
            if (li > 0) Set_MenuCloseFrom(li);
            break;
        case VK_RETURN:
        case VK_SPACE:
            if (cur.hover >= 0) Set_MenuActivate(li, cur.hover, true);
            break;
        case VK_ESCAPE:
        case VK_MENU:
            if (li > 0 && vk == VK_ESCAPE) Set_MenuCloseFrom(li);
            else Set_MenuFinish(0);
            break;
        default: return;
    }
    Set_MenuInvalidate();
}

static LRESULT CALLBACK Set_MenuProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) {
    SetMenuSession* s = Set_MenuCur();
    int li = Set_MenuIndexOf(hwnd);
    if (!s || li < 0) return DefWindowProcW(hwnd, msg, wParam, lParam);
    SetMenuLevel& lv = *s->levels[(size_t)li];
    switch (msg) {
        case WM_ERASEBKGND: return 1;
        case WM_MOUSEACTIVATE: return li == 0 ? MA_ACTIVATE : MA_NOACTIVATE;
        case WM_PAINT: {
            PAINTSTRUCT ps;
            BeginPaint(hwnd, &ps);
            if (lv.rt) {
                lv.rt->BeginDraw();
                Set_MenuPaint(*s, lv);
                if (lv.rt->EndDraw() == D2DERR_RECREATE_TARGET) {
                    RECT rc;
                    GetClientRect(hwnd, &rc);
                    lv.rt.reset();
                    D2D1_RENDER_TARGET_PROPERTIES props = D2D1::RenderTargetProperties(
                        D2D1_RENDER_TARGET_TYPE_DEFAULT,
                        D2D1::PixelFormat(DXGI_FORMAT_B8G8R8A8_UNORM, D2D1_ALPHA_MODE_PREMULTIPLIED), 96 * lv.scale,
                        96 * lv.scale);
                    s->d2d->CreateHwndRenderTarget(
                        props, D2D1::HwndRenderTargetProperties(hwnd, D2D1::SizeU((UINT32)rc.right, (UINT32)rc.bottom)),
                        lv.rt.put());
                    InvalidateRect(hwnd, nullptr, FALSE);
                }
            }
            EndPaint(hwnd, &ps);
            return 0;
        }
        case WM_MOUSEMOVE: {
            if (s->pendingLevel > li) {  // The pointer reached a deeper level: keep it open.
                KillTimer(s->levels[0]->hwnd, kSetMenuTimerSub);
                s->pendingItem = s->pendingLevel = -1;
            }
            TRACKMOUSEEVENT tme{sizeof(tme), TME_LEAVE, hwnd, 0};
            TrackMouseEvent(&tme);
            int i = Set_MenuItemAt(lv, (short)LOWORD(lParam) / lv.scale, (short)HIWORD(lParam) / lv.scale);
            if (i >= 0 && !Set_MenuSelectable((*lv.items)[(size_t)i])) i = -1;
            if (i != lv.hover) {
                lv.hover = i;
                Set_MenuHoverChanged((size_t)li, i);
                Set_MenuInvalidate();
            }
            return 0;
        }
        case WM_MOUSELEAVE:
            if (lv.hover != -1 && lv.open != lv.hover) {
                lv.hover = -1;
                InvalidateRect(hwnd, nullptr, FALSE);
            }
            return 0;
        case WM_LBUTTONUP:
        case WM_RBUTTONUP: {
            if (!s->pressed) return 0;  // The release of the click that opened the menu.
            int i = Set_MenuItemAt(lv, (short)LOWORD(lParam) / lv.scale, (short)HIWORD(lParam) / lv.scale);
            if (i >= 0) Set_MenuActivate((size_t)li, i, false);
            return 0;
        }
        case WM_ACTIVATE:
            if (li == 0 && LOWORD(wParam) != WA_INACTIVE) s->wasActive = true;
            if (li == 0 && LOWORD(wParam) == WA_INACTIVE && Set_MenuIndexOf((HWND)lParam) < 0) Set_MenuFinish(0);
            return 0;
        case WM_TIMER:
            if (wParam == kSetMenuTimerSub) {
                KillTimer(hwnd, kSetMenuTimerSub);
                int pl = s->pendingLevel, pi = s->pendingItem;
                s->pendingLevel = s->pendingItem = -1;
                if (pl >= 0 && (size_t)pl < s->levels.size()) {
                    if (pi >= 0) Set_MenuOpenSub((size_t)pl, pi, false);
                    else Set_MenuCloseFrom((size_t)pl + 1);
                }
            } else if (wParam == kSetMenuTimerFade) {
                float t = std::min(1.0f, (GetTickCount64() - s->fadeStart) / (float)kSetMenuFadeMs);
                s->alpha = 1 - (1 - t) * (1 - t);
                if (t >= 1) KillTimer(hwnd, kSetMenuTimerFade);
                Set_MenuInvalidate();
            } else if (wParam == kSetMenuTimerPoll) {
                // Click-away when Windows kept the menu out of the foreground: a press outside every level.
                if (GetForegroundWindow() != s->levels[0]->hwnd &&
                    ((GetAsyncKeyState(VK_LBUTTON) | GetAsyncKeyState(VK_RBUTTON) | GetAsyncKeyState(VK_MBUTTON)) & 0x8000)) {
                    POINT pt;
                    GetCursorPos(&pt);
                    if (Set_MenuIndexOf(WindowFromPoint(pt)) < 0) Set_MenuFinish(0);
                }
            }
            return 0;
    }
    return DefWindowProcW(hwnd, msg, wParam, lParam);
}

static int Set_TrayMenu(HWND owner, const std::vector<SetMenuItem>& items, const POINT* at = nullptr) {
    if (Set_MenuCur()) {  // A second right-click while open closes the first menu.
        Set_MenuFinish(0);
        return 0;
    }
    if (items.empty()) return 0;
    POINT pt{};
    if (at) pt = *at;
    else GetCursorPos(&pt);
    SetMenuSession session;
    if (!Set_MenuFormats(session)) return 0;
    GetModuleHandleExW(GET_MODULE_HANDLE_EX_FLAG_FROM_ADDRESS | GET_MODULE_HANDLE_EX_FLAG_UNCHANGED_REFCOUNT,
                       (LPCWSTR)(void*)&Set_MenuProc, &session.inst);
    // One class per mod, even when several mods share a process.
    session.cls = L"SeamlessTrayMenu_" + std::to_wstring((unsigned long long)(uintptr_t)(void*)&Set_MenuProc);
    PCWSTR cls = session.cls.c_str();
    WNDCLASSEXW wc{sizeof(wc)};
    wc.hInstance = session.inst;
    wc.hCursor = LoadCursorW(nullptr, IDC_ARROW);
    wc.lpfnWndProc = Set_MenuProc;
    wc.lpszClassName = cls;
    RegisterClassExW(&wc);
    session.radius = Set_MenuCornerRadius();
    Set_MenuCur() = &session;
    session.levels.push_back(std::make_unique<SetMenuLevel>());
    SetMenuLevel* root = session.levels[0].get();
    root->items = &items;
    if (!Set_MenuCreateWindow(session, *root, pt, nullptr, 0)) {
        Set_MenuCloseFrom(0);
        Set_MenuCur() = nullptr;
        UnregisterClassW(cls, session.inst);
        return 0;
    }
    BOOL animations = TRUE;
    SystemParametersInfoW(SPI_GETCLIENTAREAANIMATION, 0, &animations, 0);
    session.alpha = animations ? 0.0f : 1.0f;
    session.fadeStart = GetTickCount64();
    if (owner && IsWindow(owner)) SetForegroundWindow(owner);  // Windows' tray rule; lets the menu take the foreground.
    ShowWindow(root->hwnd, SW_SHOW);
    if (!SetForegroundWindow(root->hwnd)) {
        DWORD fg = GetWindowThreadProcessId(GetForegroundWindow(), nullptr), me = GetCurrentThreadId();
        if (fg && fg != me && AttachThreadInput(me, fg, TRUE)) {
            SetForegroundWindow(root->hwnd);
            AttachThreadInput(me, fg, FALSE);
        }
    }
    SetFocus(root->hwnd);
    if (animations) SetTimer(root->hwnd, kSetMenuTimerFade, 15, nullptr);
    SetTimer(root->hwnd, kSetMenuTimerPoll, 50, nullptr);
    MSG m;
    while (!session.done) {
        BOOL got = GetMessageW(&m, nullptr, 0, 0);
        if (got <= 0) {
            if (got == 0) PostQuitMessage((int)m.wParam);
            break;
        }
        switch (m.message) {
            case WM_KEYDOWN:
            case WM_SYSKEYDOWN:
                Set_MenuKey(m.wParam);
                continue;
            case WM_KEYUP:
            case WM_SYSKEYUP:
            case WM_CHAR:
            case WM_SYSCHAR:
                continue;
            case WM_LBUTTONDOWN:
            case WM_RBUTTONDOWN:
            case WM_MBUTTONDOWN:
            case WM_NCLBUTTONDOWN:
            case WM_NCRBUTTONDOWN:
                if (Set_MenuIndexOf(m.hwnd) < 0) {  // A click on another window of this thread closes the menu.
                    Set_MenuFinish(0);
                    continue;
                }
                session.pressed = true;
                break;
        }
        TranslateMessage(&m);
        DispatchMessageW(&m);
    }
    int result = session.result;
    Set_MenuCloseFrom(0);
    Set_MenuCur() = nullptr;
    UnregisterClassW(cls, session.inst);
    if (owner && IsWindow(owner)) PostMessageW(owner, WM_NULL, 0, 0);
    return result;
}

static void Set_MakeFormats(SetWindow& w) {
    w.family = Set_ResolveFamily();
    w.iconFamily = Set_FamilyExists(L"Segoe Fluent Icons") ? L"Segoe Fluent Icons" : L"Segoe MDL2 Assets";
    int base = std::clamp(500, 100, 900);
    int bold = std::max(base, std::min(700, base + 100));
    const auto L_ = DWRITE_TEXT_ALIGNMENT_LEADING, C_ = DWRITE_TEXT_ALIGNMENT_CENTER;
    w.fLabel = Set_Fmt(w.family, 16, base, true);
    w.fHint = Set_Fmt(w.family, 12.5f, base, true);
    w.fTitle = Set_Fmt(w.family, 26, bold, false);
    w.fIntro = Set_Fmt(w.family, 13.5f, base, true);
    w.fSection = Set_Fmt(w.family, 10.5f, bold, false);
    w.fValue = Set_Fmt(w.family, 13, base, false, L_, true);
    w.fValueC = Set_Fmt(w.family, 13, base, false, C_, true);
    w.fButton = Set_Fmt(w.family, 13.5f, bold, false, C_, true);
    w.fBig = Set_Fmt(w.family, 20, bold, false);
    w.fSmall = Set_Fmt(w.family, 12, base, false, L_, true);
    w.fIcon = Set_Fmt(w.iconFamily, 16, 400, false, C_, true);
    w.fIconS = Set_Fmt(w.iconFamily, 12, 400, false, C_, true);
    w.fIconL = Set_Fmt(w.iconFamily, 34, 400, false, C_, true);
    w.fCap = Set_Fmt(w.family, 13, bold, false, L_, true);
    w.fCapGlyph = Set_Fmt(w.iconFamily, 10, 400, false, C_, true);
    w.fStatusLine = Set_Fmt(w.family, 12.5f, base, false, L_, true);
    // The sidebar name must never clip at the narrowest open width: 18 down to 15.5 (above 85%).
    const float railW = kSetRailMin - 90 - 10;
    for (float size = 18; size >= 15.5f; size -= 0.5f) {
        w.fRailName = Set_Fmt(w.family, size, bold, false, L_, true);
        if (w.fRailName && Set_TextW(w.fRailName.get(), L"FPS Overlay") <= railW) break;
    }
}

// ---- Values ----------------------------------------------------------------

static std::wstring Set_FieldValue(const SetField& f) {
    switch (f.kind) {
        case SetField::Number: {
            if (f.cur.empty()) return f.value;
            return std::to_wstring(std::clamp(_wtoi(f.cur.c_str()), f.min, f.max));
        }
        case SetField::Check:
            return f.cur == L"0" || f.cur.empty() ? L"0" : L"1";
        default:
            return f.cur;
    }
}

static void Set_PutValue(SetField& f, const std::wstring& value) {
    switch (f.kind) {
        case SetField::Choice: {
            int index = -1;
            for (size_t i = 0; i < f.options.size(); i++) {
                if (value == f.options[i].first) index = (int)i;
            }
            for (size_t i = 0; index < 0 && i < f.options.size(); i++) {
                if (wcscmp(f.def, f.options[i].first) == 0) index = (int)i;
            }
            f.cur = f.options[std::max(index, 0)].first;
            break;
        }
        case SetField::Check:
            f.cur = value != L"0" && !value.empty() ? L"1" : L"0";
            break;
        default:
            f.cur = value;
    }
}

static void Set_LoadFields(SetWindow& w) {
    for (auto& f : w.fields) {
        bool isInt = f.kind == SetField::Number || f.kind == SetField::Check;
        Set_PutValue(f, isInt ? std::to_wstring(Wh_GetIntSetting(f.key)) : GetStringSetting(f.key));
        f.value = Set_FieldValue(f);  // What the window shows, so an untouched field never saves.
    }
}

static int Set_ChangedCount(const SetWindow& w) {
    int n = 0;
    for (auto& f : w.fields)
        if (Set_FieldValue(f) != f.value) n++;
    return n;
}

static bool Set_ParseHex(const std::wstring& text, UINT32& rgb) {
    if (text.size() != 7 || text[0] != L'#') return false;
    UINT32 v = 0;
    for (size_t i = 1; i < 7; i++) {
        WCHAR c = text[i];
        int d = c >= L'0' && c <= L'9' ? c - L'0' : c >= L'a' && c <= L'f' ? c - L'a' + 10 : c >= L'A' && c <= L'F' ? c - L'A' + 10 : -1;
        if (d < 0) return false;
        v = v * 16 + (UINT32)d;
    }
    rgb = v;
    return true;
}

static std::wstring Set_HexFromRgb(UINT32 rgb) {
    WCHAR text[16];
    swprintf_s(text, L"#%06X", rgb & 0xFFFFFF);
    return text;
}

static const wchar_t* Set_ChoiceLabel(const SetField& f) {
    for (auto& o : f.options)
        if (f.cur == o.first) return o.second;
    return f.options.empty() ? L"" : f.options[0].second;
}

static bool Set_Anim(const SetWindow& w) {
    BOOL on = TRUE;
    SystemParametersInfoW(SPI_GETCLIENTAREAANIMATION, 0, &on, 0);
    return !w.render && on;
}

static void Set_Invalidate(SetWindow& w) {
    if (w.hwnd && !w.render) InvalidateRect(w.hwnd, nullptr, FALSE);
}

static void Set_SetStatus(SetWindow& w, PCWSTR text, bool error = false) {
    w.status = text;
    w.statusError = error;
    Set_Invalidate(w);
}

// ---- Text measuring ---------------------------------------------------------

static float Set_TextH(IDWriteTextFormat* fmt, const std::wstring& text, float width) {
    SetCom<IDWriteTextLayout> l;
    if (!fmt || FAILED(g_setDw->CreateTextLayout(text.c_str(), (UINT32)text.size(), fmt, width, 10000, l.put())))
        return 18;
    DWRITE_TEXT_METRICS m{};
    l->GetMetrics(&m);
    return m.height;
}

static float Set_TextW(IDWriteTextFormat* fmt, const std::wstring& text) {
    SetCom<IDWriteTextLayout> l;
    if (!fmt || FAILED(g_setDw->CreateTextLayout(text.c_str(), (UINT32)text.size(), fmt, 10000, 100, l.put())))
        return 0;
    DWRITE_TEXT_METRICS m{};
    l->GetMetrics(&m);
    return m.widthIncludingTrailingWhitespace;
}

// ---- Layout -----------------------------------------------------------------

// The right-hand control's width, so the label column knows how much room it has.
static bool Set_FitBoxes(SetWindow& w) {
    if (!w.fValue) return false;
    bool changed = false;
    const float cap = std::floor(w.contentW * 0.5f);
    for (auto& f : w.fields) {
        float base, pad;
        std::wstring text;
        if (f.kind == SetField::Choice) {
            base = 200, pad = 46;  // 12 before the text, 30 for the arrow, 4 spare.
            for (const auto& o : f.options) text += std::wstring(o.second) + L'\n';
        } else if (f.kind == SetField::Hotkey) {
            base = 220, pad = 60;  // The key cap's own padding and the clear button.
            text = f.cur;
        } else if (f.kind == SetField::Text) {
            base = 280, pad = 26;
            text = f.cur;
        } else {
            continue;
        }
        if (f.fitText < 0 || text != f.fitFor) {
            float m = 0;
            if (f.kind == SetField::Choice) {
                for (const auto& o : f.options) m = std::max(m, Set_TextW(w.fValue.get(), o.second));
            } else {
                m = Set_TextW(w.fValue.get(), f.cur);
            }
            f.fitText = std::ceil(m);
            f.fitFor = text;
        }
        float want = std::min(std::max(base, f.fitText + pad), std::max(base, cap));
        if (fabsf(want - f.fitW) > 0.5f) {
            f.fitW = want;
            changed = true;
        }
    }
    return changed;
}

static float Set_FitOr(const SetField& f, float base) { return f.fitW > 0 ? f.fitW : base; }

static float Set_ControlW(const SetField& f) {
    switch (f.kind) {
        case SetField::Check: return 40;
        case SetField::Choice: return Set_FitOr(f, 200);
        case SetField::Number: return f.max - f.min <= 100 ? 150 + 12 + 64 : 96;
        case SetField::Text: return Set_FitOr(f, 280);
        case SetField::Hotkey: return Set_FitOr(f, 220);
        case SetField::Color: return 362;
    }
    return 100;
}

// The page scrolls under the floating footer, so the view is the full height; contentH carries
// a bottom margin (Set_FootClear) so the last row can rise above the footer.
static float Set_ViewH(const SetWindow& w) { return w.ch; }
static float Set_FootClear() { return kSetFootH + kSetFootGap + 18; }

static D2D1_RECT_F Set_RailDock(const SetWindow& w) {
    return {kSetDockGap, kSetDockGap, kSetDockGap + w.railCur, std::max(kSetDockGap + 120, w.ch - kSetDockGap)};
}
// Right edge of the sidebar dock: the page starts after it.
static float Set_RailSpace(const SetWindow& w) { return kSetDockGap + w.railCur; }
// 0 collapsed to the icon rail, 1 fully open.
static float Set_RailOpen(const SetWindow& w) {
    return std::clamp((w.railCur - kSetRailMini) / std::max(1.0f, w.railW - kSetRailMini), 0.0f, 1.0f);
}
static D2D1_RECT_F Set_RailToggleRect(const SetWindow& w) {
    D2D1_RECT_F d = Set_RailDock(w);
    return {d.left + 12, d.top + 14, d.left + 48, d.top + 50};
}

// Everything a field's control is made of, in window DIPs for a given row.
struct SetParts {
    D2D1_RECT_F box{}, track{}, clear{}, chip[kSetChipCount]{};
    bool slider = false;
};

static SetParts Set_Parts(const SetField& f, const D2D1_RECT_F& row) {
    SetParts p;
    float r = row.right - kSetRowPad, mid = (row.top + row.bottom) / 2, h = kSetBoxH / 2;
    switch (f.kind) {
        case SetField::Check:
            p.box = {r - 40, mid - 11, r, mid + 11};
            break;
        case SetField::Choice:
            p.box = {r - Set_FitOr(f, 200), mid - h, r, mid + h};
            break;
        case SetField::Number:
            if (f.max - f.min <= 100) {
                p.slider = true;
                p.box = {r - 64, mid - h, r, mid + h};
                p.track = {p.box.left - 12 - 150, mid - 2, p.box.left - 12, mid + 2};
            } else {
                p.box = {r - 96, mid - h, r, mid + h};
            }
            break;
        case SetField::Text:
            p.box = {r - Set_FitOr(f, 280), mid - h, r, mid + h};
            break;
        case SetField::Hotkey:
            p.box = {r - Set_FitOr(f, 220), mid - h, r, mid + h};
            p.clear = {p.box.right - 30, p.box.top, p.box.right, p.box.bottom};
            break;
        case SetField::Color: {
            p.box = {r - 96, mid - h, r, mid + h};
            float x = p.box.left - 12 - (kSetChipCount * 26 - 6);
            for (int i = 0; i < kSetChipCount; i++) p.chip[i] = {x + i * 26, mid - 10, x + i * 26 + 20, mid + 10};
            break;
        }
    }
    return p;
}

static bool Set_In(const D2D1_RECT_F& r, float x, float y) { return x >= r.left && x < r.right && y >= r.top && y < r.bottom; }

static D2D1_RECT_F Set_RowRect(const SetWindow& w, const SetItem& it) {
    return {w.contentX, it.y, w.contentX + w.contentW, it.y + it.h};  // Content y (not scrolled).
}

// Lays out the current page's items for the current width.
static void Set_BuildPage(SetWindow& w) {
    w.items.clear();
    const float space = Set_RailSpace(w), avail = w.cw - space;
    w.contentW = std::clamp(avail - 2 * kSetPadX, 420.0f, kSetMaxW);
    w.contentX = space + std::max(kSetPadX, (avail - w.contentW) / 2);
    float introH = Set_TextH(w.fIntro.get(), kSetPages[w.page].intro, w.contentW);
    float y = 36 + 36 + 4 + introH + 24;
    if (w.page == 0) {
        std::wstring status = Set_KeyStatusText();
        if (!status.empty()) {
            SetItem it;
            it.type = SetItem::Banner;
            it.text = status;
            it.y = y;
            it.h = Set_TextH(w.fHint.get(), status, w.contentW - 32) + 28;
            y += it.h + kSetRowGap + 8;
            w.items.push_back(it);
        }
    }
    PCWSTR lastGroup = nullptr;
    for (size_t k = 0; k < w.fields.size(); k++) {
        const SetField& f = w.fields[k];
        if (f.page != w.page) continue;
        if (!lastGroup || wcscmp(lastGroup, f.group) != 0) {
            SetItem g;
            g.type = SetItem::Group;
            g.text = f.group;
            y += lastGroup ? 14 : 0;
            g.y = y;
            g.h = 22;
            y += g.h + 6;
            w.items.push_back(g);
            lastGroup = f.group;
        }
        SetItem it;
        it.type = SetItem::Row;
        it.field = (int)k;
        float textW = w.contentW - 2 * kSetRowPad - Set_ControlW(f) - 24;
        float lh = Set_TextH(w.fLabel.get(), f.label, textW);
        float dh = f.desc ? Set_TextH(w.fHint.get(), f.desc, textW) + 3 : 0;
        it.y = y;
        it.h = std::max(kSetRowMin, 28 + lh + dh);
        y += it.h + kSetRowGap;
        w.items.push_back(it);
    }
    if (w.page == kSetAboutPage) {
        auto add = [&](SetItem::Type t, float h, PCWSTR text, PCWSTR sub, PCWSTR url) {
            SetItem it;
            it.type = t;
            it.y = y;
            it.h = h;
            it.text = text;
            it.sub = sub;
            it.url = url;
            y += h + kSetRowGap;
            w.items.push_back(it);
        };
        auto group = [&](PCWSTR text) {
            SetItem g;
            g.type = SetItem::Group;
            g.text = text;
            g.y = y + 14;
            g.h = 22;
            y = g.y + g.h + 6;
            w.items.push_back(g);
        };
        add(SetItem::About, 146, L"", L"", L"");
        add(SetItem::Support, 84, L"Like it? Help the mod keep going.",
            L"Free and open source. A tip on Ko-fi keeps it moving.", kSetKofiUrl);
        group(L"Author");
        add(SetItem::Link, 56, L"DavidHiFi on GitHub", L"github.com/DavidHiFi", kSetAuthorUrl);
        add(SetItem::Link, 56, L"Ko-fi", L"ko-fi.com/DavidHiFi", kSetKofiUrl);
        group(L"Credits");
        add(SetItem::Link, 56, L"PawnIO", L"The driver behind the processor readings", kSetDittoUrl);
        add(SetItem::Link, 56, L"PawnIO modules by namazso", L"LGPL-2.1 license", kSetKsUrl);
        group(L"Project");
        add(SetItem::Link, 56, L"Project page on GitHub", L"github.com/DavidHiFi/davids-windhawk-mods", kSetRepoUrl);
        add(SetItem::Link, 56, L"Report a problem", L"Opens a new issue on GitHub, with the mod's name filled in", kSetBugUrl);
    }
    w.contentH = y + Set_FootClear();
    w.scrollTarget = std::clamp(w.scrollTarget, 0.0f, std::max(0.0f, w.contentH - Set_ViewH(w)));
    w.scrollY = std::clamp(w.scrollY, 0.0f, std::max(0.0f, w.contentH - Set_ViewH(w)));
}

static const SetItem* Set_ItemOfField(const SetWindow& w, int field) {
    for (auto& it : w.items)
        if (it.type == SetItem::Row && it.field == field) return &it;
    return nullptr;
}

// The footer's status line: an explicit message, else the count of unsaved changes.
static std::wstring Set_FooterStatus(const SetWindow& w, UINT32* color) {
    std::wstring status = w.status;
    if (color) *color = w.statusError ? mocha::red : (status == L"Saved" ? mocha::green : mocha::subtext0);
    int changed = Set_ChangedCount(w);
    if (status.empty() && changed)
        status = changed == 1 ? L"1 change not saved" : std::to_wstring(changed) + L" changes not saved";
    return status;
}

constexpr float kSetFootW[3] = {172, 96, 100};  // Reset to suggested, Cancel, Save.

static float Set_FooterButtonsW() { return kSetFootW[0] + kSetFootW[1] + kSetFootW[2] + 2 * 8; }

// Width the status text gets inside the footer dock (0 when there is none).
static float Set_FooterStatusW(const SetWindow& w) {
    std::wstring s = Set_FooterStatus(w, nullptr);
    if (s.empty()) return 0;
    float room = w.contentW - Set_FooterButtonsW() - 2 * kSetFootPad - 30;
    return std::max(0.0f, std::min(Set_TextW(w.fStatusLine.get(), s) + 2, room));
}

// The pill that holds the status and the three buttons, sized to fit them, right-aligned to the page.
static D2D1_RECT_F Set_FooterDock(const SetWindow& w) {
    float sw = Set_FooterStatusW(w);
    float width = Set_FooterButtonsW() + 2 * kSetFootPad + (sw > 0 ? sw + 30 : 0);
    float right = w.contentX + w.contentW, bottom = w.ch - kSetFootGap;
    return {right - width, bottom - kSetFootH, right, bottom};
}

static D2D1_RECT_F Set_FooterButton(const SetWindow& w, int which) {  // 0 reset, 1 cancel, 2 save
    D2D1_RECT_F d = Set_FooterDock(w);
    float x = d.right - kSetFootPad, top = d.top + kSetFootPad;
    D2D1_RECT_F out{};
    for (int i = 2; i >= 0; i--) {
        out = {x - kSetFootW[i], top, x, top + kSetFootBtnH};
        if (i == which) return out;
        x -= kSetFootW[i] + 8;
    }
    return out;
}

static D2D1_RECT_F Set_RailRect(const SetWindow& w, int page) {
    D2D1_RECT_F d = Set_RailDock(w);
    float y = d.top + kSetRailTop + kSetRailPitch * page + (page == kSetAboutPage ? kSetAboutGap : 0);
    return {d.left + 8, y, d.right - 8, y + kSetRailItem};
}

static D2D1_RECT_F Set_SupportButton(const SetWindow& w, const SetItem& it) {
    D2D1_RECT_F r = Set_RowRect(w, it);
    return {r.right - kSetRowPad - 148, (r.top + r.bottom) / 2 - 18, r.right - kSetRowPad, (r.top + r.bottom) / 2 + 18};
}

static D2D1_RECT_F Set_ScrollThumb(const SetWindow& w) {
    float view = Set_ViewH(w), range = w.contentH - view;
    if (range <= 0) return {};
    float th = std::max(36.0f, view * view / w.contentH);
    float top = (w.scrollY / range) * (view - th - 8) + 4;
    return {w.cw - 18, top + 4, w.cw - 12, top + th - 4};
}

// ---- Painting ---------------------------------------------------------------

static D2D1_COLOR_F Set_A1(float a) { return D2DColorRef(RGB(137,180,250), a); }
static D2D1_COLOR_F Set_A2(float a) { return D2DColorRef(RGB(203,166,247), a); }

static float Set_Ease(float t) {
    t = std::clamp(t, 0.0f, 1.0f);
    return 1 - (1 - t) * (1 - t) * (1 - t);
}

struct SetPaint {
    SetWindow& w;
    ID2D1RenderTarget* rt;
    SetCom<ID2D1SolidColorBrush> sb;
    float fade = 1;
    SetPaint(SetWindow& win, ID2D1RenderTarget* target) : w(win), rt(target) {
        rt->CreateSolidColorBrush(D2DColor(0), sb.put());
    }
    ID2D1SolidColorBrush* B(UINT32 rgb, float a = 1) {
        sb->SetColor(D2DColor(rgb, a * fade));
        return sb.get();
    }
    // Blue to mauve, left to right across r.
    SetCom<ID2D1LinearGradientBrush> G(const D2D1_RECT_F& r, float a = 1) {
        SetCom<ID2D1LinearGradientBrush> out;
        D2D1_GRADIENT_STOP stops[2] = {{0, Set_A1(a * fade)}, {1, Set_A2(a * fade)}};
        SetCom<ID2D1GradientStopCollection> coll;
        if (SUCCEEDED(rt->CreateGradientStopCollection(stops, 2, coll.put())))
            rt->CreateLinearGradientBrush(
                D2D1::LinearGradientBrushProperties(D2D1::Point2F(r.left, (r.top + r.bottom) / 2),
                                                    D2D1::Point2F(std::max(r.right, r.left + 1), (r.top + r.bottom) / 2)),
                coll.get(), out.put());
        return out;
    }
    void Fill(const D2D1_RECT_F& r, UINT32 c, float a = 1) { rt->FillRectangle(r, B(c, a)); }
    void Round(const D2D1_RECT_F& r, float rad, UINT32 c, float a = 1) {
        rt->FillRoundedRectangle(D2D1::RoundedRect(r, rad, rad), B(c, a));
    }
    void Edge(const D2D1_RECT_F& r, float rad, UINT32 c, float a, float width = 1) {
        if (a <= 0.003f) return;
        float h = width / 2;
        rt->DrawRoundedRectangle(D2D1::RoundedRect({r.left + h, r.top + h, r.right - h, r.bottom - h}, rad - h, rad - h), B(c, a), width);
    }
    void GradFill(const D2D1_RECT_F& r, float rad, float a) {
        if (a <= 0.003f) return;
        if (auto g = G(r, a)) rt->FillRoundedRectangle(D2D1::RoundedRect(r, rad, rad), g.get());
    }
    void GradRing(const D2D1_RECT_F& r, float rad, float a, float width = 1.5f) {
        if (a <= 0.003f) return;
        D2D1_RECT_F in{r.left + width / 2, r.top + width / 2, r.right - width / 2, r.bottom - width / 2};
        if (auto g = G(r, a)) rt->DrawRoundedRectangle(D2D1::RoundedRect(in, rad, rad), g.get(), width);
    }
    void Text(IDWriteTextFormat* f, const std::wstring& s, const D2D1_RECT_F& r, UINT32 c, float a = 1) {
        if (!f || s.empty()) return;
        rt->DrawText(s.c_str(), (UINT32)s.size(), f, r, B(c, a), D2D1_DRAW_TEXT_OPTIONS_CLIP);
    }
    void Glyph(IDWriteTextFormat* f, WCHAR g, const D2D1_RECT_F& r, UINT32 c, float a = 1) {
        Text(f, std::wstring(1, g), r, c, a);
    }
};

static float Set_GlowOf(const SetWindow& w, int id) {
    auto it = w.glow.find(id);
    return it == w.glow.end() ? 0 : it->second;
}

// Ids that count as "pointer is here": the row (or rail item, button, link) and the control inside it.
static void Set_HoverIds(const SetHit& h, int ids[2]) {
    ids[0] = h.id;
    ids[1] = -1;
    if (h.kind == SetHit::Control || h.kind == SetHit::Slider || h.kind == SetHit::Clear || h.kind == SetHit::Chip)
        ids[1] = 6000 + h.a;
}

static bool Set_Valid(const SetWindow& w, int k) { return k >= 0 && k < (int)w.fields.size(); }

// Value boxes: a dark fill between mantle and surface0 (crust read as black), a resting
// overlay0 edge, and the blue to mauve ring on hover or while open.
constexpr UINT32 kSetBoxFill = 0x232434;
static void Set_DrawBox(SetPaint& p, SetWindow& w, int k, const D2D1_RECT_F& box, bool active) {
    p.Round(box, 8, kSetBoxFill);
    float g = std::max(Set_GlowOf(w, 6000 + k), active ? 1.0f : 0.0f);
    p.Edge(box, 8, mocha::overlay0, 0.7f * (1 - g), 1.25f);
    p.GradRing(box, 8, g, 1.75f);
}

static void Set_DrawRow(SetPaint& p, SetWindow& w, const SetItem& it) {
    const SetField& f = w.fields[it.field];
    int k = it.field;
    D2D1_RECT_F row = Set_RowRect(w, it);
    p.Round(row, 10, mocha::base);
    p.Round(row, 10, mocha::surface0, 0.32f);
    float hov = Set_GlowOf(w, 1000 + k);
    p.Edge(row, 10, mocha::surface2, 0.55f * (1 - hov));
    p.GradFill(row, 10, 0.13f * hov);
    p.GradRing(row, 10, hov, 1.5f);
    if (w.kbd && w.focus == k) p.GradRing(row, 10, 1.0f, 2.0f);

    float textW = w.contentW - 2 * kSetRowPad - Set_ControlW(f) - 24;
    float lh = Set_TextH(w.fLabel.get(), f.label, textW);
    float dh = (f.desc && *f.desc) ? Set_TextH(w.fHint.get(), f.desc, textW) + 3 : 0;
    float top = row.top + (it.h - lh - dh) / 2;
    p.Text(w.fLabel.get(), f.label, {row.left + kSetRowPad, top, row.left + kSetRowPad + textW, top + lh + 2}, mocha::text);
    if (f.desc && *f.desc)
        p.Text(w.fHint.get(), f.desc, {row.left + kSetRowPad, top + lh + 3, row.left + kSetRowPad + textW, top + lh + dh + 3},
               mocha::subtext0);

    SetParts pt = Set_Parts(f, row);
    const D2D1_RECT_F& b = pt.box;
    switch (f.kind) {
        case SetField::Check: {
            bool on = f.cur == L"1";
            float kn = w.knob.count(k) ? w.knob.at(k) : (on ? 1.0f : 0.0f);
            D2D1_RECT_F tr = pt.box;
            p.Round(tr, 11, mocha::surface1);
            p.GradFill(tr, 11, kn);
            float cx = tr.left + 11 + kn * 18, cy = (tr.top + tr.bottom) / 2;
            p.rt->FillEllipse(D2D1::Ellipse(D2D1::Point2F(cx, cy), 8, 8), p.B(on ? mocha::crust : mocha::text));
            break;
        }
        case SetField::Choice: {
            Set_DrawBox(p, w, k, b, w.openSel == k);
            p.Text(w.fValue.get(), Set_ChoiceLabel(f), {b.left + 12, b.top, b.right - 30, b.bottom}, mocha::text);
            p.Glyph(w.fIconS.get(), 0xE70D, {b.right - 30, b.top, b.right - 6, b.bottom}, mocha::subtext0);
            break;
        }
        case SetField::Number: {
            bool ed = w.editing == k;
            Set_DrawBox(p, w, k, b, ed);
            if (!ed) p.Text(w.fValueC.get(), Set_FieldValue(f), b, mocha::text);
            if (pt.slider) {
                float v = (float)(_wtoi(Set_FieldValue(f).c_str()) - f.min) / (float)std::max(1, f.max - f.min);
                D2D1_RECT_F tr = pt.track;
                p.Round(tr, 2, mocha::surface1);
                D2D1_RECT_F fillR{tr.left, tr.top, tr.left + (tr.right - tr.left) * v, tr.bottom};
                p.GradFill(fillR, 2, 1);
                float cx = tr.left + (tr.right - tr.left) * v, cy = (tr.top + tr.bottom) / 2;
                float kg = std::max(Set_GlowOf(w, 6000 + k), w.dragSlider == k ? 1.0f : 0.0f);
                p.rt->FillEllipse(D2D1::Ellipse(D2D1::Point2F(cx, cy), 8 + kg, 8 + kg), p.B(mocha::text));
                p.rt->FillEllipse(D2D1::Ellipse(D2D1::Point2F(cx, cy), 5, 5), p.B(mocha::crust));
            }
            break;
        }
        case SetField::Text: {
            bool ed = w.editing == k;
            Set_DrawBox(p, w, k, b, ed);
            if (!ed) p.Text(w.fValue.get(), f.cur, {b.left + 12, b.top, b.right - 10, b.bottom}, mocha::text);
            break;
        }
        case SetField::Hotkey: {
            bool rec = w.recording == k;
            Set_DrawBox(p, w, k, b, rec);
            if (rec) {
                p.Text(w.fValue.get(), L"Press keys...", {b.left + 12, b.top, b.right - 10, b.bottom}, mocha::blue);
            } else if (f.cur.empty()) {
                p.Text(w.fValue.get(), L"Not set", {b.left + 12, b.top, b.right - 10, b.bottom}, mocha::overlay0);
            } else {
                float tw = std::min(Set_TextW(w.fValue.get(), f.cur) + 16, b.right - b.left - 40);
                D2D1_RECT_F cap{b.left + 6, (b.top + b.bottom) / 2 - 12, b.left + 6 + tw, (b.top + b.bottom) / 2 + 12};
                p.Round(cap, 6, mocha::surface0);
                p.Text(w.fValueC.get(), f.cur, cap, mocha::text);
                float cg = Set_GlowOf(w, 7000 + k);
                p.Glyph(w.fIconS.get(), 0xE711, pt.clear, cg > 0.5f ? mocha::red : mocha::overlay1);
            }
            break;
        }
        case SetField::Color: {
            bool ed = w.editing == k;
            Set_DrawBox(p, w, k, b, ed);
            UINT32 rgb = 0;
            bool okColor = Set_ParseHex(f.cur, rgb);
            if (okColor) {
                p.rt->FillEllipse(D2D1::Ellipse(D2D1::Point2F(b.left + 17, (b.top + b.bottom) / 2), 6, 6), p.B(rgb));
            }
            if (!ed) p.Text(w.fValue.get(), f.cur, {b.left + 30, b.top, b.right - 6, b.bottom}, okColor ? mocha::text : mocha::red);
            for (int i = 0; i < kSetChipCount; i++) {
                const D2D1_RECT_F& c = pt.chip[i];
                bool sel = okColor && (rgb & 0xFFFFFF) == kSetChips[i];
                p.Round(c, 6, kSetChips[i]);
                if (sel) {
                    D2D1_RECT_F ring{c.left - 3, c.top - 3, c.right + 3, c.bottom + 3};
                    p.GradRing(ring, 8, 1, 2);
                }
            }
            break;
        }
    }
}

static void Set_DrawGroup(SetPaint& p, SetWindow& w, const SetItem& it) {
    std::wstring up = it.text;
    CharUpperBuffW(up.data(), (DWORD)up.size());
    p.Text(w.fSection.get(), up, {w.contentX + 4, it.y, w.contentX + w.contentW, it.y + it.h}, mocha::overlay2);
}

// The resting card every row uses: base, a light lift and a soft gray edge that hands over to
// the hover ring.
static void Set_DrawCard(SetPaint& p, const D2D1_RECT_F& row, float hov) {
    p.Round(row, 10, mocha::base);
    p.Round(row, 10, mocha::surface0, 0.32f);
    p.Edge(row, 10, mocha::surface2, 0.55f * (1 - hov));
}

static void Set_DrawLinkRow(SetPaint& p, SetWindow& w, const SetItem& it, int idx) {
    D2D1_RECT_F row = Set_RowRect(w, it);
    float hov = Set_GlowOf(w, 3000 + idx);
    Set_DrawCard(p, row, hov);
    p.GradFill(row, 10, 0.13f * hov);
    p.GradRing(row, 10, hov, 1.5f);
    p.Text(w.fLabel.get(), it.text, {row.left + kSetRowPad, row.top + 9, row.right - 50, row.top + 30}, mocha::text);
    p.Text(w.fHint.get(), it.sub, {row.left + kSetRowPad, row.top + 30, row.right - 50, row.bottom - 4}, mocha::subtext0);
    p.Glyph(w.fIcon.get(), 0xE8A7, {row.right - 46, row.top, row.right - 12, row.bottom}, mocha::subtext1);
}

static void Set_DrawSupport(SetPaint& p, SetWindow& w, const SetItem& it, int idx) {
    D2D1_RECT_F row = Set_RowRect(w, it);
    float card = std::max(Set_GlowOf(w, 3700 + idx), Set_GlowOf(w, 3500 + idx));
    Set_DrawCard(p, row, card);
    p.GradFill(row, 10, 0.13f * card);
    p.GradRing(row, 10, card, 1.5f);
    p.Text(w.fLabel.get(), it.text, {row.left + kSetRowPad, row.top + 14, row.right - 180, row.top + 36}, mocha::text);
    p.Text(w.fHint.get(), it.sub, {row.left + kSetRowPad, row.top + 38, row.right - 180, row.bottom - 6}, mocha::subtext0);
    D2D1_RECT_F b = Set_SupportButton(w, it);
    float hov = Set_GlowOf(w, 3500 + idx);
    p.GradFill(b, 8, 0.85f + 0.15f * hov);
    p.GradRing(b, 8, hov, 2);
    p.Text(w.fButton.get(), L"Open Ko-fi", b, mocha::crust);
}

static void Set_DrawAbout(SetPaint& p, SetWindow& w, const SetItem& it, int idx) {
    D2D1_RECT_F row = Set_RowRect(w, it);
    float hov = Set_GlowOf(w, 3800 + idx);
    Set_DrawCard(p, row, hov);
    p.GradFill(row, 10, 0.13f * hov);
    p.GradRing(row, 10, hov, 1.5f);
    D2D1_RECT_F mark{row.left + 20, row.top + 20, row.left + 92, row.top + 92};
    {  // The glyph alone in the gradient, no plate (owner, 2026-11-24).
        D2D1_MATRIX_3X2_F old;
        p.rt->GetTransform(&old);
        const D2D1_POINT_2F mc{(mark.left + mark.right) / 2, (mark.top + mark.bottom) / 2};
        p.rt->SetTransform(D2D1::Matrix3x2F::Scale(1.75f, 1.75f, mc) * old);
        const WCHAR glyph = 0xEC4A;
        auto br = p.G({mc.x - 19, mc.y - 19, mc.x + 19, mc.y + 19});
        if (br) p.rt->DrawText(&glyph, 1, w.fIconL.get(), mark, br.get());
        p.rt->SetTransform(old);
    }
    float x = mark.right + 20;
    p.Text(w.fBig.get(), L"Seamless FPS Overlay", {x, row.top + 18, row.right - 16, row.top + 46}, mocha::text);
#ifdef WH_MOD_VERSION
    std::wstring ver = std::wstring(L"Version ") + WH_MOD_VERSION + L"  \u00B7  A Windhawk mod";
#else
    std::wstring ver = L"A Windhawk mod";
#endif
    p.Text(w.fHint.get(), ver, {x, row.top + 48, row.right - 16, row.top + 68}, mocha::subtext0);
    p.Text(w.fHint.get(), L"FPS, frame times and PC temperatures over any game, without touching the game.",
           {x, row.top + 72, row.right - 16, row.top + 110}, mocha::subtext1);
    p.Text(w.fHint.get(), L"Made by DavidHiFi. Processor readings use PawnIO by namazso.",
           {x, row.top + 112, row.right - 16, row.bottom - 8}, mocha::overlay2);
}

static void Set_DrawBanner(SetPaint& p, SetWindow& w, const SetItem& it) {
    D2D1_RECT_F r = Set_RowRect(w, it);
    p.Round(r, 10, mocha::peach, 0.14f);
    p.Text(w.fHint.get(), it.text, {r.left + 16, r.top + 14, r.right - 16, r.bottom - 8}, mocha::peach);
}

// A floating dock: soft shadow, mantle fill, a quiet 1px edge at rest and the blue to mauve
// edge as the pointer comes over it.
static void Set_DrawDock(SetPaint& p, SetWindow& w, const D2D1_RECT_F& d, float rad, float fill, float glow) {
    p.Round({d.left, d.top + 3, d.right, d.bottom + 5}, rad + 2, mocha::crust, w.glass ? 0.28f : 0.5f);
    p.Round(d, rad, mocha::mantle, fill);  // Hover lights only the edge: a wash showed as a blue blob down the left.
    D2D1_RECT_F in{d.left + 0.5f, d.top + 0.5f, d.right - 0.5f, d.bottom - 0.5f};
    p.rt->DrawRoundedRectangle(D2D1::RoundedRect(in, rad, rad), p.B(mocha::surface1, 0.75f * (1 - glow)), 1);
    p.GradRing(d, rad, glow, 1.5f);
}

// Panel-left mark, as in T3's sidebar button: a window with its left pane shaded while open.
static void Set_DrawPanelIcon(SetPaint& p, const D2D1_RECT_F& r, float open, UINT32 c) {
    float cx = (r.left + r.right) / 2, cy = (r.top + r.bottom) / 2;
    D2D1_RECT_F box{cx - 9, cy - 7.5f, cx + 9, cy + 7.5f};
    p.Round({box.left + 1, box.top + 1, box.left + 6.5f, box.bottom - 1}, 1.5f, c, 0.25f + 0.35f * open);
    p.rt->DrawRoundedRectangle(D2D1::RoundedRect(box, 3, 3), p.B(c), 1.5f);
    p.rt->DrawLine({box.left + 6.5f, box.top + 0.75f}, {box.left + 6.5f, box.bottom - 0.75f}, p.B(c), 1.5f);
}

static void Set_DrawMark(SetPaint& p, IDWriteTextFormat* glyph, const D2D1_RECT_F& r, float a);
static void Set_DrawRail(SetPaint& p, SetWindow& w) {
    D2D1_RECT_F d = Set_RailDock(w);
    const float open = Set_RailOpen(w), textA = std::clamp((open - 0.45f) / 0.55f, 0.0f, 1.0f);
    // Over the resize edge or while dragging, the dock's own rounded border brightens and
    // thickens, so the handle follows the corners instead of floating as a separate line.
    float edge = std::max(Set_GlowOf(w, 41), w.dragRail ? 1.0f : 0.0f);
    Set_DrawDock(p, w, d, 14, w.glass ? 0.58f : 1.0f, std::max(w.railGlow * 0.85f, edge));
    if (edge > 0.003f) p.GradRing(d, 13, edge, 2.25f);

    D2D1_RECT_F tb = Set_RailToggleRect(w);
    float th = Set_GlowOf(w, 42);
    p.Round(tb, 9, mocha::surface0, 0.45f + 0.25f * th);
    p.GradFill(tb, 9, 0.16f * th);
    p.GradRing(tb, 9, 0.9f * th, 1.25f);
    if (w.kbd && w.focus == -20) p.GradRing(tb, 9, 1, 2);
    Set_DrawPanelIcon(p, tb, open, th > 0.5f ? mocha::text : mocha::subtext1);

    p.rt->PushAxisAlignedClip(D2D1::RectF(d.left, d.top, d.right - 6, d.bottom), D2D1_ANTIALIAS_MODE_ALIASED);
    if (textA > 0.003f) {
        float my = (tb.top + tb.bottom) / 2;
        Set_DrawMark(p, w.fIcon.get(), {d.left + 56, my - 13, d.left + 82, my + 13}, textA);
    }
    p.Text(w.fRailName.get(), L"Seamless", {d.left + 90, d.top + 9, d.left + w.railW - 10, d.top + 33}, mocha::text, textA);
    p.Text(w.fRailName.get(), L"FPS Overlay", {d.left + 90, d.top + 32, d.left + w.railW - 10, d.top + 56}, mocha::text, textA);
    for (int i = 0; i < kSetPageCount; i++) {
        D2D1_RECT_F r = Set_RailRect(w, i);
        if (i == kSetAboutPage) {
            float ly = std::round(r.top - (kSetAboutGap + kSetRailPitch - kSetRailItem) / 2);
            p.Fill({r.left + 6, ly, r.right - 6, ly + 1}, mocha::surface1, 0.7f);
        }
        float hov = Set_GlowOf(w, 100 + i);
        bool act = i == w.page;
        if (act) {
            p.GradFill(r, 8, 0.22f);
            p.GradRing(r, 8, 0.5f, 1);
            D2D1_RECT_F bar{r.left, r.top + 8, r.left + 3, r.bottom - 8};
            p.GradFill({bar.left, bar.top, bar.left + 3, bar.bottom}, 1.5f, 1);
        } else {
            p.Round(r, 8, mocha::surface0, 0.28f);
            p.Edge(r, 8, mocha::surface2, 0.5f * (1 - hov));
            p.GradFill(r, 8, 0.10f * hov);
            p.GradRing(r, 8, 0.8f * hov, 1.25f);
        }
        if (w.kbd && w.focus == -10 - i) p.GradRing(r, 8, 1, 2);
        UINT32 c = act ? mocha::text : mocha::subtext1;
        // The glyph sits in a fixed 44-wide slot, so it stays centered in the collapsed rail.
        p.Glyph(w.fIcon.get(), kSetPages[i].glyph, {r.left, r.top, r.left + 44, r.bottom}, act ? mocha::blue : mocha::subtext0);
        p.Text(w.fValue.get(), kSetPages[i].name, {r.left + 50, r.top, r.left + w.railW - 24, r.bottom}, c, textA);
    }
#ifdef WH_MOD_VERSION
    p.Text(w.fSmall.get(), std::wstring(L"Version ") + WH_MOD_VERSION,
           {d.left + 18, d.bottom - 34, d.left + w.railW - 12, d.bottom - 12}, mocha::overlay1, textA);
#endif
    p.rt->PopAxisAlignedClip();
}

static void Set_DrawFooter(SetPaint& p, SetWindow& w) {
    D2D1_RECT_F d = Set_FooterDock(w);
    const float rad = kSetFootH / 2, brad = kSetFootBtnH / 2;
    // The same see-through mantle as the rail dock, so the blurred rows under the pill read as
    // real glass instead of a near-solid bar.
    p.Round(d, rad, mocha::mantle, w.render ? 1.0f : (w.glass ? 0.58f : 0.85f));
    const D2D1_RECT_F edge{d.left + 2, d.top + 2, d.right - 2, d.bottom - 2};
    p.rt->DrawRoundedRectangle(D2D1::RoundedRect(edge, rad - 2, rad - 2),
                              p.B(mocha::overlay0, 0.9f * (1 - w.footGlow)), 2.75f);
    p.GradRing(d, rad - 1.5f, w.footGlow, 3.0f);
    UINT32 sc;
    std::wstring status = Set_FooterStatus(w, &sc);
    float sw = Set_FooterStatusW(w);
    if (sw > 0) p.Text(w.fStatusLine.get(), status, {d.left + 18, d.top, d.left + 18 + sw, d.bottom}, sc);
    static const PCWSTR names[3] = {L"Reset to suggested", L"Cancel", L"Save"};
    for (int i = 0; i < 3; i++) {
        D2D1_RECT_F b = Set_FooterButton(w, i);
        float hov = Set_GlowOf(w, 10 + i);
        p.Round(b, brad, mocha::base, 0.98f);
        p.Edge(b, brad, mocha::overlay0, 0.78f * (1 - hov), 1.75f);
        p.GradRing(b, brad - 1, hov, 2.25f);
        p.Text(w.fButton.get(), names[i], b, mocha::text, w.saving ? 0.5f : 1.0f);
        if (w.kbd && w.focus == -1 - i) p.GradRing(b, brad, 1, 2);
    }
}


static void Set_ThumbFill(SetPaint& p, const D2D1_RECT_F& r, float a) {
    if (r.bottom <= r.top) return;
    float rad = (r.right - r.left) / 2;
    SetCom<ID2D1LinearGradientBrush> g;
    D2D1_GRADIENT_STOP stops[2] = {{0, D2DColor(mocha::blue, a * p.fade)}, {1, D2DColor(mocha::mauve, a * p.fade)}};
    SetCom<ID2D1GradientStopCollection> coll;
    if (SUCCEEDED(p.rt->CreateGradientStopCollection(stops, 2, coll.put())) &&
        SUCCEEDED(p.rt->CreateLinearGradientBrush(
            D2D1::LinearGradientBrushProperties(D2D1::Point2F(r.left, r.top), D2D1::Point2F(r.left, r.bottom)),
            coll.get(), g.put())))
        p.rt->FillRoundedRectangle(D2D1::RoundedRect(r, rad, rad), g.get());
}

static int Set_DropVisible(const SetWindow& w) {
    return w.openSel < 0 ? 0 : std::min((int)w.fields[w.openSel].options.size(), kSetDropMax);
}

static void Set_DropShow(SetWindow& w, int i) {
    int vis = Set_DropVisible(w), n = w.openSel < 0 ? 0 : (int)w.fields[w.openSel].options.size();
    if (i < 0 || vis <= 0) return;
    if (i < w.dropTop) w.dropTop = i;
    if (i >= w.dropTop + vis) w.dropTop = i - vis + 1;
    w.dropTop = std::clamp(w.dropTop, 0, std::max(0, n - vis));
}

static void Set_DrawPopup(SetPaint& p, SetWindow& w) {
    if (w.openSel < 0) return;
    const SetField& f = w.fields[w.openSel];
    const D2D1_RECT_F& r = w.dropRect;
    const int n = (int)f.options.size(), vis = Set_DropVisible(w);
    const bool scrolls = n > vis;
    D2D1_RECT_F shadow{r.left - 1, r.top + 3, r.right + 1, r.bottom + 5};
    p.Round(shadow, 12, mocha::crust, 0.6f);
    p.Round(r, 10, mocha::mantle);
    p.GradRing(r, 10, 0.9f);
    const float right = r.right - (scrolls ? 12 : 4);
    for (int v = 0; v < vis; v++) {
        int i = w.dropTop + v;
        if (i >= n) break;
        D2D1_RECT_F it{r.left + 4, r.top + 4 + v * kSetDropItem, right, r.top + 4 + (v + 1) * kSetDropItem};
        bool sel = f.cur == f.options[i].first;
        if (i == w.dropHover) {
            p.GradFill(it, 6, 0.28f);
            p.GradRing(it, 6, 0.6f, 1);
        }
        p.Text(w.fValue.get(), f.options[i].second, {it.left + 10, it.top, it.right - 28, it.bottom}, sel ? mocha::blue : mocha::text);
        if (sel) p.Glyph(w.fIconS.get(), 0xE73E, {it.right - 28, it.top, it.right - 6, it.bottom}, mocha::blue);
    }
    if (scrolls) {
        float track = r.bottom - r.top - 12, th = std::max(24.0f, track * vis / n);
        float top = r.top + 6 + (track - th) * w.dropTop / std::max(1, n - vis);
        Set_ThumbFill(p, {r.right - 9, top, r.right - 5, top + th}, 0.85f);
    }
}

// Title bar buttons, in title bar DIPs: 0 minimize, 1 maximize or restore, 2 close.
static D2D1_RECT_F Set_CapButton(const SetWindow& w, int i) {
    float right = w.cw - (2 - i) * kSetCapBtnW;
    return {right - kSetCapBtnW, 0, right, kSetCapH};
}

// y is in content DIPs, so the title bar is y < 0.
static int Set_CapButtonAt(const SetWindow& w, float x, float y) {
    if (w.nativeTitle) return -1;
    for (int i = 0; i < 3; i++)
        if (Set_In(Set_CapButton(w, i), x, y + kSetCapH)) return i;
    return -1;
}

// Icon and title are centered on the whole width, laid out from the current size on every paint,
// so a move or snap can never leave them off center.
static D2D1_RECT_F Set_CapTitleRect(const SetWindow& w) {
    float tw = std::min(Set_TextW(w.fCap.get(), kSetTitle) + 2, std::max(0.0f, w.cw - 4 * kSetCapBtnW - 40));
    float x = std::round((w.cw - (16 + 8 + tw)) / 2);
    return {x, 0, x + 16 + 8 + tw, kSetCapH};
}

static void Set_DrawMark(SetPaint& p, IDWriteTextFormat* glyph, const D2D1_RECT_F& r, float a) {
    // The mod's glyph alone in the blue to mauve gradient on a clear background, no plate
    // (owner, 2026-11-24), scaled up about its centre to fill the room the plate had.
    const float cx = (r.left + r.right) / 2, cy = (r.top + r.bottom) / 2;
    const float ix = (r.right - r.left) * 0.31f, iy = (r.bottom - r.top) * 0.31f;
    SetCom<ID2D1LinearGradientBrush> g;
    D2D1_GRADIENT_STOP stops[2] = {{0, D2DColor(mocha::blue, a * p.fade)}, {1, D2DColor(mocha::mauve, a * p.fade)}};
    SetCom<ID2D1GradientStopCollection> coll;
    if (FAILED(p.rt->CreateGradientStopCollection(stops, 2, coll.put())) ||
        FAILED(p.rt->CreateLinearGradientBrush(
            D2D1::LinearGradientBrushProperties(D2D1::Point2F(cx - ix, cy - iy), D2D1::Point2F(cx + ix, cy + iy)),
            coll.get(), g.put())))
        return;
    D2D1_MATRIX_3X2_F old;
    p.rt->GetTransform(&old);
    p.rt->SetTransform(D2D1::Matrix3x2F::Scale(1.4f, 1.4f, D2D1::Point2F(cx, cy)) * old);
    const WCHAR mark = 0xEC4A;
    p.rt->DrawText(&mark, 1, glyph, r, g.get());
    p.rt->SetTransform(old);
}

static void Set_DrawCaption(SetPaint& p, SetWindow& w) {
    if (!w.glass) p.Fill({0, 0, w.cw, kSetCapH}, mocha::crust);  // Glass: the window tint already covers it.
    D2D1_RECT_F t = Set_CapTitleRect(w);
    float mid = kSetCapH / 2;
    Set_DrawMark(p, w.fCapGlyph.get(), {t.left, mid - 8, t.left + 16, mid + 8}, w.active ? 1.0f : 0.6f);
    p.Text(w.fCap.get(), kSetTitle, {t.left + 24, 0, t.right, kSetCapH}, w.active ? mocha::text : mocha::overlay1);
    for (int i = 0; i < 3; i++) {
        D2D1_RECT_F b = Set_CapButton(w, i);
        float hov = Set_GlowOf(w, 20 + i);
        if (w.capDown == i + 1) hov = 1;
        if (i == 2) p.Fill(b, mocha::red, 0.92f * hov);
        else p.Fill(b, mocha::surface0, 0.85f * hov);
        UINT32 c = i == 2 && hov > 0.5f ? mocha::crust : (w.active ? mocha::text : mocha::overlay1);
        WCHAR glyph = i == 0 ? 0xE921 : i == 1 ? (w.hwnd && IsZoomed(w.hwnd) ? 0xE923 : 0xE922) : 0xE8BB;
        p.Glyph(w.fCapGlyph.get(), glyph, b, c);
    }
}

// Draws the whole window into rt (DIPs). The target's DPI does the scaling.
// The title bar is drawn first; everything else is in content DIPs, shifted down by kSetCapH.
static void Set_PlaceEdit(SetWindow& w);

static void Set_DrawAutoScroll(SetPaint& p, SetWindow& w, bool frosted) {
    if (w.autoA <= 0.003f) return;
    const float a = w.autoA, s = 0.8f + 0.2f * a, r = kSetAutoR * s, cx = w.autoX, cy = w.autoY;
    const D2D1_RECT_F disc{cx - r, cy - r, cx + r, cy + r};
    p.Round(disc, r, mocha::mantle, (frosted ? 0.86f : 1.0f) * a);  // Opaque when nothing blurs under it.
    p.GradRing(disc, r - 1, a, 2);
    auto arrow = [&](float dir, bool lit) {
        SetCom<ID2D1PathGeometry> g;
        SetCom<ID2D1GeometrySink> k;
        if (FAILED(g_setD2d->CreatePathGeometry(g.put())) || FAILED(g->Open(k.put()))) return;
        const float tip = cy + dir * r * 0.62f, foot = cy + dir * r * 0.30f, half = r * 0.22f;
        k->BeginFigure(D2D1::Point2F(cx, tip), D2D1_FIGURE_BEGIN_FILLED);
        k->AddLine(D2D1::Point2F(cx + half, foot));
        k->AddLine(D2D1::Point2F(cx - half, foot));
        k->EndFigure(D2D1_FIGURE_END_CLOSED);
        if (SUCCEEDED(k->Close())) p.rt->FillGeometry(g.get(), p.B(lit ? mocha::blue : mocha::overlay1, a));
    };
    arrow(-1, w.autoDir < 0);
    arrow(1, w.autoDir > 0);
    const float d = 2.5f * s;
    p.Round({cx - d, cy - d, cx + d, cy + d}, d, mocha::mauve, a);
}

static void Set_Draw(SetWindow& w, ID2D1RenderTarget* rt) {
    if (Set_FitBoxes(w)) {
        Set_BuildPage(w);
        Set_PlaceEdit(w);
    }
    SetPaint p(w, rt);
    const auto base = D2D1::Matrix3x2F::Translation(0, kSetCapH);
    rt->BeginDraw();
    rt->SetTransform(D2D1::Matrix3x2F::Identity());
    if (w.glass) {
        // One tint over the whole window, title bar included, so the page and the title bar are
        // the same material. With the Windows title bar (drawn by DWM with no tint) the tint fades
        // in over the top of the page instead, so there is no step at the seam (T3 pass 24 method).
        rt->Clear(D2D1::ColorF(0, 0));
        const float total = w.ch + kSetCapH;
        if (w.nativeTitle) {
            SetCom<ID2D1LinearGradientBrush> fade;
            D2D1_GRADIENT_STOP stops[2] = {{0, D2DColor(mocha::crust, kSetGlassTint)}, {1, D2DColor(mocha::crust, kSetGlassTint)}};
            SetCom<ID2D1GradientStopCollection> coll;
            if (SUCCEEDED(rt->CreateGradientStopCollection(stops, 2, coll.put())) &&
                SUCCEEDED(rt->CreateLinearGradientBrush(
                    D2D1::LinearGradientBrushProperties(D2D1::Point2F(0, 0), D2D1::Point2F(0, kSetNativeFade)), coll.get(),
                    fade.put())))
                rt->FillRectangle(D2D1::RectF(0, 0, w.cw, kSetNativeFade), fade.get());
            p.Fill({0, kSetNativeFade, w.cw, total}, mocha::crust, kSetGlassTint);
        } else {
            p.Fill({0, 0, w.cw, total}, mocha::crust, kSetGlassTint);
        }
    } else {
        rt->Clear(D2DColor(mocha::crust));
    }
    if (!w.nativeTitle) Set_DrawCaption(p, w);
    rt->SetTransform(base);
    float viewH = Set_ViewH(w);

    auto drawPage = [&](SetPaint& cp) {
        ID2D1RenderTarget* crt = cp.rt;
        crt->PushAxisAlignedClip(D2D1::RectF(Set_RailSpace(w) + 4, 0, w.cw, viewH), D2D1_ANTIALIAS_MODE_ALIASED);
        auto place = [&](int index, float& rise) {
            float t = w.pageT >= 1 ? 1.0f : Set_Ease(w.pageT * 1.7f - std::min(index, 9) * 0.07f);
            cp.fade = t;
            rise = (1 - t) * 10;
            crt->SetTransform(D2D1::Matrix3x2F::Translation(0, -w.scrollY + rise) * base);
        };
        float rise = 0;
        place(0, rise);
        cp.Text(w.fTitle.get(), kSetPages[w.page].name, {w.contentX, 36, w.contentX + w.contentW, 72}, mocha::text);
        place(1, rise);
        cp.Text(w.fIntro.get(), kSetPages[w.page].intro, {w.contentX, 76, w.contentX + w.contentW, 76 + 40}, mocha::subtext0);
        for (size_t i = 0; i < w.items.size(); i++) {
            const SetItem& it = w.items[i];
            if (it.y + it.h < w.scrollY - 20 || it.y > w.scrollY + viewH + 20) continue;
            place((int)i + 2, rise);
            switch (it.type) {
                case SetItem::Group: Set_DrawGroup(cp, w, it); break;
                case SetItem::Row: Set_DrawRow(cp, w, it); break;
                case SetItem::Banner: Set_DrawBanner(cp, w, it); break;
                case SetItem::About: Set_DrawAbout(cp, w, it, (int)i); break;
                case SetItem::Link: Set_DrawLinkRow(cp, w, it, (int)i); break;
                case SetItem::Support: Set_DrawSupport(cp, w, it, (int)i); break;
            }
        }
        cp.fade = 1;
        crt->SetTransform(base);
        crt->PopAxisAlignedClip();
    };

    // The footer dock floats over the page with a real blur of the rows under it, clipped to the
    // pill, all in this window. (An owned popup with its own backdrop showed square corners:
    // DWM paints an accent backdrop over the full window rectangle and ignores the region.)
    const D2D1_SIZE_F full = D2D1::SizeF(w.cw, w.ch + kSetCapH);
    bool blurred = false;
    if (!w.render) {
        if (w.layer && (w.layerSize.width != full.width || w.layerSize.height != full.height)) w.layer.reset();
        if (!w.layer && SUCCEEDED(rt->CreateCompatibleRenderTarget(full, w.layer.put()))) w.layerSize = full;
        SetCom<ID2D1Bitmap> page;
        SetCom<ID2D1DeviceContext> dc;
        SetCom<ID2D1Effect> blur;
        SetCom<ID2D1RoundedRectangleGeometry> pill;
        SetCom<ID2D1RectangleGeometry> all;
        SetCom<ID2D1PathGeometry> rest;
        D2D1_RECT_F d = Set_FooterDock(w);
        d.top += kSetCapH, d.bottom += kSetCapH;
        const float rad = kSetFootH / 2;
        if (w.layer && SUCCEEDED(rt->QueryInterface(__uuidof(ID2D1DeviceContext), (void**)dc.put())) &&
            SUCCEEDED(dc->CreateEffect(CLSID_D2D1GaussianBlur, blur.put())) &&
            SUCCEEDED(g_setD2d->CreateRoundedRectangleGeometry(D2D1::RoundedRect(d, rad, rad), pill.put())) &&
            SUCCEEDED(g_setD2d->CreateRectangleGeometry(D2D1::RectF(0, 0, full.width, full.height), all.put())) &&
            SUCCEEDED(g_setD2d->CreatePathGeometry(rest.put()))) {
            SetCom<ID2D1GeometrySink> sink;
            bool ok = SUCCEEDED(rest->Open(sink.put())) &&
                      SUCCEEDED(all->CombineWithGeometry(pill.get(), D2D1_COMBINE_MODE_EXCLUDE, nullptr, sink.get())) &&
                      SUCCEEDED(sink->Close());
            ID2D1BitmapRenderTarget* lt = w.layer.get();
            if (ok) {
                SetPaint lp(w, lt);
                lt->BeginDraw();
                lt->SetTransform(D2D1::Matrix3x2F::Identity());
                lt->Clear(D2D1::ColorF(0, 0));
                lt->SetTransform(base);
                drawPage(lp);
                ok = SUCCEEDED(lt->EndDraw()) && SUCCEEDED(lt->GetBitmap(page.put()));
            }
            if (!ok) w.layer.reset();
            if (ok) {
                rt->SetTransform(D2D1::Matrix3x2F::Identity());
                rt->PushLayer(D2D1::LayerParameters(D2D1::InfiniteRect(), rest.get()), nullptr);
                rt->DrawBitmap(page.get());
                rt->PopLayer();
                blur->SetInput(0, page.get());
                blur->SetValue(D2D1_GAUSSIANBLUR_PROP_STANDARD_DEVIATION, 9.0f);
                blur->SetValue(D2D1_GAUSSIANBLUR_PROP_BORDER_MODE, D2D1_BORDER_MODE_HARD);
                rt->PushLayer(D2D1::LayerParameters(D2D1::InfiniteRect(), pill.get()), nullptr);
                D2D1_RECT_F src{d.left - 1, d.top - 1, d.right + 1, d.bottom + 1};
                dc->DrawImage(blur.get(), D2D1::Point2F(src.left, src.top), src);
                rt->PopLayer();
                if (w.autoA > 0.003f) {  // The autoscroll disc frosts the rows under it the same way.
                    const float r = kSetAutoR * (0.8f + 0.2f * w.autoA), cx = w.autoX, cy = w.autoY + kSetCapH;
                    SetCom<ID2D1EllipseGeometry> disc;
                    if (SUCCEEDED(g_setD2d->CreateEllipseGeometry(D2D1::Ellipse(D2D1::Point2F(cx, cy), r, r), disc.put()))) {
                        rt->PushLayer(D2D1::LayerParameters(D2D1::InfiniteRect(), disc.get()), nullptr);
                        D2D1_RECT_F ds{cx - r - 1, cy - r - 1, cx + r + 1, cy + r + 1};
                        dc->DrawImage(blur.get(), D2D1::Point2F(ds.left, ds.top), ds);
                        rt->PopLayer();
                    }
                }
                blurred = true;
            }
        }
    }
    if (!blurred) drawPage(p);
    rt->SetTransform(base);

    D2D1_RECT_F th = Set_ScrollThumb(w);
    Set_ThumbFill(p, th, w.dragScroll || w.hover.kind == SetHit::Scroll ? 1.0f : 0.7f);

    Set_DrawFooter(p, w);
    Set_DrawRail(p, w);
    Set_DrawPopup(p, w);
    Set_DrawAutoScroll(p, w, blurred);
    rt->SetTransform(D2D1::Matrix3x2F::Identity());
    if (false) p.GradRing({0, 0, w.cw, w.ch + kSetCapH}, SystemCornerRadius(false), 1, 1);
    HRESULT hr = rt->EndDraw();
    if (hr == D2DERR_RECREATE_TARGET) w.rt.reset(), w.layer.reset();
}

// ---- Hit testing --------------------------------------------------------------

static SetHit Set_Hit(SetWindow& w, float x, float y) {
    SetHit h;
    if (y < 0) {
        int b = Set_CapButtonAt(w, x, y);
        if (b >= 0) {
            h.kind = SetHit::Caption;
            h.a = b;
            h.id = 20 + b;
        }
        return h;
    }
    if (w.openSel >= 0) {
        if (Set_In(w.dropRect, x, y)) {
            int v = (int)((y - w.dropRect.top - 4) / kSetDropItem), i = w.dropTop + v;
            if (v >= 0 && v < Set_DropVisible(w) && i < (int)w.fields[w.openSel].options.size() &&
                y >= w.dropRect.top + 4 && x < w.dropRect.right - (Set_DropVisible(w) < (int)w.fields[w.openSel].options.size() ? 12 : 4)) {
                h.kind = SetHit::Drop;
                h.a = w.openSel;
                h.b = i;
            } else {
                h.kind = SetHit::Popup;
            }
        }
        return h;
    }
    D2D1_RECT_F dock = Set_RailDock(w);
    if (y >= dock.top + 14 && y < dock.bottom - 14 && fabsf(x - dock.right) <= kSetEdgeGrab) {
        h.kind = SetHit::RailEdge;
        h.id = 41;
        return h;
    }
    if (x < dock.right + kSetDockGap) {
        if (Set_In(Set_RailToggleRect(w), x, y)) {
            h.kind = SetHit::RailToggle;
            h.id = 42;
            return h;
        }
        for (int i = 0; i < kSetPageCount; i++) {
            if (Set_In(Set_RailRect(w, i), x, y)) {
                h.kind = SetHit::Rail;
                h.a = i;
                h.id = 100 + i;
                return h;
            }
        }
        return h;
    }
    D2D1_RECT_F foot = Set_FooterDock(w);
    if (Set_In(foot, x, y)) {
        for (int i = 0; i < 3; i++) {
            if (Set_In(Set_FooterButton(w, i), x, y)) {
                h.kind = SetHit::Footer;
                h.a = i;
                h.id = 10 + i;
                return h;
            }
        }
        return h;
    }
    D2D1_RECT_F th = Set_ScrollThumb(w);
    if (th.bottom > th.top && x >= w.cw - 16 && y >= th.top && y <= th.bottom) {
        h.kind = SetHit::Scroll;
        return h;
    }
    float cy = y + w.scrollY;
    for (size_t i = 0; i < w.items.size(); i++) {
        const SetItem& it = w.items[i];
        D2D1_RECT_F row = Set_RowRect(w, it);
        if (!Set_In(row, x, cy)) continue;
        if (it.type == SetItem::Link) {
            h.kind = SetHit::Link;
            h.a = (int)i;
            h.id = 3000 + (int)i;
        } else if (it.type == SetItem::Support) {
            h.id = 3700 + (int)i;  // The card lights up; only its button clicks.
            if (Set_In(Set_SupportButton(w, it), x, cy)) {
                h.kind = SetHit::Link;
                h.a = (int)i;
                h.id = 3500 + (int)i;
            }
        } else if (it.type == SetItem::About) {
            h.id = 3800 + (int)i;
        } else if (it.type == SetItem::Row) {
            const SetField& f = w.fields[it.field];
            SetParts pt = Set_Parts(f, row);
            h.a = it.field;
            h.id = 1000 + it.field;
            h.kind = f.kind == SetField::Check ? SetHit::Control : SetHit::Row;
            if (f.kind == SetField::Hotkey && !f.cur.empty() && w.recording != it.field && Set_In(pt.clear, x, cy)) {
                h.kind = SetHit::Clear;
            } else if (f.kind == SetField::Color) {
                for (int c = 0; c < kSetChipCount; c++) {
                    if (Set_In(pt.chip[c], x, cy)) {
                        h.kind = SetHit::Chip;
                        h.b = c;
                    }
                }
                if (h.kind != SetHit::Chip && Set_In(pt.box, x, cy)) h.kind = SetHit::Control;
            } else if (pt.slider &&
                       Set_In({pt.track.left - 8, pt.track.top - 10, pt.track.right + 8, pt.track.bottom + 10}, x, cy)) {
                h.kind = SetHit::Slider;
            } else if (Set_In(pt.box, x, cy)) {
                h.kind = SetHit::Control;
            }
        }
        return h;
    }
    return h;
}

static bool Set_Clickable(const SetHit& h) {
    return h.kind == SetHit::Rail || h.kind == SetHit::Footer || h.kind == SetHit::Control || h.kind == SetHit::Slider ||
           h.kind == SetHit::Clear || h.kind == SetHit::Chip || h.kind == SetHit::Drop || h.kind == SetHit::Link ||
           h.kind == SetHit::Scroll || h.kind == SetHit::RailToggle;
}

// Sidebar width from a drag: below the snap point it collapses to the icon rail.
static void Set_RailDragTo(SetWindow& w, float x) {
    float width = x - kSetDockGap;
    if (width < kSetRailSnap) {
        w.railCollapsed = true;
    } else {
        w.railCollapsed = false;
        w.railW = std::clamp(width, kSetRailMin, kSetRailMax);
        w.railCur = w.railW;
    }
    Set_BuildPage(w);
    Set_Invalidate(w);
}

static void Set_ToggleRail(SetWindow& w) {
    w.railCollapsed = !w.railCollapsed;
    if (!w.railCollapsed && w.railCur < kSetRailMini) w.railCur = kSetRailMini;
    Set_Invalidate(w);
}

// ---- Editing, recording, choosing -----------------------------------------------

static std::wstring Set_FormatHotkey(UINT mods, UINT vk) { return ::Hotkey_Format(mods, vk); }

static bool Set_IsModifier(UINT vk) {
    switch (vk) {
        case VK_SHIFT: case VK_LSHIFT: case VK_RSHIFT:
        case VK_CONTROL: case VK_LCONTROL: case VK_RCONTROL:
        case VK_MENU: case VK_LMENU: case VK_RMENU:
        case VK_LWIN: case VK_RWIN:
            return true;
    }
    return false;
}

static void Set_StopRecording(SetWindow& w) {
    if (w.recording < 0) return;
    w.recording = -1;
    if (w.status.rfind(L"Press the keys", 0) == 0) Set_SetStatus(w, L"");
    
    Set_Invalidate(w);
}

static void Set_StartRecording(SetWindow& w, int k) {
    Set_StopRecording(w);
    w.recording = k;
    // Our own keys would fire instead of reaching the window while it listens.
    if (!w.render) {
        SetFocus(w.hwnd);
    }
    Set_SetStatus(w, L"Press the keys you want. Esc cancels, Backspace clears.");
}

static void Set_ClosePopup(SetWindow& w) {
    if (w.openSel < 0) return;
    w.openSel = -1;
    w.dropHover = -1;
    w.dropTop = 0;
    Set_Invalidate(w);
}

static void Set_OpenPopup(SetWindow& w, int k) {
    const SetItem* it = Set_ItemOfField(w, k);
    if (!it) return;
    const SetField& f = w.fields[k];
    SetParts pt = Set_Parts(f, Set_RowRect(w, *it));
    float boxTop = pt.box.top - w.scrollY, boxBottom = pt.box.bottom - w.scrollY;
    const int n = (int)f.options.size(), vis = std::min(n, kSetDropMax);
    float h = (float)vis * kSetDropItem + 8;
    float top = boxBottom + 4;
    if (top + h > Set_ViewH(w) + 20 && boxTop - 4 - h > 0) top = boxTop - 4 - h;  // No room below: open upward.
    // As wide as the longest option (text, check mark, scrollbar), growing leftward from the box.
    float textW = 0;
    for (const auto& o : f.options) textW = std::max(textW, Set_TextW(w.fValue.get(), o.second));
    float width = std::max(pt.box.right - pt.box.left, std::ceil(textW) + 52 + (n > vis ? 8 : 0));
    float left = std::max(pt.box.right - width, Set_RailSpace(w) + 8);
    w.dropRect = {left, top, std::max(pt.box.right, left + width), top + h};
    w.openSel = k;
    w.dropHover = -1;
    w.dropTop = 0;
    for (int i = 0; i < n; i++)
        if (f.cur == f.options[i].first) w.dropHover = i;
    Set_DropShow(w, w.dropHover);
    Set_Invalidate(w);
}

static void Set_CommitEdit(SetWindow& w, bool apply) {
    if (w.editing < 0) return;
    int k = w.editing;
    w.editing = -1;  // Hiding the box ends its focus; this stops that from coming back here.
    SetField& f = w.fields[k];
    std::wstring text = w.edit ? Set_WindowText(w.edit) : L"";
    if (w.edit) ShowWindow(w.edit, SW_HIDE);
    if (apply) {
        switch (f.kind) {
            case SetField::Number:
                if (!text.empty()) f.cur = std::to_wstring(std::clamp(_wtoi(text.c_str()), f.min, f.max));
                break;
            case SetField::Color: {
                while (!text.empty() && text.back() == L' ') text.pop_back();
                while (!text.empty() && text.front() == L' ') text.erase(0, 1);
                if (!text.empty() && text[0] != L'#') text = L"#" + text;
                UINT32 rgb;
                if (Set_ParseHex(text, rgb)) {
                    f.cur = Set_HexFromRgb(rgb);
                    Set_SetStatus(w, L"");
                } else {
                    Set_SetStatus(w, L"Use a color like #89B4FA.", true);
                }
                break;
            }
            default:
                f.cur = text;
        }
    }
    if (!w.render && w.hwnd) SetFocus(w.hwnd);
    Set_Invalidate(w);
}

static void Set_PlaceEdit(SetWindow& w) {
    if (w.editing < 0 || !w.edit) return;
    const SetItem* it = Set_ItemOfField(w, w.editing);
    if (!it) return;
    SetParts pt = Set_Parts(w.fields[w.editing], Set_RowRect(w, *it));
    float left = pt.box.left + (w.fields[w.editing].kind == SetField::Color ? 30 : 10), right = pt.box.right - 8;
    float mid = (pt.box.top + pt.box.bottom) / 2 - w.scrollY + kSetCapH;
    float s = w.dpi / 96.0f;
    SetWindowPos(w.edit, HWND_TOP, (int)(left * s), (int)((mid - 10) * s), (int)((right - left) * s), (int)(20 * s),
                 SWP_NOACTIVATE | SWP_SHOWWINDOW);
}

static LRESULT CALLBACK Set_EditProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam, UINT_PTR, DWORD_PTR) {
    SetWindow* w = g_setWin.get();
    if (w && w->edit == hwnd) {
        switch (msg) {
            case WM_KEYDOWN:
                if (wParam == VK_RETURN || wParam == VK_TAB) {
                    Set_CommitEdit(*w, true);
                    return 0;
                }
                if (wParam == VK_ESCAPE) {
                    Set_CommitEdit(*w, false);
                    return 0;
                }
                break;
            case WM_CHAR:
                if (wParam == VK_RETURN || wParam == VK_ESCAPE || wParam == VK_TAB) return 0;  // No beep.
                break;
            case WM_KILLFOCUS:
                if (w->editing >= 0) Set_CommitEdit(*w, true);
                break;
        }
    }
    return DefSubclassProc(hwnd, msg, wParam, lParam);
}

static void Set_BeginEdit(SetWindow& w, int k) {
    Set_CommitEdit(w, true);
    Set_StopRecording(w);
    Set_ClosePopup(w);
    SetField& f = w.fields[k];
    if (w.edit) DestroyWindow(w.edit);
    if (w.editFont) DeleteObject(w.editFont);
    DWORD style = WS_CHILD | ES_AUTOHSCROLL | (f.kind == SetField::Number ? ES_NUMBER | ES_CENTER : 0);
    // Over the extended frame GDI text would come out see-through; a layered child keeps it solid.
    w.edit = CreateWindowExW(w.glass ? WS_EX_LAYERED : 0, L"EDIT", L"", style, 0, 0, 10, 10, w.hwnd, nullptr,
                             GetModuleHandleW(nullptr), nullptr);
    if (!w.edit) return;
    if (w.glass) SetLayeredWindowAttributes(w.edit, 0, 255, LWA_ALPHA);
    int base = std::clamp(500, 100, 900);
    w.editFont = CreateFontW(-MulDiv(13, w.dpi, 96), 0, 0, 0, base, FALSE, FALSE, FALSE, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS,
                             CLIP_DEFAULT_PRECIS, CLEARTYPE_QUALITY, DEFAULT_PITCH, w.family.c_str());
    SendMessageW(w.edit, WM_SETFONT, (WPARAM)w.editFont, TRUE);
    SendMessageW(w.edit, EM_SETLIMITTEXT, f.kind == SetField::Number ? 6 : f.kind == SetField::Color ? 7 : 260, 0);
    SetWindowTextW(w.edit, f.kind == SetField::Number ? Set_FieldValue(f).c_str() : f.cur.c_str());
    SetWindowSubclass(w.edit, Set_EditProc, 1, 0);
    w.editing = k;
    Set_PlaceEdit(w);
    if (!w.render) SetFocus(w.edit);
    SendMessageW(w.edit, EM_SETSEL, 0, -1);
    Set_Invalidate(w);
}

static void Set_Choose(SetWindow& w, int k, int option) {
    SetField& f = w.fields[k];
    if (option >= 0 && option < (int)f.options.size()) f.cur = f.options[option].first;
    Set_ClosePopup(w);
}

static void Set_SliderTo(SetWindow& w, int k, float x) {
    const SetItem* it = Set_ItemOfField(w, k);
    if (!it) return;
    SetField& f = w.fields[k];
    SetParts pt = Set_Parts(f, Set_RowRect(w, *it));
    float t = std::clamp((x - pt.track.left) / (pt.track.right - pt.track.left), 0.0f, 1.0f);
    f.cur = std::to_wstring(f.min + (int)(t * (f.max - f.min) + 0.5f));
    Set_Invalidate(w);
}

static void Set_Save(std::shared_ptr<SetWindow> keep);

static void Set_ResetToSuggested(SetWindow& w) {
    Set_CommitEdit(w, false);
    Set_StopRecording(w);
    Set_ClosePopup(w);
    for (auto& f : w.fields) Set_PutValue(f, f.def);
    Set_SetStatus(w, L"Suggested values are filled in. Press Save to keep them.");
}

static void Set_BuildAndClamp(SetWindow& w) {
    Set_BuildPage(w);
    Set_PlaceEdit(w);
    Set_Invalidate(w);
}

static void Set_GoPage(SetWindow& w, int page) {
    page = std::clamp(page, 0, kSetPageCount - 1);
    Set_CommitEdit(w, true);
    Set_StopRecording(w);
    Set_ClosePopup(w);
    if (page == w.page) return;
    w.page = page;
    w.scrollY = w.scrollTarget = 0;
    w.focus = -1;
    w.pageT = Set_Anim(w) ? 0.0f : 1.0f;
    Set_BuildAndClamp(w);
}

static void Set_OpenLink(PCWSTR url) {
#ifdef SCM_HARNESS
    Wh_Log(L"settings: would open %s", url);
#else
    ShellExecuteW(nullptr, L"open", url, nullptr, nullptr, SW_SHOWNORMAL);
#endif
}

// A click (or Space or Enter) on a field's control.
static void Set_ActivateField(SetWindow& w, int k, const SetHit* hit) {
    SetField& f = w.fields[k];
    if (w.recording >= 0 && w.recording != k) Set_StopRecording(w);
    switch (f.kind) {
        case SetField::Check:
            f.cur = f.cur == L"1" ? L"0" : L"1";
            Set_Invalidate(w);
            break;
        case SetField::Choice:
            if (w.openSel == k) {
                Set_ClosePopup(w);
            } else {
                Set_CommitEdit(w, true);
                Set_OpenPopup(w, k);
            }
            break;
        case SetField::Number:
        case SetField::Text:
            Set_BeginEdit(w, k);
            break;
        case SetField::Color:
            if (hit && hit->kind == SetHit::Chip) {
                Set_CommitEdit(w, false);
                f.cur = Set_HexFromRgb(kSetChips[hit->b]);
                Set_SetStatus(w, L"");
            } else {
                Set_BeginEdit(w, k);
            }
            break;
        case SetField::Hotkey:
            if (hit && hit->kind == SetHit::Clear) {
                f.cur.clear();
                Set_Invalidate(w);
            } else if (w.recording == k) {
                Set_StopRecording(w);
            } else {
                Set_CommitEdit(w, true);
                Set_StartRecording(w, k);
            }
            break;
    }
}

static void Set_FooterAction(SetWindow& w, int which) {
    if (which == 0) {
        Set_ResetToSuggested(w);
    } else if (which == 1) {
        if (!w.render) DestroyWindow(w.hwnd);  // w is gone after this.
    } else {
        Set_CommitEdit(w, true);
        if (g_setWin && g_setWin->hwnd == w.hwnd) Set_Save(g_setWin);
    }
}

// ---- Saving ---------------------------------------------------------------------

static std::wstring Set_ChangedParams(SetWindow& w, int& changed) {
    std::wstring params = L"--quiet mod settings set " + Set_QuoteArg(WH_MOD_ID);
    changed = 0;
    for (auto& f : w.fields) {
        std::wstring value = Set_FieldValue(f);
        if (value != f.value) {
            params += L" " + Set_QuoteArg(std::wstring(f.key) + L"=" + value);
            changed++;
        }
    }
    return params;
}

static void Set_ApplyFrame(SetWindow& w);

static void Set_Save(std::shared_ptr<SetWindow> keep) {
    SetWindow& w = *keep;
    if (w.saving) return;
    Set_StopRecording(w);
    int changed = 0;
    std::wstring params = Set_ChangedParams(w, changed);
    if (!changed) {
        Set_SetStatus(w, L"Nothing changed");
        return;
    }
    std::wstring cli = Set_CliPath();
#ifdef SCM_HARNESS
    // Tests check the command instead of running it.
    std::string line = WideToUtf8(Set_QuoteArg(cli.empty() ? L"windhawk-cli.exe" : cli) + L" " + params);
    HANDLE file = CreateFileW((StoragePath() + L"\\settings-save.txt").c_str(), GENERIC_WRITE, 0, nullptr,
                              CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, nullptr);
    DWORD written = 0;
    bool ok = file != INVALID_HANDLE_VALUE && WriteFile(file, line.data(), (DWORD)line.size(), &written, nullptr);
    if (file != INVALID_HANDLE_VALUE) CloseHandle(file);
    if (!ok) {
        Set_SetStatus(w, L"Couldn't write settings-save.txt", true);
        return;
    }
    for (auto& f : w.fields) f.value = Set_FieldValue(f);
    Set_SetStatus(w, L"Saved");
    return;
#else
    if (cli.empty()) {
        Set_SetStatus(w, L"Couldn't find windhawk-cli.exe, so nothing was saved", true);
        return;
    }
    SHELLEXECUTEINFOW info{sizeof(info)};
    info.fMask = SEE_MASK_NOCLOSEPROCESS | SEE_MASK_NOASYNC | SEE_MASK_FLAG_NO_UI;
    info.hwnd = w.hwnd;
    info.lpVerb = L"runas";
    info.lpFile = cli.c_str();
    info.lpParameters = params.c_str();
    info.nShow = SW_HIDE;
    if (!ShellExecuteExW(&info) || !info.hProcess) {
        DWORD error = GetLastError();
        if (error == ERROR_CANCELLED) {
            Set_SetStatus(w, L"Not saved. The admin prompt was turned down.", true);
        } else {
            WCHAR text[96];
            swprintf_s(text, L"Couldn't start windhawk-cli (error %lu)", error);
            Set_SetStatus(w, text, true);
        }
        return;
    }
    w.saving = true;
    Set_SetStatus(w, L"Saving...");
    // Keep painting and handling input while windhawk-cli works.
    bool quit = false, timedOut = false;
    int quitCode = 0;
    ULONGLONG deadline = GetTickCount64() + 15000;
    while (!quit && !w.destroyed) {
        ULONGLONG now = GetTickCount64();
        if (now >= deadline) {
            timedOut = true;
            break;
        }
        DWORD r = MsgWaitForMultipleObjects(1, &info.hProcess, FALSE, (DWORD)(deadline - now), QS_ALLINPUT);
        if (r == WAIT_OBJECT_0) break;
        if (r != WAIT_OBJECT_0 + 1) {
            timedOut = r == WAIT_TIMEOUT;
            break;
        }
        MSG msg;
        while (PeekMessageW(&msg, nullptr, 0, 0, PM_REMOVE)) {
            if (msg.message == WM_QUIT) {
                quit = true;
                quitCode = (int)msg.wParam;
                break;
            }
            TranslateMessage(&msg);
            DispatchMessageW(&msg);
        }
    }
    DWORD code = 1;
    bool finished = WaitForSingleObject(info.hProcess, 0) == WAIT_OBJECT_0;
    if (finished) GetExitCodeProcess(info.hProcess, &code);
    if (!finished) TerminateProcess(info.hProcess, ERROR_TIMEOUT);
    CloseHandle(info.hProcess);
    w.saving = false;
    if (quit) PostQuitMessage(quitCode);
    if (w.destroyed || !IsWindow(w.hwnd)) return;
    if (!finished && timedOut) {
        Set_SetStatus(w, L"Windhawk didn't answer in 15 seconds. Settings may not be saved.", true);
    } else if (code == 0) {
        Set_LoadFields(w);  // Shows what was stored.
        Set_ApplyFrame(w);  // The title bar and glass switches take effect now, no reopen.
        Set_SetStatus(w, L"Saved");
    } else {
        Wh_Log(L"windhawk-cli exit code %lu", code);
        WCHAR text[96];
        swprintf_s(text, L"Windhawk didn't save the settings (code %lu)", code);
        Set_SetStatus(w, text, true);
    }
#endif
}

// ---- Animation tick ----------------------------------------------------------------

static bool Set_AutoScrollStart(SetWindow& w, float x, float y) {
    if (w.render || w.contentH - Set_ViewH(w) <= 0) return false;  // Nothing to scroll.
    Set_CommitEdit(w, true);
    Set_ClosePopup(w);
    w.autoScroll = true;
    w.autoMoved = false;
    w.autoX = x, w.autoY = y, w.autoDir = 0;
    w.hover = SetHit();
    SetCapture(w.hwnd);
    SetCursor(LoadCursorW(nullptr, IDC_SIZENS));
    Set_Invalidate(w);
    return true;
}

static void Set_AutoScrollStop(SetWindow& w) {
    if (!w.autoScroll) return;
    w.autoScroll = false;  // Before ReleaseCapture: its WM_CAPTURECHANGED comes straight back here.
    w.autoDir = 0;
    if (GetCapture() == w.hwnd) ReleaseCapture();
    Set_Invalidate(w);
}

static void Set_AutoScrollMove(SetWindow& w, bool held) {
    if (held && fabsf(w.mouseY - w.autoY) > kSetAutoDead) w.autoMoved = true;
    SetCursor(LoadCursorW(nullptr, IDC_SIZENS));
}

static bool Set_AutoScrollStep(SetWindow& w) {
    if (!w.autoScroll) return false;
    const float dy = w.mouseY - w.autoY, dist = fabsf(dy) - kSetAutoDead;
    const float dir = dist > 0 ? (dy > 0 ? 1.0f : -1.0f) : 0.0f;
    bool changed = dir != w.autoDir;
    w.autoDir = dir;
    if (dist <= 0) return changed;
    const float maxScroll = std::max(0.0f, w.contentH - Set_ViewH(w));
    const float next = std::clamp(w.scrollY + dir * std::min(kSetAutoMax, dist * kSetAutoGain), 0.0f, maxScroll);
    if (next == w.scrollY) return changed;
    w.scrollY = w.scrollTarget = next;
    Set_PlaceEdit(w);
    return true;
}

static bool Set_Tick(SetWindow& w) {
    bool moved = false, anim = Set_Anim(w);
    auto step = [&](float& v, float target, float rate) {
        float d = target - v;
        if (!anim || fabsf(d) < 0.02f) {
            if (v != target) {
                v = target;
                moved = true;
            }
            return;
        }
        v += d * rate;
        moved = true;
    };
    int ids[2];
    Set_HoverIds(w.hover, ids);
    for (int id : ids)
        if (id >= 0 && !w.glow.count(id)) w.glow[id] = 0;
    for (auto it = w.glow.begin(); it != w.glow.end();) {
        bool on = it->first == ids[0] || it->first == ids[1];
        step(it->second, on ? 1.0f : 0.0f, 0.3f);
        if (!on && it->second == 0) {
            it = w.glow.erase(it);
        } else {
            ++it;
        }
    }
    for (size_t k = 0; k < w.fields.size(); k++) {
        if (w.fields[k].kind != SetField::Check) continue;
        float target = w.fields[k].cur == L"1" ? 1.0f : 0.0f;
        if (!w.knob.count((int)k)) w.knob[(int)k] = target;
        step(w.knob[(int)k], target, 0.35f);
    }
    if (Set_AutoScrollStep(w)) moved = true;
    step(w.autoA, w.autoScroll ? 1.0f : 0.0f, 0.3f);
    if (w.scrollY != w.scrollTarget) {
        float d = w.scrollTarget - w.scrollY;
        if (!anim || fabsf(d) < 0.5f) {
            w.scrollY = w.scrollTarget;
        } else {
            w.scrollY += d * 0.25f;
        }
        moved = true;
        Set_PlaceEdit(w);
    }
    if (w.pageT < 1) {
        w.pageT = anim ? std::min(1.0f, w.pageT + 0.07f) : 1.0f;
        moved = true;
    }
    // Sidebar open / collapse, and the dock edges lighting up under the pointer.
    if (!w.dragRail) {
        float target = w.railCollapsed ? kSetRailMini : w.railW, d = target - w.railCur;
        if (d != 0) {
            w.railCur = (!anim || fabsf(d) < 0.6f) ? target : w.railCur + d * 0.28f;
            Set_BuildPage(w);
            Set_PlaceEdit(w);
            moved = true;
        }
    }
    bool inRail = w.mouseX >= 0 && Set_In(Set_RailDock(w), w.mouseX, w.mouseY);
    D2D1_RECT_F foot = Set_FooterDock(w);
    bool inFoot = w.mouseX >= 0 && Set_In(foot, w.mouseX, w.mouseY);
    step(w.railGlow, inRail ? 1.0f : 0.0f, 0.25f);
    step(w.footGlow, inFoot ? 1.0f : 0.0f, 0.25f);
    return moved;
}

// ---- Keyboard focus ----------------------------------------------------------------

// Focus order: the page's rows, then Reset, Cancel, Save (-1, -2, -3).
static std::vector<int> Set_FocusOrder(const SetWindow& w) {
    std::vector<int> order;
    for (auto& it : w.items)
        if (it.type == SetItem::Row) order.push_back(it.field);
    order.push_back(-1);
    order.push_back(-2);
    order.push_back(-3);
    return order;
}

static void Set_EnsureVisible(SetWindow& w, float top, float bottom) {
    float view = Set_ViewH(w);
    float clear = Set_FootClear() - 18;  // Keep focused rows above the floating footer.
    if (top - 16 < w.scrollTarget) {
        w.scrollTarget = top - 16;
    } else if (bottom + 16 + clear > w.scrollTarget + view) {
        w.scrollTarget = bottom + 16 + clear - view;
    }
    w.scrollTarget = std::clamp(w.scrollTarget, 0.0f, std::max(0.0f, w.contentH - view));
}

static void Set_MoveFocus(SetWindow& w, int dir) {
    Set_CommitEdit(w, true);
    Set_ClosePopup(w);
    std::vector<int> order = Set_FocusOrder(w);
    int index = -1;
    for (size_t i = 0; i < order.size(); i++)
        if (order[i] == w.focus) index = (int)i;
    index = index < 0 ? (dir > 0 ? 0 : (int)order.size() - 1) : (index + dir + (int)order.size()) % (int)order.size();
    w.focus = order[index];
    w.kbd = true;
    if (w.focus >= 0) {
        if (const SetItem* it = Set_ItemOfField(w, w.focus)) Set_EnsureVisible(w, it->y, it->y + it->h);
    }
    Set_Invalidate(w);
}

static void Set_Adjust(SetWindow& w, int dir) {
    if (w.focus < 0) return;
    SetField& f = w.fields[w.focus];
    if (f.kind == SetField::Number) {
        int span = f.max - f.min, step = span <= 100 ? 1 : span <= 3000 ? 10 : 100;
        f.cur = std::to_wstring(std::clamp(_wtoi(Set_FieldValue(f).c_str()) + dir * step, f.min, f.max));
    } else if (f.kind == SetField::Choice && !f.options.empty()) {
        int n = (int)f.options.size(), at = 0;
        for (int i = 0; i < n; i++)
            if (f.cur == f.options[i].first) at = i;
        f.cur = f.options[(at + dir + n) % n].first;
    } else if (f.kind == SetField::Check) {
        f.cur = dir > 0 ? L"1" : L"0";
    }
    Set_Invalidate(w);
}

static bool Set_OnKey(SetWindow& w, UINT vk) {
    if (w.saving) return true;
    if (w.recording >= 0) {
        if (Set_IsModifier(vk)) return true;
        UINT mods = 0;
        if (GetKeyState(VK_CONTROL) & 0x8000) mods |= MOD_CONTROL;
        if (GetKeyState(VK_MENU) & 0x8000) mods |= MOD_ALT;
        if (GetKeyState(VK_SHIFT) & 0x8000) mods |= MOD_SHIFT;
        if ((GetKeyState(VK_LWIN) | GetKeyState(VK_RWIN)) & 0x8000) mods |= MOD_WIN;
        SetField& f = w.fields[w.recording];
        if (vk == VK_ESCAPE && !mods) {
            // Cancel: keep what was there.
        } else if ((vk == VK_BACK || vk == VK_DELETE) && !mods) {
            f.cur.clear();
        } else {
            f.cur = Set_FormatHotkey(mods, vk);
        }
        Set_StopRecording(w);
        return true;
    }
    if (w.openSel >= 0) {
        const SetField& f = w.fields[w.openSel];
        int n = (int)f.options.size();
        if (vk == VK_ESCAPE) Set_ClosePopup(w);
        else if (vk == VK_UP) Set_DropShow(w, w.dropHover = w.dropHover < 0 ? n - 1 : (w.dropHover - 1 + n) % n);
        else if (vk == VK_DOWN) Set_DropShow(w, w.dropHover = w.dropHover < 0 ? 0 : (w.dropHover + 1) % n);
        else if (vk == VK_RETURN || vk == VK_SPACE) Set_Choose(w, w.openSel, w.dropHover);
        Set_Invalidate(w);
        return true;
    }
    bool ctrl = (GetKeyState(VK_CONTROL) & 0x8000) != 0, shift = (GetKeyState(VK_SHIFT) & 0x8000) != 0;
    if (ctrl && vk == 'B') {  // Same shortcut as T3's sidebar.
        Set_ToggleRail(w);
        return true;
    }
    float view = Set_ViewH(w), maxScroll = std::max(0.0f, w.contentH - view);
    switch (vk) {
        case VK_TAB:
            if (ctrl) Set_GoPage(w, (w.page + (shift ? kSetPageCount - 1 : 1)) % kSetPageCount);
            else Set_MoveFocus(w, shift ? -1 : 1);
            return true;
        case VK_SPACE:
        case VK_RETURN:
            w.kbd = true;
            if (w.focus >= 0) Set_ActivateField(w, w.focus, nullptr);
            else if (w.focus <= -1 && w.focus >= -3) Set_FooterAction(w, -1 - w.focus);
            return true;
        case VK_LEFT:
        case VK_RIGHT:
            w.kbd = true;
            Set_Adjust(w, vk == VK_RIGHT ? 1 : -1);
            return true;
        case VK_UP: w.scrollTarget = std::clamp(w.scrollTarget - 60, 0.0f, maxScroll); break;
        case VK_DOWN: w.scrollTarget = std::clamp(w.scrollTarget + 60, 0.0f, maxScroll); break;
        case VK_PRIOR: w.scrollTarget = std::clamp(w.scrollTarget - view * 0.9f, 0.0f, maxScroll); break;
        case VK_NEXT: w.scrollTarget = std::clamp(w.scrollTarget + view * 0.9f, 0.0f, maxScroll); break;
        case VK_HOME: w.scrollTarget = 0; break;
        case VK_END: w.scrollTarget = maxScroll; break;
        case VK_ESCAPE:
            if (!w.render) DestroyWindow(w.hwnd);
            return true;
        default:
            if (ctrl && vk >= '1' && vk <= '6') {
                Set_GoPage(w, (int)(vk - '1'));
                return true;
            }
            return false;
    }
    if (!Set_Anim(w)) w.scrollY = w.scrollTarget;
    Set_PlaceEdit(w);
    Set_Invalidate(w);
    return true;
}

// ---- Window ---------------------------------------------------------------------

static bool Set_EnsureRt(SetWindow& w) {
    if (w.rt) return true;
    if (!Set_EnsureFactories()) return false;
    RECT rc;
    GetClientRect(w.hwnd, &rc);
    D2D1_RENDER_TARGET_PROPERTIES props = D2D1::RenderTargetProperties(
        D2D1_RENDER_TARGET_TYPE_DEFAULT, D2D1::PixelFormat(DXGI_FORMAT_B8G8R8A8_UNORM, D2D1_ALPHA_MODE_PREMULTIPLIED),
        (float)w.dpi, (float)w.dpi);
    return SUCCEEDED(g_setD2d->CreateHwndRenderTarget(
        props, D2D1::HwndRenderTargetProperties(w.hwnd, D2D1::SizeU(std::max(1L, rc.right), std::max(1L, rc.bottom))),
        w.rt.put()));
}

static void Set_Relayout(SetWindow& w) {
    RECT rc;
    GetClientRect(w.hwnd, &rc);
    w.cw = rc.right * 96.0f / w.dpi;
    w.ch = std::max(0.0f, rc.bottom * 96.0f / w.dpi - kSetCapH);
    if (w.rt) w.rt->Resize(D2D1::SizeU(std::max(1L, rc.right), std::max(1L, rc.bottom)));
    Set_BuildAndClamp(w);
}

static bool Set_FieldOn(const SetWindow& w, PCWSTR key, bool def) {
    // The window group wins over a module option with the same suffix.
    const std::wstring windowKey = std::wstring(L"SettingsWindow.") + key;
    for (const auto& f : w.fields)
        if (windowKey == f.key) return f.value == L"1";
    for (const auto& f : w.fields)
        if (wcscmp(f.key, key) == 0) return f.value == L"1";
    const size_t n = wcslen(key);
    for (const auto& f : w.fields) {
        const size_t m = wcslen(f.key);
        if (m >= n && wcscmp(f.key + m - n, key) == 0 && (m == n || f.key[m - n - 1] == L'.')) return f.value == L"1";
    }
    return def;
}

static void Set_ApplyFrame(SetWindow& w) {
    if (w.render || !w.hwnd) return;
    const HWND hwnd = w.hwnd;
    const bool native = Set_FieldOn(w, L"nativeSettingsTitleBar", false), glass = Set_FieldOn(w, L"settingsGlass", true);
    const bool first = !w.frameApplied, wasGlass = w.glass;
    if (!first && native == w.nativeTitle && glass == w.glass) return;
    w.frameApplied = true;
    w.nativeTitle = native;
    w.glass = glass;
    kSetCapH = native ? 0.0f : 40.0f;
    struct SetAccentPolicy { int state, flags, abgr, animation; };
    struct SetCompositionData { DWORD attribute; void* data; SIZE_T size; };
    using SetComposition_t = BOOL(WINAPI*)(HWND, SetCompositionData*);
    auto setComposition =
        (SetComposition_t)(void*)GetProcAddress(GetModuleHandleW(L"user32.dll"), "SetWindowCompositionAttribute");
    if (glass) {
        // Acrylic as one sheet over the whole window, the same material Seamless Flyouts
        // gives the Launchpad settings window in Explorer: the accent acrylic with an 85%
        // Mocha base tint, under the page's own crust tint. The system backdrop
        // (DWMSBT_TRANSIENTWINDOW) went light grey over bright windows and turned to a flat
        // grey slab when the window lost focus; the accent acrylic stays the same.
        int backdrop = 1;  // DWMSBT_NONE
        DwmSetWindowAttribute(hwnd, 38 /* DWMWA_SYSTEMBACKDROP_TYPE */, &backdrop, sizeof(backdrop));
        DWM_BLURBEHIND bb{};
        bb.dwFlags = DWM_BB_ENABLE | DWM_BB_BLURREGION;
        bb.fEnable = TRUE;
        bb.hRgnBlur = CreateRectRgn(0, 0, -1, -1);
        DwmEnableBlurBehindWindow(hwnd, &bb);
        if (bb.hRgnBlur) DeleteObject(bb.hRgnBlur);
        if (setComposition) {
            SetAccentPolicy policy{4 /* ACCENT_ENABLE_ACRYLICBLURBEHIND */, 2, (int)0x012E1E1E, 0};  // same as the launcher grid
            SetCompositionData data{19 /* WCA_ACCENT_POLICY */, &policy, sizeof(policy)};
            setComposition(hwnd, &data);
        }
        MARGINS margins{-1, -1, -1, -1};
        DwmExtendFrameIntoClientArea(hwnd, &margins);
        COLORREF none = 0xFFFFFFFE;  // DWMWA_COLOR_NONE
        DwmSetWindowAttribute(hwnd, 35 /* DWMWA_CAPTION_COLOR */, &none, sizeof(none));
    } else if (wasGlass) {
        // Glass switched off while open: back to a plain solid window.
        if (setComposition) {
            SetAccentPolicy policy{0, 0, 0, 0};
            SetCompositionData data{19 /* WCA_ACCENT_POLICY */, &policy, sizeof(policy)};
            setComposition(hwnd, &data);
        }
        DWM_BLURBEHIND bb{};
        bb.dwFlags = DWM_BB_ENABLE;
        bb.fEnable = FALSE;
        DwmEnableBlurBehindWindow(hwnd, &bb);
        MARGINS margins{0, 0, 0, 0};
        DwmExtendFrameIntoClientArea(hwnd, &margins);
        int backdrop = 0;  // DWMSBT_AUTO
        DwmSetWindowAttribute(hwnd, 38 /* DWMWA_SYSTEMBACKDROP_TYPE */, &backdrop, sizeof(backdrop));
        COLORREF caption = RefFromRgb(mocha::crust);
        DwmSetWindowAttribute(hwnd, 35 /* DWMWA_CAPTION_COLOR */, &caption, sizeof(caption));
    }
    // With the frame extended DWM would draw its own minimize, maximize and close buttons over the
    // built-in title bar; without a system menu it draws none. The Windows title bar keeps it.
    // Minimize, maximize and close still work from the taskbar either way.
    LONG_PTR style = GetWindowLongPtrW(hwnd, GWL_STYLE);
    SetWindowLongPtrW(hwnd, GWL_STYLE, native ? (style | WS_SYSMENU) : (style & ~WS_SYSMENU));
    // Set_WndProc's WM_NCCALCSIZE drops or keeps the system title bar to match.
    SetWindowPos(hwnd, nullptr, 0, 0, 0, 0, SWP_FRAMECHANGED | SWP_NOMOVE | SWP_NOSIZE | SWP_NOZORDER | SWP_NOACTIVATE);
    if (!first) {
        Set_Relayout(w);
        RedrawWindow(hwnd, nullptr, nullptr, RDW_INVALIDATE | RDW_FRAME | RDW_UPDATENOW);
    }
}

static void Set_RememberRect(SetWindow& w) {
    if (w.render || IsIconic(w.hwnd) || IsZoomed(w.hwnd)) return;
    GetWindowRect(w.hwnd, &w.normalRect);
}

static LRESULT CALLBACK Set_WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) {
    SetWindow* w = g_setWin && g_setWin->hwnd == hwnd ? g_setWin.get() : nullptr;
    if (!w) return DefWindowProcW(hwnd, msg, wParam, lParam);
    if (w->nativeTitle) {
        LRESULT r = 0;
        if (DwmDefWindowProc(hwnd, msg, wParam, lParam, &r)) return r;  // Hover and clicks on DWM's buttons.
    }
    auto dipX = [&](LPARAM l) { return (float)(short)LOWORD(l) * 96.0f / w->dpi; };
    auto dipY = [&](LPARAM l) { return (float)(short)HIWORD(l) * 96.0f / w->dpi - kSetCapH; };
    switch (msg) {
        case WM_APP_SETTINGS_RELOAD:
            if (!w->saving) {
                Set_LoadFields(*w);
                Set_ApplyFrame(*w);
            }
            return 0;
        case WM_APP_SETTINGS_ACTIVATE: ShowWindow(hwnd, SW_RESTORE); ForceForeground(hwnd); return 0;
        case WM_NCCALCSIZE:
            // No system title bar: keep the side and bottom frames, the client starts at the top edge.
            if (wParam && !w->render && !w->nativeTitle) {
                auto* nc = (NCCALCSIZE_PARAMS*)lParam;
                LONG top = nc->rgrc[0].top;
                LRESULT r = DefWindowProcW(hwnd, msg, wParam, lParam);
                nc->rgrc[0].top = top;
                if (IsZoomed(hwnd))
                    nc->rgrc[0].top += GetSystemMetricsForDpi(SM_CYSIZEFRAME, w->dpi) +
                                       GetSystemMetricsForDpi(SM_CXPADDEDBORDER, w->dpi);
                return r;
            }
            break;
        case WM_NCHITTEST: {
            if (w->render || w->nativeTitle) break;
            POINT pt{GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam)};
            ScreenToClient(hwnd, &pt);
            RECT rc;
            GetClientRect(hwnd, &rc);
            if (pt.x < 0 || pt.y < 0 || pt.x >= rc.right || pt.y >= rc.bottom) break;
            int frame = GetSystemMetricsForDpi(SM_CYSIZEFRAME, w->dpi) + GetSystemMetricsForDpi(SM_CXPADDEDBORDER, w->dpi);
            if (!IsZoomed(hwnd) && pt.y < frame)
                return pt.x < frame * 2 ? HTTOPLEFT : pt.x >= rc.right - frame * 2 ? HTTOPRIGHT : HTTOP;
            float x = pt.x * 96.0f / w->dpi, y = pt.y * 96.0f / w->dpi - kSetCapH;
            if (y < 0) return Set_CapButtonAt(*w, x, y) >= 0 ? HTCLIENT : HTCAPTION;
            return HTCLIENT;
        }
        case WM_ACTIVATE:
            w->active = LOWORD(wParam) != WA_INACTIVE;
            if (!w->active) Set_AutoScrollStop(*w);
            Set_Invalidate(*w);
            break;
        case WM_ERASEBKGND:
            return 1;
        case WM_PAINT:
        case WM_PRINTCLIENT: {
            PAINTSTRUCT ps;
            BeginPaint(hwnd, &ps);
            if (!w->render && Set_EnsureRt(*w)) Set_Draw(*w, w->rt.get());
            EndPaint(hwnd, &ps);
            return 0;
        }
        case WM_CTLCOLOREDIT: {
            HDC dc = (HDC)wParam;
            SetTextColor(dc, RefFromRgb(mocha::text));
            SetBkColor(dc, RefFromRgb(kSetBoxFill));
            return (LRESULT)w->editBrush;
        }
        case WM_SIZE:
            if (wParam != SIZE_MINIMIZED && !w->render) {
                Set_Relayout(*w);
                Set_RememberRect(*w);
                RedrawWindow(hwnd, nullptr, nullptr, RDW_INVALIDATE | RDW_UPDATENOW);  // No stale title bar after a snap.
            }
            return 0;
        case WM_MOVE:
            Set_RememberRect(*w);
            return 0;
        case WM_GETMINMAXINFO: {
            auto* mm = (MINMAXINFO*)lParam;
            RECT r{0, 0, MulDiv(760, w->dpi, 96), MulDiv(520, w->dpi, 96)};
            AdjustWindowRectExForDpi(&r, GetWindowLongW(hwnd, GWL_STYLE), FALSE, GetWindowLongW(hwnd, GWL_EXSTYLE),
                                     w->dpi);
            mm->ptMinTrackSize = {r.right - r.left, r.bottom - r.top};
            return 0;
        }
        case WM_DPICHANGED: {
            if (g_setForceDpi) return 0;
            Set_CommitEdit(*w, true);
            w->dpi = HIWORD(wParam);
            if (w->rt) w->rt->SetDpi((float)w->dpi, (float)w->dpi);
            auto* r = (RECT*)lParam;
            SetWindowPos(hwnd, nullptr, r->left, r->top, r->right - r->left, r->bottom - r->top,
                         SWP_NOZORDER | SWP_NOACTIVATE);
            Set_Relayout(*w);
            return 0;
        }
        case WM_TIMER:
            if (wParam == kSetTimerId) {
                if (Set_Tick(*w)) Set_Invalidate(*w);
                return 0;
            }
            break;
        case WM_MOUSEMOVE: {
            if (w->saving) return 0;
#ifdef LP_TEST_HOVER  // Only the test script's moves (marked 0x8000), never a real cursor passing over.
            if (!(wParam & 0x8000)) return 0;
#endif
            float x = dipX(lParam), y = dipY(lParam);
#ifndef LP_TEST_HOVER  // The test build feeds pointer moves by message; a leave would undo them.
            if (!w->tracking && !w->render) {
#else
            if (false) {
#endif
                TRACKMOUSEEVENT t{sizeof(t), TME_LEAVE, hwnd, 0};
                TrackMouseEvent(&t);
                w->tracking = true;
            }
            w->mouseX = x;
            w->mouseY = y;
            if (w->autoScroll) {
                Set_AutoScrollMove(*w, (wParam & MK_MBUTTON) != 0);
                return 0;
            }
            if (w->dragRail) {
                Set_RailDragTo(*w, x - w->dragOff);
                return 0;
            }
            if (w->dragSlider >= 0) {
                Set_SliderTo(*w, w->dragSlider, x);
                return 0;
            }
            if (w->dragScroll) {
                D2D1_RECT_F th = Set_ScrollThumb(*w);
                float view = Set_ViewH(*w), thh = th.bottom - th.top, range = view - thh - 8;
                float t = range > 0 ? std::clamp((y - w->dragOff - 4) / range, 0.0f, 1.0f) : 0;
                w->scrollTarget = w->scrollY = t * std::max(0.0f, w->contentH - view);
                Set_PlaceEdit(*w);
                Set_Invalidate(*w);
                return 0;
            }
            SetHit h = Set_Hit(*w, x, y);
            int dh = h.kind == SetHit::Drop ? h.b : -1;
            if (h.kind != w->hover.kind || h.id != w->hover.id || h.a != w->hover.a || h.b != w->hover.b ||
                dh != w->dropHover) {
                w->hover = h;
                if (w->openSel >= 0) w->dropHover = dh;
                Set_Invalidate(*w);
            }
            return 0;
        }
        case WM_MOUSELEAVE: {
            POINT pointer; GetCursorPos(&pointer);
            w->tracking = false;
            w->hover = SetHit();
            if (!w->dragRail && !w->autoScroll) w->mouseX = w->mouseY = -1;
            Set_Invalidate(*w);
            return 0;
        }
        case WM_SETCURSOR:
            if (LOWORD(lParam) == HTCLIENT) {
                PCWSTR cur = w->dragRail || w->hover.kind == SetHit::RailEdge ? IDC_SIZEWE
                             : Set_Clickable(w->hover)                         ? IDC_HAND
                                                                               : IDC_ARROW;
                SetCursor(LoadCursorW(nullptr, cur));
                return TRUE;
            }
            break;
        case WM_LBUTTONDOWN: {
            if (w->saving) return 0;
            if (w->autoScroll) {  // A click ends autoscroll and does nothing else.
                Set_AutoScrollStop(*w);
                return 0;
            }
            if (!w->render) SetFocus(hwnd);
            w->kbd = false;
            float x = dipX(lParam), y = dipY(lParam);
            SetHit h = Set_Hit(*w, x, y);
            if (w->openSel >= 0) {  // The popup eats the click, whatever it hits.
                if (h.kind == SetHit::Drop) Set_Choose(*w, h.a, h.b);
                else Set_ClosePopup(*w);
                return 0;
            }
            Set_CommitEdit(*w, true);
            if (w->recording >= 0 && !(h.kind == SetHit::Control && h.a == w->recording)) Set_StopRecording(*w);
            w->hover = h;
            switch (h.kind) {
                case SetHit::Rail:
                    Set_GoPage(*w, h.a);
                    break;
                case SetHit::RailToggle:
                    Set_ToggleRail(*w);
                    break;
                case SetHit::RailEdge:
                    w->dragRail = true;
                    w->dragOff = x - Set_RailDock(*w).right;
                    SetCapture(hwnd);
                    Set_Invalidate(*w);
                    break;
                case SetHit::Footer:
                    Set_FooterAction(*w, h.a);
                    return 0;  // The window may be gone.
                case SetHit::Control:
                case SetHit::Clear:
                case SetHit::Chip:
                    w->focus = h.a;
                    Set_ActivateField(*w, h.a, &h);
                    break;
                case SetHit::Slider:
                    w->focus = h.a;
                    w->dragSlider = h.a;
                    SetCapture(hwnd);
                    Set_SliderTo(*w, h.a, x);
                    break;
                case SetHit::Scroll: {
                    w->dragScroll = true;
                    w->dragOff = y - Set_ScrollThumb(*w).top;
                    SetCapture(hwnd);
                    Set_Invalidate(*w);
                    break;
                }
                case SetHit::Link:
                    Set_OpenLink(w->items[h.a].url.c_str());
                    break;
                case SetHit::Caption:
                    w->capDown = h.a + 1;
                    SetCapture(hwnd);
                    Set_Invalidate(*w);
                    break;
                default:
                    break;
            }
            return 0;
        }
        case WM_LBUTTONUP:
        case WM_CAPTURECHANGED:
            if (msg == WM_CAPTURECHANGED && w->autoScroll && (HWND)lParam != hwnd) Set_AutoScrollStop(*w);
            if (w->capDown) {
                int b = w->capDown - 1;
                w->capDown = 0;
                if (msg == WM_LBUTTONUP) {
                    if (GetCapture() == hwnd) ReleaseCapture();
                    SetHit h = Set_Hit(*w, dipX(lParam), dipY(lParam));
                    if (h.kind == SetHit::Caption && h.a == b) {
                        if (b == 0) ShowWindow(hwnd, SW_MINIMIZE);
                        else if (b == 1) ShowWindow(hwnd, IsZoomed(hwnd) ? SW_RESTORE : SW_MAXIMIZE);
                        else PostMessageW(hwnd, WM_CLOSE, 0, 0);
                    }
                }
                Set_Invalidate(*w);
                return 0;
            }
            if (w->dragSlider >= 0 || w->dragScroll || w->dragRail) {
                w->dragSlider = -1;
                w->dragScroll = false;
                w->dragRail = false;
                if (msg == WM_LBUTTONUP && GetCapture() == hwnd) ReleaseCapture();
                Set_Invalidate(*w);
            }
            return 0;
        case WM_MBUTTONDOWN:
            if (w->saving) return 0;
            if (w->autoScroll) Set_AutoScrollStop(*w);  // Toggle mode: the next middle click ends it.
            else Set_AutoScrollStart(*w, dipX(lParam), dipY(lParam));
            return 0;
        case WM_MBUTTONUP:
            if (w->autoScroll && w->autoMoved) Set_AutoScrollStop(*w);  // Held and dragged: stop on release.
            return 0;
        case WM_RBUTTONDOWN:
        case WM_XBUTTONDOWN:
            if (w->autoScroll) {
                Set_AutoScrollStop(*w);
                return msg == WM_XBUTTONDOWN ? TRUE : 0;
            }
            break;
        case WM_MOUSEWHEEL: {
            Set_AutoScrollStop(*w);
            if (w->openSel >= 0 && Set_In(w->dropRect, w->mouseX, w->mouseY)) {
                int n = (int)w->fields[w->openSel].options.size(), vis = Set_DropVisible(*w);
                int step = GET_WHEEL_DELTA_WPARAM(wParam) > 0 ? -3 : 3;
                w->dropTop = std::clamp(w->dropTop + step, 0, std::max(0, n - vis));
                SetHit h = Set_Hit(*w, w->mouseX, w->mouseY);
                w->hover = h;
                w->dropHover = h.kind == SetHit::Drop ? h.b : w->dropHover;
                Set_Invalidate(*w);
                return 0;
            }
            Set_CommitEdit(*w, true);
            Set_ClosePopup(*w);
            float delta = (float)GET_WHEEL_DELTA_WPARAM(wParam) / WHEEL_DELTA;
            float maxScroll = std::max(0.0f, w->contentH - Set_ViewH(*w));
            w->scrollTarget = std::clamp(w->scrollTarget - delta * 72, 0.0f, maxScroll);
            if (!Set_Anim(*w)) w->scrollY = w->scrollTarget;
            Set_Invalidate(*w);
            return 0;
        }
        case WM_KEYDOWN:
        case WM_SYSKEYDOWN:
            if (w->autoScroll) {  // Any key ends autoscroll; Escape does nothing else.
                Set_AutoScrollStop(*w);
                if (wParam == VK_ESCAPE) return 0;
            }
            if (Set_OnKey(*w, (UINT)wParam)) return 0;
            // Without a system menu (glass title bar) Windows no longer turns Alt+F4 into a close.
            if (msg == WM_SYSKEYDOWN && wParam == VK_F4 && w->recording < 0) {
                PostMessageW(hwnd, WM_CLOSE, 0, 0);
                return 0;
            }
            break;
        case WM_CHAR:
        case WM_SYSCHAR:
            if (w->recording >= 0) return 0;
            break;
        case WM_KILLFOCUS:
            if (w->recording >= 0 && (HWND)wParam != w->edit) Set_StopRecording(*w);
            break;
        case WM_CLOSE:
            DestroyWindow(hwnd);
            return 0;
        case WM_DESTROY: {
            Set_StopRecording(*w);
            RemovePropW(hwnd, kSetAutoProp);
            if (w->timer) KillTimer(hwnd, kSetTimerId);
            if (!w->render && w->normalRect.right > w->normalRect.left) {
                const RECT& r = w->normalRect;
                SetState(StateKey(L"Settings", L"X").c_str(), r.left);
                SetState(StateKey(L"Settings", L"Y").c_str(), r.top);
                SetState(StateKey(L"Settings", L"CX").c_str(), r.right - r.left);
                SetState(StateKey(L"Settings", L"CY").c_str(), r.bottom - r.top);
            }
            if (!w->render) {
                SetState(StateKey(L"Settings", L"RailW").c_str(), (int)w->railW);
                SetState(StateKey(L"Settings", L"RailCollapsed").c_str(), w->railCollapsed ? 1 : 0);
            }
            return 0;
        }
        case WM_NCDESTROY: {
            if (w->editFont) DeleteObject(w->editFont);
            if (w->editBrush) DeleteObject(w->editBrush);
            if (w->iconSmall) DestroyIcon(w->iconSmall);
            if (w->iconBig) DestroyIcon(w->iconBig);
            if (w->owner) DestroyWindow(w->owner);
            w->destroyed = true;
            w->hwnd = nullptr;
            w->edit = nullptr;
            w->rt.reset();
            g_settingsWnd = nullptr; PostQuitMessage(0);
            g_setWin.reset();
            Set_ReleaseFactories();
            return DefWindowProcW(hwnd, msg, wParam, lParam);
        }
    }
    return DefWindowProcW(hwnd, msg, wParam, lParam);
}

// Blue to mauve rounded square with a clipboard glyph, px pixels square.
static HICON Set_MakeIcon(const std::wstring& iconFamily, int px) {
    if (px <= 0 || !Set_EnsureFactories()) return nullptr;
    SetCom<IWICBitmap> bmp;
    SetCom<ID2D1RenderTarget> rt;
    if (FAILED(g_setWic->CreateBitmap(px, px, GUID_WICPixelFormat32bppPBGRA, WICBitmapCacheOnLoad, bmp.put())))
        return nullptr;
    D2D1_RENDER_TARGET_PROPERTIES props = D2D1::RenderTargetProperties(
        D2D1_RENDER_TARGET_TYPE_DEFAULT, D2D1::PixelFormat(DXGI_FORMAT_UNKNOWN, D2D1_ALPHA_MODE_PREMULTIPLIED), 96, 96);
    if (FAILED(g_setD2d->CreateWicBitmapRenderTarget(bmp.get(), props, rt.put()))) return nullptr;
    float s = (float)px;
    SetWindow dummy;
    SetPaint p(dummy, rt.get());
    auto glyph = Set_Fmt(iconFamily, s * 0.6f, 400, false, DWRITE_TEXT_ALIGNMENT_CENTER, true);
    rt->BeginDraw();
    rt->Clear(D2D1::ColorF(0, 0));
    Set_DrawMark(p, glyph.get(), {0, 0, s, s}, 1);
    if (FAILED(rt->EndDraw())) return nullptr;
    std::vector<BYTE> pix((size_t)px * px * 4);
    if (FAILED(bmp->CopyPixels(nullptr, px * 4, (UINT)pix.size(), pix.data()))) return nullptr;
    for (size_t i = 0; i < pix.size(); i += 4) {  // Icons want straight alpha.
        BYTE a = pix[i + 3];
        if (a && a < 255)
            for (int c = 0; c < 3; c++) pix[i + c] = (BYTE)std::min(255, pix[i + c] * 255 / a);
    }
    BITMAPV5HEADER bi{};
    bi.bV5Size = sizeof(bi);
    bi.bV5Width = px;
    bi.bV5Height = -px;
    bi.bV5Planes = 1;
    bi.bV5BitCount = 32;
    bi.bV5Compression = BI_BITFIELDS;
    bi.bV5RedMask = 0x00FF0000;
    bi.bV5GreenMask = 0x0000FF00;
    bi.bV5BlueMask = 0x000000FF;
    bi.bV5AlphaMask = 0xFF000000;
    void* bits = nullptr;
    HDC dc = GetDC(nullptr);
    HBITMAP color = CreateDIBSection(dc, (BITMAPINFO*)&bi, DIB_RGB_COLORS, &bits, nullptr, 0);
    ReleaseDC(nullptr, dc);
    if (!color || !bits) return nullptr;
    memcpy(bits, pix.data(), pix.size());
    std::vector<BYTE> maskBits((size_t)((px + 15) / 16) * 2 * px, 0);
    HBITMAP mask = CreateBitmap(px, px, 1, 1, maskBits.data());
    ICONINFO ii{TRUE, 0, 0, mask, color};
    HICON icon = CreateIconIndirect(&ii);
    DeleteObject(mask);
    DeleteObject(color);
    return icon;
}

// The class belongs to this DLL and goes away with the settings thread. Registered under
// Explorer's handle it outlived a mod update, and the next window ran the unloaded code.
static void Set_RegisterClass() {
    UnregisterClassW(kSettingsClass, GetModuleHandleW(nullptr));  // left by builds before 2.3.0
    WNDCLASSEXW wc{sizeof(wc)};
    wc.lpfnWndProc = Set_WndProc;
    wc.hInstance = (HINSTANCE)&__ImageBase;
    wc.hCursor = LoadCursorW(nullptr, IDC_ARROW);
    wc.lpszClassName = kSettingsClass;
    RegisterClassExW(&wc);
}

// Builds the window, hidden. render: an off-screen copy that is never shown (tests and PNG output).
static bool Set_Create(bool render) {
    if (!Set_EnsureFactories()) return false;
    Set_RegisterClass();
    auto w = std::make_shared<SetWindow>();
    w->render = render;
    w->editBrush = CreateSolidBrush(RefFromRgb(kSetBoxFill));
    g_setWin = w;
    if (render) {
        // An owned window gets no taskbar button.
        w->owner = CreateWindowExW(WS_EX_TOOLWINDOW, L"STATIC", L"", WS_POPUP, 0, 0, 0, 0, nullptr, nullptr,
                                   GetModuleHandleW(nullptr), nullptr);
    }
    const int offX = GetSystemMetrics(SM_XVIRTUALSCREEN) - 6000, offY = GetSystemMetrics(SM_YVIRTUALSCREEN);
    // The built-in title bar until Set_ApplyFrame reads the switches.
    kSetCapH = 40.0f;
    const DWORD style = WS_OVERLAPPEDWINDOW | WS_CLIPCHILDREN;
    HWND hwnd = CreateWindowExW(0, kSettingsClass, L"Seamless FPS Overlay settings", style,
                                render ? offX : CW_USEDEFAULT, render ? offY : CW_USEDEFAULT, 800, 600, w->owner,
                                nullptr, (HINSTANCE)&__ImageBase, nullptr);
    if (!hwnd) {
        g_setWin.reset();
        return false;
    }
    w->hwnd = hwnd;
    SetPropW(hwnd, kSetAutoProp, (HANDLE)1);  // Seamless Autoscroll leaves this window to Set_AutoScroll*.
    w->dpi = g_setForceDpi ? g_setForceDpi : GetDpiForWindow(hwnd);
    ApplyDarkWindow(hwnd);
    COLORREF caption = RefFromRgb(mocha::crust), captionText = RefFromRgb(mocha::text);
    DwmSetWindowAttribute(hwnd, 35 /* DWMWA_CAPTION_COLOR */, &caption, sizeof(caption));
    DwmSetWindowAttribute(hwnd, 36 /* DWMWA_TEXT_COLOR */, &captionText, sizeof(captionText));
    Set_MakeFormats(*w);
    Set_LoadFields(*w);
    if (!render) {
        w->railW = std::clamp((float)GetState(StateKey(L"Settings", L"RailW").c_str(), (int)kSetRailDef), kSetRailMin, kSetRailMax);
        w->railCollapsed = GetState(StateKey(L"Settings", L"RailCollapsed").c_str(), 0) != 0;
        w->railCur = w->railCollapsed ? kSetRailMini : w->railW;
    }
    if (!render) {
        w->iconSmall = Set_MakeIcon(w->iconFamily, GetSystemMetricsForDpi(SM_CXSMICON, w->dpi));
        w->iconBig = Set_MakeIcon(w->iconFamily, GetSystemMetricsForDpi(SM_CXICON, w->dpi));
        if (w->iconSmall) SendMessageW(hwnd, WM_SETICON, ICON_SMALL, (LPARAM)w->iconSmall);
        if (w->iconBig) SendMessageW(hwnd, WM_SETICON, ICON_BIG, (LPARAM)w->iconBig);
        Set_ApplyFrame(*w);  // Title bar and glass; also drops the system title bar the first WM_NCCALCSIZE kept.
    }

    auto outer = [&](float cwDip, float chDip, SIZE& size) {
        RECT r{0, 0, MulDiv((int)cwDip, w->dpi, 96), MulDiv((int)chDip, w->dpi, 96)};
        AdjustWindowRectExForDpi(&r, style, FALSE, 0, w->dpi);
        size = {r.right - r.left, r.bottom - r.top};
    };
    SIZE size;
    if (render) {
        w->cw = 980;
        w->ch = 700;
        outer(w->cw, w->ch, size);
        SetWindowPos(hwnd, nullptr, offX, offY, size.cx, size.cy, SWP_NOZORDER | SWP_NOACTIVATE);
        Set_BuildPage(*w);
        return true;
    }
    outer(980, 720, size);
    POINT cursor;
    GetCursorPos(&cursor);
    MONITORINFO mi{sizeof(mi)};
    GetMonitorInfoW(MonitorFromPoint(cursor, MONITOR_DEFAULTTONEAREST), &mi);
    const RECT& work = mi.rcWork;
    int width = std::min((int)size.cx, (int)(work.right - work.left) * 9 / 10);
    int height = std::min((int)size.cy, (int)(work.bottom - work.top) * 9 / 10);
    RECT r{(work.left + work.right - width) / 2, (work.top + work.bottom - height) / 2, 0, 0};
    r.right = r.left + width;
    r.bottom = r.top + height;
    int cx = GetState(StateKey(L"Settings", L"CX").c_str(), 0);
    int cy = GetState(StateKey(L"Settings", L"CY").c_str(), 0);
    if (cx > 0 && cy > 0) {
        RECT saved{GetState(StateKey(L"Settings", L"X").c_str(), 0), GetState(StateKey(L"Settings", L"Y").c_str(), 0),
                   0, 0};
        saved.right = saved.left + cx;
        saved.bottom = saved.top + cy;
        if (MonitorFromRect(&saved, MONITOR_DEFAULTTONULL)) r = saved;
    }
    SetWindowPos(hwnd, nullptr, r.left, r.top, r.right - r.left, r.bottom - r.top, SWP_NOZORDER | SWP_NOACTIVATE);
    // The monitor it landed on may have a different scale.
    UINT dpi = GetDpiForWindow(hwnd);
    if (!g_setForceDpi && dpi != w->dpi) w->dpi = dpi;
    Set_Relayout(*w);
    w->pageT = Set_Anim(*w) ? 0.0f : 1.0f;
    w->timer = SetTimer(hwnd, kSetTimerId, 15, nullptr) != 0;
    return true;
}

void Settings_Open() {
    if (g_setWin && g_setWin->hwnd && !g_setWin->render) {
        HWND hwnd = g_setWin->hwnd;
        if (IsIconic(hwnd)) ShowWindow(hwnd, SW_RESTORE);
        SetForegroundWindow(hwnd);
        return;
    }
    if (g_setWin) Settings_Close();
    if (!Set_Create(false)) return;
    HWND hwnd = g_setWin->hwnd;
    ShowWindow(hwnd, SW_SHOW);
    SetForegroundWindow(hwnd);
    SetFocus(hwnd);
}

void Settings_Close() {
    if (g_setWin && g_setWin->hwnd) DestroyWindow(g_setWin->hwnd);
    g_setWin.reset();
}

bool Settings_IsOpen() { return g_setWin && g_setWin->hwnd && !g_setWin->render; }


DWORD WINAPI SettingsThread(void*) {
 SetThreadDpiAwarenessContext(DPI_AWARENESS_CONTEXT_PER_MONITOR_AWARE_V2);
 CoInitializeEx(nullptr, COINIT_APARTMENTTHREADED);
 Settings_Open();
 if (g_setWin) g_settingsWnd=g_setWin->hwnd;
 MSG msg;
 while (g_settingsWnd && GetMessageW(&msg,nullptr,0,0)>0) { TranslateMessage(&msg); DispatchMessageW(&msg); }
 Settings_Close(); UnregisterClassW(kSettingsClass,(HINSTANCE)&__ImageBase); Set_ReleaseFactories(); CoUninitialize(); return 0;
}
void OpenSettingsWindow() {
 if (HWND hwnd=g_settingsWnd) { PostMessageW(hwnd,WM_APP_SETTINGS_ACTIVATE,0,0); return; }
 if(g_settingsThread) { if(WaitForSingleObject(g_settingsThread,0)==WAIT_TIMEOUT) return; CloseHandle(g_settingsThread); }
 g_settingsStop=false; g_settingsThread=CreateThread(nullptr,0,SettingsThread,nullptr,0,nullptr);
}
void CloseSettingsWindow() {
 g_settingsStop=true;
 if(HWND hwnd=g_settingsWnd) PostMessageW(hwnd,WM_CLOSE,0,0);
 if(g_settingsThread) { WaitForSingleObject(g_settingsThread,15000); CloseHandle(g_settingsThread); g_settingsThread=nullptr; }
}
// The tray menu: the engine's own menu (Set_TrayMenu), rows in the order they always had.
static std::vector<SetMenuItem> TrayItems(const std::vector<TrayRow>& rows) {
    std::vector<SetMenuItem> out;
    for (const TrayRow& r : rows) {
        if (r.separator) out.push_back(Set_MenuSep());
        else if (!r.sub.empty()) out.push_back(Set_MenuSub(r.glyph.c_str(), r.label.c_str(), TrayItems(r.sub), r.disabled));
        else out.push_back(Set_MenuRow(r.id, r.glyph.c_str(), r.label.c_str(), r.checked, r.disabled, r.hint.c_str()));
    }
    return out;
}
int ShowTrayMenu(HWND owner, const POINT* at, const std::vector<TrayRow>& rows) {
    return Set_TrayMenu(owner, TrayItems(rows), at);
}
}  // namespace sfoset
