//--------------------------------------------------------------------------------------
// File: Audio.h
//
// DirectXTK for Audio header
//
// Copyright (c) Microsoft Corporation.
// Licensed under the MIT License.
//
// http://go.microsoft.com/fwlink/?LinkId=248929
// http://go.microsoft.com/fwlink/?LinkID=615561
//--------------------------------------------------------------------------------------

#pragma once

#include <HDirectXTKDef.h>

#include <cstddef>
#include <cstdint>
#include <functional>
#include <memory>
#include <string>
#include <vector>

#include <objbase.h>
#include <mmreg.h>
#include <Audioclient.h>

#if (defined(_XBOX_ONE) && defined(_TITLE)) || defined(_GAMING_XBOX)
#include <xma2defs.h>
#ifdef _MSC_VER
#pragma comment(lib,"acphal.lib")
#endif
#endif

#ifndef XAUDIO2_HELPER_FUNCTIONS
#define XAUDIO2_HELPER_FUNCTIONS
#endif

#if defined(USING_XAUDIO2_REDIST) || (_WIN32_WINNT >= 0x0A00 /*_WIN32_WINNT_WIN10*/) || defined(_XBOX_ONE)
#define USING_XAUDIO2_9
#elif (_WIN32_WINNT >= 0x0602 /*_WIN32_WINNT_WIN8*/)
#define USING_XAUDIO2_8
#elif (_WIN32_WINNT >= 0x0601 /*_WIN32_WINNT_WIN7*/)
#error Windows 7 SP1 requires the XAudio2Redist NuGet package https://aka.ms/xaudio2redist
#else
#error DirectX Tool Kit for Audio not supported on this platform
#endif

#include <xaudio2.h>
#include <xaudio2fx.h>

#ifdef _MSC_VER
#pragma warning(push)
#pragma warning(disable : 4619 4616 5246)
#endif
#include <x3daudio.h>
#ifdef _MSC_VER
#pragma warning(pop)
#endif

#include <xapofx.h>

#if !defined(USING_XAUDIO2_REDIST) && defined(_MSC_VER)
#if defined(USING_XAUDIO2_8) && defined(NTDDI_WIN10) && !defined(_M_IX86)
// The xaudio2_8.lib in the Windows 10 SDK for x86 is incorrectly annotated as __cdecl instead of __stdcall, so avoid using it in this case.
#pragma comment(lib,"xaudio2_8.lib")
#else
#pragma comment(lib,"xaudio2.lib")
#endif
#endif

#include <DirectXMath.h>


namespace DirectX
{
    class SoundEffectInstance;
    class SoundStreamInstance;

    //----------------------------------------------------------------------------------
    struct AudioStatistics
    {
        size_t  playingOneShots;        // Number of one-shot sounds currently playing
        size_t  playingInstances;       // Number of sound effect instances currently playing
        size_t  allocatedInstances;     // Number of SoundEffectInstance allocated
        size_t  allocatedVoices;        // Number of XAudio2 voices allocated (standard, 3D, one-shots, and idle one-shots)
        size_t  allocatedVoices3d;      // Number of XAudio2 voices allocated for 3D
        size_t  allocatedVoicesOneShot; // Number of XAudio2 voices allocated for one-shot sounds
        size_t  allocatedVoicesIdle;    // Number of XAudio2 voices allocated for one-shot sounds but not currently in use
        size_t  audioBytes;             // Total wave data (in bytes) in SoundEffects and in-memory WaveBanks
    #if (defined(_XBOX_ONE) && defined(_TITLE)) || defined(_GAMING_XBOX)
        size_t  xmaAudioBytes;          // Total wave data (in bytes) in SoundEffects and in-memory WaveBanks allocated with ApuAlloc
    #endif
        size_t  streamingBytes;         // Total size of streaming buffers (in bytes) in streaming WaveBanks
    };


    //----------------------------------------------------------------------------------
    class IVoiceNotify
    {
    public:
        virtual ~IVoiceNotify() = default;

        IVoiceNotify(const IVoiceNotify&) = delete;
        IVoiceNotify& operator=(const IVoiceNotify&) = delete;

        IVoiceNotify(IVoiceNotify&&) = default;
        IVoiceNotify& operator=(IVoiceNotify&&) = default;

        virtual void __cdecl OnBufferEnd() = 0;
            // Notfication that a voice buffer has finished
            // Note this is called from XAudio2's worker thread, so it should perform very minimal and thread-safe operations

        virtual void __cdecl OnCriticalError() = 0;
            // Notification that the audio engine encountered a critical error

        virtual void __cdecl OnReset() = 0;
            // Notification of an audio engine reset

        virtual void __cdecl OnUpdate() = 0;
            // Notification of an audio engine per-frame update (opt-in)

