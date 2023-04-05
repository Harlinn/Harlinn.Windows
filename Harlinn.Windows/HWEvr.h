#pragma once
#ifndef HARLINN_WINDOWS_HWEVR_H_
#define HARLINN_WINDOWS_HWEVR_H_

#include <HWMFIDL.h>

#pragma comment(lib,"evr.lib")

namespace Harlinn::Windows
{
    class MFVideoPositionMapper : public Unknown
    {
    public:
        HCC_COM_STANDARD_METHODS_IMPL(MFVideoPositionMapper, Unknown, IMFVideoPositionMapper, IUnknown)
    public:
        void MapOutputCoordinateToInputStream( float xOut, float yOut, DWORD dwOutputStreamIndex, DWORD dwInputStreamIndex, float* pxIn, float* pyIn) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->MapOutputCoordinateToInputStream(xOut, yOut, dwOutputStreamIndex, dwInputStreamIndex, pxIn, pyIn);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }
    };

    class MFVideoDeviceID : public Unknown
    {
    public:
        HCC_COM_STANDARD_METHODS_IMPL(MFVideoDeviceID, Unknown, IMFVideoDeviceID, IUnknown)
    public:
        void GetDeviceID(Guid* pDeviceID) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->GetDeviceID((GUID *) pDeviceID);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }
    };

    class MFVideoDisplayControl : public Unknown
    {
    public:
        HCC_COM_STANDARD_METHODS_IMPL(MFVideoDisplayControl, Unknown, IMFVideoDisplayControl, IUnknown)
    public:
        void GetNativeVideoSize( SIZE* videoSize, SIZE* arVideoSize) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->GetNativeVideoSize(videoSize, arVideoSize);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        void GetIdealVideoSize( SIZE* minSize, SIZE* maxSize) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->GetIdealVideoSize(minSize, maxSize);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        void SetVideoPosition( const MFVideoNormalizedRect* videoNormalizedRectSource, const LPRECT destinationRect) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->SetVideoPosition(videoNormalizedRectSource, destinationRect);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        void GetVideoPosition( MFVideoNormalizedRect* videoNormalizedRectSource, LPRECT destinationRect) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->GetVideoPosition(videoNormalizedRectSource, destinationRect);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        void SetAspectRatioMode( DWORD aspectRatioMode) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->SetAspectRatioMode(aspectRatioMode);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        void GetAspectRatioMode( DWORD* aspectRatioMode) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->GetAspectRatioMode(aspectRatioMode);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        void SetVideoWindow( HWND videoWindow) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->SetVideoWindow(videoWindow);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        void GetVideoWindow( HWND* videoWindow) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->GetVideoWindow(videoWindow);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        void RepaintVideo( ) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->RepaintVideo();
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        void GetCurrentImage( BITMAPINFOHEADER* bitmapinfoHeader, BYTE** dib, DWORD* dibSize, LONGLONG* timeStamp) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->GetCurrentImage(bitmapinfoHeader, dib, dibSize, timeStamp);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        void SetBorderColor( COLORREF color) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->SetBorderColor(color);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        void GetBorderColor( COLORREF* color) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->GetBorderColor(color);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        void SetRenderingPrefs( DWORD renderFlags) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->SetRenderingPrefs(renderFlags);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        void GetRenderingPrefs( DWORD* renderFlags) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->GetRenderingPrefs(renderFlags);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        void SetFullscreen( BOOL fullscreen) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->SetFullscreen(fullscreen);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        void GetFullscreen( BOOL* fullscreen) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->GetFullscreen(fullscreen);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }
    };

    class MFVideoPresenter : public MFClockStateSink
    {
    public:
        HCC_COM_STANDARD_METHODS_IMPL(MFVideoPresenter, MFClockStateSink, IMFVideoPresenter, IMFClockStateSink)
    public:
        void ProcessMessage(MFVP_MESSAGE_TYPE messageType, ULONG_PTR param) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->ProcessMessage(messageType, param);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        void GetCurrentMediaType( IMFVideoMediaType** mediaType) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->GetCurrentMediaType(mediaType);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }
    };

    class MFDesiredSample : public Unknown
    {
    public:
        HCC_COM_STANDARD_METHODS_IMPL(MFDesiredSample, Unknown, IMFDesiredSample, IUnknown)
    public:
        void GetDesiredSampleTimeAndDuration(LONGLONG* sampleTime, LONGLONG* sampleDuration) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->GetDesiredSampleTimeAndDuration(sampleTime, sampleDuration);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        void SetDesiredSampleTimeAndDuration( LONGLONG sampleTime, LONGLONG sampleDuration) const
        {
            InterfaceType* pInterface = GetInterface();
            pInterface->SetDesiredSampleTimeAndDuration(sampleTime, sampleDuration);
        }

        void Clear( ) const
        {
            InterfaceType* pInterface = GetInterface();
            pInterface->Clear();
        }
    };

    class MFVideoMixerControl : public Unknown
    {
    public:
        HCC_COM_STANDARD_METHODS_IMPL(MFVideoMixerControl, Unknown, IMFVideoMixerControl, IUnknown)
    public:
        void SetStreamZOrder(DWORD streamID, DWORD zOrder) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->SetStreamZOrder(streamID, zOrder);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        void GetStreamZOrder( DWORD streamID, DWORD* zOrder) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->GetStreamZOrder(streamID, zOrder);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        void SetStreamOutputRect( DWORD streamID, const MFVideoNormalizedRect* videoNormalizedRectOutput) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->SetStreamOutputRect(streamID, videoNormalizedRectOutput);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        void GetStreamOutputRect( DWORD streamID, MFVideoNormalizedRect* videoNormalizedRectOutput) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->GetStreamOutputRect(streamID, videoNormalizedRectOutput);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }
    };

    class MFVideoMixerControl2 : public MFVideoMixerControl
    {
    public:
        HCC_COM_STANDARD_METHODS_IMPL(MFVideoMixerControl2, MFVideoMixerControl, IMFVideoMixerControl2, IMFVideoMixerControl)
    public:
        void SetMixingPrefs( DWORD mixFlags) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->SetMixingPrefs(mixFlags);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        void GetMixingPrefs( DWORD* mixFlags) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->GetMixingPrefs(mixFlags);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }
    };

    class MFVideoRenderer : public Unknown
    {
    public:
        HCC_COM_STANDARD_METHODS_IMPL(MFVideoRenderer, Unknown, IMFVideoRenderer, IUnknown)
    public:
        void InitializeRenderer(IMFTransform* videoMixer, IMFVideoPresenter* videoPresenter) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->InitializeRenderer(videoMixer, videoPresenter);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }
    };

    class EVRFilterConfig : public Unknown
    {
    public:
        HCC_COM_STANDARD_METHODS_IMPL(EVRFilterConfig, Unknown, IEVRFilterConfig, IUnknown)
    public:
        void SetNumberOfStreams(DWORD maxStreams) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->SetNumberOfStreams(maxStreams);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        void GetNumberOfStreams( DWORD* maxStreams) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->GetNumberOfStreams(maxStreams);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }
    };

    class EVRFilterConfigEx : public EVRFilterConfig
    {
    public:
        HCC_COM_STANDARD_METHODS_IMPL(EVRFilterConfigEx, EVRFilterConfig, IEVRFilterConfigEx, IEVRFilterConfig)
    public:
        void SetConfigPrefs(DWORD configFlags) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->SetConfigPrefs(configFlags);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        void GetConfigPrefs( DWORD* configFlags) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->GetConfigPrefs(configFlags);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

    };

    class MFTopologyServiceLookup : public Unknown
    {
    public:
        HCC_COM_STANDARD_METHODS_IMPL(MFTopologyServiceLookup, Unknown, IMFTopologyServiceLookup, IUnknown)
    public:
        void LookupService(MF_SERVICE_LOOKUP_TYPE serviceLookupType, DWORD index, const Guid& serviceId, const Guid& riid, LPVOID* ppvObjects, DWORD* pnObjects) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->LookupService(serviceLookupType, index, serviceId, riid, ppvObjects, pnObjects);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }
    };

    class MFTopologyServiceLookupClient : public Unknown
    {
    public:
        HCC_COM_STANDARD_METHODS_IMPL(MFTopologyServiceLookupClient, Unknown, IMFTopologyServiceLookupClient, IUnknown)
    public:
        void InitServicePointers(IMFTopologyServiceLookup* lookup) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->InitServicePointers(lookup);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        void ReleaseServicePointers( ) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->ReleaseServicePointers( );
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }
    };

    class EVRTrustedVideoPlugin : public Unknown
    {
    public:
        HCC_COM_STANDARD_METHODS_IMPL(EVRTrustedVideoPlugin, Unknown, IEVRTrustedVideoPlugin, IUnknown)
    public:
        void IsInTrustedVideoMode(BOOL* yes) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->IsInTrustedVideoMode(yes);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        void CanConstrict(BOOL* yes) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->CanConstrict(yes);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        void SetConstriction( DWORD constriction) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->SetConstriction(constriction);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        void DisableImageExport( BOOL disable) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->DisableImageExport(disable);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }
    };


}

#endif
