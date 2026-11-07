# Merges App Volume Booster (shubho) into local@better-volume-mixer-plus.
# Usage: python 2026-11-07-volmixer-boost-patch.py <path-to-.wh.cpp>
# Each anchor must match exactly once or nothing is written.
import sys

path = sys.argv[1]
src = open(path, 'rb').read().decode('utf-8')
if 'namespace boost {' in src:
    sys.exit('already patched')
src = src.replace('\r\n', '\n')

edits = []
def rep(old, new):
    edits.append((old, new))

# ---------------------------------------------------------------- header
rep('''// @name         Better Volume Mixer Plus
// @description  A compact tray volume mixer with per-app volume and per-app output and input devices
// @version      1.2.1
// @author       DavidHiFi, 0Allu''',
'''// @name         Seamless Volume Mixer
// @description  A compact tray volume mixer with per-app volume up to 1000%, a per-app compressor, and per-app output and input devices
// @version      1.3.0
// @author       DavidHiFi, 0Allu, shubho''')

rep('''# Better Volume Mixer Plus

A compact volume mixer in the system tray, with per-app volume and per-app
audio devices. Better Volume Mixer, plus device routing.

![Better Volume Mixer Plus preview]''',
'''# Seamless Volume Mixer

A compact volume mixer in the system tray, with per-app volume up to 1000%,
a per-app compressor and per-app audio devices.

![Seamless Volume Mixer preview]''')

rep('''- **Master and per-app volume** with mute buttons, scroll-wheel control and
  exact values.''',
'''- **Master and per-app volume** with mute buttons, scroll-wheel control and
  exact values.
- **Boost any app up to 1000%.** The left half of an app slider is the normal
  Windows volume (0 to 100%). The right half, past the tick, boosts the app's
  own audio up to ten times louder.
- **Per-app compressor.** The equalizer button next to an app turns its
  compressor on or off. The arrow button opens threshold, ratio, attack and
  release for that app.''')

rep('''To avoid two volume icons, install''',
'''### Boost and compressor

The first time you boost an app past 100% or turn on its compressor, the mixer
adds the app to this mod's custom process inclusion list (Advanced tab). That
needs admin rights once. Restart the app once afterwards so the mod sees its
new audio streams. Until then the percentage shows in orange and the open
compressor panel says "Restart ... to apply".

Boost does not reach exclusive-mode audio, spatial audio streams, Store apps
that block outside code, or processes Windhawk skips (such as many games).
High boost can clip; the compressor keeps loud parts in check. Boost and
compressor values are saved per app.

To avoid two volume icons, install''')

rep('''Based on [Better Volume Mixer](https://windhawk.net/mods/better-volume-mixer)
by 0Allu. MIT.''',
'''Based on [Better Volume Mixer](https://windhawk.net/mods/better-volume-mixer)
by 0Allu. MIT.

Boost and compressor from
[App Volume Booster](https://windhawk.net/mods/app-volume-booster) by
[shubho](https://github.com/shubho193).''')

rep('''  $description: Percentage points per mouse-wheel step over an app or master-volume row. Valid range is 1 to 20; default is 5.''',
'''  $description: Percentage points per mouse-wheel step over an app or master-volume row. Above 100% each step is ten times larger. Valid range is 1 to 20; default is 5.''')

rep('''  $description: Click a percentage to enter a whole number from 0 to 100. Enter applies it; Escape or clicking elsewhere cancels. Off by default.''',
'''  $description: Click a percentage to enter a whole number, 0 to 1000 for apps or 0 to 100 for master volume. Enter applies it; Escape or clicking elsewhere cancels. Off by default.''')

# ---------------------------------------------------------------- includes
rep('''#include <mmdeviceapi.h>
#include <audiopolicy.h>''',
'''#include <mmdeviceapi.h>
#include <audioclient.h>
#include <mmreg.h>
#include <ksmedia.h>
#include <sddl.h>
#include <audiopolicy.h>''')

rep('''#include <memory>
#include <optional>''',
'''#include <memory>
#include <mutex>
#include <optional>''')