        virtual void __cdecl OnDestroyEngine() noexcept = 0;
            // Notification that the audio engine is being destroyed

        virtual void __cdecl OnTrim() = 0;
            // Notification of a request to trim the voice pool

        virtual void __cdecl GatherStatistics(AudioStatistics& stats) const = 0;
            // Contribute to statistics request

        virtual void __cdecl OnDestroyParent() noexcept = 0;
            // Optional notification used by some objects

    protected:
        IVoiceNotify() = default;
    };

    //----------------------------------------------------------------------------------
    enum AUDIO_ENGINE_FLAGS : uint32_t
    {
        AudioEngine_Default = 0x0,

        AudioEngine_EnvironmentalReverb = 0x1,
        AudioEngine_ReverbUseFilters = 0x2,
        AudioEngine_UseMasteringLimiter = 0x4,

        AudioEngine_Debug = 0x10000,
        AudioEngine_ThrowOnNoAudioHW = 0x20000,
        AudioEngine_DisableVoiceReuse = 0x40000,
    };

    enum SOUND_EFFECT_INSTANCE_FLAGS : uint32_t
    {
        SoundEffectInstance_Default = 0x0,

        SoundEffectInstance_Use3D = 0x1,
        SoundEffectInstance_ReverbUseFilters = 0x2,
        SoundEffectInstance_NoSetPitch = 0x4,

        SoundEffectInstance_UseRedirectLFE = 0x10000,
    };

    enum AUDIO_ENGINE_REVERB : uint32_t
    {
        Reverb_Off,
        Reverb_Default,
        Reverb_Generic,
        Reverb_Forest,
        Reverb_PaddedCell,
        Reverb_Room,
        Reverb_Bathroom,
        Reverb_LivingRoom,
        Reverb_StoneRoom,
        Reverb_Auditorium,
        Reverb_ConcertHall,
        Reverb_Cave,
        Reverb_Arena,
        Reverb_Hangar,
        Reverb_CarpetedHallway,
        Reverb_Hallway,
        Reverb_StoneCorridor,
        Reverb_Alley,
        Reverb_City,
        Reverb_Mountains,
        Reverb_Quarry,
        Reverb_Plain,
        Reverb_ParkingLot,
        Reverb_SewerPipe,
        Reverb_Underwater,
        Reverb_SmallRoom,
        Reverb_MediumRoom,
        Reverb_LargeRoom,
        Reverb_MediumHall,
        Reverb_LargeHall,
        Reverb_Plate,
        Reverb_MAX
    };

    enum SoundState : uint32_t
    {
        STOPPED = 0,
        PLAYING,
        PAUSED
    };


    //----------------------------------------------------------------------------------
    class AudioEngine
    {
    public:
        HDXTK_EXPORT explicit AudioEngine(
            AUDIO_ENGINE_FLAGS flags = AudioEngine_Default,
            _In_opt_ const WAVEFORMATEX* wfx = nullptr,
            _In_opt_z_ const wchar_t* deviceId = nullptr,
            AUDIO_STREAM_CATEGORY category = AudioCategory_GameEffects) noexcept(false);

        HDXTK_EXPORT AudioEngine(AudioEngine&&) noexcept;
        HDXTK_EXPORT AudioEngine& operator= (AudioEngine&&) noexcept;

        AudioEngine(AudioEngine const&) = delete;
        AudioEngine& operator= (AudioEngine const&) = delete;

        HDXTK_EXPORT virtual ~AudioEngine();

        HDXTK_EXPORT bool __cdecl Update();
            // Performs per-frame processing for the audio engine, returns false if in 'silent mode'

        HDXTK_EXPORT bool __cdecl Reset(_In_opt_ const WAVEFORMATEX* wfx = nullptr, _In_opt_z_ const wchar_t* deviceId = nullptr);
            // Reset audio engine from critical error/silent mode using a new device; can also 'migrate' the graph
            // Returns true if succesfully reset, false if in 'silent mode' due to no default device
            // Note: One shots are lost, all SoundEffectInstances are in the STOPPED state after successful reset

        HDXTK_EXPORT void __cdecl Suspend() noexcept;
        HDXTK_EXPORT void __cdecl Resume();
            // Suspend/resumes audio processing (i.e. global pause/resume)

        HDXTK_EXPORT float __cdecl GetMasterVolume() const noexcept;
        HDXTK_EXPORT void __cdecl SetMasterVolume(float volume);
            // Master volume property for all sounds

        HDXTK_EXPORT void __cdecl SetReverb(AUDIO_ENGINE_REVERB reverb);
        HDXTK_EXPORT void __cdecl SetReverb(_In_opt_ const XAUDIO2FX_REVERB_PARAMETERS* native);
            // Sets environmental reverb for 3D positional audio (if active)

