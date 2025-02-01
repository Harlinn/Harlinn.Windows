#pragma once
#ifndef HARLINN_WINDOWS_HWMEDIAENGINE_H_
#define HARLINN_WINDOWS_HWMEDIAENGINE_H_

/*
   Copyright 2024-2025 Espen Harlinn

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

#include <HCCCom.h>
#include <HWMFObjects.h>

namespace Harlinn::Windows::Media
{
    class MFMediaError : public Unknown
    {
    public:
        HCC_COM_STANDARD_METHODS_IMPL( MFMediaError, Unknown, IMFMediaError, IUnknown )
    public:
        USHORT GetErrorCode( ) const
        {
            InterfaceType* pInterface = GetInterface( );
            return pInterface->GetErrorCode( );
        }

        HRESULT GetExtendedErrorCode( ) const
        {
            InterfaceType* pInterface = GetInterface( );
            return pInterface->GetExtendedErrorCode( );
        }

        void SetErrorCode( _In_  MF_MEDIA_ENGINE_ERR error ) const
        {
            InterfaceType* pInterface = GetInterface( );
            auto hr = pInterface->SetErrorCode( error );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

        void SetExtendedErrorCode( _In_  HRESULT error ) const
        {
            InterfaceType* pInterface = GetInterface( );
            auto hr = pInterface->SetExtendedErrorCode( error );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }
    };


    class MFMediaTimeRange : public Unknown
    {
    public:
        HCC_COM_STANDARD_METHODS_IMPL( MFMediaTimeRange, Unknown, IMFMediaTimeRange, IUnknown )
    public:
        DWORD GetLength( ) const
        {
            InterfaceType* pInterface = GetInterface( );
            return pInterface->GetLength( );
        }

        void GetStart( _In_  DWORD index, _Out_  double* pStart ) const
        {
            InterfaceType* pInterface = GetInterface( );
            auto hr =  pInterface->GetStart( index, pStart );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }
        double GetStart( _In_  DWORD index ) const
        {
            double result = 0.;
            GetStart( index, &result );
            return result;
        }



        void GetEnd( _In_  DWORD index, _Out_  double* pEnd ) const
        {
            InterfaceType* pInterface = GetInterface( );
            auto hr = pInterface->GetEnd( index, pEnd );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

        double GetEnd( _In_  DWORD index ) const
        {
            double result = 0.;
            GetEnd( index, &result );
            return result;
        }

        bool ContainsTime( _In_  double time ) const
        {
            InterfaceType* pInterface = GetInterface( );
            return pInterface->ContainsTime( time ) != FALSE;
        }

        void AddRange( _In_  double startTime, _In_  double endTime ) const
        {
            InterfaceType* pInterface = GetInterface( );
            auto hr = pInterface->AddRange( startTime, endTime );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

        void Clear( ) const
        {
            InterfaceType* pInterface = GetInterface( );
            auto hr = pInterface->Clear( );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }
    };


    class MFMediaEngineNotify : public Unknown
    {
    public:
        HCC_COM_STANDARD_METHODS_IMPL( MFMediaEngineNotify, Unknown, IMFMediaEngineNotify, IUnknown )
    public:
        void EventNotify( _In_  DWORD event, _In_  DWORD_PTR param1, _In_  DWORD param2 ) const
        {
            InterfaceType* pInterface = GetInterface( );
            auto hr = pInterface->EventNotify( event, param1, param2 );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }
    };


    class MFMediaEngineSrcElements : public Unknown
    {
    public:
        HCC_COM_STANDARD_METHODS_IMPL( MFMediaEngineSrcElements, Unknown, IMFMediaEngineSrcElements, IUnknown )
    public:
        DWORD GetLength( ) const
        {
            InterfaceType* pInterface = GetInterface( );
            return pInterface->GetLength( );
        }

        void GetURL( _In_  DWORD index, _Out_  BSTR* pURL ) const
        {
            InterfaceType* pInterface = GetInterface( );
            auto hr = pInterface->GetURL( index, pURL );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

        void GetType( _In_  DWORD index, _Out_  BSTR* pType ) const
        {
            InterfaceType* pInterface = GetInterface( );
            auto hr = pInterface->GetType( index, pType );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

        void GetMedia( _In_  DWORD index, _Out_  BSTR* pMedia ) const
        {
            InterfaceType* pInterface = GetInterface( );
            auto hr = pInterface->GetMedia( index, pMedia );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

        void AddElement( _In_opt_  BSTR pURL, _In_opt_  BSTR pType, _In_opt_  BSTR pMedia ) const
        {
            InterfaceType* pInterface = GetInterface( );
            auto hr = pInterface->AddElement( pURL, pType, pMedia );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

        void RemoveAllElements( ) const
        {
            InterfaceType* pInterface = GetInterface( );
            auto hr = pInterface->RemoveAllElements( );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }
    };

    class MFMediaEngine : public Unknown
    {
    public:
        HCC_COM_STANDARD_METHODS_IMPL( MFMediaEngine, Unknown, IMFMediaEngine, IUnknown )
    public:
        void GetError( _Outptr_  IMFMediaError** error ) const
        {
            InterfaceType* pInterface = GetInterface( );
            auto hr = pInterface->GetError( error );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

        MFMediaError GetError( ) const
        {
            MFMediaError::InterfaceType* itf = nullptr;
            GetError( &itf );
            return MFMediaError( itf );
        }

        void SetErrorCode( _In_  MF_MEDIA_ENGINE_ERR error ) const
        {
            InterfaceType* pInterface = GetInterface( );
            auto hr = pInterface->SetErrorCode( error );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

        void SetSourceElements( _In_  IMFMediaEngineSrcElements* pSrcElements ) const
        {
            InterfaceType* pInterface = GetInterface( );
            auto hr = pInterface->SetSourceElements( pSrcElements );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

        void SetSourceElements( const  MFMediaEngineSrcElements& srcElements ) const
        {
            SetSourceElements( srcElements.GetInterfacePointer<IMFMediaEngineSrcElements>( ) );
        }

        void SetSource( _In_  BSTR pUrl ) const
        {
            InterfaceType* pInterface = GetInterface( );
            auto hr = pInterface->SetSource( pUrl );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

        void GetCurrentSource( _Out_  BSTR* ppUrl ) const
        {
            InterfaceType* pInterface = GetInterface( );
            auto hr = pInterface->GetCurrentSource( ppUrl );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

        USHORT GetNetworkState( ) const
        {
            InterfaceType* pInterface = GetInterface( );
            return pInterface->GetNetworkState( );
        }

        MF_MEDIA_ENGINE_PRELOAD GetPreload( ) const
        {
            InterfaceType* pInterface = GetInterface( );
            return pInterface->GetPreload( );
        }

        void SetPreload( _In_  MF_MEDIA_ENGINE_PRELOAD preload ) const
        {
            InterfaceType* pInterface = GetInterface( );
            auto hr = pInterface->SetPreload( preload );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

        void GetBuffered( _Outptr_  IMFMediaTimeRange** buffered ) const
        {
            InterfaceType* pInterface = GetInterface( );
            auto hr = pInterface->GetBuffered( buffered );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

        MFMediaTimeRange GetBuffered( ) const
        {
            IMFMediaTimeRange* itf = nullptr;
            GetBuffered( &itf );
            return MFMediaTimeRange( itf );
        }


        void Load( ) const
        {
            InterfaceType* pInterface = GetInterface( );
            auto hr = pInterface->Load( );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

        void CanPlayType( _In_  BSTR type, _Out_  MF_MEDIA_ENGINE_CANPLAY* answer ) const
        {
            InterfaceType* pInterface = GetInterface( );
            auto hr = pInterface->CanPlayType( type, answer );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

        MF_MEDIA_ENGINE_CANPLAY CanPlayType( _In_  BSTR type ) const
        {
            MF_MEDIA_ENGINE_CANPLAY result{};
            CanPlayType( type, &result );
            return result;
        }

        USHORT GetReadyState( ) const
        {
            InterfaceType* pInterface = GetInterface( );
            return pInterface->GetReadyState( );
        }

        bool IsSeeking( ) const
        {
            InterfaceType* pInterface = GetInterface( );
            return pInterface->IsSeeking( ) != FALSE;
        }

        double GetCurrentTime( ) const
        {
            InterfaceType* pInterface = GetInterface( );
            return pInterface->GetCurrentTime( );
        }

        void SetCurrentTime( _In_  double seekTime ) const
        {
            InterfaceType* pInterface = GetInterface( );
            auto hr = pInterface->SetCurrentTime( seekTime );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

        double GetStartTime( ) const
        {
            InterfaceType* pInterface = GetInterface( );
            return pInterface->GetStartTime( );
        }

        double GetDuration( ) const
        {
            InterfaceType* pInterface = GetInterface( );
            return pInterface->GetDuration( );
        }

        bool IsPaused( ) const
        {
            InterfaceType* pInterface = GetInterface( );
            return pInterface->IsPaused( ) != FALSE;
        }

        double GetDefaultPlaybackRate( ) const
        {
            InterfaceType* pInterface = GetInterface( );
            return pInterface->GetDefaultPlaybackRate( );
        }

        void SetDefaultPlaybackRate( _In_  double rate ) const
        {
            InterfaceType* pInterface = GetInterface( );
            auto hr = pInterface->SetDefaultPlaybackRate( rate );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

        double GetPlaybackRate( ) const
        {
            InterfaceType* pInterface = GetInterface( );
            return pInterface->GetPlaybackRate( );
        }

        void SetPlaybackRate( _In_  double rate ) const
        {
            InterfaceType* pInterface = GetInterface( );
            auto hr = pInterface->SetPlaybackRate( rate );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

        void GetPlayed( _Outptr_  IMFMediaTimeRange** played ) const
        {
            InterfaceType* pInterface = GetInterface( );
            auto hr = pInterface->GetPlayed( played );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }
        MFMediaTimeRange GetPlayed( ) const
        {
            IMFMediaTimeRange* itf = nullptr;
            GetPlayed( &itf );
            return MFMediaTimeRange( itf );
        }


        void GetSeekable( _Outptr_  IMFMediaTimeRange** seekable ) const
        {
            InterfaceType* pInterface = GetInterface( );
            auto hr = pInterface->GetPlayed( seekable );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }
        MFMediaTimeRange GetSeekable( ) const
        {
            IMFMediaTimeRange* itf = nullptr;
            GetSeekable( &itf );
            return MFMediaTimeRange( itf );
        }


        bool IsEnded( ) const
        {
            InterfaceType* pInterface = GetInterface( );
            return pInterface->IsEnded( ) != FALSE;
        }

        bool GetAutoPlay( ) const
        {
            InterfaceType* pInterface = GetInterface( );
            return pInterface->GetAutoPlay( ) != FALSE;
        }

        void SetAutoPlay( _In_  BOOL autoPlay ) const
        {
            InterfaceType* pInterface = GetInterface( );
            auto hr = pInterface->SetAutoPlay( autoPlay );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

        bool GetLoop( ) const
        {
            InterfaceType* pInterface = GetInterface( );
            return pInterface->GetLoop( ) != FALSE;
        }

        void SetLoop( _In_  BOOL loop ) const
        {
            InterfaceType* pInterface = GetInterface( );
            auto hr = pInterface->SetLoop( loop );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

        void Play( ) const
        {
            InterfaceType* pInterface = GetInterface( );
            auto hr = pInterface->Play( );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

        void Pause( ) const
        {
            InterfaceType* pInterface = GetInterface( );
            auto hr = pInterface->Pause( );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

        bool GetMuted( ) const
        {
            InterfaceType* pInterface = GetInterface( );
            return pInterface->GetMuted( ) != FALSE;
        }

        void SetMuted( _In_  BOOL muted ) const
        {
            InterfaceType* pInterface = GetInterface( );
            auto hr = pInterface->SetMuted( muted );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

        double GetVolume( ) const
        {
            InterfaceType* pInterface = GetInterface( );
            return pInterface->GetVolume( );
        }

        void SetVolume( _In_  double volume ) const
        {
            InterfaceType* pInterface = GetInterface( );
            auto hr = pInterface->SetVolume( volume );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

        bool HasVideo( ) const
        {
            InterfaceType* pInterface = GetInterface( );
            return pInterface->HasVideo( ) != FALSE;
        }

        bool HasAudio( ) const
        {
            InterfaceType* pInterface = GetInterface( );
            return pInterface->HasAudio( ) != FALSE;
        }

        void GetNativeVideoSize( _Out_opt_  DWORD* cx, _Out_opt_  DWORD* cy ) const
        {
            InterfaceType* pInterface = GetInterface( );
            auto hr = pInterface->GetNativeVideoSize( cx, cy );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }
        Size GetNativeVideoSize( ) const
        {
            DWORD x = 0, y = 0;
            GetNativeVideoSize( &x, &y );
            return Size( x, y );
        }

        void GetVideoAspectRatio( _Out_opt_  DWORD* cx, _Out_opt_  DWORD* cy ) const
        {
            InterfaceType* pInterface = GetInterface( );
            auto hr = pInterface->GetVideoAspectRatio( cx, cy );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

        Size GetVideoAspectRatio( ) const
        {
            DWORD x = 0, y = 0;
            GetVideoAspectRatio( &x, &y );
            return Size( x, y );
        }


        void Shutdown( ) const
        {
            InterfaceType* pInterface = GetInterface( );
            auto hr = pInterface->Shutdown( );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

        void TransferVideoFrame( _In_  IUnknown* destinationSurface, _In_opt_  const MFVideoNormalizedRect* pSrc, _In_  const RECT* pDst, _In_opt_  const MFARGB* pBorderClr ) const
        {
            InterfaceType* pInterface = GetInterface( );
            auto hr = pInterface->TransferVideoFrame( destinationSurface, pSrc, pDst, pBorderClr );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

        bool OnVideoStreamTick( _Out_  LONGLONG* pPts ) const
        {
            InterfaceType* pInterface = GetInterface( );
            auto hr = pInterface->OnVideoStreamTick( pPts );
            if ( hr == S_FALSE )
            {
                return false;
            }
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
            return hr == S_OK;
        }
    };


    class MFMediaEngineEx : public MFMediaEngine
    {
    public:
        HCC_COM_STANDARD_METHODS_IMPL( MFMediaEngineEx, MFMediaEngine, IMFMediaEngineEx, IMFMediaEngine )
    public:

        void SetSourceFromByteStream( _In_  IMFByteStream* pByteStream, _In_  BSTR pURL ) const
        {
            InterfaceType* pInterface = GetInterface( );
            auto hr = pInterface->SetSourceFromByteStream( pByteStream, pURL );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

        void GetStatistics( _In_  MF_MEDIA_ENGINE_STATISTIC StatisticID, _Out_  PROPVARIANT* pStatistic ) const
        {
            InterfaceType* pInterface = GetInterface( );
            auto hr = pInterface->GetStatistics( StatisticID, pStatistic );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

        void UpdateVideoStream( _In_opt_  const MFVideoNormalizedRect* pSrc, _In_opt_  const RECT* pDst, _In_opt_  const MFARGB* pBorderClr ) const
        {
            InterfaceType* pInterface = GetInterface( );
            auto hr = pInterface->UpdateVideoStream( pSrc, pDst, pBorderClr );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

        double GetBalance( ) const
        {
            InterfaceType* pInterface = GetInterface( );
            return pInterface->GetBalance( );
        }

        void SetBalance( _In_  double balance ) const
        {
            InterfaceType* pInterface = GetInterface( );
            auto hr = pInterface->SetBalance( balance );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

        bool IsPlaybackRateSupported( _In_  double rate ) const
        {
            InterfaceType* pInterface = GetInterface( );
            return pInterface->IsPlaybackRateSupported( rate ) != FALSE;
        }

        void FrameStep( _In_  BOOL Forward ) const
        {
            InterfaceType* pInterface = GetInterface( );
            auto hr = pInterface->FrameStep( Forward );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

        void GetResourceCharacteristics( _Out_  DWORD* pCharacteristics ) const
        {
            InterfaceType* pInterface = GetInterface( );
            auto hr = pInterface->GetResourceCharacteristics( pCharacteristics );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

        void GetPresentationAttribute( _In_  REFGUID guidMFAttribute, _Out_  PROPVARIANT* pvValue ) const
        {
            InterfaceType* pInterface = GetInterface( );
            auto hr = pInterface->GetPresentationAttribute( guidMFAttribute, pvValue );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

        void GetNumberOfStreams( _Out_  DWORD* pdwStreamCount ) const
        {
            InterfaceType* pInterface = GetInterface( );
            auto hr = pInterface->GetNumberOfStreams( pdwStreamCount );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

        void GetStreamAttribute( _In_  DWORD dwStreamIndex, _In_  REFGUID guidMFAttribute, _Out_  PROPVARIANT* pvValue ) const
        {
            InterfaceType* pInterface = GetInterface( );
            auto hr = pInterface->GetStreamAttribute( dwStreamIndex, guidMFAttribute, pvValue );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

        void GetStreamSelection( _In_  DWORD dwStreamIndex, _Out_  BOOL* pEnabled ) const
        {
            InterfaceType* pInterface = GetInterface( );
            auto hr = pInterface->GetStreamSelection( dwStreamIndex, pEnabled );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

        void SetStreamSelection( _In_  DWORD dwStreamIndex, _In_  BOOL Enabled ) const
        {
            InterfaceType* pInterface = GetInterface( );
            auto hr = pInterface->SetStreamSelection( dwStreamIndex, Enabled );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

        void ApplyStreamSelections( ) const
        {
            InterfaceType* pInterface = GetInterface( );
            auto hr = pInterface->ApplyStreamSelections( );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

        void IsProtected( _Out_  BOOL* pProtected ) const
        {
            InterfaceType* pInterface = GetInterface( );
            auto hr = pInterface->IsProtected( pProtected );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

        void InsertVideoEffect( _In_  IUnknown* pEffect, _In_  BOOL fOptional ) const
        {
            InterfaceType* pInterface = GetInterface( );
            auto hr = pInterface->InsertVideoEffect( pEffect, fOptional );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

        void InsertAudioEffect( _In_  IUnknown* pEffect, _In_  BOOL fOptional ) const
        {
            InterfaceType* pInterface = GetInterface( );
            auto hr = pInterface->InsertAudioEffect( pEffect, fOptional );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

        void RemoveAllEffects( ) const
        {
            InterfaceType* pInterface = GetInterface( );
            auto hr = pInterface->RemoveAllEffects( );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

        void SetTimelineMarkerTimer( _In_  double timeToFire ) const
        {
            InterfaceType* pInterface = GetInterface( );
            auto hr = pInterface->SetTimelineMarkerTimer( timeToFire );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

        void GetTimelineMarkerTimer( _Out_  double* pTimeToFire ) const
        {
            InterfaceType* pInterface = GetInterface( );
            auto hr = pInterface->GetTimelineMarkerTimer( pTimeToFire );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

        void CancelTimelineMarkerTimer( ) const
        {
            InterfaceType* pInterface = GetInterface( );
            auto hr = pInterface->CancelTimelineMarkerTimer( );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

        bool IsStereo3D( ) const
        {
            InterfaceType* pInterface = GetInterface( );
            return pInterface->IsStereo3D( ) != FALSE;
        }

        void GetStereo3DFramePackingMode( _Out_  MF_MEDIA_ENGINE_S3D_PACKING_MODE* packMode ) const
        {
            InterfaceType* pInterface = GetInterface( );
            auto hr = pInterface->GetStereo3DFramePackingMode( packMode );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

        void SetStereo3DFramePackingMode( _In_  MF_MEDIA_ENGINE_S3D_PACKING_MODE packMode ) const
        {
            InterfaceType* pInterface = GetInterface( );
            auto hr = pInterface->SetStereo3DFramePackingMode( packMode );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

        void GetStereo3DRenderMode( _Out_  MF3DVideoOutputType* outputType ) const
        {
            InterfaceType* pInterface = GetInterface( );
            auto hr = pInterface->GetStereo3DRenderMode( outputType );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

        void SetStereo3DRenderMode( _In_  MF3DVideoOutputType outputType ) const
        {
            InterfaceType* pInterface = GetInterface( );
            auto hr = pInterface->SetStereo3DRenderMode( outputType );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

        void EnableWindowlessSwapchainMode( _In_  BOOL fEnable ) const
        {
            InterfaceType* pInterface = GetInterface( );
            auto hr = pInterface->EnableWindowlessSwapchainMode( fEnable );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

        void GetVideoSwapchainHandle( _Out_  HANDLE* phSwapchain ) const
        {
            InterfaceType* pInterface = GetInterface( );
            auto hr = pInterface->GetVideoSwapchainHandle( phSwapchain );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

        void EnableHorizontalMirrorMode( _In_  BOOL fEnable ) const
        {
            InterfaceType* pInterface = GetInterface( );
            auto hr = pInterface->EnableHorizontalMirrorMode( fEnable );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

        void GetAudioStreamCategory( _Out_  UINT32* pCategory ) const
        {
            InterfaceType* pInterface = GetInterface( );
            auto hr = pInterface->GetAudioStreamCategory( pCategory );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

        void SetAudioStreamCategory( _In_  UINT32 category ) const
        {
            InterfaceType* pInterface = GetInterface( );
            auto hr = pInterface->SetAudioStreamCategory( category );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

        void GetAudioEndpointRole( _Out_  UINT32* pRole ) const
        {
            InterfaceType* pInterface = GetInterface( );
            auto hr = pInterface->GetAudioEndpointRole( pRole );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

        void SetAudioEndpointRole( _In_  UINT32 role ) const
        {
            InterfaceType* pInterface = GetInterface( );
            auto hr = pInterface->SetAudioEndpointRole( role );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

        void GetRealTimeMode( _Out_  BOOL* pfEnabled ) const
        {
            InterfaceType* pInterface = GetInterface( );
            auto hr = pInterface->GetRealTimeMode( pfEnabled );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

        void SetRealTimeMode( _In_  BOOL fEnable ) const
        {
            InterfaceType* pInterface = GetInterface( );
            auto hr = pInterface->SetRealTimeMode( fEnable );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

        void SetCurrentTimeEx( _In_  double seekTime, _In_  MF_MEDIA_ENGINE_SEEK_MODE seekMode ) const
        {
            InterfaceType* pInterface = GetInterface( );
            auto hr = pInterface->SetCurrentTimeEx( seekTime, seekMode );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

        void EnableTimeUpdateTimer( _In_  BOOL fEnableTimer ) const
        {
            InterfaceType* pInterface = GetInterface( );
            auto hr = pInterface->EnableTimeUpdateTimer( fEnableTimer );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }
    };

    class MFMediaEngineAudioEndpointId : public Unknown
    {
    public:
        HCC_COM_STANDARD_METHODS_IMPL( MFMediaEngineAudioEndpointId, Unknown, IMFMediaEngineAudioEndpointId, IUnknown )
    public:
        void SetAudioEndpointId( _In_opt_  LPCWSTR pszEndpointId ) const
        {
            InterfaceType* pInterface = GetInterface( );
            auto hr = pInterface->SetAudioEndpointId( pszEndpointId );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

        void GetAudioEndpointId( _Outptr_  LPWSTR* ppszEndpointId ) const
        {
            InterfaceType* pInterface = GetInterface( );
            auto hr = pInterface->GetAudioEndpointId( ppszEndpointId );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }
    };

    class MFMediaEngineExtension : public Unknown
    {
    public:
        HCC_COM_STANDARD_METHODS_IMPL( MFMediaEngineExtension, Unknown, IMFMediaEngineExtension, IUnknown )
    public:
        void CanPlayType( _In_  BOOL AudioOnly, _In_  BSTR MimeType, _Out_  MF_MEDIA_ENGINE_CANPLAY* pAnswer ) const
        {
            InterfaceType* pInterface = GetInterface( );
            auto hr = pInterface->CanPlayType( AudioOnly, MimeType, pAnswer );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

        void BeginCreateObject( _In_  BSTR bstrURL, _In_opt_  IMFByteStream* pByteStream, _In_  MF_OBJECT_TYPE type, _Outptr_  IUnknown** ppIUnknownCancelCookie, _In_  IMFAsyncCallback* pCallback, _In_opt_  IUnknown* punkState ) const
        {
            InterfaceType* pInterface = GetInterface( );
            auto hr = pInterface->BeginCreateObject( bstrURL, pByteStream, type, ppIUnknownCancelCookie, pCallback, punkState );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

        void CancelObjectCreation( _In_  IUnknown* pIUnknownCancelCookie ) const
        {
            InterfaceType* pInterface = GetInterface( );
            auto hr = pInterface->CancelObjectCreation( pIUnknownCancelCookie );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

        void EndCreateObject( _In_  IMFAsyncResult* pResult, _Outptr_  IUnknown** ppObject ) const
        {
            InterfaceType* pInterface = GetInterface( );
            auto hr = pInterface->EndCreateObject( pResult, ppObject );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }
    };

    class MFMediaEngineProtectedContent : public Unknown
    {
    public:
        HCC_COM_STANDARD_METHODS_IMPL( MFMediaEngineProtectedContent, Unknown, IMFMediaEngineProtectedContent, IUnknown )
    public:
        void ShareResources( _In_  IUnknown* pUnkDeviceContext ) const
        {
            InterfaceType* pInterface = GetInterface( );
            auto hr = pInterface->ShareResources( pUnkDeviceContext );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

        void GetRequiredProtections( _Out_  DWORD* pFrameProtectionFlags ) const
        {
            InterfaceType* pInterface = GetInterface( );
            auto hr = pInterface->GetRequiredProtections( pFrameProtectionFlags );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

        void SetOPMWindow( _In_  HWND hwnd ) const
        {
            InterfaceType* pInterface = GetInterface( );
            auto hr = pInterface->SetOPMWindow( hwnd );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

        void TransferVideoFrame( _In_  IUnknown* pDstSurf, _In_opt_  const MFVideoNormalizedRect* pSrc, _In_  const RECT* pDst, _In_opt_  const MFARGB* pBorderClr, _Out_  DWORD* pFrameProtectionFlags ) const
        {
            InterfaceType* pInterface = GetInterface( );
            auto hr = pInterface->TransferVideoFrame( pDstSurf, pSrc, pDst, pBorderClr, pFrameProtectionFlags );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

        void SetContentProtectionManager( _In_opt_  IMFContentProtectionManager* pCPM ) const
        {
            InterfaceType* pInterface = GetInterface( );
            auto hr = pInterface->SetContentProtectionManager( pCPM );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

        void SetApplicationCertificate( _In_reads_bytes_( cbBlob )  const BYTE* pbBlob, _In_  DWORD cbBlob ) const
        {
            InterfaceType* pInterface = GetInterface( );
            auto hr = pInterface->SetApplicationCertificate( pbBlob, cbBlob );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }
    };


    class MFAudioSourceProvider : public Unknown
    {
    public:
        HCC_COM_STANDARD_METHODS_IMPL( MFAudioSourceProvider, Unknown, IAudioSourceProvider, IUnknown )
    public:
        void ProvideInput( _In_  DWORD dwSampleCount, _Inout_  DWORD* pdwChannelCount, _Out_writes_opt_( dwSampleCount* ( *pdwChannelCount ) )  float* pInterleavedAudioData ) const
        {
            InterfaceType* pInterface = GetInterface( );
            auto hr = pInterface->ProvideInput( dwSampleCount, pdwChannelCount, pInterleavedAudioData );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }
    };

    class MFMediaEngineWebSupport : public Unknown
    {
    public:
        HCC_COM_STANDARD_METHODS_IMPL( MFMediaEngineWebSupport, Unknown, IMFMediaEngineWebSupport, IUnknown )
    public:
        bool ShouldDelayTheLoadEvent( ) const
        {
            InterfaceType* pInterface = GetInterface( );
            return pInterface->ShouldDelayTheLoadEvent( ) == FALSE;
        }

        void ConnectWebAudio( _In_  DWORD dwSampleRate, _COM_Outptr_  IAudioSourceProvider** ppSourceProvider ) const
        {
            InterfaceType* pInterface = GetInterface( );
            auto hr = pInterface->ConnectWebAudio( dwSampleRate, ppSourceProvider );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

        void DisconnectWebAudio( ) const
        {
            InterfaceType* pInterface = GetInterface( );
            auto hr = pInterface->DisconnectWebAudio( );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }
    };

    class MFMediaSourceExtensionNotify : public Unknown
    {
    public:
        HCC_COM_STANDARD_METHODS_IMPL( MFMediaSourceExtensionNotify, Unknown, IMFMediaSourceExtensionNotify, IUnknown )
    public:
        void OnSourceOpen( ) const
        {
            InterfaceType* pInterface = GetInterface( );
            pInterface->OnSourceOpen( );
        }

        void OnSourceEnded( ) const
        {
            InterfaceType* pInterface = GetInterface( );
            pInterface->OnSourceEnded( );
        }

        void OnSourceClose( ) const
        {
            InterfaceType* pInterface = GetInterface( );
            pInterface->OnSourceClose( );
        }
    };

    class MFBufferListNotify : public Unknown
    {
    public:
        HCC_COM_STANDARD_METHODS_IMPL( MFBufferListNotify, Unknown, IMFBufferListNotify, IUnknown )
    public:
        void OnAddSourceBuffer( ) const
        {
            InterfaceType* pInterface = GetInterface( );
            pInterface->OnAddSourceBuffer( );
        }

        void OnRemoveSourceBuffer( ) const
        {
            InterfaceType* pInterface = GetInterface( );
            pInterface->OnRemoveSourceBuffer( );
        }
    };

    class MFSourceBufferNotify : public Unknown
    {
    public:
        HCC_COM_STANDARD_METHODS_IMPL( MFSourceBufferNotify, Unknown, IMFSourceBufferNotify, IUnknown )
    public:
        void OnUpdateStart( ) const
        {
            InterfaceType* pInterface = GetInterface( );
            pInterface->OnUpdateStart( );
        }

        void OnAbort( ) const
        {
            InterfaceType* pInterface = GetInterface( );
            pInterface->OnAbort( );
        }

        void OnError( _In_  HRESULT hr ) const
        {
            InterfaceType* pInterface = GetInterface( );
            pInterface->OnError( hr );
        }

        void OnUpdate( ) const
        {
            InterfaceType* pInterface = GetInterface( );
            pInterface->OnUpdate( );
        }

        void OnUpdateEnd( ) const
        {
            InterfaceType* pInterface = GetInterface( );
            pInterface->OnUpdateEnd( );
        }
    };

    class MFSourceBuffer : public Unknown
    {
    public:
        HCC_COM_STANDARD_METHODS_IMPL( MFSourceBuffer, Unknown, IMFSourceBuffer, IUnknown )
    public:
        bool GetUpdating( ) const
        {
            InterfaceType* pInterface = GetInterface( );
            return pInterface->GetUpdating( ) != FALSE;
        }

        void GetBuffered( _Outptr_  IMFMediaTimeRange** ppBuffered ) const
        {
            InterfaceType* pInterface = GetInterface( );
            auto hr = pInterface->GetBuffered( ppBuffered );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

        double GetTimeStampOffset( ) const
        {
            InterfaceType* pInterface = GetInterface( );
            return pInterface->GetTimeStampOffset( );
        }

        void SetTimeStampOffset( _In_  double offset ) const
        {
            InterfaceType* pInterface = GetInterface( );
            auto hr = pInterface->SetTimeStampOffset( offset );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

        double GetAppendWindowStart( ) const
        {
            InterfaceType* pInterface = GetInterface( );
            return pInterface->GetAppendWindowStart( );
        }

        void SetAppendWindowStart( _In_  double time ) const
        {
            InterfaceType* pInterface = GetInterface( );
            auto hr = pInterface->SetAppendWindowStart( time );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

        double GetAppendWindowEnd( ) const
        {
            InterfaceType* pInterface = GetInterface( );
            return pInterface->GetAppendWindowEnd( );
        }

        void SetAppendWindowEnd( _In_  double time ) const
        {
            InterfaceType* pInterface = GetInterface( );
            auto hr = pInterface->SetAppendWindowEnd( time );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

        void Append( _In_reads_bytes_( len )  const BYTE* pData, _In_  DWORD len ) const
        {
            InterfaceType* pInterface = GetInterface( );
            auto hr = pInterface->Append( pData, len );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

        void AppendByteStream( _In_  IMFByteStream* pStream, _In_opt_  DWORDLONG* pMaxLen ) const
        {
            InterfaceType* pInterface = GetInterface( );
            auto hr = pInterface->AppendByteStream( pStream, pMaxLen );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

        void Abort( ) const
        {
            InterfaceType* pInterface = GetInterface( );
            auto hr = pInterface->Abort( );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

        void Remove( _In_  double start, _In_  double end ) const
        {
            InterfaceType* pInterface = GetInterface( );
            auto hr = pInterface->Remove( start, end );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }
    };

    class MFSourceBufferAppendMode : public Unknown
    {
    public:
        HCC_COM_STANDARD_METHODS_IMPL( MFSourceBufferAppendMode, Unknown, IMFSourceBufferAppendMode, IUnknown )
    public:
        MF_MSE_APPEND_MODE GetAppendMode( ) const
        {
            InterfaceType* pInterface = GetInterface( );
            return pInterface->GetAppendMode( );
        }

        void SetAppendMode( _In_  MF_MSE_APPEND_MODE mode ) const
        {
            InterfaceType* pInterface = GetInterface( );
            auto hr = pInterface->SetAppendMode( mode );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }
    };

    class MFSourceBufferList : public Unknown
    {
    public:
        HCC_COM_STANDARD_METHODS_IMPL( MFSourceBufferList, Unknown, IMFSourceBufferList, IUnknown )
    public:
        DWORD GetLength( ) const
        {
            InterfaceType* pInterface = GetInterface( );
            return pInterface->GetLength( );
        }

        IMFSourceBuffer* GetSourceBuffer_( _In_  DWORD index ) const
        {
            InterfaceType* pInterface = GetInterface( );
            return pInterface->GetSourceBuffer( index );
        }

        MFSourceBuffer GetSourceBuffer( _In_  DWORD index ) const
        {
            InterfaceType* pInterface = GetInterface( );
            return MFSourceBuffer(pInterface->GetSourceBuffer( index ));
        }
    };

    class MediaSourceExtension : public Unknown
    {
    public:
        HCC_COM_STANDARD_METHODS_IMPL( MediaSourceExtension, Unknown, IMFMediaSourceExtension, IUnknown )
    public:
        IMFSourceBufferList* GetSourceBuffers_( ) const
        {
            InterfaceType* pInterface = GetInterface( );
            return pInterface->GetSourceBuffers( );
        }

        MFSourceBufferList GetSourceBuffers( ) const
        {
            InterfaceType* pInterface = GetInterface( );
            return MFSourceBufferList(pInterface->GetSourceBuffers( ));
        }

        IMFSourceBufferList* GetActiveSourceBuffers_( ) const
        {
            InterfaceType* pInterface = GetInterface( );
            return pInterface->GetActiveSourceBuffers( );
        }

        MFSourceBufferList GetActiveSourceBuffers( ) const
        {
            InterfaceType* pInterface = GetInterface( );
            return MFSourceBufferList( pInterface->GetActiveSourceBuffers( ) );
        }

        MF_MSE_READY GetReadyState( ) const
        {
            InterfaceType* pInterface = GetInterface( );
            return pInterface->GetReadyState( );
        }

        double GetDuration( ) const
        {
            InterfaceType* pInterface = GetInterface( );
            return pInterface->GetDuration( );
        }

        void SetDuration(_In_  double duration ) const
        {
            InterfaceType* pInterface = GetInterface( );
            auto hr = pInterface->SetDuration( duration );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

        void AddSourceBuffer( _In_  BSTR type, _In_  IMFSourceBufferNotify* pNotify, _Outptr_  IMFSourceBuffer** ppSourceBuffer ) const
        {
            InterfaceType* pInterface = GetInterface( );
            auto hr = pInterface->AddSourceBuffer( type, pNotify, ppSourceBuffer );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

        void RemoveSourceBuffer( _In_  IMFSourceBuffer* pSourceBuffer ) const
        {
            InterfaceType* pInterface = GetInterface( );
            auto hr = pInterface->RemoveSourceBuffer( pSourceBuffer );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

        void SetEndOfStream( _In_  MF_MSE_ERROR error ) const
        {
            InterfaceType* pInterface = GetInterface( );
            auto hr = pInterface->SetEndOfStream( error );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

        BOOL IsTypeSupported( _In_  BSTR type ) const
        {
            InterfaceType* pInterface = GetInterface( );
            return pInterface->IsTypeSupported( type ) != FALSE;
        }

        IMFSourceBuffer* GetSourceBuffer_( _In_  DWORD dwStreamIndex ) const
        {
            InterfaceType* pInterface = GetInterface( );
            return pInterface->GetSourceBuffer( dwStreamIndex );
        }

        MFSourceBuffer GetSourceBuffer( _In_  DWORD dwStreamIndex ) const
        {
            InterfaceType* pInterface = GetInterface( );
            return MFSourceBuffer( pInterface->GetSourceBuffer( dwStreamIndex ) );
        }
    };



    class MFMediaSourceExtensionLiveSeekableRange : public Unknown
    {
    public:
        HCC_COM_STANDARD_METHODS_IMPL( MFMediaSourceExtensionLiveSeekableRange, Unknown, IMFMediaSourceExtensionLiveSeekableRange, IUnknown )
    public:
        void SetLiveSeekableRange( _In_  double start, _In_  double end ) const
        {
            InterfaceType* pInterface = GetInterface( );
            auto hr = pInterface->SetLiveSeekableRange( start, end );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

        void ClearLiveSeekableRange( ) const
        {
            InterfaceType* pInterface = GetInterface( );
            auto hr = pInterface->ClearLiveSeekableRange( );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }
    };


    class MFMediaEngineEME : public Unknown
    {
    public:
        HCC_COM_STANDARD_METHODS_IMPL( MFMediaEngineEME, Unknown, IMFMediaEngineEME, IUnknown )
    public:
        void get_Keys( _COM_Outptr_result_maybenull_  IMFMediaKeys** keys ) const
        {
            InterfaceType* pInterface = GetInterface( );
            auto hr = pInterface->get_Keys( keys );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

        void SetMediaKeys( _In_opt_  IMFMediaKeys* keys ) const
        {
            InterfaceType* pInterface = GetInterface( );
            auto hr = pInterface->SetMediaKeys( keys );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }
    };


    class MFMediaEngineSrcElementsEx : public MFMediaEngineSrcElements
    {
    public:
        HCC_COM_STANDARD_METHODS_IMPL( MFMediaEngineSrcElementsEx, MFMediaEngineSrcElements, IMFMediaEngineSrcElementsEx, IMFMediaEngineSrcElements )
    public:
        void AddElementEx( _In_opt_  BSTR pURL, _In_opt_  BSTR pType, _In_opt_  BSTR pMedia, _In_opt_  BSTR keySystem ) const
        {
            InterfaceType* pInterface = GetInterface( );
            auto hr = pInterface->AddElementEx( pURL, pType, pMedia, keySystem );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

        void GetKeySystem( _In_  DWORD index, _Outptr_result_maybenull_  BSTR* pType ) const
        {
            InterfaceType* pInterface = GetInterface( );
            auto hr = pInterface->GetKeySystem( index, pType );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }
    };

    class MFMediaEngineNeedKeyNotify : public Unknown
    {
    public:
        HCC_COM_STANDARD_METHODS_IMPL( MFMediaEngineNeedKeyNotify, Unknown, IMFMediaEngineNeedKeyNotify, IUnknown )
    public:
        void NeedKey( _In_reads_bytes_opt_( cb )  const BYTE* initData, _In_  DWORD cb ) const
        {
            InterfaceType* pInterface = GetInterface( );
            pInterface->NeedKey( initData, cb );
        }
    };

    class MFMediaKeys : public Unknown
    {
    public:
        HCC_COM_STANDARD_METHODS_IMPL( MFMediaKeys, Unknown, IMFMediaKeys, IUnknown )
    public:
        void CreateSession( _In_opt_  BSTR mimeType, _In_reads_bytes_opt_( cb )  const BYTE* initData, _In_opt_  DWORD cb, _In_reads_bytes_opt_( cbCustomData )  const BYTE* customData, _In_  DWORD cbCustomData, _In_  IMFMediaKeySessionNotify* notify, _COM_Outptr_  IMFMediaKeySession** ppSession ) const
        {
            InterfaceType* pInterface = GetInterface( );
            auto hr = pInterface->CreateSession( mimeType, initData, cb, customData, cbCustomData, notify, ppSession );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

        void get_KeySystem( _COM_Outptr_  BSTR* keySystem ) const
        {
            InterfaceType* pInterface = GetInterface( );
            auto hr = pInterface->get_KeySystem( keySystem );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

        void Shutdown( ) const
        {
            InterfaceType* pInterface = GetInterface( );
            auto hr = pInterface->Shutdown( );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

        void GetSuspendNotify( _COM_Outptr_  IMFCdmSuspendNotify** notify ) const
        {
            InterfaceType* pInterface = GetInterface( );
            auto hr = pInterface->GetSuspendNotify( notify );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }
    };

    class MFMediaKeySession : public Unknown
    {
    public:
        HCC_COM_STANDARD_METHODS_IMPL( MFMediaKeySession, Unknown, IMFMediaKeySession, IUnknown )
    public:
        void GetError( _Out_  USHORT* code, _Out_  DWORD* systemCode ) const
        {
            InterfaceType* pInterface = GetInterface( );
            auto hr = pInterface->GetError( code, systemCode );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }
        void get_KeySystem( _COM_Outptr_  BSTR* keySystem ) const
        {
            InterfaceType* pInterface = GetInterface( );
            auto hr = pInterface->get_KeySystem( keySystem );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }
        void get_SessionId( _COM_Outptr_  BSTR* sessionId ) const
        {
            InterfaceType* pInterface = GetInterface( );
            auto hr = pInterface->get_SessionId( sessionId );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }
        void Update( _In_reads_bytes_( cb )  const BYTE* key, _In_  DWORD cb ) const
        {
            InterfaceType* pInterface = GetInterface( );
            auto hr = pInterface->Update( key, cb );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }
        void Close( ) const
        {
            InterfaceType* pInterface = GetInterface( );
            auto hr = pInterface->Close( );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }
    };

    class MFMediaKeySessionNotify : public Unknown
    {
    public:
        HCC_COM_STANDARD_METHODS_IMPL( MFMediaKeySessionNotify, Unknown, IMFMediaKeySessionNotify, IUnknown )
    public:
        void KeyMessage( _In_opt_  BSTR destinationURL, _In_reads_bytes_( cb )  const BYTE* message, _In_  DWORD cb ) const
        {
            InterfaceType* pInterface = GetInterface( );
            pInterface->KeyMessage( destinationURL, message, cb );
        }

        void KeyAdded( ) const
        {
            InterfaceType* pInterface = GetInterface( );
            pInterface->KeyAdded( );
        }

        void KeyError( _In_  USHORT code, _In_  DWORD systemCode ) const
        {
            InterfaceType* pInterface = GetInterface( );
            pInterface->KeyError( code, systemCode );
        }
    };

    class MFCdmSuspendNotify : public Unknown
    {
    public:
        HCC_COM_STANDARD_METHODS_IMPL( MFCdmSuspendNotify, Unknown, IMFCdmSuspendNotify, IUnknown )
    public:
        void Begin( ) const
        {
            InterfaceType* pInterface = GetInterface( );
            auto hr = pInterface->Begin( );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

        void End( void ) const
        {
            InterfaceType* pInterface = GetInterface( );
            auto hr = pInterface->End( );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }
    };

    class MFHDCPStatus : public Unknown
    {
    public:
        HCC_COM_STANDARD_METHODS_IMPL( MFHDCPStatus, Unknown, IMFHDCPStatus, IUnknown )
    public:
        void Query( _Inout_  MF_HDCP_STATUS* pStatus, _Inout_  BOOL* pfStatus ) const
        {
            InterfaceType* pInterface = GetInterface( );
            auto hr = pInterface->Query( pStatus, pfStatus );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

        void Set( _In_  MF_HDCP_STATUS status ) const
        {
            InterfaceType* pInterface = GetInterface( );
            auto hr = pInterface->Set( status );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }
    };

    class MFMediaEngineOPMInfo : public Unknown
    {
    public:
        HCC_COM_STANDARD_METHODS_IMPL( MFMediaEngineOPMInfo, Unknown, IMFMediaEngineOPMInfo, IUnknown )
    public:
        void GetOPMInfo( _Out_  MF_MEDIA_ENGINE_OPM_STATUS* pStatus, _Out_  BOOL* pConstricted ) const
        {
            InterfaceType* pInterface = GetInterface( );
            auto hr = pInterface->GetOPMInfo( pStatus, pConstricted );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }
    };

    class MFMediaEngineClassFactory : public Unknown
    {
    public:
        HCC_COM_STANDARD_METHODS_IMPL( MFMediaEngineClassFactory, Unknown, IMFMediaEngineClassFactory, IUnknown )
    public:
        static MFMediaEngineClassFactory Create( )
        {
            IMFMediaEngineClassFactory* itf = nullptr;
            auto hr = CoCreateInstance( CLSID_MFMediaEngineClassFactory, nullptr, CLSCTX_ALL, __uuidof( IMFMediaEngineClassFactory ), reinterpret_cast<void**>( &itf ) );
            HCC_COM_CHECK_HRESULT( hr );
            return MFMediaEngineClassFactory( itf );
        }


        void CreateInstance( _In_  DWORD dwFlags, _In_  IMFAttributes* pAttr, _Outptr_  IMFMediaEngine** ppPlayer ) const
        {
            InterfaceType* pInterface = GetInterface( );
            auto hr = pInterface->CreateInstance( dwFlags, pAttr, ppPlayer );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

        MFMediaEngine CreateInstance( _In_  DWORD dwFlags, _In_  IMFAttributes* pAttr ) const
        {
            IMFMediaEngine* itf = nullptr;
            CreateInstance( dwFlags, pAttr, &itf );
            return MFMediaEngine( itf );
        }

        MFMediaEngine CreateInstance( _In_  DWORD dwFlags, const MFAttributes& pAttr ) const
        {
            return CreateInstance( dwFlags, pAttr.GetInterfacePointer<IMFAttributes>( ) );
        }



        void CreateTimeRange( _Outptr_  IMFMediaTimeRange** ppTimeRange ) const
        {
            InterfaceType* pInterface = GetInterface( );
            auto hr = pInterface->CreateTimeRange( ppTimeRange );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

        MFMediaTimeRange CreateTimeRange( ) const
        {
            IMFMediaTimeRange* itf = nullptr;
            CreateTimeRange( &itf );
            return MFMediaTimeRange( itf );
        }


        void CreateError( _Outptr_  IMFMediaError** ppError ) const
        {
            InterfaceType* pInterface = GetInterface( );
            auto hr = pInterface->CreateError( ppError );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

        MFMediaError CreateError( ) const
        {
            IMFMediaError* itf = nullptr;
            CreateError( &itf );
            return MFMediaError( itf );
        }
    };

    class MFMediaEngineClassFactoryEx : public MFMediaEngineClassFactory
    {
    public:
        HCC_COM_STANDARD_METHODS_IMPL( MFMediaEngineClassFactoryEx, MFMediaEngineClassFactory, IMFMediaEngineClassFactoryEx, IMFMediaEngineClassFactory )
    public:
        void CreateMediaSourceExtension( _In_  DWORD dwFlags, _In_  IMFAttributes* pAttr, _COM_Outptr_  IMFMediaSourceExtension** ppMSE ) const
        {
            InterfaceType* pInterface = GetInterface( );
            auto hr = pInterface->CreateMediaSourceExtension( dwFlags, pAttr, ppMSE );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

        void CreateMediaKeys( _In_  BSTR keySystem, _In_opt_  BSTR cdmStorePath, _COM_Outptr_  IMFMediaKeys** ppKeys ) const
        {
            InterfaceType* pInterface = GetInterface( );
            auto hr = pInterface->CreateMediaKeys( keySystem, cdmStorePath, ppKeys );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

        void IsTypeSupported( _In_opt_  BSTR type, _In_  BSTR keySystem, _Out_  BOOL* isSupported ) const
        {
            InterfaceType* pInterface = GetInterface( );
            auto hr = pInterface->IsTypeSupported( type, keySystem, isSupported );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }
    };

    class MFMediaEngineClassFactory2 : public Unknown
    {
    public:
        HCC_COM_STANDARD_METHODS_IMPL( MFMediaEngineClassFactory2, Unknown, IMFMediaEngineClassFactory2, IUnknown )
    public:
        void CreateMediaKeys2( _In_  BSTR keySystem, _In_  BSTR defaultCdmStorePath, _In_opt_  BSTR inprivateCdmStorePath, _COM_Outptr_  IMFMediaKeys** ppKeys ) const
        {
            InterfaceType* pInterface = GetInterface( );
            auto hr = pInterface->CreateMediaKeys2( keySystem, defaultCdmStorePath, inprivateCdmStorePath, ppKeys );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }
    };


    class MFExtendedDRMTypeSupport : public Unknown
    {
    public:
        HCC_COM_STANDARD_METHODS_IMPL( MFExtendedDRMTypeSupport, Unknown, IMFExtendedDRMTypeSupport, IUnknown )
    public:
        void IsTypeSupportedEx( _In_opt_  BSTR type, _In_  BSTR keySystem, _Out_  MF_MEDIA_ENGINE_CANPLAY* pAnswer ) const
        {
            InterfaceType* pInterface = GetInterface( );
            auto hr = pInterface->IsTypeSupportedEx( type, keySystem, pAnswer );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }
    };


    class MFMediaEngineSupportsSourceTransfer : public Unknown
    {
    public:
        HCC_COM_STANDARD_METHODS_IMPL( MFMediaEngineSupportsSourceTransfer, Unknown, IMFMediaEngineSupportsSourceTransfer, IUnknown )
    public:
        void ShouldTransferSource( _Out_  BOOL* pfShouldTransfer ) const
        {
            InterfaceType* pInterface = GetInterface( );
            auto hr = pInterface->ShouldTransferSource( pfShouldTransfer );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

        void DetachMediaSource( _COM_Outptr_  IMFByteStream** ppByteStream, _COM_Outptr_  IMFMediaSource** ppMediaSource, _COM_Outptr_  IMFMediaSourceExtension** ppMSE ) const
        {
            InterfaceType* pInterface = GetInterface( );
            auto hr = pInterface->DetachMediaSource( ppByteStream, ppMediaSource, ppMSE );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

        void AttachMediaSource( _In_opt_  IMFByteStream* pByteStream, _In_  IMFMediaSource* pMediaSource, _In_opt_  IMFMediaSourceExtension* pMSE ) const
        {
            InterfaceType* pInterface = GetInterface( );
            auto hr = pInterface->AttachMediaSource( pByteStream, pMediaSource, pMSE );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }
    };

    class MFMediaEngineTransferSource : public Unknown
    {
    public:
        HCC_COM_STANDARD_METHODS_IMPL( MFMediaEngineTransferSource, Unknown, IMFMediaEngineTransferSource, IUnknown )
    public:
        void TransferSourceToMediaEngine( _In_  IMFMediaEngine* destination ) const
        {
            InterfaceType* pInterface = GetInterface( );
            auto hr = pInterface->TransferSourceToMediaEngine( destination );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }
    };

    class MFTimedText : public Unknown
    {
    public:
        HCC_COM_STANDARD_METHODS_IMPL( MFTimedText, Unknown, IMFTimedText, IUnknown )
    public:
        void RegisterNotifications( _In_opt_  IMFTimedTextNotify* notify ) const
        {
            InterfaceType* pInterface = GetInterface( );
            auto hr = pInterface->RegisterNotifications( notify );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

        void SelectTrack( _In_  DWORD trackId, _In_  BOOL selected ) const
        {
            InterfaceType* pInterface = GetInterface( );
            auto hr = pInterface->SelectTrack( trackId, selected );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

        void AddDataSource( _In_  IMFByteStream* byteStream, _In_opt_  LPCWSTR label, _In_opt_  LPCWSTR language, _In_  MF_TIMED_TEXT_TRACK_KIND kind, _In_  BOOL isDefault, _Out_  DWORD* trackId ) const
        {
            InterfaceType* pInterface = GetInterface( );
            auto hr = pInterface->AddDataSource( byteStream, label, language, kind, isDefault, trackId );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

        void AddDataSourceFromUrl(_In_  LPCWSTR url, _In_opt_  LPCWSTR label, _In_opt_  LPCWSTR language, _In_  MF_TIMED_TEXT_TRACK_KIND kind, _In_  BOOL isDefault, _Out_  DWORD* trackId ) const
        {
            InterfaceType* pInterface = GetInterface( );
            auto hr = pInterface->AddDataSourceFromUrl( url, label, language, kind, isDefault, trackId );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

        void AddTrack( _In_opt_  LPCWSTR label, _In_opt_  LPCWSTR language, _In_  MF_TIMED_TEXT_TRACK_KIND kind, _COM_Outptr_  IMFTimedTextTrack** track ) const
        {
            InterfaceType* pInterface = GetInterface( );
            auto hr = pInterface->AddTrack( label, language, kind, track );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

        void RemoveTrack( _In_  IMFTimedTextTrack* track ) const
        {
            InterfaceType* pInterface = GetInterface( );
            auto hr = pInterface->RemoveTrack( track );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

        void GetCueTimeOffset( _Out_  double* offset ) const
        {
            InterfaceType* pInterface = GetInterface( );
            auto hr = pInterface->GetCueTimeOffset( offset );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

        void SetCueTimeOffset( _In_  double offset ) const
        {
            InterfaceType* pInterface = GetInterface( );
            auto hr = pInterface->SetCueTimeOffset( offset );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

        void GetTracks( _COM_Outptr_  IMFTimedTextTrackList** tracks ) const
        {
            InterfaceType* pInterface = GetInterface( );
            auto hr = pInterface->GetTracks( tracks );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

        void GetActiveTracks( _COM_Outptr_  IMFTimedTextTrackList** activeTracks ) const
        {
            InterfaceType* pInterface = GetInterface( );
            auto hr = pInterface->GetActiveTracks( activeTracks );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

        void GetTextTracks( _COM_Outptr_  IMFTimedTextTrackList** textTracks ) const
        {
            InterfaceType* pInterface = GetInterface( );
            auto hr = pInterface->GetTextTracks( textTracks );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

        void GetMetadataTracks( _COM_Outptr_  IMFTimedTextTrackList** metadataTracks ) const
        {
            InterfaceType* pInterface = GetInterface( );
            auto hr = pInterface->GetMetadataTracks( metadataTracks );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

        void SetInBandEnabled( _In_  BOOL enabled ) const
        {
            InterfaceType* pInterface = GetInterface( );
            auto hr = pInterface->SetInBandEnabled( enabled );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

        bool IsInBandEnabled( ) const
        {
            InterfaceType* pInterface = GetInterface( );
            return pInterface->IsInBandEnabled( ) != FALSE;
        }
    };

    class MFTimedTextNotify : public Unknown
    {
    public:
        HCC_COM_STANDARD_METHODS_IMPL( MFTimedTextNotify, Unknown, IMFTimedTextNotify, IUnknown )
    public:
        void TrackAdded( _In_  DWORD trackId ) const
        {
            InterfaceType* pInterface = GetInterface( );
            pInterface->TrackAdded( trackId );
        }

        void TrackRemoved( _In_  DWORD trackId ) const
        {
            InterfaceType* pInterface = GetInterface( );
            pInterface->TrackRemoved( trackId );
        }

        void TrackSelected( _In_  DWORD trackId, _In_  BOOL selected ) const
        {
            InterfaceType* pInterface = GetInterface( );
            pInterface->TrackRemoved( trackId );
        }

        void TrackReadyStateChanged( _In_  DWORD trackId ) const
        {
            InterfaceType* pInterface = GetInterface( );
            pInterface->TrackReadyStateChanged( trackId );
        }

        void Error( _In_  MF_TIMED_TEXT_ERROR_CODE errorCode, _In_  HRESULT extendedErrorCode, _In_  DWORD sourceTrackId ) const
        {
            InterfaceType* pInterface = GetInterface( );
            pInterface->Error( errorCode, extendedErrorCode, sourceTrackId );
        }

        void Cue( _In_  MF_TIMED_TEXT_CUE_EVENT cueEvent, _In_  double currentTime, _In_opt_  IMFTimedTextCue* cue ) const
        {
            InterfaceType* pInterface = GetInterface( );
            pInterface->Cue( cueEvent, currentTime, cue );
        }

        void Reset(  ) const
        {
            InterfaceType* pInterface = GetInterface( );
            pInterface->Reset( );
        }
    };

    class MFTimedTextTrack : public Unknown
    {
    public:
        HCC_COM_STANDARD_METHODS_IMPL( MFTimedTextTrack, Unknown, IMFTimedTextTrack, IUnknown )
    public:
        DWORD GetId( ) const
        {
            InterfaceType* pInterface = GetInterface( );
            return pInterface->GetId( );
        }

        void GetLabel( _Outptr_  LPWSTR* label ) const
        {
            InterfaceType* pInterface = GetInterface( );
            auto hr = pInterface->GetLabel( label );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

        void SetLabel( _In_  LPCWSTR label ) const
        {
            InterfaceType* pInterface = GetInterface( );
            auto hr = pInterface->SetLabel( label );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

        void GetLanguage( _Outptr_  LPWSTR* language ) const
        {
            InterfaceType* pInterface = GetInterface( );
            auto hr = pInterface->GetLanguage( language );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

        MF_TIMED_TEXT_TRACK_KIND GetTrackKind( ) const
        {
            InterfaceType* pInterface = GetInterface( );
            return pInterface->GetTrackKind( );
        }

        BOOL IsInBand( ) const
        {
            InterfaceType* pInterface = GetInterface( );
            return pInterface->IsInBand( ) != FALSE;
        }

        void GetInBandMetadataTrackDispatchType( _Outptr_  LPWSTR* dispatchType ) const
        {
            InterfaceType* pInterface = GetInterface( );
            auto hr = pInterface->GetInBandMetadataTrackDispatchType( dispatchType );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

        BOOL IsActive( ) const
        {
            InterfaceType* pInterface = GetInterface( );
            return pInterface->IsActive( ) != FALSE;
        }

        MF_TIMED_TEXT_ERROR_CODE GetErrorCode( ) const
        {
            InterfaceType* pInterface = GetInterface( );
            return pInterface->GetErrorCode( );
        }

        HRESULT GetExtendedErrorCode( ) const
        {
            InterfaceType* pInterface = GetInterface( );
            return pInterface->GetExtendedErrorCode( );
        }

        void GetDataFormat( _Out_  GUID* format ) const
        {
            InterfaceType* pInterface = GetInterface( );
            auto hr = pInterface->GetDataFormat( format );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

        MF_TIMED_TEXT_TRACK_READY_STATE GetReadyState( ) const
        {
            InterfaceType* pInterface = GetInterface( );
            return pInterface->GetReadyState( );
        }

        void GetCueList( _COM_Outptr_  IMFTimedTextCueList** cues ) const
        {
            InterfaceType* pInterface = GetInterface( );
            auto hr = pInterface->GetCueList( cues );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }
    };

    class MFTimedTextTrackList : public Unknown
    {
    public:
        HCC_COM_STANDARD_METHODS_IMPL( MFTimedTextTrackList, Unknown, IMFTimedTextTrackList, IUnknown )
    public:
        DWORD GetLength( void ) const
        {
            InterfaceType* pInterface = GetInterface( );
            return pInterface->GetLength( );
        }

        void GetTrack( _In_  DWORD index, _COM_Outptr_  IMFTimedTextTrack** track ) const
        {
            InterfaceType* pInterface = GetInterface( );
            auto hr = pInterface->GetTrack( index, track );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

        void GetTrackById( _In_  DWORD trackId, _COM_Outptr_  IMFTimedTextTrack** track ) const
        {
            InterfaceType* pInterface = GetInterface( );
            auto hr = pInterface->GetTrackById( trackId, track );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }
    };

    class MFTimedTextCue : public Unknown
    {
    public:
        HCC_COM_STANDARD_METHODS_IMPL( MFTimedTextCue, Unknown, IMFTimedTextCue, IUnknown )
    public:
        DWORD GetId( ) const
        {
            InterfaceType* pInterface = GetInterface( );
            return pInterface->GetId( );
        }

        void GetOriginalId( _Outptr_  LPWSTR* originalId ) const
        {
            InterfaceType* pInterface = GetInterface( );
            auto hr = pInterface->GetOriginalId( originalId );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

        MF_TIMED_TEXT_TRACK_KIND GetCueKind( ) const
        {
            InterfaceType* pInterface = GetInterface( );
            return pInterface->GetCueKind( );
        }

        double GetStartTime( ) const
        {
            InterfaceType* pInterface = GetInterface( );
            return pInterface->GetStartTime( );
        }

        double GetDuration( ) const
        {
            InterfaceType* pInterface = GetInterface( );
            return pInterface->GetDuration( );
        }

        DWORD GetTrackId( ) const
        {
            InterfaceType* pInterface = GetInterface( );
            return pInterface->GetTrackId( );
        }

        void GetData(_COM_Outptr_result_maybenull_  IMFTimedTextBinary** data ) const
        {
            InterfaceType* pInterface = GetInterface( );
            auto hr = pInterface->GetData( data );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

        void GetRegion(_COM_Outptr_result_maybenull_  IMFTimedTextRegion** region ) const
        {
            InterfaceType* pInterface = GetInterface( );
            auto hr = pInterface->GetRegion( region );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

        void GetStyle(_COM_Outptr_result_maybenull_  IMFTimedTextStyle** style ) const
        {
            InterfaceType* pInterface = GetInterface( );
            auto hr = pInterface->GetStyle( style );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

        DWORD GetLineCount( ) const
        {
            InterfaceType* pInterface = GetInterface( );
            return pInterface->GetLineCount( );
        }

        void GetLine( _In_  DWORD index, _COM_Outptr_  IMFTimedTextFormattedText** line ) const
        {
            InterfaceType* pInterface = GetInterface( );
            auto hr = pInterface->GetLine( index, line );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }
    };

    class MFTimedTextFormattedText : public Unknown
    {
    public:
        HCC_COM_STANDARD_METHODS_IMPL( MFTimedTextFormattedText, Unknown, IMFTimedTextFormattedText, IUnknown )
    public:
        void GetText( _Outptr_result_maybenull_  LPWSTR* text ) const
        {
            InterfaceType* pInterface = GetInterface( );
            auto hr = pInterface->GetText( text );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

        DWORD GetSubformattingCount( ) const
        {
            InterfaceType* pInterface = GetInterface( );
            return pInterface->GetSubformattingCount( );
        }

        void GetSubformatting( _In_  DWORD index, _Out_  DWORD* firstChar, _Out_  DWORD* charLength, _COM_Outptr_result_maybenull_  IMFTimedTextStyle** style ) const
        {
            InterfaceType* pInterface = GetInterface( );
            auto hr = pInterface->GetSubformatting( index, firstChar, charLength, style );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }
    };

    class MFTimedTextStyle : public Unknown
    {
    public:
        HCC_COM_STANDARD_METHODS_IMPL( MFTimedTextStyle, Unknown, IMFTimedTextStyle, IUnknown )
    public:
        void GetName( _Outptr_  LPWSTR* name ) const
        {
            InterfaceType* pInterface = GetInterface( );
            auto hr = pInterface->GetName( name );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

        bool IsExternal( ) const
        {
            InterfaceType* pInterface = GetInterface( );
            return pInterface->IsExternal( ) != FALSE;
        }

        void GetFontFamily( _Outptr_  LPWSTR* fontFamily ) const
        {
            InterfaceType* pInterface = GetInterface( );
            auto hr = pInterface->GetFontFamily( fontFamily );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

        void GetFontSize( _Out_  double* fontSize, _Out_  MF_TIMED_TEXT_UNIT_TYPE* unitType ) const
        {
            InterfaceType* pInterface = GetInterface( );
            auto hr = pInterface->GetFontSize( fontSize, unitType );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

        void GetColor( _Out_  MFARGB* color ) const
        {
            InterfaceType* pInterface = GetInterface( );
            auto hr = pInterface->GetColor( color );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

        void GetBackgroundColor( _Out_  MFARGB* bgColor ) const
        {
            InterfaceType* pInterface = GetInterface( );
            auto hr = pInterface->GetBackgroundColor( bgColor );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

        void GetShowBackgroundAlways( _Out_  BOOL* showBackgroundAlways ) const
        {
            InterfaceType* pInterface = GetInterface( );
            auto hr = pInterface->GetShowBackgroundAlways( showBackgroundAlways );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

        void GetFontStyle( _Out_  MF_TIMED_TEXT_FONT_STYLE* fontStyle ) const
        {
            InterfaceType* pInterface = GetInterface( );
            auto hr = pInterface->GetFontStyle( fontStyle );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

        void GetBold( _Out_  BOOL* bold ) const
        {
            InterfaceType* pInterface = GetInterface( );
            auto hr = pInterface->GetBold( bold );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

        void GetRightToLeft( _Out_  BOOL* rightToLeft ) const
        {
            InterfaceType* pInterface = GetInterface( );
            auto hr = pInterface->GetRightToLeft( rightToLeft );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

        void GetTextAlignment( _Out_  MF_TIMED_TEXT_ALIGNMENT* textAlign ) const
        {
            InterfaceType* pInterface = GetInterface( );
            auto hr = pInterface->GetTextAlignment( textAlign );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

        void GetTextDecoration( _Out_  DWORD* textDecoration ) const
        {
            InterfaceType* pInterface = GetInterface( );
            auto hr = pInterface->GetTextDecoration( textDecoration );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

        void GetTextOutline( _Out_  MFARGB* color, _Out_  double* thickness, _Out_  double* blurRadius, _Out_  MF_TIMED_TEXT_UNIT_TYPE* unitType ) const
        {
            InterfaceType* pInterface = GetInterface( );
            auto hr = pInterface->GetTextOutline( color, thickness, blurRadius, unitType );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }
    };

    class MFTimedTextRegion : public Unknown
    {
    public:
        HCC_COM_STANDARD_METHODS_IMPL( MFTimedTextRegion, Unknown, IMFTimedTextRegion, IUnknown )
    public:
        void GetName( _Outptr_  LPWSTR* name ) const
        {
            InterfaceType* pInterface = GetInterface( );
            auto hr = pInterface->GetName( name );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

        void GetPosition( _Out_  double* pX, _Out_  double* pY, _Out_  MF_TIMED_TEXT_UNIT_TYPE* unitType ) const
        {
            InterfaceType* pInterface = GetInterface( );
            auto hr = pInterface->GetPosition( pX, pY, unitType );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

        void GetExtent( _Out_  double* pWidth, _Out_  double* pHeight, _Out_  MF_TIMED_TEXT_UNIT_TYPE* unitType ) const
        {
            InterfaceType* pInterface = GetInterface( );
            auto hr = pInterface->GetExtent( pWidth, pHeight, unitType );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

        void GetBackgroundColor( _Out_  MFARGB* bgColor ) const
        {
            InterfaceType* pInterface = GetInterface( );
            auto hr = pInterface->GetBackgroundColor( bgColor );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

        void GetWritingMode( _Out_  MF_TIMED_TEXT_WRITING_MODE* writingMode ) const
        {
            InterfaceType* pInterface = GetInterface( );
            auto hr = pInterface->GetWritingMode( writingMode );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

        void GetDisplayAlignment( _Out_  MF_TIMED_TEXT_DISPLAY_ALIGNMENT* displayAlign ) const
        {
            InterfaceType* pInterface = GetInterface( );
            auto hr = pInterface->GetDisplayAlignment( displayAlign );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

        void GetLineHeight( _Out_  double* pLineHeight, _Out_  MF_TIMED_TEXT_UNIT_TYPE* unitType ) const
        {
            InterfaceType* pInterface = GetInterface( );
            auto hr = pInterface->GetLineHeight( pLineHeight, unitType );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

        void GetClipOverflow( _Out_  BOOL* clipOverflow ) const
        {
            InterfaceType* pInterface = GetInterface( );
            auto hr = pInterface->GetClipOverflow( clipOverflow );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

        void GetPadding( _Out_  double* before, _Out_  double* start, _Out_  double* after, _Out_  double* end, _Out_  MF_TIMED_TEXT_UNIT_TYPE* unitType ) const
        {
            InterfaceType* pInterface = GetInterface( );
            auto hr = pInterface->GetPadding( before, start, after, end, unitType );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

        void GetWrap( _Out_  BOOL* wrap ) const
        {
            InterfaceType* pInterface = GetInterface( );
            auto hr = pInterface->GetWrap( wrap );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

        void GetZIndex( _Out_  INT32* zIndex ) const
        {
            InterfaceType* pInterface = GetInterface( );
            auto hr = pInterface->GetZIndex( zIndex );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

        void GetScrollMode( _Out_  MF_TIMED_TEXT_SCROLL_MODE* scrollMode ) const
        {
            InterfaceType* pInterface = GetInterface( );
            auto hr = pInterface->GetScrollMode( scrollMode );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }
    };

    class MFTimedTextBinary : public Unknown
    {
    public:
        HCC_COM_STANDARD_METHODS_IMPL( MFTimedTextBinary, Unknown, IMFTimedTextBinary, IUnknown )
    public:
        void GetData( _Outptr_result_bytebuffer_( *length )  const BYTE** data, _Out_  DWORD* length ) const
        {
            InterfaceType* pInterface = GetInterface( );
            auto hr = pInterface->GetData( data, length );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }
    };

    class MFTimedTextCueList : public Unknown
    {
    public:
        HCC_COM_STANDARD_METHODS_IMPL( MFTimedTextCueList, Unknown, IMFTimedTextCueList, IUnknown )
    public:
        DWORD GetLength( ) const
        {
            InterfaceType* pInterface = GetInterface( );
            return pInterface->GetLength( );
        }

        void GetCueByIndex( _In_  DWORD index, _COM_Outptr_  IMFTimedTextCue** cue ) const
        {
            InterfaceType* pInterface = GetInterface( );
            auto hr = pInterface->GetCueByIndex( index, cue );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

        void GetCueById( _In_  DWORD id, _COM_Outptr_  IMFTimedTextCue** cue ) const
        {
            InterfaceType* pInterface = GetInterface( );
            auto hr = pInterface->GetCueById( id, cue );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

        void GetCueByOriginalId( _In_  LPCWSTR originalId, _COM_Outptr_  IMFTimedTextCue** cue ) const
        {
            InterfaceType* pInterface = GetInterface( );
            auto hr = pInterface->GetCueByOriginalId( originalId, cue );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

        void AddTextCue( _In_  double start, _In_  double duration, _In_  LPCWSTR text, _COM_Outptr_opt_  IMFTimedTextCue** cue ) const
        {
            InterfaceType* pInterface = GetInterface( );
            auto hr = pInterface->AddTextCue( start, duration, text, cue );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

        void AddDataCue( _In_  double start, _In_  double duration, _In_reads_bytes_( dataSize )  const BYTE* data, _In_  DWORD dataSize, _COM_Outptr_opt_  IMFTimedTextCue** cue ) const
        {
            InterfaceType* pInterface = GetInterface( );
            auto hr = pInterface->AddDataCue( start, duration, data, dataSize, cue );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

        void RemoveCue( _In_  IMFTimedTextCue* cue ) const
        {
            InterfaceType* pInterface = GetInterface( );
            auto hr = pInterface->RemoveCue( cue );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }
    };

    class MFTimedTextRuby : public Unknown
    {
    public:
        HCC_COM_STANDARD_METHODS_IMPL( MFTimedTextRuby, Unknown, IMFTimedTextRuby, IUnknown )
    public:
        void GetRubyText( _Outptr_  LPWSTR* rubyText ) const
        {
            InterfaceType* pInterface = GetInterface( );
            auto hr = pInterface->GetRubyText( rubyText );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

        void GetRubyPosition( _Out_  MF_TIMED_TEXT_RUBY_POSITION* value ) const
        {
            InterfaceType* pInterface = GetInterface( );
            auto hr = pInterface->GetRubyPosition( value );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

        void GetRubyAlign( _Out_  MF_TIMED_TEXT_RUBY_ALIGN* value ) const
        {
            InterfaceType* pInterface = GetInterface( );
            auto hr = pInterface->GetRubyAlign( value );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

        void GetRubyReserve( _Out_  MF_TIMED_TEXT_RUBY_RESERVE* value ) const
        {
            InterfaceType* pInterface = GetInterface( );
            auto hr = pInterface->GetRubyReserve( value );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }
    };

    class MFTimedTextBouten : public Unknown
    {
    public:
        HCC_COM_STANDARD_METHODS_IMPL( MFTimedTextBouten, Unknown, IMFTimedTextBouten, IUnknown )
    public:
        void GetBoutenType( _Out_  MF_TIMED_TEXT_BOUTEN_TYPE* value ) const
        {
            InterfaceType* pInterface = GetInterface( );
            auto hr = pInterface->GetBoutenType( value );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

        void GetBoutenColor( _Out_  MFARGB* value ) const
        {
            InterfaceType* pInterface = GetInterface( );
            auto hr = pInterface->GetBoutenColor( value );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

        void GetBoutenPosition( _Out_  MF_TIMED_TEXT_BOUTEN_POSITION* value ) const
        {
            InterfaceType* pInterface = GetInterface( );
            auto hr = pInterface->GetBoutenPosition( value );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }
    };

    class MFTimedTextStyle2 : public Unknown
    {
    public:
        HCC_COM_STANDARD_METHODS_IMPL( MFTimedTextStyle2, Unknown, IMFTimedTextStyle2, IUnknown )
    public:
        void GetRuby( _COM_Outptr_result_maybenull_  IMFTimedTextRuby** ruby ) const
        {
            InterfaceType* pInterface = GetInterface( );
            auto hr = pInterface->GetRuby( ruby );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

        void GetBouten( _COM_Outptr_result_maybenull_  IMFTimedTextBouten** bouten ) const
        {
            InterfaceType* pInterface = GetInterface( );
            auto hr = pInterface->GetBouten( bouten );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

        void IsTextCombined( _Out_  BOOL* value ) const
        {
            InterfaceType* pInterface = GetInterface( );
            auto hr = pInterface->IsTextCombined( value );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

        void GetFontAngleInDegrees( _Out_  double* value ) const
        {
            InterfaceType* pInterface = GetInterface( );
            auto hr = pInterface->GetFontAngleInDegrees( value );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }
    };

    class MFMediaEngineEMENotify : public Unknown
    {
    public:
        HCC_COM_STANDARD_METHODS_IMPL( MFMediaEngineEMENotify, Unknown, IMFMediaEngineEMENotify, IUnknown )
    public:
        void Encrypted( _In_reads_bytes_opt_( cb )  const BYTE* pbInitData, _In_  DWORD cb, _In_  BSTR bstrInitDataType ) const
        {
            InterfaceType* pInterface = GetInterface( );
            pInterface->Encrypted( pbInitData, cb, bstrInitDataType );
        }

        void WaitingForKey( ) const
        {
            InterfaceType* pInterface = GetInterface( );
            pInterface->WaitingForKey( );
        }
    };

    class MFMediaKeySessionNotify2 : public MFMediaKeySessionNotify
    {
    public:
        HCC_COM_STANDARD_METHODS_IMPL( MFMediaKeySessionNotify2, MFMediaKeySessionNotify, IMFMediaKeySessionNotify2, IMFMediaKeySessionNotify )
    public:
        void KeyMessage2( _In_  MF_MEDIAKEYSESSION_MESSAGETYPE eMessageType, _In_opt_  BSTR destinationURL, _In_reads_bytes_( cbMessage )  const BYTE* pbMessage, _In_  DWORD cbMessage ) const
        {
            InterfaceType* pInterface = GetInterface( );
            pInterface->KeyMessage2( eMessageType, destinationURL, pbMessage, cbMessage );
        }

        void KeyStatusChange( ) const
        {
            InterfaceType* pInterface = GetInterface( );
            pInterface->KeyStatusChange( );
        }
    };

    class MFMediaKeySystemAccess : public Unknown
    {
    public:
        HCC_COM_STANDARD_METHODS_IMPL( MFMediaKeySystemAccess, Unknown, IMFMediaKeySystemAccess, IUnknown )
    public:
        void CreateMediaKeys( _In_opt_  IPropertyStore* pCdmCustomConfig, _COM_Outptr_  IMFMediaKeys2** ppKeys ) const
        {
            InterfaceType* pInterface = GetInterface( );
            auto hr = pInterface->CreateMediaKeys( pCdmCustomConfig, ppKeys );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

        void get_SupportedConfiguration( _COM_Outptr_  IPropertyStore** ppSupportedConfiguration ) const
        {
            InterfaceType* pInterface = GetInterface( );
            auto hr = pInterface->get_SupportedConfiguration( ppSupportedConfiguration );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

        void get_KeySystem( _Out_  BSTR* pKeySystem ) const
        {
            InterfaceType* pInterface = GetInterface( );
            auto hr = pInterface->get_KeySystem( pKeySystem );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }
    };

    class MFMediaEngineClassFactory3 : public Unknown
    {
    public:
        HCC_COM_STANDARD_METHODS_IMPL( MFMediaEngineClassFactory3, Unknown, IMFMediaEngineClassFactory3, IUnknown )
    public:
        void CreateMediaKeySystemAccess( _In_  BSTR keySystem, _In_count_( uSize )  IPropertyStore** ppSupportedConfigurationsArray, _In_  UINT uSize, _COM_Outptr_  IMFMediaKeySystemAccess** ppKeyAccess ) const
        {
            InterfaceType* pInterface = GetInterface( );
            auto hr = pInterface->CreateMediaKeySystemAccess( keySystem, ppSupportedConfigurationsArray, uSize, ppKeyAccess );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }
    };

    class MFMediaKeys2 : public MFMediaKeys
    {
    public:
        HCC_COM_STANDARD_METHODS_IMPL( MFMediaKeys2, MFMediaKeys, IMFMediaKeys2, IMFMediaKeys )
    public:
        void CreateSession2( _In_  MF_MEDIAKEYSESSION_TYPE eSessionType, _In_  IMFMediaKeySessionNotify2* pMFMediaKeySessionNotify2, _COM_Outptr_  IMFMediaKeySession2** ppSession ) const
        {
            InterfaceType* pInterface = GetInterface( );
            auto hr = pInterface->CreateSession2( eSessionType, pMFMediaKeySessionNotify2, ppSession );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

        void SetServerCertificate( _In_reads_bytes_opt_( cb )  const BYTE* pbServerCertificate, _In_  DWORD cb ) const
        {
            InterfaceType* pInterface = GetInterface( );
            auto hr = pInterface->SetServerCertificate( pbServerCertificate, cb );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

        void GetDOMException( _In_  HRESULT systemCode, _Out_  HRESULT* code ) const
        {
            InterfaceType* pInterface = GetInterface( );
            auto hr = pInterface->GetDOMException( systemCode, code );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }
    };

    class MFMediaKeySession2 : public MFMediaKeySession
    {
    public:
        HCC_COM_STANDARD_METHODS_IMPL( MFMediaKeySession2, MFMediaKeySession, IMFMediaKeySession2, IMFMediaKeySession )
    public:
        void get_KeyStatuses( _Outptr_result_buffer_( *puSize )  MFMediaKeyStatus** pKeyStatusesArray, _Out_  UINT* puSize ) const
        {
            InterfaceType* pInterface = GetInterface( );
            auto hr = pInterface->get_KeyStatuses( pKeyStatusesArray, puSize );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

        void Load( _In_  BSTR bstrSessionId, _Out_  BOOL* pfLoaded ) const
        {
            InterfaceType* pInterface = GetInterface( );
            auto hr = pInterface->Load( bstrSessionId, pfLoaded );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

        void GenerateRequest( _In_  BSTR initDataType, _In_reads_bytes_( cb )  const BYTE* pbInitData, _In_  DWORD cb ) const
        {
            InterfaceType* pInterface = GetInterface( );
            auto hr = pInterface->GenerateRequest( initDataType, pbInitData, cb );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

        void get_Expiration( _Out_  double* dblExpiration ) const
        {
            InterfaceType* pInterface = GetInterface( );
            auto hr = pInterface->get_Expiration( dblExpiration );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

        void Remove( ) const
        {
            InterfaceType* pInterface = GetInterface( );
            auto hr = pInterface->Remove( );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

        void Shutdown( ) const
        {
            InterfaceType* pInterface = GetInterface( );
            auto hr = pInterface->Shutdown( );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }
    };

    class MFMediaEngineClassFactory4 : public Unknown
    {
    public:
        HCC_COM_STANDARD_METHODS_IMPL( MFMediaEngineClassFactory4, Unknown, IMFMediaEngineClassFactory4, IUnknown )
    public:
        void CreateContentDecryptionModuleFactory( _In_  LPCWSTR keySystem, _In_  REFIID riid, _Outptr_  LPVOID* ppvObject ) const
        {
            InterfaceType* pInterface = GetInterface( );
            auto hr = pInterface->CreateContentDecryptionModuleFactory( keySystem, riid, ppvObject );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }
    };

}

#endif