# ---------------------------------------------------------------- boost core (global scope)
BOOST_CORE = r'''
// MinGW's ksmedia.h declares these subformats without defining them.
const CDECL GUID DECLSPEC_SELECTANY KSDATAFORMAT_SUBTYPE_PCM = {
    0x00000001, 0x0000, 0x0010, {0x80, 0x00, 0x00, 0xAA, 0x00, 0x38, 0x9B, 0x71}
};
const CDECL GUID DECLSPEC_SELECTANY KSDATAFORMAT_SUBTYPE_IEEE_FLOAT = {
    0x00000003, 0x0000, 0x0010, {0x80, 0x00, 0x00, 0xAA, 0x00, 0x38, 0x9B, 0x71}
};

// Per-app boost and compressor, merged from App Volume Booster by shubho.
// This DLL runs in two roles. In the mixer tool process it draws the UI and
// owns the settings. Inside each boosted app it hooks WASAPI rendering and
// scales the samples. The mixer publishes live values in a named shared
// table; the app also reads the saved values at start-up.
namespace boost {

constexpr wchar_t kMapName[] = L"Local\\BetterVolumeMixerPlusBoost";
constexpr wchar_t kLiveEventPrefix[] = L"Local\\BVMPBoostLive_";
constexpr wchar_t kStorageName[] = L"boostConfig";
constexpr int kMaxEntries = 128;
constexpr int kExeChars = 64;
constexpr float kMaxGain = 10.0f;

struct Params {
    float gain = 1.0f;
    bool compressor = false;
    float thresholdDb = -25.0f;
    float ratio = 2.0f;
    float attackMs = 10.0f;
    float releaseMs = 150.0f;
};

struct SharedEntry {
    wchar_t exe[kExeChars];
    float gain;
    LONG compressor;
    float thresholdDb;
    float ratio;
    float attackMs;
    float releaseMs;
};

// Single writer (the mixer). The sequence is odd while an entry is written.
struct SharedTable {
    volatile LONG sequence;
    volatile LONG count;
    SharedEntry entries[kMaxEntries];
};

float ClampF(float value, float low, float high) {
    return value < low ? low : (value > high ? high : value);
}

Params Sanitize(Params p) {
    p.gain = ClampF(p.gain, 1.0f, kMaxGain);
    p.thresholdDb = ClampF(p.thresholdDb, -60.0f, 0.0f);
    p.ratio = ClampF(p.ratio, 1.0f, 20.0f);
    p.attackMs = ClampF(p.attackMs, 1.0f, 500.0f);
    p.releaseMs = ClampF(p.releaseMs, 10.0f, 2000.0f);
    return p;
}

bool IsDefault(const Params& p) {
    Params d;
    return p.gain == d.gain && p.compressor == d.compressor &&
           p.thresholdDb == d.thresholdDb && p.ratio == d.ratio &&
           p.attackMs == d.attackMs && p.releaseMs == d.releaseMs;
}

std::wstring LowerText(std::wstring text) {
    for (auto& c : text) c = static_cast<wchar_t>(std::towlower(c));
    return text;
}

std::wstring ExeKeyFromPath(const std::wstring& path) {
    size_t separator = path.find_last_of(L"\\/");
    std::wstring name =
        LowerText(separator == std::wstring::npos ? path : path.substr(separator + 1));
    // Self-updating apps rename their running image (app.exe.12345.old);
    // the process was started, and will start again, as app.exe.
    size_t exe = name.find(L".exe.");
    if (exe != std::wstring::npos) name.resize(exe + 4);
    return name;
}

// The processor never runs in Windhawk itself, the shell, the compositor or
// system audio and security hosts, even if someone adds them by hand.
bool IsBoostableExe(const std::wstring& exe) {
    if (exe.size() <= 4 || exe.size() >= kExeChars ||
        exe.compare(exe.size() - 4, 4, L".exe") != 0 ||
        exe.find_first_of(L"|\"=;,") != std::wstring::npos) {
        return false;
    }
    static const wchar_t* const kBlocked[] = {
        L"windhawk.exe", L"windhawk-mod.exe", L"windhawk-mod-elevated.exe",
        L"windhawk-mod-uiaccess.exe", L"windhawk-ui.exe", L"dwm.exe",
        L"explorer.exe", L"audiodg.exe", L"svchost.exe", L"csrss.exe",
        L"winlogon.exe", L"lsass.exe", L"services.exe", L"smss.exe",
        L"wininit.exe", L"fontdrvhost.exe", L"conhost.exe"};
    for (const wchar_t* blocked : kBlocked) {
        if (exe == blocked) return false;
    }
    return true;
}

// Saved as exe=gain%,compressor,thresholdDb,ratio*10,attackMs,releaseMs;...
// Whole numbers only, so a host app's locale can never change the parse.
void ParseConfig(const std::wstring& text,
                 std::unordered_map<std::wstring, Params>& out) {
    size_t position = 0;
    while (position < text.size()) {
        size_t end = text.find(L';', position);
        if (end == std::wstring::npos) end = text.size();
        std::wstring item = text.substr(position, end - position);
        position = end + 1;
        size_t equals = item.find(L'=');
        if (equals == std::wstring::npos || equals == 0) continue;
        std::wstring exe = LowerText(item.substr(0, equals));
        if (!IsBoostableExe(exe)) continue;
        int gain = 100, compressor = 0, threshold = -25, ratio = 20,
            attack = 10, release = 150;
        if (swscanf(item.c_str() + equals + 1, L"%d,%d,%d,%d,%d,%d", &gain,
                    &compressor, &threshold, &ratio, &attack, &release) < 1) {
            continue;
        }
        Params p;
        p.gain = gain / 100.0f;
        p.compressor = compressor != 0;
        p.thresholdDb = static_cast<float>(threshold);
        p.ratio = ratio / 10.0f;
        p.attackMs = static_cast<float>(attack);
        p.releaseMs = static_cast<float>(release);
        out[exe] = Sanitize(p);
    }
}

std::wstring SerializeConfig(const std::unordered_map<std::wstring, Params>& config) {
    std::wstring text;
    WCHAR item[192];
    for (const auto& [exe, p] : config) {
        if (IsDefault(p)) continue;
        swprintf_s(item, L"%s=%d,%d,%d,%d,%d,%d;", exe.c_str(),
                   static_cast<int>(std::lround(p.gain * 100.0f)),
                   p.compressor ? 1 : 0,
                   static_cast<int>(std::lround(p.thresholdDb)),
                   static_cast<int>(std::lround(p.ratio * 10.0f)),
                   static_cast<int>(std::lround(p.attackMs)),
                   static_cast<int>(std::lround(p.releaseMs)));
        text += item;
    }
    return text;
}

std::wstring ReadStoredConfig() {
    std::vector<WCHAR> buffer(32768, L'\0');
    Wh_GetStringValue(kStorageName, buffer.data(), buffer.size() - 1);
    buffer.back() = L'\0';
    return buffer.data();
}

bool ReadShared(const SharedTable* table, const std::wstring& exe, Params& out) {
    for (int attempt = 0; attempt < 16; ++attempt) {
        LONG before = table->sequence;
        if (before & 1) {
            YieldProcessor();
            continue;
        }
        MemoryBarrier();
        LONG count = table->count;
        if (count < 0) count = 0;
        if (count > kMaxEntries) count = kMaxEntries;
        bool found = false;
        Params p;
        for (LONG i = 0; i < count; ++i) {
            const SharedEntry& entry = table->entries[i];
            if (wcsncmp(entry.exe, exe.c_str(), kExeChars) != 0) continue;
            p.gain = entry.gain;
            p.compressor = entry.compressor != 0;
            p.thresholdDb = entry.thresholdDb;
            p.ratio = entry.ratio;
            p.attackMs = entry.attackMs;
            p.releaseMs = entry.releaseMs;
            found = true;
            break;
        }
        MemoryBarrier();
        if (table->sequence != before) continue;
        if (found) out = Sanitize(p);
        return found;
    }
    return false;
}

// ---- Audio processor (runs inside boosted apps) ----

constexpr UINT32 kMaxChannels = 32;

enum class SampleKind { Unsupported, Float32, Int16, Int24, Int32 };

struct FmtInfo {
    SampleKind kind = SampleKind::Unsupported;
    UINT32 blockAlign = 0;
    UINT32 channels = 0;
    UINT32 sampleRate = 48000;
    UINT32 bytesPerSample = 0;
};

struct RenderInfo {
    FmtInfo fmt;
    BYTE* lastBuffer = nullptr;
    UINT32 lastBufferFrames = 0;
    float env = 0.0f;  // compressor envelope, persists between buffers
    bool loggedFirst = false;
};

std::atomic<bool> g_loggedUnknownClient{false};
std::atomic<float> g_gain{1.0f};
std::atomic<bool> g_compressor{false};
std::atomic<float> g_thresholdDb{-25.0f};
std::atomic<float> g_ratio{2.0f};
std::atomic<float> g_attackMs{10.0f};
std::atomic<float> g_releaseMs{150.0f};

std::mutex g_mutex;
std::unordered_map<void*, FmtInfo> g_clientFormats;                      // IAudioClient*       -> format
std::unordered_map<void*, std::shared_ptr<RenderInfo>> g_renderClients; // IAudioRenderClient* -> state

std::wstring g_exe;
std::mutex g_refreshLock;
std::atomic<ULONGLONG> g_nextRefresh{0};
ULONGLONG g_nextOpen;
std::atomic<const SharedTable*> g_table{nullptr};
HANDLE g_tableMapping;
std::atomic<bool> g_liveSignaled{false};
HANDLE g_liveEvent;

void ApplyParams(const Params& p) {
    g_gain = p.gain;
    g_compressor = p.compressor;
    g_thresholdDb = p.thresholdDb;
    g_ratio = p.ratio;
    g_attackMs = p.attackMs;
    g_releaseMs = p.releaseMs;
}

// Called from the audio thread at most every 100 ms. Opening the table is
// retried every 2 s while the mixer is not running.
void RefreshFromTable() {
    ULONGLONG now = GetTickCount64();
    if (now < g_nextRefresh.load(std::memory_order_relaxed)) return;
    std::unique_lock<std::mutex> lock(g_refreshLock, std::try_to_lock);
    if (!lock.owns_lock()) return;
    g_nextRefresh.store(now + 100, std::memory_order_relaxed);
    const SharedTable* table = g_table.load();
    if (!table && now >= g_nextOpen) {
        g_nextOpen = now + 2000;
        HANDLE mapping = OpenFileMappingW(FILE_MAP_READ, FALSE, kMapName);
        if (mapping) {
            void* view = MapViewOfFile(mapping, FILE_MAP_READ, 0, 0, sizeof(SharedTable));
            if (view) {
                g_tableMapping = mapping;
                table = static_cast<const SharedTable*>(view);
                g_table.store(table);
            } else {
                CloseHandle(mapping);
            }
        }
    }
    Params p;
    if (table && ReadShared(table, g_exe, p)) ApplyParams(p);
}

// Tells the mixer that this process tracks at least one stream, so the
// "restart to apply" hint can go away.
void SignalLive() {
    if (g_liveSignaled.exchange(true)) return;
    WCHAR name[64];
    swprintf_s(name, L"%s%lu", kLiveEventPrefix, GetCurrentProcessId());
    g_liveEvent = CreateEventW(nullptr, TRUE, TRUE, name);
}

inline float Clip(float x) {
    if (x > 1.0f) return 1.0f;
    if (x < -1.0f) return -1.0f;
    return x;
}

inline float LoadSample(const BYTE* p, SampleKind k) {
    switch (k) {
    case SampleKind::Float32:
        return *(const float*)p;
    case SampleKind::Int16:
        return *(const int16_t*)p / 32768.0f;
    case SampleKind::Int24: {
        int32_t v = (int32_t)((p[0] << 8) | (p[1] << 16) | ((uint32_t)p[2] << 24)) >> 8;
        return v / 8388608.0f;
    }
    case SampleKind::Int32:
        return (float)((double)*(const int32_t*)p / 2147483648.0);
    default:
        return 0.0f;
    }
}

inline void StoreSample(BYTE* p, SampleKind k, float x) {
    switch (k) {
    case SampleKind::Float32:
        *(float*)p = x;
        break;
    case SampleKind::Int16:
        *(int16_t*)p = (int16_t)lrintf(x * 32767.0f);
        break;
    case SampleKind::Int24: {
        int32_t o = (int32_t)lrintf(x * 8388607.0f);
        p[0] = (BYTE)(o & 0xFF);
        p[1] = (BYTE)((o >> 8) & 0xFF);
        p[2] = (BYTE)((o >> 16) & 0xFF);
        break;
    }
    case SampleKind::Int32:
        *(int32_t*)p = (int32_t)((double)x * 2147483647.0);
        break;
    default:
        break;
    }
}

// Applies gain (and optionally compression) to one buffer of interleaved samples.
void ProcessBuffer(BYTE* data, UINT32 frames, RenderInfo& ri) {
    const FmtInfo& f = ri.fmt;
    const UINT32 ch = f.channels;
    const UINT32 bps = f.bytesPerSample;
    if (ch == 0 || ch > kMaxChannels || bps == 0 || f.blockAlign < ch * bps) return;

    const bool comp = g_compressor.load();
    const float makeup = g_gain.load();

    const float thresholdDb = g_thresholdDb.load();
    const float slope = 1.0f - 1.0f / g_ratio.load();
    const float sr = (float)f.sampleRate;
    const float atkCoef = expf(-1.0f / (sr * g_attackMs.load() * 0.001f));
    const float relCoef = expf(-1.0f / (sr * g_releaseMs.load() * 0.001f));
    float env = ri.env;

    float s[kMaxChannels];
    BYTE* p = data;

    for (UINT32 n = 0; n < frames; n++, p += f.blockAlign) {
        float level = 0.0f;
        for (UINT32 c = 0; c < ch; c++) {
            s[c] = LoadSample(p + c * bps, f.kind);
            float a = fabsf(s[c]);
            if (a > level) level = a;
        }

        float g = makeup;
        if (comp) {
            // Peak envelope follower, linked across channels
            float coef = level > env ? atkCoef : relCoef;
            env = coef * env + (1.0f - coef) * level;

            if (env > 1e-6f) {
                float over = 20.0f * log10f(env) - thresholdDb;
                if (over > 0.0f) g *= powf(10.0f, -over * slope / 20.0f);
            }
        }

        for (UINT32 c = 0; c < ch; c++) {
            StoreSample(p + c * bps, f.kind, Clip(s[c] * g));
        }
    }

    ri.env = env;
}

FmtInfo ParseFormat(const WAVEFORMATEX* wf) {
    FmtInfo f;
    if (!wf) return f;

    f.blockAlign = wf->nBlockAlign;
    f.channels = wf->nChannels;
    f.sampleRate = wf->nSamplesPerSec ? wf->nSamplesPerSec : 48000;

    bool isPcm = false;
    bool isFloat = false;

    if (wf->wFormatTag == WAVE_FORMAT_EXTENSIBLE && wf->cbSize >= 22) {
        const auto* ext = reinterpret_cast<const WAVEFORMATEXTENSIBLE*>(wf);
        if (IsEqualGUID(ext->SubFormat, KSDATAFORMAT_SUBTYPE_PCM)) {
            isPcm = true;
        } else if (IsEqualGUID(ext->SubFormat, KSDATAFORMAT_SUBTYPE_IEEE_FLOAT)) {
            isFloat = true;
        }
    } else if (wf->wFormatTag == WAVE_FORMAT_IEEE_FLOAT) {
        isFloat = true;
    } else if (wf->wFormatTag == WAVE_FORMAT_PCM) {
        isPcm = true;
    }

    if (isFloat && wf->wBitsPerSample == 32) {
        f.kind = SampleKind::Float32;
        f.bytesPerSample = 4;
    } else if (isPcm) {
        switch (wf->wBitsPerSample) {
        case 16: f.kind = SampleKind::Int16; f.bytesPerSample = 2; break;
        case 24: f.kind = SampleKind::Int24; f.bytesPerSample = 3; break;
        case 32: f.kind = SampleKind::Int32; f.bytesPerSample = 4; break;
        }
    }

    return f;
}

using Release_t = ULONG(STDMETHODCALLTYPE*)(IUnknown*);
using Initialize_t = HRESULT(STDMETHODCALLTYPE*)(IAudioClient*, AUDCLNT_SHAREMODE, DWORD,
                                                 REFERENCE_TIME, REFERENCE_TIME,
                                                 const WAVEFORMATEX*, LPCGUID);
using GetService_t = HRESULT(STDMETHODCALLTYPE*)(IAudioClient*, REFIID, void**);
using GetBuffer_t = HRESULT(STDMETHODCALLTYPE*)(IAudioRenderClient*, UINT32, BYTE**);
using ReleaseBuffer_t = HRESULT(STDMETHODCALLTYPE*)(IAudioRenderClient*, UINT32, DWORD);
// IAudioClient3::InitializeSharedAudioStream (low-latency path, used by many games/engines)
using InitShared_t = HRESULT(STDMETHODCALLTYPE*)(IAudioClient*, DWORD, UINT32, const WAVEFORMATEX*, LPCGUID);

Release_t Orig_ClientRelease;
Release_t Orig_RenderRelease;
Initialize_t Orig_Initialize;
InitShared_t Orig_InitShared;
GetService_t Orig_GetService;
GetBuffer_t Orig_GetBuffer;
ReleaseBuffer_t Orig_ReleaseBuffer;

ULONG STDMETHODCALLTYPE Hook_ClientRelease(IUnknown* self) {
    ULONG ref = Orig_ClientRelease(self);
    if (ref == 0) {
        std::lock_guard<std::mutex> lock(g_mutex);
        g_clientFormats.erase(self);
        g_renderClients.erase(self);
    }
    return ref;
}

ULONG STDMETHODCALLTYPE Hook_RenderRelease(IUnknown* self) {
    ULONG ref = Orig_RenderRelease(self);
    if (ref == 0) {
        std::lock_guard<std::mutex> lock(g_mutex);
        g_clientFormats.erase(self);
        g_renderClients.erase(self);
    }
    return ref;
}

void RememberClientFormat(const wchar_t* via, IAudioClient* self, const WAVEFORMATEX* fmt) {
    if (!fmt) return;
    FmtInfo info = ParseFormat(fmt);
    Wh_Log(L"Boost: %s: tag=%u ch=%u bits=%u rate=%u -> %s", via, (unsigned)fmt->wFormatTag,
           (unsigned)fmt->nChannels, (unsigned)fmt->wBitsPerSample, (unsigned)fmt->nSamplesPerSec,
           info.kind == SampleKind::Unsupported ? L"UNSUPPORTED format" : L"supported");
    std::lock_guard<std::mutex> lock(g_mutex);
    g_clientFormats[self] = info;
}

HRESULT STDMETHODCALLTYPE Hook_Initialize(IAudioClient* self, AUDCLNT_SHAREMODE mode, DWORD flags,
                                          REFERENCE_TIME duration, REFERENCE_TIME period,
                                          const WAVEFORMATEX* fmt, LPCGUID session) {
    HRESULT hr = Orig_Initialize(self, mode, flags, duration, period, fmt, session);
    if (SUCCEEDED(hr)) {
        RememberClientFormat(L"IAudioClient::Initialize", self, fmt);
    } else {
        std::lock_guard<std::mutex> lock(g_mutex);
        g_clientFormats.erase(self);
    }
    return hr;
}

HRESULT STDMETHODCALLTYPE Hook_InitShared(IAudioClient* self, DWORD flags, UINT32 periodFrames,
                                          const WAVEFORMATEX* fmt, LPCGUID session) {
    HRESULT hr = Orig_InitShared(self, flags, periodFrames, fmt, session);
    if (SUCCEEDED(hr)) {
        RememberClientFormat(L"IAudioClient3::InitializeSharedAudioStream", self, fmt);
    } else {
        std::lock_guard<std::mutex> lock(g_mutex);
        g_clientFormats.erase(self);
    }
    return hr;
}

HRESULT STDMETHODCALLTYPE Hook_GetService(IAudioClient* self, REFIID riid, void** ppv) {
    HRESULT hr = Orig_GetService(self, riid, ppv);
    if (SUCCEEDED(hr) && ppv && *ppv && IsEqualIID(riid, __uuidof(IAudioRenderClient))) {
        bool attached = false;
        {
            std::lock_guard<std::mutex> lock(g_mutex);
            auto it = g_clientFormats.find(self);
            if (it != g_clientFormats.end()) {
                auto ri = std::make_shared<RenderInfo>();
                ri->fmt = it->second;
                g_renderClients[*ppv] = ri;
                attached = true;
            } else {
                g_renderClients.erase(*ppv);
            }
        }
        if (attached) {
            Wh_Log(L"Boost: render client attached");
            SignalLive();
        } else {
            Wh_Log(L"Boost: render client format unknown (stream was created before the mod loaded)");
        }
    }
    return hr;
}

HRESULT STDMETHODCALLTYPE Hook_GetBuffer(IAudioRenderClient* self, UINT32 frames, BYTE** ppData) {
    HRESULT hr = Orig_GetBuffer(self, frames, ppData);
    if (SUCCEEDED(hr) && ppData) {
        std::lock_guard<std::mutex> lock(g_mutex);
        auto it = g_renderClients.find(self);
        if (it != g_renderClients.end()) {
            it->second->lastBuffer = *ppData;
            it->second->lastBufferFrames = frames;
        }
    }
    return hr;
}

HRESULT STDMETHODCALLTYPE Hook_ReleaseBuffer(IAudioRenderClient* self, UINT32 framesWritten, DWORD flags) {
    RefreshFromTable();
    bool active = g_compressor.load() || g_gain.load() != 1.0f;
    if (active && framesWritten > 0 && !(flags & AUDCLNT_BUFFERFLAGS_SILENT)) {
        std::shared_ptr<RenderInfo> ri;
        {
            std::lock_guard<std::mutex> lock(g_mutex);
            auto it = g_renderClients.find(self);
            if (it != g_renderClients.end()) ri = it->second;
        }
        if (!ri) {
            if (!g_loggedUnknownClient.exchange(true)) {
                Wh_Log(L"Boost: audio goes through a render client created before the mod loaded; restart the app");
            }
        } else if (ri->lastBuffer && ri->fmt.kind != SampleKind::Unsupported) {
            BYTE* buf = ri->lastBuffer;
            UINT32 maxFrames = ri->lastBufferFrames;
            ri->lastBuffer = nullptr;
            ri->lastBufferFrames = 0;
            UINT32 framesToProcess = framesWritten < maxFrames ? framesWritten : maxFrames;
            if (framesToProcess > 0) {
                if (!ri->loggedFirst) {
                    ri->loggedFirst = true;
                    Wh_Log(L"Boost: processing audio, gain %.2fx, compressor %d",
                           g_gain.load(), (int)g_compressor.load());
                }
                ProcessBuffer(buf, framesToProcess, *ri);
            }
        }
    }
    return Orig_ReleaseBuffer(self, framesWritten, flags);
}

// Locates the COM method addresses by creating a throwaway audio client.
bool InstallHooks() {
    HRESULT hrInit = CoInitializeEx(nullptr, COINIT_MULTITHREADED);
    bool needUninit = SUCCEEDED(hrInit);

    IMMDeviceEnumerator* en = nullptr;
    IMMDevice* dev = nullptr;
    IAudioClient* ac = nullptr;
    IAudioRenderClient* rc = nullptr;
    WAVEFORMATEX* mix = nullptr;
    bool ok = false;

    do {
        if (FAILED(CoCreateInstance(__uuidof(MMDeviceEnumerator), nullptr, CLSCTX_ALL,
                                    __uuidof(IMMDeviceEnumerator), (void**)&en))) break;
        if (FAILED(en->GetDefaultAudioEndpoint(eRender, eConsole, &dev))) break;
        if (FAILED(dev->Activate(__uuidof(IAudioClient), CLSCTX_ALL, nullptr, (void**)&ac))) break;
        if (FAILED(ac->GetMixFormat(&mix))) break;
        if (FAILED(ac->Initialize(AUDCLNT_SHAREMODE_SHARED, 0, 10000000, 0, mix, nullptr))) break;
        if (FAILED(ac->GetService(__uuidof(IAudioRenderClient), (void**)&rc))) break;

        void** acVtbl = *(void***)ac;
        void** rcVtbl = *(void***)rc;

        // IAudioClient:       2 = Release, 3 = Initialize, 14 = GetService
        // IAudioRenderClient: 2 = Release, 3 = GetBuffer,   4 = ReleaseBuffer
        ok = WindhawkUtils::SetFunctionHook((Release_t)acVtbl[2], Hook_ClientRelease, &Orig_ClientRelease) &&
             WindhawkUtils::SetFunctionHook((Initialize_t)acVtbl[3], Hook_Initialize, &Orig_Initialize) &&
             WindhawkUtils::SetFunctionHook((GetService_t)acVtbl[14], Hook_GetService, &Orig_GetService) &&
             WindhawkUtils::SetFunctionHook((GetBuffer_t)rcVtbl[3], Hook_GetBuffer, &Orig_GetBuffer) &&
             WindhawkUtils::SetFunctionHook((ReleaseBuffer_t)rcVtbl[4], Hook_ReleaseBuffer, &Orig_ReleaseBuffer);
        if (!ok) break;

        if (rcVtbl[2] != acVtbl[2]) {
            if (!WindhawkUtils::SetFunctionHook((Release_t)rcVtbl[2], Hook_RenderRelease, &Orig_RenderRelease)) {
                Wh_Log(L"Boost: could not hook IAudioRenderClient::Release");
            }
        }

        // IAudioClient3: 20 = InitializeSharedAudioStream. Streams created
        // through it never call IAudioClient::Initialize.
        void* ac3 = nullptr;
        if (SUCCEEDED(ac->QueryInterface(__uuidof(IAudioClient3), &ac3)) && ac3) {
            void** ac3Vtbl = *(void***)ac3;
            if (!WindhawkUtils::SetFunctionHook((InitShared_t)ac3Vtbl[20], Hook_InitShared, &Orig_InitShared)) {
                Wh_Log(L"Boost: could not hook InitializeSharedAudioStream");
            }
            ((IUnknown*)ac3)->Release();
        }
    } while (false);

    if (mix) CoTaskMemFree(mix);
    if (rc) rc->Release();
    if (ac) ac->Release();
    if (dev) dev->Release();
    if (en) en->Release();
    if (needUninit) CoUninitialize();

    return ok;
}

bool ProcessorInit(const std::wstring& exe) {
    if (!IsBoostableExe(exe)) return false;
    g_exe = exe;
    std::unordered_map<std::wstring, Params> config;
    ParseConfig(ReadStoredConfig(), config);
    auto saved = config.find(exe);
    if (saved != config.end()) ApplyParams(saved->second);
    RefreshFromTable();
    if (!InstallHooks()) {
        Wh_Log(L"Boost: could not hook WASAPI in %s (no output device?)", exe.c_str());
        return false;
    }
    Wh_Log(L"Boost: active in %s, gain %.2fx, compressor %d", exe.c_str(),
           g_gain.load(), (int)g_compressor.load());
    return true;
}

void ProcessorUninit() {
    // The table view stays mapped: an audio thread may still be reading it.
    if (g_liveEvent) {
        CloseHandle(g_liveEvent);
        g_liveEvent = nullptr;
    }
}

}  // namespace boost

namespace {
'''
rep('''#endif
#endif

namespace {
''', '''#endif
#endif
''' + BOOST_CORE)