        HDXTK_EXPORT void __cdecl SetMasteringLimit(int release, int loudness);
            // Sets the mastering volume limiter properties (if active)

        HDXTK_EXPORT AudioStatistics __cdecl GetStatistics() const;
            // Gathers audio engine statistics

        HDXTK_EXPORT WAVEFORMATEXTENSIBLE __cdecl GetOutputFormat() const noexcept;
            // Returns the format of the audio output device associated with the mastering voice.

        HDXTK_EXPORT uint32_t __cdecl GetChannelMask() const noexcept;
            // Returns the output channel mask

        HDXTK_EXPORT int __cdecl GetOutputSampleRate() const noexcept;
            // Returns the sample rate going into the mastering voice

        HDXTK_EXPORT unsigned int __cdecl GetOutputChannels() const noexcept;
            // Returns the number of channels going into the mastering voice

        HDXTK_EXPORT bool __cdecl IsAudioDevicePresent() const noexcept;
            // Returns true if the audio graph is operating normally, false if in 'silent mode'

        HDXTK_EXPORT bool __cdecl IsCriticalError() const noexcept;
            // Returns true if the audio graph is halted due to a critical error (which also places the engine into 'silent mode')

        // Voice pool management.
        HDXTK_EXPORT void __cdecl SetDefaultSampleRate(int sampleRate);
            // Sample rate for voices in the reuse pool (defaults to 44100)

        HDXTK_EXPORT void __cdecl SetMaxVoicePool(size_t maxOneShots, size_t maxInstances);
            // Maximum number of voices to allocate for one-shots and instances
            // Note: one-shots over this limit are ignored; too many instance voices throws an exception

        HDXTK_EXPORT void __cdecl TrimVoicePool();
            // Releases any currently unused voices

        // Internal-use functions
        HDXTK_EXPORT void __cdecl AllocateVoice(_In_ const WAVEFORMATEX* wfx,
            SOUND_EFFECT_INSTANCE_FLAGS flags, bool oneshot, _Outptr_result_maybenull_ IXAudio2SourceVoice** voice);

        HDXTK_EXPORT void __cdecl DestroyVoice(_In_ IXAudio2SourceVoice* voice) noexcept;
            // Should only be called for instance voices, not one-shots

        HDXTK_EXPORT void __cdecl RegisterNotify(_In_ IVoiceNotify* notify, bool usesUpdate);
        HDXTK_EXPORT void __cdecl UnregisterNotify(_In_ IVoiceNotify* notify, bool usesOneShots, bool usesUpdate);

        // XAudio2 interface access
        HDXTK_EXPORT IXAudio2* __cdecl GetInterface() const noexcept;
        HDXTK_EXPORT IXAudio2MasteringVoice* __cdecl GetMasterVoice() const noexcept;
        HDXTK_EXPORT IXAudio2SubmixVoice* __cdecl GetReverbVoice() const noexcept;
        HDXTK_EXPORT X3DAUDIO_HANDLE& __cdecl Get3DHandle() const noexcept;

        // Static functions
        struct RendererDetail
        {
            std::wstring deviceId;
            std::wstring description;
        };

        static std::vector<RendererDetail> __cdecl GetRendererDetails();
            // Returns a list of valid audio endpoint devices

#if defined(_MSC_VER) && !defined(_NATIVE_WCHAR_T_DEFINED)
        explicit AudioEngine(
            AUDIO_ENGINE_FLAGS flags = AudioEngine_Default,
            _In_opt_ const WAVEFORMATEX* wfx = nullptr,
            _In_opt_z_ const __wchar_t* deviceId = nullptr,
            AUDIO_STREAM_CATEGORY category = AudioCategory_GameEffects) noexcept(false);

        bool __cdecl Reset(_In_opt_ const WAVEFORMATEX* wfx = nullptr, _In_opt_z_ const __wchar_t* deviceId = nullptr);
#endif

    private:
        // Private implementation.
        class Impl;
        std::unique_ptr<Impl> pImpl;
    };


    //----------------------------------------------------------------------------------
    class WaveBank
    {
    public:
        HDXTK_EXPORT WaveBank(_In_ AudioEngine* engine, _In_z_ const wchar_t* wbFileName);

        HDXTK_EXPORT WaveBank(WaveBank&&) noexcept;
        HDXTK_EXPORT WaveBank& operator= (WaveBank&&) noexcept;

        WaveBank(WaveBank const&) = delete;
        WaveBank& operator= (WaveBank const&) = delete;

        HDXTK_EXPORT virtual ~WaveBank();

        HDXTK_EXPORT void __cdecl Play(unsigned int index);
        HDXTK_EXPORT void __cdecl Play(unsigned int index, float volume, float pitch, float pan);

