// Silent boost check for Seamless Volume Mixer.
// bvmp-boosttest.exe probe <seconds>   writes 0.01 samples with session volume 0,
//                                      reads each buffer back after ReleaseBuffer
//                                      (where the boost hook scales it).
// bvmp-boosttest.exe hold <seconds>    writes silence at session volume 100%, so the
//                                      app shows up in the mixer for a screenshot.
#include <windows.h>
#include <mmdeviceapi.h>
#include <audioclient.h>
#include <audiopolicy.h>
#include <mmreg.h>
#include <cstdio>
#include <cwchar>

int wmain(int argc, wchar_t** argv) {
    bool probe = argc > 1 && wcscmp(argv[1], L"probe") == 0;
    int seconds = argc > 2 ? _wtoi(argv[2]) : 3;
    Sleep(1500);  // let Windhawk finish loading mods into this process
    CoInitializeEx(nullptr, COINIT_MULTITHREADED);
    IMMDeviceEnumerator* en = nullptr;
    IMMDevice* dev = nullptr;
    IAudioClient* ac = nullptr;
    IAudioRenderClient* rc = nullptr;
    ISimpleAudioVolume* vol = nullptr;
    WAVEFORMATEX* mix = nullptr;
    if (FAILED(CoCreateInstance(__uuidof(MMDeviceEnumerator), nullptr, CLSCTX_ALL,
                                __uuidof(IMMDeviceEnumerator), (void**)&en)) ||
        FAILED(en->GetDefaultAudioEndpoint(eRender, eConsole, &dev)) ||
        FAILED(dev->Activate(__uuidof(IAudioClient), CLSCTX_ALL, nullptr, (void**)&ac)) ||
        FAILED(ac->GetMixFormat(&mix)) ||
        FAILED(ac->Initialize(AUDCLNT_SHAREMODE_SHARED, 0, 2000000, 0, mix, nullptr)) ||
        FAILED(ac->GetService(__uuidof(ISimpleAudioVolume), (void**)&vol)) ||
        FAILED(ac->GetService(__uuidof(IAudioRenderClient), (void**)&rc))) {
        printf("setup failed\n");
        return 1;
    }
    vol->SetMasterVolume(probe ? 0.0f : 1.0f, nullptr);
    vol->SetMute(FALSE, nullptr);
    bool isFloat = mix->wBitsPerSample == 32 &&
        (mix->wFormatTag == WAVE_FORMAT_IEEE_FLOAT ||
         (mix->wFormatTag == WAVE_FORMAT_EXTENSIBLE &&
          ((WAVEFORMATEXTENSIBLE*)mix)->SubFormat.Data1 == 3));
    bool isInt16 = mix->wBitsPerSample == 16;
    if (probe && !isFloat && !isInt16) {
        printf("unsupported mix format, bits=%u\n", mix->wBitsPerSample);
        return 1;
    }
    UINT32 bufferFrames = 0;
    ac->GetBufferSize(&bufferFrames);
    UINT32 samplesPerFrame = mix->nChannels;
    ac->Start();
    float minOut = 1e9f, maxOut = -1e9f;
    long buffers = 0;
    ULONGLONG end = GetTickCount64() + seconds * 1000ULL;
    while (GetTickCount64() < end) {
        UINT32 padding = 0;
        ac->GetCurrentPadding(&padding);
        UINT32 frames = bufferFrames - padding;
        BYTE* data = nullptr;
        if (frames && SUCCEEDED(rc->GetBuffer(frames, &data))) {
            UINT32 samples = frames * samplesPerFrame;
            if (!probe) {
                memset(data, 0, frames * mix->nBlockAlign);
            } else if (isFloat) {
                for (UINT32 i = 0; i < samples; ++i) ((float*)data)[i] = 0.01f;
            } else {
                for (UINT32 i = 0; i < samples; ++i) ((short*)data)[i] = 328;
            }
            rc->ReleaseBuffer(frames, 0);
            if (probe) {
                float out = isFloat ? ((float*)data)[samples / 2]
                                    : ((short*)data)[samples / 2] / 32768.0f;
                if (out < minOut) minOut = out;
                if (out > maxOut) maxOut = out;
                ++buffers;
            }
        }
        Sleep(10);
    }
    ac->Stop();
    if (probe) {
        printf("format=%s in=0.0100 out_min=%.4f out_max=%.4f buffers=%ld ratio=%.2f\n",
               isFloat ? "float32" : "int16", minOut, maxOut, buffers, maxOut / 0.01f);
    } else {
        printf("held %d s\n", seconds);
    }
    return 0;
}
