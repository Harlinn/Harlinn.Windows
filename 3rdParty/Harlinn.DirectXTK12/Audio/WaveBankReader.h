//--------------------------------------------------------------------------------------
// File: WaveBankReader.h
//
// Functions for loading audio data from Wave Banks
//
// Copyright (c) Microsoft Corporation.
// Licensed under the MIT License.
//
// http://go.microsoft.com/fwlink/?LinkId=248929
// http://go.microsoft.com/fwlink/?LinkID=615561
//-------------------------------------------------------------------------------------

#pragma once

#include <HDirectXTK12Def.h>

#include <objbase.h>
#include <mmreg.h>

#include <cstdint>
#include <memory>


namespace DirectX
{
    class WaveBankReader
    {
    public:
        HDXTK12_EXPORT WaveBankReader() noexcept(false);

        WaveBankReader(WaveBankReader&&) = default;
        WaveBankReader& operator= (WaveBankReader&&) = default;

        WaveBankReader(WaveBankReader const&) = delete;
        WaveBankReader& operator= (WaveBankReader const&) = delete;

        HDXTK12_EXPORT ~WaveBankReader();

        HDXTK12_EXPORT HRESULT Open(_In_z_ const wchar_t* szFileName) noexcept;

        HDXTK12_EXPORT uint32_t Find(_In_z_ const char* name) const;

        HDXTK12_EXPORT bool IsPrepared() noexcept;
        HDXTK12_EXPORT void WaitOnPrepare() noexcept;

        HDXTK12_EXPORT bool HasNames() const noexcept;
        HDXTK12_EXPORT bool IsStreamingBank() const noexcept;

    #if (defined(_XBOX_ONE) && defined(_TITLE)) || defined(_GAMING_XBOX)
        HDXTK12_EXPORT bool HasXMA() const noexcept;
    #endif

        HDXTK12_EXPORT const char* BankName() const noexcept;

        HDXTK12_EXPORT uint32_t Count() const noexcept;

        HDXTK12_EXPORT uint32_t BankAudioSize() const noexcept;

        HDXTK12_EXPORT HRESULT GetFormat(_In_ uint32_t index, _Out_writes_bytes_(maxsize) WAVEFORMATEX* pFormat, _In_ size_t maxsize) const noexcept;

        HDXTK12_EXPORT HRESULT GetWaveData(_In_ uint32_t index, _Outptr_ const uint8_t** pData, _Out_ uint32_t& dataSize) const noexcept;

        HDXTK12_EXPORT HRESULT GetSeekTable(_In_ uint32_t index, _Out_ const uint32_t** pData, _Out_ uint32_t& dataCount, _Out_ uint32_t& tag) const noexcept;

        HDXTK12_EXPORT HANDLE GetAsyncHandle() const noexcept;

        HDXTK12_EXPORT uint32_t GetWaveAlignment() const noexcept;

        struct Metadata
        {
            uint32_t    duration;
            uint32_t    loopStart;
            uint32_t    loopLength;
            uint32_t    offsetBytes;
            uint32_t    lengthBytes;
        };
        HDXTK12_EXPORT HRESULT GetMetadata(_In_ uint32_t index, _Out_ Metadata& metadata) const noexcept;

    private:
        // Private implementation.
        class Impl;

        std::unique_ptr<Impl> pImpl;
    };
}