        HDXTK_EXPORT void __cdecl Play(_In_z_ const char* name);
        HDXTK_EXPORT void __cdecl Play(_In_z_ const char* name, float volume, float pitch, float pan);

        HDXTK_EXPORT std::unique_ptr<SoundEffectInstance> __cdecl CreateInstance(unsigned int index,
                            SOUND_EFFECT_INSTANCE_FLAGS flags = SoundEffectInstance_Default);
        HDXTK_EXPORT std::unique_ptr<SoundEffectInstance> __cdecl CreateInstance(_In_z_ const char* name,
                            SOUND_EFFECT_INSTANCE_FLAGS flags = SoundEffectInstance_Default);

        HDXTK_EXPORT std::unique_ptr<SoundStreamInstance> __cdecl CreateStreamInstance(unsigned int index,
                            SOUND_EFFECT_INSTANCE_FLAGS flags = SoundEffectInstance_Default);
        HDXTK_EXPORT std::unique_ptr<SoundStreamInstance> __cdecl CreateStreamInstance(_In_z_ const char* name,
                        SOUND_EFFECT_INSTANCE_FLAGS flags = SoundEffectInstance_Default);

        HDXTK_EXPORT bool __cdecl IsPrepared() const noexcept;
        HDXTK_EXPORT bool __cdecl IsInUse() const noexcept;
        HDXTK_EXPORT bool __cdecl IsStreamingBank() const noexcept;
        HDXTK_EXPORT bool __cdecl IsAdvancedFormat() const noexcept;

        HDXTK_EXPORT size_t __cdecl GetSampleSizeInBytes(unsigned int index) const noexcept;
        // Returns size of wave audio data

        HDXTK_EXPORT size_t __cdecl GetSampleDuration(unsigned int index) const noexcept;
        // Returns the duration in samples

        HDXTK_EXPORT size_t __cdecl GetSampleDurationMS(unsigned int index) const noexcept;
        // Returns the duration in milliseconds

        HDXTK_EXPORT const WAVEFORMATEX* __cdecl GetFormat(unsigned int index, _Out_writes_bytes_(maxsize) WAVEFORMATEX* wfx, size_t maxsize) const noexcept;

        HDXTK_EXPORT int __cdecl Find(_In_z_ const char* name) const;

    #ifdef USING_XAUDIO2_9
        HDXTK_EXPORT bool __cdecl FillSubmitBuffer(unsigned int index, _Out_ XAUDIO2_BUFFER& buffer, _Out_ XAUDIO2_BUFFER_WMA& wmaBuffer) const;
    #else
        HDXTK_EXPORT void __cdecl FillSubmitBuffer(unsigned int index, _Out_ XAUDIO2_BUFFER& buffer) const;
    #endif

        HDXTK_EXPORT void __cdecl UnregisterInstance(_In_ IVoiceNotify* instance);

        HDXTK_EXPORT HANDLE __cdecl GetAsyncHandle() const noexcept;

        HDXTK_EXPORT bool __cdecl GetPrivateData(unsigned int index, _Out_writes_bytes_(datasize) void* data, size_t datasize);

#if defined(_MSC_VER) && !defined(_NATIVE_WCHAR_T_DEFINED)
        HDXTK_EXPORT WaveBank(_In_ AudioEngine* engine, _In_z_ const __wchar_t* wbFileName);
#endif

    private:
        // Private implementation.
        class Impl;

        std::unique_ptr<Impl> pImpl;
    };


    //----------------------------------------------------------------------------------
    class SoundEffect
    {
    public:
        HDXTK_EXPORT SoundEffect(_In_ AudioEngine* engine, _In_z_ const wchar_t* waveFileName);

        HDXTK_EXPORT SoundEffect(_In_ AudioEngine* engine, _Inout_ std::unique_ptr<uint8_t[]>& wavData,
            _In_ const WAVEFORMATEX* wfx, _In_reads_bytes_(audioBytes) const uint8_t* startAudio, size_t audioBytes);

        HDXTK_EXPORT SoundEffect(_In_ AudioEngine* engine, _Inout_ std::unique_ptr<uint8_t[]>& wavData,
            _In_ const WAVEFORMATEX* wfx, _In_reads_bytes_(audioBytes) const uint8_t* startAudio, size_t audioBytes,
            uint32_t loopStart, uint32_t loopLength);

    #ifdef USING_XAUDIO2_9

        HDXTK_EXPORT SoundEffect(_In_ AudioEngine* engine, _Inout_ std::unique_ptr<uint8_t[]>& wavData,
            _In_ const WAVEFORMATEX* wfx, _In_reads_bytes_(audioBytes) const uint8_t* startAudio, size_t audioBytes,
            _In_reads_(seekCount) const uint32_t* seekTable, size_t seekCount);