rep('''constexpr UINT_PTR TIMER_DEVICE_REFRESH = 5;''',
'''constexpr UINT_PTR TIMER_DEVICE_REFRESH = 5;
constexpr UINT_PTR TIMER_BOOST_SAVE = 6;''')

# ---------------------------------------------------------------- AppSession
rep('''    std::wstring pinKey;
    bool pinned = false;
    bool active = false;
    float volume = 1.0f;''',
'''    std::wstring pinKey;
    std::wstring exeKey;  // lowercase file name, keys boost settings
    bool boostable = false;
    bool pinned = false;
    bool active = false;
    float volume = 1.0f;''')

rep('''            pinKey = std::move(other.pinKey);
            pinned = other.pinned;''',
'''            pinKey = std::move(other.pinKey);
            exeKey = std::move(other.exeKey);
            boostable = other.boostable;
            pinned = other.pinned;''')

rep('''    float selection = 0.0f, muteHover = 0.0f, pinHover = 0.0f, percentHover = 0.0f;''',
'''    float selection = 0.0f, muteHover = 0.0f, pinHover = 0.0f, percentHover = 0.0f;
    float compHover = 0.0f, chevronHover = 0.0f, paramHover[4] = {};''')

rep('''int g_dragRow = DRAG_NONE;
bool g_mouseTracking;''',
'''int g_dragRow = DRAG_NONE;
int g_dragParam = -1;  // compressor slider being dragged in g_dragRow, or -1
std::wstring g_expandedKey;  // app whose compressor panel is open
bool g_mouseTracking;''')

