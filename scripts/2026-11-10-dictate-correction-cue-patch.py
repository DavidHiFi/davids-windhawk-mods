"""Seamless Dictate 1.0.6: correction cue (ported from T3 Code's voice cleanup).

Usage: python -I 2026-11-10-dictate-correction-cue-patch.py <in.wh.cpp> <out.wh.cpp>
Each edit must match exactly once, or nothing is written.
Source of the feature: pingdotgg/t3code
  apps/server/src/textGeneration/TranscriptionPostProcessing.ts (cue instruction)
  apps/server/src/speech/fillerWords.ts (cue kept out of filler removal)
"""
import sys
from pathlib import Path

src = Path(sys.argv[1]).read_text(encoding="utf-8")
edits = []


def sub(old, new, count=1):
    edits.append((old, new, count))


# --- version -----------------------------------------------------------------
sub("// @version         1.0.5", "// @version         1.0.6")

# --- readme ------------------------------------------------------------------
sub("""  Professional, VS Code always Prompt).
""", """  Professional, VS Code always Prompt).
- **Self-corrections.** Say "make it 42, sorry, 24" and you get "make it 24".
  Set a correction cue (Settings > Styles > Clean-up) with the word or phrase
  you use to fix yourself, like "sorry" or "scratch that", and the AI applies
  the fix only where you meant one.
""")
sub("""  Profissional, VS Code sempre Prompt).
""", """  Profissional, VS Code sempre Prompt).
- **Autocorreções.** Diga "põe 42, desculpa, 24" e sai "põe 24". Em
  Configurações > Estilos > Limpeza, o sinal de correção é a palavra que você
  usa para se corrigir ("desculpa", "na verdade"); a IA só aplica a correção
  onde ela foi pretendida.
""")
sub("""  transcripción y los tuyos), con un estilo por app.
""", """  transcripción y los tuyos), con un estilo por app.
- **Autocorrecciones**: di "ponlo en 42, perdón, 24" y queda "ponlo en 24".
  La señal de corrección (la palabra con la que te corriges) se elige en
  Estilos > Limpieza.
""")

# --- base rule 3: T3's built-in correction wording ---------------------------
sub("""3. Autocorreções e falsos começos: se a pessoa disser algo e depois se corrigir ("faz X... não, na verdade Y"), mantenha só a decisão final (Y).""",
    """3. Autocorreções e falsos começos: se a pessoa disser algo e depois se corrigir ("faz X... não, na verdade Y", "make it 42, sorry, 24", "oh wait, I mean Y", "scratch that"), mantenha só a decisão final (Y) e tire a expressão de correção. A correção pode trocar, acrescentar ou desfazer o que foi dito antes. Mantenha contrastes intencionais ("42, não 24") e repetições usadas para dar ênfase.""")

# --- system prompt: the cue --------------------------------------------------
sub("""                         std::string_view app,
                         std::string_view spoken = "") {
    std::string p = kBaseRules;""",
    """                         std::string_view app,
                         std::string_view spoken = "",
                         std::string_view correctionCue = "") {
    std::string p = kBaseRules;""")
sub("""    AppendAppContext(&p, app);
    if (!target.empty()) {
        p += "\\n\\nIDIOMA DE SAÍDA: escreva o resultado final em " +""",
    """    // The person's correction cue (T3 Code's wording).
    if (const std::wstring cue = Trim(Utf8ToWide(correctionCue)); !cue.empty()) {
        p += "\\n\\nSINAL DE CORREÇÃO: " + JsonQuote(WideToUtf8(cue)) +
             ". Só quando esse sinal marcar claramente uma autocorreção falada, aplique a "
             "correção que a pessoa fez e tire o sinal do resultado. A correção pode trocar, "
             "acrescentar ou desfazer o que foi dito antes. Preserve todo o resto. Se o sinal "
             "fizer parte da frase de propósito, mantenha-o. Decida pelo contexto; não trate "
             "toda ocorrência como correção.";
    }
    AppendAppContext(&p, app);
    if (!target.empty()) {
        p += "\\n\\nIDIOMA DE SAÍDA: escreva o resultado final em " +""")