    #endif

        HDXTK_EXPORT SoundEffect(SoundEffect&&) noexcept;
        HDXTK_EXPORT SoundEffect& operator= (SoundEffect&&) noexcept;

        SoundEffect(SoundEffect const&) = delete;
        SoundEffect& operator= (SoundEffect const&) = delete;

        virtual ~SoundEffect();

        HDXTK_EXPORT void __cdecl Play();
        HDXTK_EXPORT void __cdecl Play(float volume, float pitch, float pan);

        HDXTK_EXPORT std::unique_ptr<SoundEffectInstance> __cdecl CreateInstance(SOUND_EFFECT_INSTANCE_FLAGS flags = SoundEffectInstance_Default);

        HDXTK_EXPORT bool __cdecl IsInUse() const noexcept;

        HDXTK_EXPORT size_t __cdecl GetSampleSizeInBytes() const noexcept;
        // Returns size of wave audio data

        HDXTK_EXPORT size_t __cdecl GetSampleDuration() const noexcept;
        // Returns the duration in samples

        HDXTK_EXPORT size_t __cdecl GetSampleDurationMS() const noexcept;
        // Returns the duration in milliseconds

        HDXTK_EXPORT const WAVEFORMATEX* __cdecl GetFormat() const noexcept;

    #ifdef USING_XAUDIO2_9
        HDXTK_EXPORT bool __cdecl FillSubmitBuffer(_Out_ XAUDIO2_BUFFER& buffer, _Out_ XAUDIO2_BUFFER_WMA& wmaBuffer) const;
    #else
        HDXTK_EXPORT void __cdecl FillSubmitBuffer(_Out_ XAUDIO2_BUFFER& buffer) const;
    #endif

        HDXTK_EXPORT void __cdecl UnregisterInstance(_In_ IVoiceNotify* instance);

#if defined(_MSC_VER) && !defined(_NATIVE_WCHAR_T_DEFINED)
        HDXTK_EXPORT SoundEffect(_In_ AudioEngine* engine, _In_z_ const __wchar_t* waveFileName);
#endif

    private:
        // Private implementation.
        class Impl;

        std::unique_ptr<Impl> pImpl;
    };


    //----------------------------------------------------------------------------------
    struct AudioListener : public X3DAUDIO_LISTENER
    {
        X3DAUDIO_CONE   ListenerCone;

        AudioListener() noexcept :
            X3DAUDIO_LISTENER{},
            ListenerCone{}
        {
            OrientFront.z = -1.f;

            OrientTop.y = 1.f;
        }

        void XM_CALLCONV SetPosition(FXMVECTOR v) noexcept
        {
            XMStoreFloat3(reinterpret_cast<XMFLOAT3*>(&Position), v);
        }
        void __cdecl SetPosition(const XMFLOAT3& pos) noexcept
        {
            Position.x = pos.x;
            Position.y = pos.y;
            Position.z = pos.z;
        }

        void XM_CALLCONV SetVelocity(FXMVECTOR v) noexcept
        {
            XMStoreFloat3(reinterpret_cast<XMFLOAT3*>(&Velocity), v);
        }
        void __cdecl SetVelocity(const XMFLOAT3& vel) noexcept
        {
            Velocity.x = vel.x;
            Velocity.y = vel.y;
            Velocity.z = vel.z;
        }

        void XM_CALLCONV SetOrientation(FXMVECTOR forward, FXMVECTOR up) noexcept
        {
            XMStoreFloat3(reinterpret_cast<XMFLOAT3*>(&OrientFront), forward);
            XMStoreFloat3(reinterpret_cast<XMFLOAT3*>(&OrientTop), up);
        }
        void __cdecl SetOrientation(const XMFLOAT3& forward, const XMFLOAT3& up) noexcept
        {
            OrientFront.x = forward.x;  OrientTop.x = up.x;
            OrientFront.y = forward.y;  OrientTop.y = up.y;
            OrientFront.z = forward.z;  OrientTop.z = up.z;
        }

        void XM_CALLCONV SetOrientationFromQuaternion(FXMVECTOR quat) noexcept
        {
            const XMVECTOR forward = XMVector3Rotate(g_XMIdentityR2, quat);
            XMStoreFloat3(reinterpret_cast<XMFLOAT3*>(&OrientFront), forward);

            const XMVECTOR up = XMVector3Rotate(g_XMIdentityR1, quat);
            XMStoreFloat3(reinterpret_cast<XMFLOAT3*>(&OrientTop), up);
        }