rep('''            app.executablePath = std::move(processPath);
            app.pinKey = std::move(pinKey);''',
'''            app.executablePath = std::move(processPath);
            if (!systemSounds) {
                app.exeKey = boost::ExeKeyFromPath(app.executablePath);
                app.boostable = boost::IsBoostableExe(app.exeKey);
            }
            app.pinKey = std::move(pinKey);''')

# ---------------------------------------------------------------- mixer-side boost logic
TOOL_BOOST = r'''
// ---- Boost settings on the mixer side ----

std::unordered_map<std::wstring, boost::Params> g_boostConfig;
HANDLE g_boostMapping;
boost::SharedTable* g_boostTable;
bool g_boostSaveDirty;
std::mutex g_includeLock;
std::unordered_set<std::wstring> g_includeRequested;
std::unordered_map<DWORD, std::pair<bool, ULONGLONG>> g_liveCache;

const boost::Params& BoostFor(const std::wstring& exe) {
    static const boost::Params kDefault;
    auto it = g_boostConfig.find(exe);
    return it == g_boostConfig.end() ? kDefault : it->second;
}

void PublishBoost(const std::wstring& exe, const boost::Params& p) {
    boost::SharedTable* table = g_boostTable;
    if (!table || exe.size() >= boost::kExeChars) return;
    LONG count = table->count;
    if (count < 0 || count > boost::kMaxEntries) count = 0;
    int index = -1;
    for (LONG i = 0; i < count; ++i) {
        if (wcsncmp(table->entries[i].exe, exe.c_str(), boost::kExeChars) == 0) {
            index = i;
            break;
        }
    }
    if (index < 0) {
        if (count >= boost::kMaxEntries) {
            Wh_Log(L"Boost: shared table full, %s not published", exe.c_str());
            return;
        }
        index = count;
    }
    InterlockedIncrement(&table->sequence);
    boost::SharedEntry& entry = table->entries[index];
    memcpy(entry.exe, exe.c_str(), exe.size() * sizeof(wchar_t));
    entry.exe[exe.size()] = L'\0';
    entry.gain = p.gain;
    entry.compressor = p.compressor ? 1 : 0;
    entry.thresholdDb = p.thresholdDb;
    entry.ratio = p.ratio;
    entry.attackMs = p.attackMs;
    entry.releaseMs = p.releaseMs;
    if (index == count) table->count = count + 1;
    InterlockedIncrement(&table->sequence);
}

void OpenBoostTable() {
    // Owner full access; everyone else, AppContainers and low integrity read only.
    PSECURITY_DESCRIPTOR descriptor = nullptr;
    SECURITY_ATTRIBUTES attributes{sizeof(attributes), nullptr, FALSE};
    if (ConvertStringSecurityDescriptorToSecurityDescriptorW(
            L"D:(A;;GA;;;SY)(A;;GA;;;OW)(A;;GR;;;WD)(A;;GR;;;AC)S:(ML;;NW;;;LW)",
            SDDL_REVISION_1, &descriptor, nullptr)) {
        attributes.lpSecurityDescriptor = descriptor;
    }
    g_boostMapping = CreateFileMappingW(INVALID_HANDLE_VALUE, &attributes,
                                        PAGE_READWRITE, 0,
                                        sizeof(boost::SharedTable), boost::kMapName);
    DWORD error = GetLastError();
    if (descriptor) LocalFree(descriptor);
    if (!g_boostMapping) {
        Wh_Log(L"Boost: CreateFileMapping failed, error %lu", error);
        return;
    }
    g_boostTable = static_cast<boost::SharedTable*>(MapViewOfFile(
        g_boostMapping, FILE_MAP_ALL_ACCESS, 0, 0, sizeof(boost::SharedTable)));
    if (!g_boostTable) {
        Wh_Log(L"Boost: MapViewOfFile failed, error %lu", GetLastError());
        CloseHandle(g_boostMapping);
        g_boostMapping = nullptr;
    }
}

DWORD WINAPI BoostIncludeWorker(void* parameter) {
    std::unique_ptr<std::wstring> exe(static_cast<std::wstring*>(parameter));
    std::lock_guard<std::mutex> lock(g_includeLock);
    const wchar_t* keyPath = L"SOFTWARE\\Windhawk\\Engine\\Mods\\" WH_MOD_ID;
    HKEY key;
    if (RegOpenKeyExW(HKEY_LOCAL_MACHINE, keyPath, 0, KEY_READ, &key) != ERROR_SUCCESS) {
        Wh_Log(L"Boost: mod registry key not found, add %s to the custom process list by hand",
               exe->c_str());
        return 0;
    }
    WCHAR current[4096] = L"";
    DWORD size = sizeof(current) - sizeof(WCHAR);
    if (RegGetValueW(key, nullptr, L"IncludeCustom", RRF_RT_REG_SZ, nullptr,
                     current, &size) != ERROR_SUCCESS) {
        current[0] = L'\0';
    }
    RegCloseKey(key);

    std::wstring list = current;
    size_t start = 0;
    while (start <= list.size()) {
        size_t end = list.find(L'|', start);
        if (end == std::wstring::npos) end = list.size();
        std::wstring item = list.substr(start, end - start);
        size_t first = item.find_first_not_of(L" \t");
        size_t last = item.find_last_not_of(L" \t");
        if (first != std::wstring::npos &&
            boost::LowerText(item.substr(first, last - first + 1)) == *exe) {
            return 0;
        }
        start = end + 1;
    }
    while (!list.empty() && (list.back() == L'|' || list.back() == L' ')) list.pop_back();
    std::wstring updated = list.empty() ? *exe : list + L"|" + *exe;
    if (updated.size() > 4000) {
        Wh_Log(L"Boost: custom process list is too long to add %s", exe->c_str());
        return 0;
    }

    WCHAR regPath[MAX_PATH];
    UINT length = GetSystemDirectoryW(regPath, MAX_PATH - 10);
    if (!length || length >= MAX_PATH - 10) return 0;
    wcscat_s(regPath, L"\\reg.exe");
    std::wstring arguments = std::wstring(L"add \"HKLM\\") + keyPath +
        L"\" /v IncludeCustom /t REG_SZ /d \"" + updated + L"\" /f";

    HRESULT com = CoInitializeEx(nullptr, COINIT_APARTMENTTHREADED | COINIT_DISABLE_OLE1DDE);
    SHELLEXECUTEINFOW info{};
    info.cbSize = sizeof(info);
    info.fMask = SEE_MASK_NOCLOSEPROCESS | SEE_MASK_FLAG_NO_UI | SEE_MASK_NOASYNC;
    info.lpVerb = L"runas";
    info.lpFile = regPath;
    info.lpParameters = arguments.c_str();
    info.nShow = SW_HIDE;
    if (!ShellExecuteExW(&info)) {
        Wh_Log(L"Boost: could not add %s to the custom process list, error %lu",
               exe->c_str(), GetLastError());
    } else if (info.hProcess) {
        WaitForSingleObject(info.hProcess, 30000);
        DWORD exitCode = 1;
        GetExitCodeProcess(info.hProcess, &exitCode);
        CloseHandle(info.hProcess);
        Wh_Log(L"Boost: added %s to the custom process list, reg exit %lu",
               exe->c_str(), exitCode);
    }
    if (SUCCEEDED(com)) CoUninitialize();
    return 0;
}

// The processor only loads into apps on this mod's custom process list.
// Apps are added once, the first time they need boost or the compressor;
// nothing is ever removed.
void EnsureBoostInclude(const std::wstring& exe) {
    if (!boost::IsBoostableExe(exe) || !g_includeRequested.insert(exe).second) return;
    auto* parameter = new std::wstring(exe);
    HANDLE thread = CreateThread(nullptr, 0, BoostIncludeWorker, parameter, 0, nullptr);
    if (thread) {
        CloseHandle(thread);
    } else {
        delete parameter;
        g_includeRequested.erase(exe);
    }
}

void SaveBoostConfig() {
    g_boostSaveDirty = false;
    if (!Wh_SetStringValue(boost::kStorageName,
                           boost::SerializeConfig(g_boostConfig).c_str())) {
        Wh_Log(L"Boost: saving settings failed");
    }
}

void ScheduleBoostSave() {
    g_boostSaveDirty = true;
    HWND window = g_hWnd.load();
    if (!window || !SetTimer(window, TIMER_BOOST_SAVE, 1000, nullptr)) SaveBoostConfig();
}

void LoadBoostConfig() {
    g_boostConfig.clear();
    boost::ParseConfig(boost::ReadStoredConfig(), g_boostConfig);
    for (const auto& [exe, p] : g_boostConfig) {
        PublishBoost(exe, p);
        if (p.gain > 1.001f || p.compressor) EnsureBoostInclude(exe);
    }
    Wh_Log(L"Boost: loaded settings for %zu apps", g_boostConfig.size());
}

void UpdateBoost(const std::wstring& exe, const boost::Params& p) {
    if (!boost::IsBoostableExe(exe)) return;
    boost::Params clean = boost::Sanitize(p);
    g_boostConfig[exe] = clean;
    PublishBoost(exe, clean);
    ScheduleBoostSave();
    if (clean.gain > 1.001f || clean.compressor) EnsureBoostInclude(exe);
}

bool BoostIsLive(DWORD processId) {
    ULONGLONG now = GetTickCount64();
    if (g_liveCache.size() > 256) g_liveCache.clear();
    auto& slot = g_liveCache[processId];
    if (slot.second && now - slot.second < 1000) return slot.first;
    WCHAR name[64];
    swprintf_s(name, L"%s%lu", boost::kLiveEventPrefix, processId);
    HANDLE event = OpenEventW(SYNCHRONIZE, FALSE, name);
    if (event) CloseHandle(event);
    slot = {event != nullptr, now};
    return slot.first;
}

// Boost or compressor is set, but the app has no tracked stream yet.
bool BoostPending(const AppSession& app) {
    if (!app.boostable || !app.processId) return false;
    const boost::Params& p = BoostFor(app.exeKey);
    return (p.gain > 1.001f || p.compressor) && !BoostIsLive(app.processId);
}

// An app's level runs 0..10: up to 1 it is the Windows session volume, above
// 1 the session stays at 100% and the processor gain makes up the rest.
float AppMaxLevel(const AppSession& app) {
    return app.boostable ? boost::kMaxGain : 1.0f;
}

float AppLevel(const AppSession& app) {
    return app.volume * (app.boostable ? BoostFor(app.exeKey).gain : 1.0f);
}

bool IsAppRow(int row) {
    return row >= 0 && row < static_cast<int>(g_apps->size());
}

float RowMaxLevel(int row) {
    return IsAppRow(row) ? AppMaxLevel((*g_apps)[row]) : 1.0f;
}

float RowLevel(int row) {
    if (row == DRAG_MASTER) return GetMasterVolume();
    return IsAppRow(row) ? AppLevel((*g_apps)[row]) : 0.0f;
}

void SetRowLevel(int row, float level) {
    if (!IsAppRow(row) || !(*g_apps)[row].boostable) {
        SetRowVolume(row, level);
        return;
    }
    AppSession& app = (*g_apps)[row];
    level = boost::ClampF(level, 0.0f, AppMaxLevel(app));
    level = std::round(level * 100.0f) / 100.0f;
    SetRowVolume(row, std::min(level, 1.0f));
    boost::Params p = BoostFor(app.exeKey);
    float gain = std::max(level, 1.0f);
    if (std::fabs(p.gain - gain) > 0.0005f) {
        p.gain = gain;
        UpdateBoost(app.exeKey, p);
    }
}

// Below 100% a step is the wheel step; above it, ten times that. Steps
// always stop at 100% on the way through.
float StepLevel(int row, float level, int direction) {
    float step = g_settings.volumeStep / 100.0f;
    if (RowMaxLevel(row) <= 1.0f) return level + direction * step;
    if (direction > 0) {
        return level < 0.9995f ? std::min(1.0f, level + step) : level + step * 10.0f;
    }
    return level > 1.0005f ? std::max(1.0f, level - step * 10.0f) : level - step;
}

void ToggleCompressor(int row) {
    if (!IsAppRow(row) || !(*g_apps)[row].boostable) return;
    const std::wstring& exe = (*g_apps)[row].exeKey;
    boost::Params p = BoostFor(exe);
    p.compressor = !p.compressor;
    UpdateBoost(exe, p);
}

// Compressor panel sliders: 0 threshold, 1 ratio, 2 attack, 3 release.
struct ParamRange {
    float minimum;
    float maximum;
    bool logarithmic;
};
constexpr ParamRange kParamRanges[4] = {
    {-60.0f, 0.0f, false}, {1.0f, 20.0f, false},
    {1.0f, 500.0f, true}, {10.0f, 2000.0f, true}};
constexpr const wchar_t* kParamNames[4] = {L"Threshold", L"Ratio", L"Attack", L"Release"};

float ParamValue(const boost::Params& p, int index) {
    switch (index) {
        case 0: return p.thresholdDb;
        case 1: return p.ratio;
        case 2: return p.attackMs;
        default: return p.releaseMs;
    }
}

void SetParamValue(boost::Params& p, int index, float value) {
    const ParamRange& range = kParamRanges[index];
    value = boost::ClampF(index == 1 ? std::round(value * 2.0f) / 2.0f : std::round(value),
                          range.minimum, range.maximum);
    switch (index) {
        case 0: p.thresholdDb = value; break;
        case 1: p.ratio = value; break;
        case 2: p.attackMs = value; break;
        default: p.releaseMs = value; break;
    }
}

float ParamToFraction(int index, float value) {
    const ParamRange& range = kParamRanges[index];
    float fraction = range.logarithmic
        ? std::log(value / range.minimum) / std::log(range.maximum / range.minimum)
        : (value - range.minimum) / (range.maximum - range.minimum);
    return boost::ClampF(fraction, 0.0f, 1.0f);
}

float FractionToParam(int index, float fraction) {
    const ParamRange& range = kParamRanges[index];
    fraction = boost::ClampF(fraction, 0.0f, 1.0f);
    return range.logarithmic
        ? range.minimum * std::pow(range.maximum / range.minimum, fraction)
        : range.minimum + fraction * (range.maximum - range.minimum);
}

float StepParam(int index, float value, int direction) {
    if (!kParamRanges[index].logarithmic) {
        return value + direction * (index == 1 ? 0.5f : 1.0f);
    }
    float next = std::round(value * (direction > 0 ? 1.12f : 1.0f / 1.12f));
    if (next == value) next = value + direction;
    return next;
}

std::wstring ParamText(const boost::Params& p, int index) {
    WCHAR text[32];
    float value = ParamValue(p, index);
    if (index == 0) {
        swprintf_s(text, L"%d dB", static_cast<int>(std::lround(value)));
    } else if (index == 1) {
        int tenths = static_cast<int>(std::lround(value * 10.0f));
        swprintf_s(text, L"%d.%d:1", tenths / 10, tenths % 10);
    } else {
        swprintf_s(text, L"%d ms", static_cast<int>(std::lround(value)));
    }
    return text;
}

// Slider positions: the left half is 0..100%, the right half 100..1000%.
float LevelToTrack(float level, float maxLevel) {
    if (maxLevel <= 1.0f) return ClampVolume(level);
    if (level <= 1.0f) return ClampVolume(level) * 0.5f;
    return 0.5f + boost::ClampF((level - 1.0f) / (maxLevel - 1.0f), 0.0f, 1.0f) * 0.5f;
}

float TrackToLevel(float track, float maxLevel) {
    track = ClampVolume(track);
    if (maxLevel <= 1.0f) return track;
    return track <= 0.5f ? track * 2.0f : 1.0f + (track - 0.5f) * 2.0f * (maxLevel - 1.0f);
}

bool IsCompact() {'''
rep('''
bool IsCompact() {''', TOOL_BOOST)

