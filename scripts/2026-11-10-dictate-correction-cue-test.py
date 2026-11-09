"""Seamless Dictate 1.0.6: send sample transcripts through the owner's real
cleanup (Groq, their model and Prompt-style strength) with the 1.0.5 prompt
and the 1.0.6 prompt plus the correction cue. Prints results only, never the key.

Usage: python -I 2026-11-10-dictate-correction-cue-test.py <old.wh.cpp> <new.wh.cpp> <out.json>
"""
import ctypes, ctypes.wintypes as wt, json, re, sys, urllib.error, urllib.request, winreg

STORE = r"SOFTWARE\Windhawk\Engine\ModsWritable\local@seamless-dictate\LocalStorage"


def values():
    k = winreg.OpenKey(winreg.HKEY_LOCAL_MACHINE, STORE)
    out, i = {}, 0
    while True:
        try:
            n, v, _ = winreg.EnumValue(k, i)
        except OSError:
            return out
        out[n.split("_S-")[0]] = v
        i += 1


class Blob(ctypes.Structure):
    _fields_ = [("cbData", wt.DWORD), ("pbData", ctypes.POINTER(ctypes.c_char))]


def unprotect(data, entropy):
    buf = ctypes.create_string_buffer(data, len(data))
    ent = ctypes.create_string_buffer(entropy, len(entropy))
    din, dent, dout = Blob(len(data), buf), Blob(len(entropy), ent), Blob()
    if not ctypes.windll.crypt32.CryptUnprotectData(
        ctypes.byref(din), None, ctypes.byref(dent), None, None, 1, ctypes.byref(dout)
    ):
        raise SystemExit("key not readable")
    key = ctypes.string_at(dout.pbData, dout.cbData).decode()
    ctypes.windll.kernel32.LocalFree(dout.pbData)
    return key


def raw(src, name):
    m = re.search(r'constexpr char ' + name + r'\[\] =\s*R"P\((.*?)\)P";', src, re.S)
    return m.group(1)


def light(src):
    m = re.search(r'if \(strength == "light"\) \{\s*return R"P\((.*?)\)P";', src, re.S)
    return m.group(1)


def system(src, cue):
    p = raw(src, "kBaseRules") + "\n\n" + light(src).strip()
    if cue:
        p += ("\n\nSINAL DE CORREÇÃO: " + json.dumps(cue, ensure_ascii=False) +
              ". Só quando esse sinal marcar claramente uma autocorreção falada, aplique a "
              "correção que a pessoa fez e tire o sinal do resultado. A correção pode trocar, "
              "acrescentar ou desfazer o que foi dito antes. Preserve todo o resto. Se o sinal "
              "fizer parte da frase de propósito, mantenha-o. Decida pelo contexto; não trate "
              "toda ocorrência como correção.")
    return p + "\n\nIDIOMA DE SAÍDA: o mesmo idioma da transcrição (provavelmente inglês). Não traduza."


CASES = [
    "Make it 42 people, oh wait sorry, 24 people for the meeting.",
    "Schedule the test for Friday, sorry, Monday.",
    "Send the file to Mike, oh wait sorry, send it to Sarah instead.",
    "I'm really sorry I missed your call yesterday, can we talk tomorrow?",
    "Use the blue button, not the red one.",
    "Rename the mod to Seamless Dictate Plus, sorry, scratch that, keep the name.",
]


def main():
    old_src = open(sys.argv[1], encoding="utf-8").read()
    new_src = open(sys.argv[2], encoding="utf-8").read()
    v = values()
    cfg = json.loads(v["config"])
    provider = sys.argv[4] if len(sys.argv) > 4 else "gemini"
    key = unprotect(bytes(v["groqKey"] if provider == "groq" else v["key_" + provider]), ("ai-voice-typing/" + provider).encode())
    model = sys.argv[5] if len(sys.argv) > 5 else cfg.get("chatModel")
    url = {"groq": "https://api.groq.com/openai/v1", "gemini": "https://generativelanguage.googleapis.com/v1beta/openai"}[provider] + "/chat/completions"

    def ask(sys_prompt, text):
        body = json.dumps({"model": model, "temperature": 0, "max_tokens": 1024,
                           "messages": [{"role": "system", "content": sys_prompt},
                                        {"role": "user", "content": "<transcricao>\n" + text + "\n</transcricao>"}]}).encode()
        req = urllib.request.Request(url, body,
                                     {"Authorization": "Bearer " + key, "Content-Type": "application/json",
                                      "User-Agent": "Mozilla/5.0 (Windows NT 10.0; Win64; x64)"})
        try:
            with urllib.request.urlopen(req, timeout=60) as r:
                return json.load(r)["choices"][0]["message"]["content"].strip()
        except urllib.error.HTTPError as e:
            raise SystemExit(f"HTTP {e.code}: {e.read()[:300]!r}")

    rows = []
    for text in CASES:
        row = {"said": text,
               "before (1.0.5)": ask(system(old_src, ""), text),
               "after (1.0.6, cue sorry)": ask(system(new_src, "sorry"), text)}
        rows.append(row)
        print(json.dumps(row, ensure_ascii=False))
    json.dump({"provider": provider, "model": model, "strength": cfg.get("promptStrength"), "rows": rows},
              open(sys.argv[3], "w", encoding="utf-8"), ensure_ascii=False, indent=1)


main()
