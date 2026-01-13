#pragma once
#ifndef MEDIAENGINEPLAYER_H_
#define MEDIAENGINEPLAYER_H_

/*
   Copyright 2024-2026 Espen Harlinn

   Licensed under the Apache License, Version 2.0 (the "License");
   you may not use this file except in compliance with the License.
   You may obtain a copy of the License at

       http://www.apache.org/licenses/LICENSE-2.0

   Unless required by applicable law or agreed to in writing, software
   distributed under the License is distributed on an "AS IS" BASIS,
   WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
   See the License for the specific language governing permissions and
   limitations under the License.
*/


#include <HWMediaFoundation.h>
#include <HWDXGI.h>
#include <HWGraphicsD3D11.h>
#include <HWGraphicsD3D12.h>
#include <HWMediaEngine.h>

using namespace Harlinn::Windows;

//-------------------------------------------------------------------------------------
class IMFNotify
{
public:
    virtual ~IMFNotify( ) = default;

    IMFNotify( const IMFNotify& ) = delete;
    IMFNotify& operator=( const IMFNotify& ) = delete;

    IMFNotify( IMFNotify&& ) = delete;
    IMFNotify& operator=( IMFNotify&& ) = delete;

    virtual void OnMediaEngineEvent( uint32_t meEvent, DWORD_PTR param1, DWORD param2 ) = 0;

protected:
    IMFNotify( ) = default;
};


//-------------------------------------------------------------------------------------
class MediaEnginePlayer : public IMFNotify
{
    Graphics::D3D11::Device1 device_;
    Media::MFMediaEngine mediaEngine_;
    Media::MFMediaEngineEx engineEx_;

    MFARGB  bkgColor_{};

    bool isPlaying_ = false;
    bool isInfoReady_ = false;
    bool isFinished_ = false;

public:
    MediaEnginePlayer( ) noexcept;
    ~MediaEnginePlayer( );

    MediaEnginePlayer( const MediaEnginePlayer& ) = delete;
    MediaEnginePlayer& operator=( const MediaEnginePlayer& ) = delete;

    MediaEnginePlayer( MediaEnginePlayer&& ) = default;
    MediaEnginePlayer& operator=( MediaEnginePlayer&& ) = default;

    void Initialize( const Graphics::DXGI::Factory4& dxgiFactory, Graphics::D3D12::Device& device, Graphics::DXGI::Format format );
    void Shutdown( );

    void Play( );
    void Pause( );
    void SetLoop( bool loop );
    void SetMuted( bool muted );

    void SetSource( _In_z_ const wchar_t* sourceUri );

    bool TransferFrame( HANDLE textureHandle, MFVideoNormalizedRect rect, RECT rcTarget );

    // Callbacks
    void OnMediaEngineEvent( uint32_t meEvent, DWORD_PTR param1, DWORD param2 ) override;

    // Properties
    void GetNativeVideoSize( uint32_t& cx, uint32_t& cy );
    bool IsPlaying( ) const { return isPlaying_; }
    bool IsInfoReady( ) const { return isInfoReady_; }
    bool IsFinished( ) const { return isFinished_; }

private:
    
};

#endif