# ---------------------------------------------------------------- layout
rep('''int RowTop(int visibleRow) {
    return HeaderHeight() + visibleRow * RowHeight() +
           (visibleRow > 0 ? SectionGap() : 0);
}''',
'''int VisibleAppCount();

int PanelHeight() {
    return Scale(IsCompact() ? 86 : 104);
}

std::wstring ExpandKeyFor(const AppSession& app) {
    return std::to_wstring(app.processId) + L":" + app.exeKey;
}

bool RowHasBoostUi(int row) {
    return IsAppRow(row) && (*g_apps)[row].boostable;
}

bool IsRowExpanded(int row) {
    return RowHasBoostUi(row) && !g_expandedKey.empty() &&
           ExpandKeyFor((*g_apps)[row]) == g_expandedKey;
}

int DataRowForVisibleRow(int visibleRow) {
    return visibleRow == 0 ? DRAG_MASTER : g_scrollRow + visibleRow - 1;
}

bool IsVisibleRowExpanded(int visibleRow) {
    return visibleRow >= 1 && visibleRow <= VisibleAppCount() &&
           IsRowExpanded(g_scrollRow + visibleRow - 1);
}

int RowTop(int visibleRow) {
    int top = HeaderHeight() + visibleRow * RowHeight() +
              (visibleRow > 0 ? SectionGap() : 0);
    for (int i = 1; i < visibleRow; ++i) {
        if (IsVisibleRowExpanded(i)) top += PanelHeight();
    }
    return top;
}''')