        // Updates velocity and orientation by tracking changes in position over time.
        void XM_CALLCONV Update(FXMVECTOR newPos, XMVECTOR upDir, float dt) noexcept
        {
            if (dt > 0.f)
            {
                const XMVECTOR lastPos = XMLoadFloat3(reinterpret_cast<const XMFLOAT3*>(&Position));

                XMVECTOR vDelta = XMVectorSubtract(newPos, lastPos);
                const XMVECTOR vt = XMVectorReplicate(dt);
                XMVECTOR v = XMVectorDivide(vDelta, vt);
                XMStoreFloat3(reinterpret_cast<XMFLOAT3*>(&Velocity), v);

                vDelta = XMVector3Normalize(vDelta);
                XMStoreFloat3(reinterpret_cast<XMFLOAT3*>(&OrientFront), vDelta);

                v = XMVector3Cross(upDir, vDelta);
                v = XMVector3Normalize(v);

                v = XMVector3Cross(vDelta, v);
                v = XMVector3Normalize(v);
                XMStoreFloat3(reinterpret_cast<XMFLOAT3*>(&OrientTop), v);

                XMStoreFloat3(reinterpret_cast<XMFLOAT3*>(&Position), newPos);
            }
        }

        void __cdecl SetOmnidirectional() noexcept
        {
            pCone = nullptr;
        }

        HDXTK_EXPORT void __cdecl SetCone(const X3DAUDIO_CONE& listenerCone);

        HDXTK_EXPORT bool __cdecl IsValid() const;
    };


    //----------------------------------------------------------------------------------
    struct AudioEmitter : public X3DAUDIO_EMITTER
    {
        X3DAUDIO_CONE   EmitterCone;
        float           EmitterAzimuths[XAUDIO2_MAX_AUDIO_CHANNELS];

        AudioEmitter() noexcept :
            X3DAUDIO_EMITTER{},
            EmitterCone{},
            EmitterAzimuths{}
        {
            OrientFront.z = -1.f;

            OrientTop.y =
                ChannelRadius =
                CurveDistanceScaler =
                DopplerScaler = 1.f;

            ChannelCount = 1;
            pChannelAzimuths = EmitterAzimuths;

            InnerRadiusAngle = X3DAUDIO_PI / 4.0f;
        }

        void XM_CALLCONV SetPosition(FXMVECTOR v) noexcept
        {
            XMStoreFloat3(reinterpret_cast<XMFLOAT3*>(&Position), v);
        }
        void __cdecl SetPosition(const XMFLOAT3& pos) noexcept
        {
            Position.x = pos.x;
            Position.y = pos.y;
            Position.z = pos.z;
        }

        void XM_CALLCONV SetVelocity(FXMVECTOR v) noexcept
        {
            XMStoreFloat3(reinterpret_cast<XMFLOAT3*>(&Velocity), v);
        }
        void __cdecl SetVelocity(const XMFLOAT3& vel) noexcept
        {
            Velocity.x = vel.x;
            Velocity.y = vel.y;
            Velocity.z = vel.z;
        }

        void XM_CALLCONV SetOrientation(FXMVECTOR forward, FXMVECTOR up) noexcept
        {
            XMStoreFloat3(reinterpret_cast<XMFLOAT3*>(&OrientFront), forward);
            XMStoreFloat3(reinterpret_cast<XMFLOAT3*>(&OrientTop), up);
        }
        void __cdecl SetOrientation(const XMFLOAT3& forward, const XMFLOAT3& up) noexcept
        {
            OrientFront.x = forward.x;  OrientTop.x = up.x;
            OrientFront.y = forward.y;  OrientTop.y = up.y;
            OrientFront.z = forward.z;  OrientTop.z = up.z;
        }

        void XM_CALLCONV SetOrientationFromQuaternion(FXMVECTOR quat) noexcept
        {
            const XMVECTOR forward = XMVector3Rotate(g_XMIdentityR2, quat);
            XMStoreFloat3(reinterpret_cast<XMFLOAT3*>(&OrientFront), forward);

            const XMVECTOR up = XMVector3Rotate(g_XMIdentityR1, quat);
            XMStoreFloat3(reinterpret_cast<XMFLOAT3*>(&OrientTop), up);
        }

        // Updates velocity and orientation by tracking changes in position over time.
        void XM_CALLCONV Update(FXMVECTOR newPos, XMVECTOR upDir, float dt) noexcept
        {
            if (dt > 0.f)
            {
                const XMVECTOR lastPos = XMLoadFloat3(reinterpret_cast<const XMFLOAT3*>(&Position));

                XMVECTOR vDelta = XMVectorSubtract(newPos, lastPos);
                const XMVECTOR vt = XMVectorReplicate(dt);
                XMVECTOR v = XMVectorDivide(vDelta, vt);
                XMStoreFloat3(reinterpret_cast<XMFLOAT3*>(&Velocity), v);

                vDelta = XMVector3Normalize(vDelta);
                XMStoreFloat3(reinterpret_cast<XMFLOAT3*>(&OrientFront), vDelta);

                v = XMVector3Cross(upDir, vDelta);
                v = XMVector3Normalize(v);

                v = XMVector3Cross(vDelta, v);
                v = XMVector3Normalize(v);
                XMStoreFloat3(reinterpret_cast<XMFLOAT3*>(&OrientTop), v);

                XMStoreFloat3(reinterpret_cast<XMFLOAT3*>(&Position), newPos);
            }
        }