# --- filler removal keeps the cue (T3's fillerWords.ts) ----------------------
sub("""// Removes fillers conservatively. `language` is the speech language ("pt",
// "en", "auto"...).
std::wstring RemoveFillers(const std::wstring& text, std::wstring_view language) {""",
    """// Removes fillers conservatively. `language` is the speech language ("pt",
// "en", "auto"...). `cue`: the correction cue, never taken out (the AI needs
// it to see the correction).
std::wstring RemoveFillersCore(const std::wstring& text, std::wstring_view language);

std::wstring RemoveFillers(const std::wstring& text, std::wstring_view language,
                           std::wstring_view cue = L"") {
    const std::wstring needle = Lower(Trim(cue));
    if (needle.empty()) {
        return RemoveFillersCore(text, language);
    }
    // Each whole-word cue becomes its own private-use mark while the fillers
    // go, then comes back as it was spoken.
    const std::wstring lower = Lower(text);
    auto edge = [&](size_t at) {
        return at >= lower.size() || !IsCharAlphaNumericW(lower[at]);
    };
    std::vector<std::wstring> found;
    std::wstring masked;
    size_t last = 0;
    for (size_t at = lower.find(needle); at != std::wstring::npos && found.size() < 32;
         at = lower.find(needle, at + 1)) {
        if (at < last || (at && !edge(at - 1)) || !edge(at + needle.size())) {
            continue;
        }
        masked.append(text, last, at - last);
        masked.push_back((wchar_t)(0xE000 + found.size()));
        found.push_back(text.substr(at, needle.size()));
        last = at + needle.size();
    }
    if (found.empty()) {
        return RemoveFillersCore(text, language);
    }
    masked.append(text, last, std::wstring::npos);
    std::wstring out = RemoveFillersCore(masked, language);
    for (size_t i = 0; i < found.size(); i++) {
        const size_t at = out.find((wchar_t)(0xE000 + i));
        if (at != std::wstring::npos) {
            out.replace(at, 1, at == 0 ? CapitalizeFirst(found[i]) : found[i]);
        }
    }
    return out;
}

std::wstring RemoveFillersCore(const std::wstring& text, std::wstring_view language) {""")
sub("""                                     ? RemoveFillers(raw, language)
                                     : raw;""",
    """                                     ? RemoveFillers(raw, language,
                                                     Utf8ToWide(config.correctionCue))
                                     : raw;""")
sub("""                              target, config.dictionary, WideToUtf8(appName), spoken);""",
    """                              target, config.dictionary, WideToUtf8(appName), spoken,
                              config.correctionCue);""")

# --- config ------------------------------------------------------------------
sub("""    bool removeFillers = true;
    bool livePreview = true;""",
    """    bool removeFillers = true;
    // The word or phrase said to flag a self-correction ("sorry", "scratch
    // that"); empty: the AI's general rule only.
    std::string correctionCue;
    bool livePreview = true;""")
sub("""    c->pasteLastHotkey = CleanText(c->pasteLastHotkey, 60);
""", """    c->pasteLastHotkey = CleanText(c->pasteLastHotkey, 60);
    c->correctionCue = CleanText(c->correctionCue, 50);
""")
sub("""                       ",\\"removeFillers\\":" + boolean(c.removeFillers) +
""", """                       ",\\"removeFillers\\":" + boolean(c.removeFillers) +
                       ",\\"correctionCue\\":" + JsonQuote(c.correctionCue) +
""")
sub("""    boolean("removeFillers", &c.removeFillers);
""", """    boolean("removeFillers", &c.removeFillers);
    str("correctionCue", &c.correctionCue);
""")

# --- settings: typed field ---------------------------------------------------
sub("""    return key.starts_with("model-") || key.starts_with("stt-") || key.starts_with("base-") ||
           key == "wizard-name";""",
    """    return key.starts_with("model-") || key.starts_with("stt-") || key.starts_with("base-") ||
           key == "wizard-name" || key == "correction-cue";""")
sub("""            if (key == "wizard-name") {
                c.userName = value;
                continue;
            }""",
    """            if (key == "wizard-name") {
                c.userName = value;
                continue;
            }
            if (key == "correction-cue") {
                c.correctionCue = CleanText(value, 50);
                continue;
            }""")
sub("""           T(L"Takes them out before the AI (fewer tokens) and in the styles without AI.",
             L"Tira as muletas antes de enviar para a IA (economiza tokens) e também nos "
             L"estilos sem IA."),
           fillers, 44);
""", """           T(L"Takes them out before the AI (fewer tokens) and in the styles without AI.",
             L"Tira as muletas antes de enviar para a IA (economiza tokens) e também nos "
             L"estilos sem IA."),
           fillers, 44);
    // The correction cue (T3 Code's): kept as typed, saved a moment after.
    const bool cueFresh = std::none_of(m_edits.begin(), m_edits.end(), [](const EditField& f) {
        return f.key == "correction-cue";
    });
    Widget cue;
    cue.kind = W::Edit;
    cue.edit = "correction-cue";
    cue.text = T(L"e.g. sorry", L"ex.: desculpa");
    AddRow(x, w, y, T(L"Correction cue", L"Sinal de correção"),
           T(L"The word or phrase you say to fix yourself, like \\u201csorry\\u201d or "
             L"\\u201cscratch that\\u201d. The AI applies the fix only where you meant one. "
             L"AI styles only.",
             L"A palavra ou frase que você diz para se corrigir, como \\u201cdesculpa\\u201d "
             L"ou \\u201cna verdade\\u201d. A IA só aplica a correção onde ela foi pretendida. "
             L"Só nos estilos com IA."),
           cue, 160);
    if (cueFresh) {
        SetEditText("correction-cue", Utf8ToWide(c.correctionCue));
    }
""")

for old, new, count in edits:
    n = src.count(old)
    if n != count:
        sys.exit(f"expected {count} match(es), found {n}:\n{old[:200]}")
    src = src.replace(old, new)
Path(sys.argv[2]).write_text(src, encoding="utf-8", newline="")
print(f"ok: {len(edits)} edits")