rep('''    int fixedHeight = HeaderHeight() + RowHeight() + SectionGap() +
                      FooterHeight(true);''',
'''    // Room for one open compressor panel is always kept, so opening it
    // never changes the page size.
    int fixedHeight = HeaderHeight() + RowHeight() + SectionGap() +
                      FooterHeight(true) + PanelHeight();''')

rep('''    return HeaderHeight() + RowHeight() * (1 + slots) + SectionGap() +
           FooterHeight(PageCount() > 1);
}''',
'''    int panels = 0;
    for (int i = 1; i <= VisibleAppCount(); ++i) {
        if (IsVisibleRowExpanded(i)) ++panels;
    }
    return HeaderHeight() + RowHeight() * (1 + slots) + SectionGap() +
           PanelHeight() * panels + FooterHeight(PageCount() > 1);
}''')

rep('''RECT NameRectForRow(int visibleRow, int clientWidth) {
    int top = RowTop(visibleRow);
    if (IsCompact()) {
        return {Scale(62), top + Scale(3), clientWidth - Scale(132),
                top + Scale(27)};
    }
    return {Scale(68), top + Scale(9), clientWidth - Scale(132),
            top + Scale(33)};
}

RECT PercentRectForRow(int visibleRow, int clientWidth) {
    int top = RowTop(visibleRow);
    if (IsCompact()) {
        if (visibleRow == 0) {
            return {clientWidth - Scale(100), top + Scale(3),
                    clientWidth - Scale(50), top + Scale(27)};
        }
        return {clientWidth - Scale(124), top + Scale(3),
                clientWidth - Scale(76), top + Scale(27)};
    }
    return {clientWidth - Scale(124), top + Scale(9),
            clientWidth - Scale(78), top + Scale(33)};
}''',
'''RECT NameRectForRow(int visibleRow, int clientWidth) {
    int top = RowTop(visibleRow);
    bool boostUi = RowHasBoostUi(DataRowForVisibleRow(visibleRow));
    if (IsCompact()) {
        return {Scale(62), top + Scale(3), clientWidth - Scale(boostUi ? 186 : 132),
                top + Scale(27)};
    }
    return {Scale(68), top + Scale(9), clientWidth - Scale(boostUi ? 188 : 132),
            top + Scale(33)};
}

RECT PercentRectForRow(int visibleRow, int clientWidth) {
    int top = RowTop(visibleRow);
    int left = RowHasBoostUi(DataRowForVisibleRow(visibleRow)) ? 130 : 124;
    if (IsCompact()) {
        if (visibleRow == 0) {
            return {clientWidth - Scale(100), top + Scale(3),
                    clientWidth - Scale(50), top + Scale(27)};
        }
        return {clientWidth - Scale(left), top + Scale(3),
                clientWidth - Scale(76), top + Scale(27)};
    }
    return {clientWidth - Scale(left), top + Scale(9),
            clientWidth - Scale(78), top + Scale(33)};
}

RECT CompressorRectForRow(int visibleRow, int clientWidth) {
    int top = RowTop(visibleRow);
    if (IsCompact()) {
        return {clientWidth - Scale(182), top + Scale(3),
                clientWidth - Scale(158), top + Scale(27)};
    }
    return {clientWidth - Scale(184), top + Scale(9),
            clientWidth - Scale(160), top + Scale(33)};
}

RECT ChevronRectForRow(int visibleRow, int clientWidth) {
    int top = RowTop(visibleRow);
    int inset = IsCompact() ? 3 : 9;
    return {clientWidth - Scale(156), top + Scale(inset),
            clientWidth - Scale(132), top + Scale(inset + 24)};
}

RECT PanelRectForRow(int visibleRow, int clientWidth) {
    int top = RowTop(visibleRow);
    return {Scale(IsCompact() ? 62 : 68), top + RowHeight() - Scale(4),
            clientWidth - Scale(28), top + RowHeight() + PanelHeight() - Scale(10)};
}

RECT PanelStatusRect(int visibleRow, int clientWidth) {
    RECT panel = PanelRectForRow(visibleRow, clientWidth);
    return {panel.left, panel.top, panel.right,
            panel.top + Scale(IsCompact() ? 19 : 22)};
}

RECT ParamCellRect(int visibleRow, int clientWidth, int index) {
    RECT panel = PanelRectForRow(visibleRow, clientWidth);
    int gridTop = PanelStatusRect(visibleRow, clientWidth).bottom;
    int gap = Scale(20);
    int columnWidth = (panel.right - panel.left - gap) / 2;
    int rowHeight = (panel.bottom - gridTop) / 2;
    int left = panel.left + (index % 2) * (columnWidth + gap);
    int top = gridTop + (index / 2) * rowHeight;
    return {left, top, left + columnWidth, top + rowHeight};
}

RECT ParamLabelRect(int visibleRow, int clientWidth, int index) {
    RECT cell = ParamCellRect(visibleRow, clientWidth, index);
    return {cell.left, cell.top, cell.right, cell.top + Scale(IsCompact() ? 14 : 16)};
}

RECT ParamSliderRect(int visibleRow, int clientWidth, int index) {
    RECT cell = ParamCellRect(visibleRow, clientWidth, index);
    int center = cell.top + Scale(IsCompact() ? 20 : 24);
    return {cell.left + Scale(7), center - Scale(3), cell.right - Scale(7),
            center + Scale(3)};
}

RECT ParamHitRect(int visibleRow, int clientWidth, int index) {
    RECT cell = ParamCellRect(visibleRow, clientWidth, index);
    return {cell.left, cell.top + Scale(IsCompact() ? 12 : 14), cell.right, cell.bottom};
}''')

rep('''int RowFromPoint(POINT point) {
    if (point.y < HeaderHeight()) {
        return DRAG_NONE;
    }
    int relative = point.y - HeaderHeight();
    int visibleRow = 0;
    if (relative >= RowHeight()) {
        if (relative < RowHeight() + SectionGap()) {
            return DRAG_NONE;
        }
        visibleRow = 1 + (relative - RowHeight() - SectionGap()) / RowHeight();
    }
    if (visibleRow > VisibleAppCount()) {
        return DRAG_NONE;
    }
    if (visibleRow == 0) {
        return DRAG_MASTER;
    }
    int appIndex = g_scrollRow + visibleRow - 1;
    return appIndex >= 0 && appIndex < static_cast<int>(g_apps->size())
               ? appIndex
               : DRAG_NONE;
}''',
'''int RowFromPoint(POINT point) {
    if (point.y < HeaderHeight()) {
        return DRAG_NONE;
    }
    if (point.y < HeaderHeight() + RowHeight()) {
        return DRAG_MASTER;
    }
    int count = VisibleAppCount();
    for (int visibleRow = 1; visibleRow <= count; ++visibleRow) {
        int top = RowTop(visibleRow);
        int bottom = top + RowHeight() +
                     (IsVisibleRowExpanded(visibleRow) ? PanelHeight() : 0);
        if (point.y >= top && point.y < bottom) {
            int appIndex = g_scrollRow + visibleRow - 1;
            return IsAppRow(appIndex) ? appIndex : DRAG_NONE;
        }
    }
    return DRAG_NONE;
}''')

# ---------------------------------------------------------------- exact entry
rep('''bool ParseVolumePercent(const std::wstring& text, int& value) {
    if (text.empty() || text.size() > 3) return false;
    int parsed = 0;
    for (wchar_t c : text) {
        if (c < L'0' || c > L'9') return false;
        parsed = parsed * 10 + (c - L'0');
    }
    if (parsed > 100) return false;''',
'''bool ParseVolumePercent(const std::wstring& text, int maximum, int& value) {
    if (text.empty() || text.size() > 4) return false;
    int parsed = 0;
    for (wchar_t c : text) {
        if (c < L'0' || c > L'9') return false;
        parsed = parsed * 10 + (c - L'0');
    }
    if (parsed > maximum) return false;''')

rep('''        int percent;
        if (!ParseVolumePercent(text, percent)) {
            MessageBeep(MB_ICONWARNING);
            SendMessageW(g_volumeEdit, EM_SETSEL, 0, -1);
            return false;
        }
        SetRowVolume(g_volumeEntryRow, percent / 100.0f);''',
'''        int percent;
        int maximum = static_cast<int>(std::lround(RowMaxLevel(g_volumeEntryRow) * 100.0f));
        if (!ParseVolumePercent(text, maximum, percent)) {
            MessageBeep(MB_ICONWARNING);
            SendMessageW(g_volumeEdit, EM_SETSEL, 0, -1);
            return false;
        }
        SetRowLevel(g_volumeEntryRow, percent / 100.0f);''')

rep('''        VOLUME_ENTRY_CLASS, L"Volume (0-100%)", WS_POPUP | WS_BORDER,''',
'''        VOLUME_ENTRY_CLASS,
        RowMaxLevel(row) > 1.0f ? L"Volume (0-1000%)" : L"Volume (0-100%)",
        WS_POPUP | WS_BORDER,''')

rep('''    float volume = row == DRAG_MASTER ? GetMasterVolume() : (*g_apps)[row].volume;
    std::wstring text = std::to_wstring(static_cast<int>(volume * 100.0f + 0.5f));''',
'''    std::wstring text = std::to_wstring(static_cast<int>(RowLevel(row) * 100.0f + 0.5f));''')

