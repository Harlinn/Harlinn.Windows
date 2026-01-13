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

#include "MediaEnginePlayer.h"
#include <HCCComImpl.h>

namespace
{
    template<typename DerivedT>
    class MediaEngineNotifyImpl : public Com::ObjectBase<DerivedT,IMFMediaEngineNotify>
    {
        IMFNotify* callback_ = nullptr;
    public:
        MediaEngineNotifyImpl( IMFNotify* callback ) noexcept
            : callback_( callback )
        { }

        HRESULT __stdcall EventNotify( DWORD meEvent, DWORD_PTR param1, DWORD param2 )
        {
            HRESULT result = S_OK;
            try
            {
                callback_->OnMediaEngineEvent( meEvent, param1, param2 );
            }
            catch ( ... )
            {
                result = E_UNEXPECTED;
            }
            if ( meEvent == MF_MEDIA_ENGINE_EVENT_NOTIFYSTABLESTATE )
            {
                SetEvent( reinterpret_cast< HANDLE >( param1 ) );
            }
            return result;
        }
    };

    class MediaEngineNotify : public Com::HeapObject<MediaEngineNotifyImpl<MediaEngineNotify>>
    {
    public:
        using Base = Com::HeapObject<MediaEngineNotifyImpl<MediaEngineNotify>>;
        MediaEngineNotify( IMFNotify* callback ) noexcept
            : Base( callback )
        { }
    };
}


MediaEnginePlayer::MediaEnginePlayer( ) noexcept 
{
}

MediaEnginePlayer::~MediaEnginePlayer( )
{
    Shutdown( );
}

void MediaEnginePlayer::Initialize( const Graphics::DXGI::Factory4& dxgiFactory, Graphics::D3D12::Device& device, Graphics::DXGI::Format format )
{
    // Create our own device to avoid threading issues
    auto adapterLuid = device.GetAdapterLuid( );
    auto adapter = dxgiFactory.FindAdapter( adapterLuid );
    static const D3D_FEATURE_LEVEL s_featureLevels[ ] =
    {
        D3D_FEATURE_LEVEL_11_1,
        D3D_FEATURE_LEVEL_11_0,
    };

    D3D12_FEATURE_DATA_FEATURE_LEVELS featLevels =
    {
        _countof( s_featureLevels ), s_featureLevels, D3D_FEATURE_LEVEL_11_0
    };


    D3D_FEATURE_LEVEL fLevel = D3D_FEATURE_LEVEL_11_0;
    if ( device.CheckFeatureSupport( featLevels ) == false )
    {
        fLevel = featLevels.MaxSupportedFeatureLevel;
    }

    auto baseDevice = Graphics::D3D11::CreateDevice( adapter, D3D_DRIVER_TYPE_UNKNOWN, D3D11_CREATE_DEVICE_VIDEO_SUPPORT | D3D11_CREATE_DEVICE_BGRA_SUPPORT, &fLevel, 1 );
    auto multithreaded = baseDevice.As<Graphics::D3D10::Multithread>( );
    multithreaded.SetMultithreadProtected( true );
    device_ = baseDevice;

    // Setup Media Engine
    UINT resetToken;
    auto dxgiManager = Media::MFDXGIDeviceManager::Create( &resetToken );
    dxgiManager.ResetDevice( device_, resetToken );

    Media::MFMediaEngineNotify mediaEngineNotify( new MediaEngineNotify( this ) );

    auto attributes = Media::MFAttributes::Create( 3 );
    attributes.SetUnknown( MF_MEDIA_ENGINE_DXGI_MANAGER, dxgiManager );
    attributes.SetUnknown( MF_MEDIA_ENGINE_CALLBACK, mediaEngineNotify );
    attributes.SetUINT32( MF_MEDIA_ENGINE_VIDEO_OUTPUT_FORMAT, format );
    
    // Create MediaEngine.
    auto mfFactory = Media::MFMediaEngineClassFactory::Create( );
    mediaEngine_ = mfFactory.CreateInstance( 0, attributes );
    // Create MediaEngineEx
    engineEx_ = mediaEngine_.As<Media::MFMediaEngineEx>( );
}


void MediaEnginePlayer::Shutdown( )
{
    if ( mediaEngine_ )
    {
        mediaEngine_.Shutdown( );
    }
}

void MediaEnginePlayer::Play( )
{
    if ( isPlaying_ == false && mediaEngine_ )
    {
        mediaEngine_.Play( );
        isPlaying_ = true;
        isFinished_ = false;
    }
}

void MediaEnginePlayer::SetLoop( bool loop )
{
    if ( mediaEngine_ )
    {
        mediaEngine_.SetLoop( loop );
    }
}

void MediaEnginePlayer::Pause( )
{
    if ( isPlaying_ && isFinished_ == false && mediaEngine_ )
    {
        mediaEngine_.Pause( );
        isPlaying_ = false;
    }
}

void MediaEnginePlayer::SetMuted( bool muted )
{
    if ( mediaEngine_ )
    {
        mediaEngine_.SetMuted( muted );
    }
}

void MediaEnginePlayer::SetSource( _In_z_ const wchar_t* sourceUri )
{
    
    isPlaying_ = false;
    isInfoReady_ = false;
    isFinished_ = false;

    if ( mediaEngine_ )
    {
        SysString url( sourceUri );
        mediaEngine_.SetSource( url.data() );
    }
}

bool MediaEnginePlayer::TransferFrame( HANDLE textureHandle, MFVideoNormalizedRect rect, RECT rcTarget )
{
    if ( mediaEngine_ && isPlaying_ )
    {
        LONGLONG pts;
        if ( mediaEngine_.OnVideoStreamTick( &pts ) )
        {
            auto mediaTexture = device_.OpenSharedResource<Graphics::D3D11::Texture2D>( textureHandle );
            mediaEngine_.TransferVideoFrame( mediaTexture, &rect, &rcTarget, &bkgColor_ );
            return true;
        }
    }

    return false;
}

void MediaEnginePlayer::OnMediaEngineEvent( uint32_t meEvent, DWORD_PTR param1, DWORD param2 )
{
    switch ( meEvent )
    {
        case MF_MEDIA_ENGINE_EVENT_LOADEDMETADATA:
            isInfoReady_ = true;
            break;

        case MF_MEDIA_ENGINE_EVENT_CANPLAY:

            // Here we auto-play when ready...
            Play( );

            break;

        case MF_MEDIA_ENGINE_EVENT_PLAY:
            break;

        case MF_MEDIA_ENGINE_EVENT_PAUSE:
            break;

        case MF_MEDIA_ENGINE_EVENT_ENDED:
            isFinished_ = true;
            break;

        case MF_MEDIA_ENGINE_EVENT_TIMEUPDATE:
            break;

        case MF_MEDIA_ENGINE_EVENT_ERROR:
#ifdef _DEBUG
            if ( mediaEngine_ )
            {
                auto error = mediaEngine_.GetError( );
                auto errorCode = error.GetErrorCode( );
                PrintLn("ERROR: Media Foundation Event Error {}", errorCode );
            }
#endif
            break;
    }
}

void MediaEnginePlayer::GetNativeVideoSize( uint32_t& cx, uint32_t& cy )
{
    cx = cy = 0;
    if ( mediaEngine_ && isInfoReady_ )
    {
        DWORD x, y;
        mediaEngine_.GetNativeVideoSize( &x, &y );
        cx = x;
        cy = y;
    }
}


