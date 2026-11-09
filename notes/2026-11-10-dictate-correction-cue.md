# 2026-11-10: Seamless Dictate 1.0.6, correction cue (T3 Code port)

Owner asked for T3 Code's "Correction cue" voice setting inside Seamless Dictate:
saying "oh wait sorry" (or any self-correction) while dictating should fix the text
the way T3 does.

## What T3 does (pingdotgg/t3code, nightly)

- `TranscriptionPostProcessing.ts`: adds a "Correction cue: <cue>" paragraph to the
  cleanup prompt. Apply the correction only when the cue clearly marks a spoken
  self-correction, drop the cue, keep it when it is part of the sentence, decide by context.
- `fillerWords.ts`: filler removal never deletes the cue.
- The cue is also sent to speech-to-text as a vocabulary hint. NOT ported: this mod
  never sends prompts or vocabulary to Whisper (hallucination risk, by design).

## What changed (1.0.5 -> 1.0.6)

- Settings > Styles > Clean-up: new "Correction cue" box under Remove fillers
  (placeholder "e.g. sorry", PT "Sinal de correção"). Empty by default. AI styles only.
- Config key `correctionCue` (max 50 chars) in the LocalStorage config JSON.
- Built-in rule 3 now carries T3's examples: "make it 42, sorry, 24" -> 24,
  "oh wait, I mean Y", "scratch that"; a fix may replace, add or undo; keep real
  contrasts ("42, not 24") and emphasis.
- When a cue is set, the system prompt gets the SINAL DE CORREÇÃO paragraph (T3's text,
  in the prompt's Portuguese).
- Filler removal protects every whole-word match of the cue (swapped for a private-use
  mark before the filler pass, restored after).
- Readme bullet "Self-corrections" in EN/PT/ES.

Patch: `scripts\2026-11-10-dictate-correction-cue-patch.py` (17 exact edits, installed 1.0.5 in).
Workspace source was a stale 1.0.3; it is now the installed 1.0.6.

## Evidence

- Compiled and enabled: library `local@seamless-dictate_1.0.6_883675.dll`, loaded in the
  Dictate host (windhawk-mod.exe, not elevated). Receipt in the backup folder.
- Cleanup test against the owner's real provider (`scripts\2026-11-10-dictate-correction-cue-test.py`,
  results `backups\2026-11-10-dictate-correction-cue\llm-test*.json`). Groq returns 403
  "Access denied. Please check your network settings." from this network, so the owner's
  cleanup really runs on the Gemini fallback (gemini-3.1-flash-lite); tested there.
  - "Make it 42 people, oh wait sorry, 24 people for the meeting." -> "Make it 24 people for the meeting."
  - "Friday, sorry, Monday" -> Monday. "Mike, oh wait sorry, ... Sarah" -> Sarah.
  - Real apology ("I'm really sorry I missed your call") keeps "sorry".
  - "the blue button, not the red one" keeps the contrast. "scratch that, keep the name" -> "Keep the name."
  - Custom cues "backspace" and "rewind" work; "Press rewind on the tape player" unchanged.
- Honest read: Gemini already caught these corrections with the 1.0.5 prompt. The cue and
  the stronger rule are a safety net for weaker models (gpt-oss-20b on Groq) and for
  odd cue words.

## Rollback

Elevated: `scripts\2026-11-10-dictate-correction-cue.ps1 -Rollback` (copies
`backups\2026-11-10-dictate-correction-cue\installed.wh.cpp` back, recompiles, cycles the mod).
Old 1.0.5, new 1.0.6. Registry export of the mod key: `mod.reg` in the same folder.
A saved `correctionCue` value in the config JSON is ignored by 1.0.5.

## Traps

- Groq 403 from this network: test cleanup on Gemini.
- PowerShell `lp` is an alias (Out-Printer): a helper named LP never runs.
- `$null` to a string P/Invoke arg becomes ""; use `[NullString]::Value`.
- Screenshots of the settings window need per-monitor DPI awareness (-4) first, or they
  capture the wrong area on the side monitors.
- After compile, the host can be gone (receipt hosts=0); a second disable+enable brings it back.
- NEVER send EM_GETCUEBANNER (0x1502) to another process's edit box: it is not marshalled,
  so the control writes into a bogus address and the target crashes. It killed the Dictate
  host at 1:40 am (msvcrt.dll access violation); restored by an elevated disable+enable at
  1:41 am (host 34804). WM_GETTEXT / WM_SETTEXT are marshalled and safe. Both capture
  scripts no longer send it.
- Styles in the settings rail is at client (60, 170) DIPs, not (60, 206).

## On-screen check (1:43 am)

`Windhawk\seamless-dictate\cue-1.0.6-before.png`: Styles > Clean-up shows "Correction cue"
under Remove fillers, box reads "sorry". Config JSON has `correctionCue: "sorry"` (same as the
owner's T3 setting).