        void __cdecl SetOmnidirectional() noexcept
        {
            pCone = nullptr;
        }

        // Only used for single-channel emitters.
        HDXTK_EXPORT void __cdecl SetCone(const X3DAUDIO_CONE& emitterCone);

        // Set multi-channel emitter azimuths based on speaker configuration geometry.
        HDXTK_EXPORT void __cdecl EnableDefaultMultiChannel(unsigned int channels, float radius = 1.f);

        // Set default volume, LFE, LPF, and reverb curves.
        HDXTK_EXPORT void __cdecl EnableDefaultCurves() noexcept;
        HDXTK_EXPORT void __cdecl EnableLinearCurves() noexcept;

        void __cdecl EnableInverseSquareCurves() noexcept
        {
            pVolumeCurve = nullptr;
            pLFECurve = nullptr;
            pLPFDirectCurve = nullptr;
            pLPFReverbCurve = nullptr;
            pReverbCurve = nullptr;
        }

        HDXTK_EXPORT bool __cdecl IsValid() const;
    };


    //----------------------------------------------------------------------------------
    class SoundEffectInstance
    {
    public:
        HDXTK_EXPORT SoundEffectInstance(SoundEffectInstance&&) noexcept;
        HDXTK_EXPORT SoundEffectInstance& operator= (SoundEffectInstance&&) noexcept;

        SoundEffectInstance(SoundEffectInstance const&) = delete;
        SoundEffectInstance& operator= (SoundEffectInstance const&) = delete;

        HDXTK_EXPORT virtual ~SoundEffectInstance();

        HDXTK_EXPORT void __cdecl Play(bool loop = false);
        HDXTK_EXPORT void __cdecl Stop(bool immediate = true) noexcept;
        HDXTK_EXPORT void __cdecl Pause() noexcept;
        HDXTK_EXPORT void __cdecl Resume();

        HDXTK_EXPORT void __cdecl SetVolume(float volume);
        HDXTK_EXPORT void __cdecl SetPitch(float pitch);
        HDXTK_EXPORT void __cdecl SetPan(float pan);

        HDXTK_EXPORT void __cdecl Apply3D(const X3DAUDIO_LISTENER& listener, const X3DAUDIO_EMITTER& emitter, bool rhcoords = true);

        HDXTK_EXPORT bool __cdecl IsLooped() const noexcept;

        HDXTK_EXPORT SoundState __cdecl GetState() noexcept;

        HDXTK_EXPORT unsigned int __cdecl GetChannelCount() const noexcept;

        HDXTK_EXPORT IVoiceNotify* __cdecl GetVoiceNotify() const noexcept;

    private:
        // Private implementation.
        class Impl;

        std::unique_ptr<Impl> pImpl;

        // Private constructors
        HDXTK_EXPORT SoundEffectInstance(_In_ AudioEngine* engine, _In_ SoundEffect* effect, SOUND_EFFECT_INSTANCE_FLAGS flags);
        HDXTK_EXPORT SoundEffectInstance(_In_ AudioEngine* engine, _In_ WaveBank* effect, unsigned int index, SOUND_EFFECT_INSTANCE_FLAGS flags);

        friend std::unique_ptr<SoundEffectInstance> __cdecl SoundEffect::CreateInstance(SOUND_EFFECT_INSTANCE_FLAGS);
        friend std::unique_ptr<SoundEffectInstance> __cdecl WaveBank::CreateInstance(unsigned int, SOUND_EFFECT_INSTANCE_FLAGS);
    };


    //----------------------------------------------------------------------------------
    class SoundStreamInstance
    {
    public:
        HDXTK_EXPORT SoundStreamInstance(SoundStreamInstance&&) noexcept;
        HDXTK_EXPORT SoundStreamInstance& operator= (SoundStreamInstance&&) noexcept;

        SoundStreamInstance(SoundStreamInstance const&) = delete;
        SoundStreamInstance& operator= (SoundStreamInstance const&) = delete;

        HDXTK_EXPORT virtual ~SoundStreamInstance();

        HDXTK_EXPORT void __cdecl Play(bool loop = false);
        HDXTK_EXPORT void __cdecl Stop(bool immediate = true) noexcept;
        HDXTK_EXPORT void __cdecl Pause() noexcept;
        HDXTK_EXPORT void __cdecl Resume();