rep('''        float volume = g_selectedRow == DRAG_MASTER ? GetMasterVolume()
            : (*g_apps)[g_selectedRow].volume;
        SetRowVolume(g_selectedRow, volume +
            (key == VK_RIGHT ? 1 : -1) * g_settings.volumeStep / 100.0f);''',
'''        SetRowLevel(g_selectedRow, StepLevel(g_selectedRow, RowLevel(g_selectedRow),
                                             key == VK_RIGHT ? 1 : -1));''')

rep('''void ApplyVolumeFromPoint(HWND hWnd, int row, int x) {
    RECT client;
    GetClientRect(hWnd, &client);
    RECT slider = SliderRectForRow(VisibleRowForDataRow(row), client.right);
    float value = static_cast<float>(x - slider.left) /
                  static_cast<float>(slider.right - slider.left);
    SetRowVolume(row, value);
    InvalidateRect(hWnd, nullptr, FALSE);
}''',
'''void ApplyVolumeFromPoint(HWND hWnd, int row, int x) {
    RECT client;
    GetClientRect(hWnd, &client);
    RECT slider = SliderRectForRow(VisibleRowForDataRow(row), client.right);
    float value = static_cast<float>(x - slider.left) /
                  static_cast<float>(slider.right - slider.left);
    float maxLevel = RowMaxLevel(row);
    float level = TrackToLevel(value, maxLevel);
    // Snap to 100% near the tick so the boost-free point is easy to hit.
    if (maxLevel > 1.0f &&
        std::abs(x - (slider.left + slider.right) / 2) <= Scale(3)) {
        level = 1.0f;
    }
    SetRowLevel(row, level);
    InvalidateRect(hWnd, nullptr, FALSE);
}

void PositionMixer(HWND hWnd);

void ApplyParamFromPoint(HWND hWnd, int row, int index, int x) {
    if (!RowHasBoostUi(row)) return;
    RECT client;
    GetClientRect(hWnd, &client);
    RECT slider = ParamSliderRect(VisibleRowForDataRow(row), client.right, index);
    float fraction = static_cast<float>(x - slider.left) /
                     static_cast<float>(std::max<LONG>(1, slider.right - slider.left));
    const std::wstring& exe = (*g_apps)[row].exeKey;
    boost::Params p = BoostFor(exe);
    SetParamValue(p, index, FractionToParam(index, fraction));
    UpdateBoost(exe, p);
    InvalidateRect(hWnd, nullptr, FALSE);
}

void ToggleBoostPanel(HWND hWnd, int row) {
    if (!RowHasBoostUi(row)) return;
    std::wstring key = ExpandKeyFor((*g_apps)[row]);
    g_expandedKey = g_expandedKey == key ? std::wstring() : key;
    CancelNameTooltip(hWnd);
    PositionMixer(hWnd);
    InvalidateRect(hWnd, nullptr, FALSE);
}''')

# ---------------------------------------------------------------- drawing
rep('''COLORREF IconColor() {
    return g_lightTheme
        ? MixColor(g_theme.text, g_theme.secondaryText, 0.35f)
        : g_theme.secondaryText;
}''',
'''COLORREF IconColor() {
    return g_lightTheme
        ? MixColor(g_theme.text, g_theme.secondaryText, 0.35f)
        : g_theme.secondaryText;
}

// Catppuccin mauve marks boost past 100%; peach marks boost not yet applied.
COLORREF BoostColor() {
    return g_lightTheme ? RGB(0x88, 0x39, 0xEF) : RGB(0xCB, 0xA6, 0xF7);
}

COLORREF PendingColor() {
    return g_lightTheme ? RGB(0xFE, 0x64, 0x0B) : RGB(0xFA, 0xB3, 0x87);
}''')

rep('''void DrawSlider(HDC dc, const RECT& rect, float volume, float peak,
                bool muted, float hover) {''',
'''void DrawSlider(HDC dc, const RECT& rect, float volume, float peak,
                bool muted, float hover, bool boostScale = false) {''')

rep('''    capsule(left, trackTop, width, trackHeight, inactiveTrack);
    capsule(left, trackTop, fillWidth, trackHeight, activeTrack);
''',
'''    bool boosted = boostScale && !muted && fillWidth > width * 0.5f;
    capsule(left, trackTop, width, trackHeight, inactiveTrack);
    if (boosted) {
        capsule(left, trackTop, fillWidth, trackHeight, BoostColor());
        capsule(left, trackTop, width * 0.5f, trackHeight, activeTrack);
    } else {
        capsule(left, trackTop, fillWidth, trackHeight, activeTrack);
    }
    if (boostScale) {
        float tickWidth = 2.0f * density;
        float tickHeight = 11.0f * density;
        capsule(left + width * 0.5f - tickWidth * 0.5f, centerY - tickHeight * 0.5f,
                tickWidth, tickHeight, MixColor(g_theme.secondaryText, g_theme.panel, 0.25f));
    }
''')

rep('''    capsule(thumbX - insetDiameter * 0.5f, centerY - insetDiameter * 0.5f,
            insetDiameter, insetDiameter, activeTrack);
}''',
'''    capsule(thumbX - insetDiameter * 0.5f, centerY - insetDiameter * 0.5f,
            insetDiameter, insetDiameter, boosted ? BoostColor() : activeTrack);
}

void DrawBoostPanel(HDC dc, int visibleRow, int dataRow, int clientWidth,
                    RowVisual& visual) {
    const AppSession& app = (*g_apps)[dataRow];
    const boost::Params& p = BoostFor(app.exeKey);
    UINT left = DT_LEFT | DT_VCENTER | DT_SINGLELINE;
    UINT right = DT_RIGHT | DT_VCENTER | DT_SINGLELINE | DT_END_ELLIPSIS;
    RECT status = PanelStatusRect(visibleRow, clientWidth);
    DrawLabel(dc, p.compressor ? L"Compressor on" : L"Compressor off", status,
              g_smallFont, p.compressor ? g_theme.text : g_theme.secondaryText, left);
    if (BoostPending(app)) {
        RECT hint = status;
        hint.left += Scale(104);
        DrawLabel(dc, L"Restart " + app.name + L" to apply", hint, g_smallFont,
                  PendingColor(), right);
    }
    for (int i = 0; i < 4; ++i) {
        bool dragging = g_dragRow == dataRow && g_dragParam == i;
        RECT label = ParamLabelRect(visibleRow, clientWidth, i);
        DrawLabel(dc, kParamNames[i], label, g_smallFont, g_theme.secondaryText, left);
        DrawLabel(dc, ParamText(p, i), label, g_smallFont,
                  p.compressor ? g_theme.text : g_theme.secondaryText, right,
                  /*percentage=*/false, /*allowSmooth=*/!dragging);
        RECT hit = ParamHitRect(visibleRow, clientWidth, i);
        AnimateState(visual.paramHover[i], dragging ||
            (g_hoverRow == dataRow && g_dragRow == DRAG_NONE && PtInRect(&hit, g_hoverPoint)));
        DrawSlider(dc, ParamSliderRect(visibleRow, clientWidth, i),
                   ParamToFraction(i, ParamValue(p, i)), 0.0f, !p.compressor,
                   visual.paramHover[i]);
    }
}''')

rep('''    std::wstring name;
    float volume;
    float peak = 0.0f;
    bool muted;
    HICON icon = nullptr;
''',
'''    std::wstring name;
    float volume;
    float level;
    float peak = 0.0f;
    bool muted;
    bool boostUi = false;
    bool pending = false;
    HICON icon = nullptr;
''')

rep('''        volume = g_masterPaintVolume;
        muted = g_masterPaintMuted;
        icon = g_masterIcon;
    } else {
        const AppSession& app = (*g_apps)[dataRow];
        name = app.name;
        volume = app.volume;
        muted = app.muted;''',
'''        volume = g_masterPaintVolume;
        level = volume;
        muted = g_masterPaintMuted;
        icon = g_masterIcon;
    } else {
        const AppSession& app = (*g_apps)[dataRow];
        name = app.name;
        boostUi = app.boostable;
        level = AppLevel(app);
        // The slider works on track position, which is not linear past 100%.
        volume = LevelToTrack(level, AppMaxLevel(app));
        pending = BoostPending(app);
        muted = app.muted;''')

rep('''    RECT rowRect = {Scale(12), top, clientWidth - Scale(12), top + RowHeight() - Scale(2)};''',
'''    bool expanded = !master && IsRowExpanded(dataRow);
    RECT rowRect = {Scale(12), top, clientWidth - Scale(12),
                    top + RowHeight() - Scale(2) + (expanded ? PanelHeight() : 0)};''')

rep('''    swprintf_s(percent, L"%d%%",
               static_cast<int>(volume * 100.0f + 0.5f));''',
'''    swprintf_s(percent, L"%d%%",
               static_cast<int>(level * 100.0f + 0.5f));''')

rep('''    DrawLabel(dc, percent, percentTextRect, g_bodyFont,
              muted ? g_theme.secondaryText : g_theme.text,''',
'''    DrawLabel(dc, percent, percentTextRect, g_bodyFont,
              pending ? PendingColor() : muted ? g_theme.secondaryText : g_theme.text,''')

rep('''    DrawSlider(dc, SliderRectForRow(visibleRow, clientWidth), visual.volume,
               visual.peak, muted, visual.hover);''',
'''    DrawSlider(dc, SliderRectForRow(visibleRow, clientWidth), visual.volume,
               visual.peak, muted, visual.hover, boostUi);''')

