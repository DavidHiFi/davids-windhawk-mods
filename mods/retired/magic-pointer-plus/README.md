# Magic Pointer Plus

[☕ Support on Ko-fi](https://ko-fi.com/DavidHiFi)

The Plus version gives its menus the same look as the rest of the desktop: a blurred,
rounded Catppuccin menu with roomy rows and one soft hover, matching Seamless Flyouts.
Based on Magic Pointer by Rono.

The Magic Pointer from Google's Googlebooks, on Windows: an AI mouse cursor.
Wiggle the mouse, then point at anything on screen, select it, and ask Gemini,
ChatGPT or Claude about it, search it with Google Lens, copy its text or
translate it.

[GitHub](https://github.com/rono-zeroseven) · Discord: **rono007**

![Magic Pointer in action](https://raw.githubusercontent.com/rono-zeroseven/magic-pointer/v1.0.2/assets/magic-pointer/preview.gif)

*Animated preview of Magic Pointer.*

## How to use

1. **Shake the mouse**, or swipe back and forth on the touchpad. The keyboard
   shortcut (**Win+Shift+G** by default) works too.
2. **Point and select.** Hover over a button, image, link or paragraph to
   outline it, then click to select it. Or click and drag to select any area.
3. **Ask.** A card opens next to your selection. Type a question and press
   Enter, or pick a suggestion. With an API key, the **Translate** button on
   the card translates the text in your selection into your Windows language,
   or into the language you pick in the settings.

**No selection needed.** While the pointer is on screen, just start typing: the
card opens at the pointer with your text and no image, and Enter asks. Its **+**
button adds a selection later. Magic Pointer only takes your typing while the
pointer is showing; to keep typing in the app you were using, turn off **Start
typing to ask** in the settings.

Press **Esc** or **right-click** to put the Magic Pointer away. It also leaves
on its own when the mouse stays still for a while.

## Gemini, ChatGPT and Claude

Paste an API key in the mod's Windhawk settings to receive answers directly in
the card. You can ask follow-up questions. There is just one **API key**
setting: the mod recognizes which service a key belongs to.

* **Gemini**: get a free key from
  [Google AI Studio](https://aistudio.google.com/apikey).
* **ChatGPT**: create a key on the
  [OpenAI platform](https://platform.openai.com/api-keys). OpenAI bills API
  usage to your account.
* **Claude**: create a key in the
  [Claude Console](https://platform.claude.com/settings/keys). Anthropic bills
  API usage to your account.

With a key, that assistant handles everything that needs one: answers,
follow-up questions, **Smart suggestions** and **Translate**. The **Model**
setting chooses how it answers. **Fast**, the default, starts in a second or
two. **Balanced** and **Smartest** think longer, so their answers are better
but start later and cost more. They use Gemini Flash-Lite, 3.6 Flash and Pro
(Pro usually needs a paid plan); ChatGPT gpt-6-luna, gpt-6.1-terra and
gpt-6.1-sol; Claude Haiku 5.5, Sonnet 5.5 and Opus 5.5. If the chosen model
isn't available, for example because it is busy or needs a paid plan, a faster
one answers instead. Without any key, Magic Pointer works through Gemini in
your browser, as described below.

**Smart suggestions** are optional and disabled by default. When enabled,
the assistant suggests up to three things to do with each selection, always
with its fastest model so that the suggestions appear quickly.
Drag over an answer to select text, then press Ctrl+C or right-click to copy.
The **Copy** button copies the whole answer, including while it is streaming.


It also works without a key: **Send** (or **Ask in Gemini**) opens
Gemini in your browser, types your question into its message box and pastes
your selections there as PNG files. It waits for the new Gemini page to finish
loading, never uses a Gemini tab that was already open, and never presses
Enter: review the draft and send it when ready. If something couldn't be
added, the card comes back and says what to do, usually to click Gemini's
message box and press Ctrl+V. You can also search with Google Lens or copy the
image and its recognized text.

With a key, the **Ask in Gemini** button in the card's top row (the arrow
leaving a window) carries on in Gemini's own app instead of in the card: it
types the question you have started to write, or else the last one you asked
here, and attaches every selection.

Gemini and Google Lens open in your Windows default browser, or in the one you
pick with the **Browser** setting: Chrome, Edge, Firefox, Brave, Zen, Opera,
Vivaldi, LibreWolf, Waterfox, Floorp, or any other browser through the path of
its program. The draft is only typed into a window of that browser, and only
once the browser itself reports that the page is Gemini's chat. Chrome, Edge,
Firefox and Zen have been tried; the others share their engines. Like
Chromium-based browsers, Firefox-based ones turn on their accessibility support
when it's used.

## Text recognition

Every selection is read with the OCR built into Windows 10 and 11, entirely
on your PC. Copy the text with the **Aa** button, and the assistant gets it as
extra context. OCR uses the languages installed in Windows.

## Privacy and temporary files

Summoning the pointer, selecting an area and copying its image or text stay
on your PC with the default settings. The mod contacts the services of
Google, OpenAI or Anthropic when you use these features:

* With an API key, **Send**, a suggestion chip or **Translate** sends your
  selected regions as JPEG images (up to 1536 pixels on the longest side),
  their UI Automation names and recognized text, your question and the card's
  conversation over HTTPS to the assistant whose key is in use:
  `generativelanguage.googleapis.com` for Gemini, `api.openai.com` for
  ChatGPT or `api.anthropic.com` for Claude. Only that service receives
  them. Follow-up questions include the selections and conversation again.
* **Smart suggestions** is off by default. If you enable it with an API key,
  every selection is uploaded as soon as you make or add it, even if you only
  intend to copy its text or search it with Lens. The suggestion request sends
  the selection images and text, without the card's conversation.
* **Ask in Gemini** (also **Send** without an API key) opens
  `gemini.google.com/app` and puts your question and selection PNG files into
  a new draft. Attaching files can upload them before you send the draft; the
  mod leaves sending the message to you.
* **Search with Google Lens** opens a temporary local HTML page containing
  your selection as a PNG (up to 1000 pixels on the longest side). That page
  immediately uploads the image to `lens.google.com/v3/upload` when it opens.

Under Google's [Gemini API terms](https://ai.google.dev/gemini-api/terms),
free-tier submissions and responses, including images, may be used to improve
Google's products and machine learning, and may be read by human reviewers in
most regions. The terms describe regional exceptions and different treatment
for paid services. Avoid sending sensitive, confidential or personal content
through the free tier.

[OpenAI's data controls](https://developers.openai.com/api/docs/guides/your-data)
say that API data isn't used to train its models by default, and that
abuse-monitoring logs are kept for up to 30 days. Magic Pointer sends ChatGPT
requests with `store` set to `false`, so they are not kept as application
state. Anthropic's
[Commercial Terms](https://www.anthropic.com/legal/commercial-terms) say it
may not train models on customer content from its services. Check each
provider's current terms before you send sensitive content.

Browser handoff PNGs (`gemini-selection-*.png`) and Lens HTML pages are written
temporarily to the mod's Windhawk storage folder, normally under
`%ProgramData%\Windhawk`. This folder is shared across Windows accounts.
PNGs are scheduled for deletion after 30 minutes and Lens pages after 10
minutes; both are also deleted when the mod is disabled. Files left by an
interrupted process are cleaned up on the next start once they expire. A file held open by another program may delay
deletion. **Copy image** and browser handoff also put the selection on the
Windows clipboard; clipboard history follows your Windows settings.

## Look and feel

* The card and the hint sit on Windows' live frosted glass (acrylic) with
  rounded corners, so they follow whatever is behind them, even as it changes.
  Turning off *Transparency effects* in Windows, or *Glass effect* here,
  switches them to solid colors, as does a Windows older than 10 version 1803.
* Pick any **glow color**: `#4285F4`, `66,133,244`, a name like `purple`,
  `accent` for your Windows accent color, or `rainbow` for Google's colors.
* Use your own pointer: set **Custom pointer file** to a `.cur` or `.ani` file,
  animated ones included. It only replaces the pointer while the Magic Pointer
  is on screen, with the same glow, and never changes your normal cursors.
  **Pointer size** scales it. If the file can't be loaded, the default pointer
  is used and Windhawk's log says why.
* **Dim outside the selection** darkens the surrounding screen only while you
  drag a rectangle. The area inside stays clear.


## Languages

The hint, the card, its buttons and its messages are shown in your **Windows
display language**, or in the one you pick with the **Language** setting.
Magic Pointer is translated into Arabic, Bengali, Chinese (Simplified and
Traditional), Croatian, Czech, Danish, Dutch, Finnish, French, German, Greek,
Hebrew, Hindi, Hungarian, Indonesian, Italian, Japanese, Korean, Norwegian,
Persian, Polish, Portuguese (Brazil), Romanian, Russian, Spanish, Swedish,
Tamil, Thai, Turkish, Ukrainian and Vietnamese. Any other language shows
English. Arabic, Hebrew and Persian read from right to left, but the layout of
the card is not mirrored.

This settings page is translated as well, in the languages Windhawk itself
offers, and follows Windhawk's own language. The suggestions that Magic Pointer
makes, including **Smart suggestions**, are written in the Magic Pointer's
language, and the assistant answers in the language your question is written in.
With **Translate to** set to Auto, the Translate button uses the **Language**
setting.

The translations were written with the help of AI, and not every one has been
checked by a native speaker. If a text reads wrong, please
[open an issue](https://github.com/rono-zeroseven/magic-pointer/issues) with the
language and a better wording.

## Games and other apps

Shaking is ignored while a game, video or presentation fills the screen, and
in any app on the *Excluded apps* list (for example `RobloxPlayerBeta.exe`,
`C:\Games\*` or a window title).

## Notes

* Runs as a *tool mod* in its own background process. It doesn't inject into
  other programs and never changes your system cursors.
* Uses Windhawk's standard host without requesting UIAccess. Highlighting
  controls and browser handoff are subject to Windows' restrictions on
  interacting with elevated apps.
* Works on every Windows version Windhawk runs on, on x64, ARM64 and 32-bit
  systems, and supports multiple monitors with per-monitor display scaling.
* The mod never blocks or rewrites your normal mouse input.
* *Highlight what you point at* reads the layout of the app under the pointer
  through UI Automation, the accessibility API. Chromium-based browsers turn
  on their accessibility support when it's used, which costs a little memory.
  Turn it off if you prefer: click and drag always works.

## Report a problem

[Open an issue](https://github.com/rono-zeroseven/magic-pointer/issues) with your
Windows version, Windhawk version, Magic Pointer version, and steps to reproduce
the problem. Include screenshots when useful and remove private content.

## Install

Open Windhawk, click "Create new mod", paste `magic-pointer-plus.wh.cpp`, and hit Compile.