        HDXTK_EXPORT void __cdecl SetVolume(float volume);
        HDXTK_EXPORT void __cdecl SetPitch(float pitch);
        HDXTK_EXPORT void __cdecl SetPan(float pan);

        HDXTK_EXPORT void __cdecl Apply3D(const X3DAUDIO_LISTENER& listener, const X3DAUDIO_EMITTER& emitter, bool rhcoords = true);

        HDXTK_EXPORT bool __cdecl IsLooped() const noexcept;

        HDXTK_EXPORT SoundState __cdecl GetState() noexcept;

        HDXTK_EXPORT unsigned int __cdecl GetChannelCount() const noexcept;

        HDXTK_EXPORT IVoiceNotify* __cdecl GetVoiceNotify() const noexcept;

    private:
        // Private implementation.
        class Impl;

        std::unique_ptr<Impl> pImpl;

        // Private constructors
        SoundStreamInstance(_In_ AudioEngine* engine, _In_ WaveBank* effect, unsigned int index, SOUND_EFFECT_INSTANCE_FLAGS flags);

        friend std::unique_ptr<SoundStreamInstance> __cdecl WaveBank::CreateStreamInstance(unsigned int, SOUND_EFFECT_INSTANCE_FLAGS);
    };


    //----------------------------------------------------------------------------------
    class DynamicSoundEffectInstance
    {
    public:
        HDXTK_EXPORT DynamicSoundEffectInstance(_In_ AudioEngine* engine,
                    _In_ std::function<void __cdecl(DynamicSoundEffectInstance*)> bufferNeeded,
                    int sampleRate, int channels, int sampleBits = 16,
                    SOUND_EFFECT_INSTANCE_FLAGS flags = SoundEffectInstance_Default);

        HDXTK_EXPORT DynamicSoundEffectInstance(DynamicSoundEffectInstance&&) noexcept;
        HDXTK_EXPORT DynamicSoundEffectInstance& operator= (DynamicSoundEffectInstance&&) noexcept;

        DynamicSoundEffectInstance(DynamicSoundEffectInstance const&) = delete;
        DynamicSoundEffectInstance& operator= (DynamicSoundEffectInstance const&) = delete;

        HDXTK_EXPORT virtual ~DynamicSoundEffectInstance();

        HDXTK_EXPORT void __cdecl Play();
        HDXTK_EXPORT void __cdecl Stop(bool immediate = true) noexcept;
        HDXTK_EXPORT void __cdecl Pause() noexcept;
        HDXTK_EXPORT void __cdecl Resume();

        HDXTK_EXPORT void __cdecl SetVolume(float volume);
        HDXTK_EXPORT void __cdecl SetPitch(float pitch);
        HDXTK_EXPORT void __cdecl SetPan(float pan);

        HDXTK_EXPORT void __cdecl Apply3D(const X3DAUDIO_LISTENER& listener, const X3DAUDIO_EMITTER& emitter, bool rhcoords = true);

        HDXTK_EXPORT void __cdecl SubmitBuffer(_In_reads_bytes_(audioBytes) const uint8_t* pAudioData, size_t audioBytes);
        HDXTK_EXPORT void __cdecl SubmitBuffer(_In_reads_bytes_(audioBytes) const uint8_t* pAudioData, uint32_t offset, size_t audioBytes);

        HDXTK_EXPORT SoundState __cdecl GetState() noexcept;

        HDXTK_EXPORT size_t __cdecl GetSampleDuration(size_t bytes) const noexcept;
        // Returns duration in samples of a buffer of a given size

        HDXTK_EXPORT size_t __cdecl GetSampleDurationMS(size_t bytes) const noexcept;
        // Returns duration in milliseconds of a buffer of a given size

        HDXTK_EXPORT size_t __cdecl GetSampleSizeInBytes(uint64_t duration) const noexcept;
        // Returns size of a buffer for a duration given in milliseconds

        HDXTK_EXPORT int __cdecl GetPendingBufferCount() const noexcept;

        HDXTK_EXPORT const WAVEFORMATEX* __cdecl GetFormat() const noexcept;

        HDXTK_EXPORT unsigned int __cdecl GetChannelCount() const noexcept;

    private:
        // Private implementation.
        class Impl;

        std::unique_ptr<Impl> pImpl;
    };

#ifdef __clang__
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wdeprecated-dynamic-exception-spec"
#endif

    DEFINE_ENUM_FLAG_OPERATORS(AUDIO_ENGINE_FLAGS)
    DEFINE_ENUM_FLAG_OPERATORS(SOUND_EFFECT_INSTANCE_FLAGS)

#ifdef __clang__
#pragma clang diagnostic pop
#endif
}