rep('''        DrawLabel(dc, pinned ? L"\\uE840" : L"\\uE718", pin, g_symbolFont,
                  pinned ? g_theme.accent : IconColor(),
                  DT_CENTER | DT_VCENTER | DT_SINGLELINE);
    }
}''',
'''        DrawLabel(dc, pinned ? L"\\uE840" : L"\\uE718", pin, g_symbolFont,
                  pinned ? g_theme.accent : IconColor(),
                  DT_CENTER | DT_VCENTER | DT_SINGLELINE);
    }
    if (boostUi) {
        bool compressor = BoostFor((*g_apps)[dataRow].exeKey).compressor;
        RECT comp = CompressorRectForRow(visibleRow, clientWidth);
        RECT chevron = ChevronRectForRow(visibleRow, clientWidth);
        AnimateState(visual.compHover, g_hoverRow == dataRow && PtInRect(&comp, g_hoverPoint));
        AnimateState(visual.chevronHover, g_hoverRow == dataRow && PtInRect(&chevron, g_hoverPoint));
        if (compressor || visual.compHover > 0.001f)
            DrawStateSurface(dc, comp, base, visual.compHover, compressor ? 1.0f : 0.0f);
        DrawLabel(dc, L"\\uE9E9", comp, g_symbolFont,
                  compressor ? g_theme.accent : IconColor(),
                  DT_CENTER | DT_VCENTER | DT_SINGLELINE);
        if (expanded || visual.chevronHover > 0.001f)
            DrawStateSurface(dc, chevron, base, visual.chevronHover, expanded ? 1.0f : 0.0f);
        DrawLabel(dc, expanded ? L"\\uE70E" : L"\\uE70D", chevron, g_symbolFont,
                  expanded ? g_theme.accent : IconColor(),
                  DT_CENTER | DT_VCENTER | DT_SINGLELINE);
        if (expanded) DrawBoostPanel(dc, visibleRow, dataRow, clientWidth, visual);
    }
}''')

# ---------------------------------------------------------------- hide, input
rep('''    g_paintTimerInterval = 0;
    g_openTime = 0;
    g_dragRow = DRAG_NONE;''',
'''    g_paintTimerInterval = 0;
    g_openTime = 0;
    g_dragRow = DRAG_NONE;
    g_dragParam = -1;
    g_expandedKey.clear();''')

rep('''    if (g_dragRow != DRAG_NONE && (GetKeyState(VK_LBUTTON) & 0x8000)) {
        ApplyVolumeFromPoint(hWnd, g_dragRow, point.x);
    }''',
'''    if (g_dragRow != DRAG_NONE && (GetKeyState(VK_LBUTTON) & 0x8000)) {
        if (g_dragParam >= 0) {
            ApplyParamFromPoint(hWnd, g_dragRow, g_dragParam, point.x);
        } else {
            ApplyVolumeFromPoint(hWnd, g_dragRow, point.x);
        }
    }''')

rep('''            if (wParam == TIMER_NAME_TOOLTIP) {
                ShowNameTooltip(hWnd);
                return 0;
            }''',
'''            if (wParam == TIMER_NAME_TOOLTIP) {
                ShowNameTooltip(hWnd);
                return 0;
            }
            if (wParam == TIMER_BOOST_SAVE) {
                KillTimer(hWnd, TIMER_BOOST_SAVE);
                if (g_boostSaveDirty) SaveBoostConfig();
                return 0;
            }''')

rep('''            RECT sliderRect = SliderHitRect(visibleRow, client.right);
            if (PtInRect(&sliderRect, point)) {
                g_dragRow = row;
                SetCapture(hWnd);
                ApplyVolumeFromPoint(hWnd, row, point.x);
            }
            return 0;''',
'''            if (RowHasBoostUi(row)) {
                RECT compRect = CompressorRectForRow(visibleRow, client.right);
                if (PtInRect(&compRect, point)) {
                    ToggleCompressor(row);
                    InvalidateRect(hWnd, nullptr, FALSE);
                    return 0;
                }
                RECT chevronRect = ChevronRectForRow(visibleRow, client.right);
                if (PtInRect(&chevronRect, point)) {
                    ToggleBoostPanel(hWnd, row);
                    return 0;
                }
                if (IsRowExpanded(row)) {
                    for (int i = 0; i < 4; ++i) {
                        RECT hit = ParamHitRect(visibleRow, client.right, i);
                        if (PtInRect(&hit, point)) {
                            g_dragRow = row;
                            g_dragParam = i;
                            SetCapture(hWnd);
                            ApplyParamFromPoint(hWnd, row, i, point.x);
                            return 0;
                        }
                    }
                    if (point.y >= RowTop(visibleRow) + RowHeight() - Scale(4)) return 0;
                }
            }

            RECT sliderRect = SliderHitRect(visibleRow, client.right);
            if (PtInRect(&sliderRect, point)) {
                g_dragRow = row;
                g_dragParam = -1;
                SetCapture(hWnd);
                ApplyVolumeFromPoint(hWnd, row, point.x);
            }
            return 0;''')

rep('''        case WM_LBUTTONUP:
            if (g_dragRow != DRAG_NONE) {
                g_dragRow = DRAG_NONE;
                ReleaseCapture();
            }
            return 0;

        case WM_CAPTURECHANGED:
            g_dragRow = DRAG_NONE;
            return 0;''',
'''        case WM_LBUTTONUP:
            if (g_dragRow != DRAG_NONE) {
                g_dragRow = DRAG_NONE;
                g_dragParam = -1;
                ReleaseCapture();
            }
            return 0;

        case WM_CAPTURECHANGED:
            g_dragRow = DRAG_NONE;
            g_dragParam = -1;
            return 0;''')

rep('''            int notches = GET_WHEEL_DELTA_WPARAM(wParam) / WHEEL_DELTA;
            if (row != DRAG_NONE && notches) {
                float current = row == DRAG_MASTER ? GetMasterVolume()
                                                   : (*g_apps)[row].volume;
                SetRowVolume(row, current + notches *
                                              g_settings.volumeStep / 100.0f);
                InvalidateRect(hWnd, nullptr, FALSE);''',
'''            int notches = GET_WHEEL_DELTA_WPARAM(wParam) / WHEEL_DELTA;
            int direction = notches > 0 ? 1 : -1;
            if (notches && IsRowExpanded(row)) {
                int visibleRow = VisibleRowForDataRow(row);
                for (int i = 0; i < 4; ++i) {
                    RECT hit = ParamHitRect(visibleRow, client.right, i);
                    if (!PtInRect(&hit, point)) continue;
                    const std::wstring& exe = (*g_apps)[row].exeKey;
                    boost::Params p = BoostFor(exe);
                    float value = ParamValue(p, i);
                    for (int n = 0; n < std::abs(notches); ++n) {
                        value = StepParam(i, value, direction);
                    }
                    SetParamValue(p, i, value);
                    UpdateBoost(exe, p);
                    InvalidateRect(hWnd, nullptr, FALSE);
                    return 0;
                }
                if (point.y >= RowTop(visibleRow) + RowHeight() - Scale(4)) return 0;
            }
            if (row != DRAG_NONE && notches) {
                float level = RowLevel(row);
                for (int n = 0; n < std::abs(notches); ++n) {
                    level = StepLevel(row, level, direction);
                }
                SetRowLevel(row, level);
                InvalidateRect(hWnd, nullptr, FALSE);''')

# ---------------------------------------------------------------- lifecycle
rep('''    Wh_Log(L"Mixer: initializing tool");
    LoadSettings();
''',
'''    Wh_Log(L"Mixer: initializing tool");
    LoadSettings();
    OpenBoostTable();
    LoadBoostConfig();
''')

rep('''        CloseHandle(g_thread);
        g_thread = nullptr;
    }
    if (g_windowReadyEvent) {
        CloseHandle(g_windowReadyEvent);
        g_windowReadyEvent = nullptr;
    }
}''',
'''        CloseHandle(g_thread);
        g_thread = nullptr;
    }
    if (g_boostSaveDirty) SaveBoostConfig();
    if (g_windowReadyEvent) {
        CloseHandle(g_windowReadyEvent);
        g_windowReadyEvent = nullptr;
    }
}''')

rep('''bool g_isToolModProcessLauncher;
HANDLE g_toolModProcessMutex;''',
'''bool g_isToolModProcessLauncher;
bool g_isBoostProcess;
HANDLE g_toolModProcessMutex;''')

rep('''    if (isToolModProcess) {
        return FALSE;
    }

    g_isToolModProcessLauncher = true;
    return TRUE;
}''',
'''    if (isToolModProcess) {
        return FALSE;
    }

    WCHAR modulePath[MAX_PATH];
    DWORD modulePathLength = GetModuleFileNameW(nullptr, modulePath, ARRAYSIZE(modulePath));
    if (!modulePathLength || modulePathLength >= ARRAYSIZE(modulePath)) {
        return FALSE;
    }
    std::wstring exe = boost::ExeKeyFromPath(modulePath);
    // Windhawk itself and its windhawk-mod.exe tool host launch the mixer,
    // exactly as before boost existed.
    if (exe.rfind(L"windhawk", 0) == 0) {
        g_isToolModProcessLauncher = true;
        return TRUE;
    }

    // Any other process is here through the custom process list: run the
    // audio processor only. It never starts the mixer or exits the process.
    if (!boost::ProcessorInit(exe)) {
        return FALSE;
    }
    g_isBoostProcess = true;
    return TRUE;
}''')

rep('''void Wh_ModSettingsChanged() {
    if (g_isToolModProcessLauncher) {
        return;
    }

    WhTool_ModSettingsChanged();
}

void Wh_ModUninit() {
    if (g_isToolModProcessLauncher) {
        return;
    }
''',
'''void Wh_ModSettingsChanged() {
    if (g_isToolModProcessLauncher || g_isBoostProcess) {
        return;
    }

    WhTool_ModSettingsChanged();
}

void Wh_ModUninit() {
    if (g_isToolModProcessLauncher) {
        return;
    }
    if (g_isBoostProcess) {
        boost::ProcessorUninit();
        return;
    }
''')

bad = []
for old, new in edits:
    n = src.count(old)
    if n != 1:
        bad.append((n, old[:90]))
if bad:
    for n, o in bad:
        print('ANCHOR x%d: %r' % (n, o))
    sys.exit(1)
for old, new in edits:
    src = src.replace(old, new, 1)
src.encode('ascii')  # stays ASCII; glyphs use \u escapes
open(path, 'wb').write(src.replace('\n', '\r\n').encode('utf-8'))
print('patched %d edits' % len(edits))
