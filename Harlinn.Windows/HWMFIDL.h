#pragma once
#ifndef HARLINN_WINDOWS_HWMFIDL_H_
#define HARLINN_WINDOWS_HWMFIDL_H_
/*
   Copyright 2024 Espen Harlinn

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

#include <HWMFObjects.h>

#pragma comment(lib,"Mf.lib")
#pragma comment(lib,"strmiids.lib")

namespace Harlinn::Windows
{
    class MFMediaSession;
    class MFSourceResolver;
    class MFMediaSource;
    class MFMediaSourceEx;
    class MFClockConsumer;
    class MFMediaStream;
    class MFMediaSink;
    class MFStreamSink;
    class MFVideoSampleAllocator;
    class MFVideoSampleAllocatorNotify;
    class MFVideoSampleAllocatorNotifyEx;
    class MFVideoSampleAllocatorCallback;
    class MFVideoSampleAllocatorEx;
    class MFDXGIDeviceManagerSource;
    class MFVideoProcessorControl;
    class MFVideoProcessorControl2;
    class MFVideoProcessorControl3;
    class MFVideoRendererEffectControl;
    class MFTopology;
    class MFTopologyNode;
    class MFGetService;
    class MFClock;
    class MFPresentationClock;
    class MFPresentationTimeSource;
    class MFClockStateSink;
    class MFPresentationDescriptor;
    class MFStreamDescriptor;
    class MFMediaTypeHandler;
    class MFTimer;
    class MFShutdown;
    class MFTopoLoader;
    class MFContentProtectionManager;
    class MFContentEnabler;
    class MFMetadata;
    class MFMetadataProvider;
    class MFRateSupport;
    class MFRateControl;
    class MFTimecodeTranslate;
    class MFSeekInfo;
    class MFSimpleAudioVolume;
    class MFAudioStreamVolume;
    class MFAudioPolicy;
    class MFSampleGrabberSinkCallback;
    class MFSampleGrabberSinkCallback2;
    class MFWorkQueueServices;
    class MFWorkQueueServicesEx;
    class MFQualityManager;
    class MFQualityAdvise;
    class MFQualityAdvise2;
    class MFQualityAdviseLimits;
    class MFRealTimeClient;
    class MFRealTimeClientEx;
    class MFSequencerSource;
    class MFMediaSourceTopologyProvider;
    class MFMediaSourcePresentationProvider;
    class MFTopologyNodeAttributeEditor;
    class MFByteStreamBuffering;
    class MFByteStreamCacheControl;
    class MFByteStreamTimeSeek;
    class MFByteStreamCacheControl2;
    class MFNetCredential;
    class MFNetCredentialManager;
    class MFNetCredentialCache;
    class MFSSLCertificateManager;
    class MFNetResourceFilter;
    class MFSourceOpenMonitor;
    class MFNetProxyLocator;
    class MFNetProxyLocatorFactory;
    class MFSaveJob;
    class MFNetSchemeHandlerConfig;
    class MFSchemeHandler;
    class MFByteStreamHandler;
    class MFTrustedInput;
    class MFInputTrustAuthority;
    class MFTrustedOutput;
    class MFOutputTrustAuthority;
    class MFOutputPolicy;
    class MFOutputSchema;
    class MFSecureChannel;
    class MFSampleProtection;
    class MFMediaSinkPreroll;
    class MFFinalizableMediaSink;
    class MFStreamingSinkConfig;
    class MFRemoteProxy;
    class MFObjectReferenceStream;
    class MFPMPHost;
    class MFPMPClient;
    class MFPMPServer;
    class MFRemoteDesktopPlugin;
    class MFSAMIStyle;
    class MFTranscodeProfile;
    class MFTranscodeSinkInfoProvider;
    class MFFieldOfUseMFTUnlock;
    class MFLocalMFTRegistration;
    class MFCapturePhotoConfirmation;
    class MFPMPHostApp;
    class MFPMPClientApp;
    class MFMediaStreamSourceSampleRequest;
    class MFTrackedSample;
    class MFProtectedEnvironmentAccess;
    class MFSignedLibrary;
    class MFSystemId;
    class MFContentProtectionDevice;
    class MFContentDecryptorContext;
    class MFNetCrossOriginSupport;
    class MFHttpDownloadRequest;
    class MFHttpDownloadSession;
    class MFHttpDownloadSessionProvider;
    class MFMediaSource2;
    class MFMediaStream2;
    class MFSensorDevice;
    class MFSensorGroup;
    class MFSensorStream;
    class MFSensorTransformFactory;
    class MFSensorProfile;
    class MFSensorProfileCollection;
    class MFSensorProcessActivity;
    class MFSensorActivityReport;
    class MFSensorActivitiesReport;
    class MFSensorActivitiesReportCallback;
    class MFSensorActivityMonitor;
    class MFExtendedCameraIntrinsicModel;
    class MFExtendedCameraIntrinsicsDistortionModel6KT;
    class MFExtendedCameraIntrinsicsDistortionModelArcTan;
    class MFExtendedCameraIntrinsics;
    class MFExtendedCameraControl;
    class MFExtendedCameraController;
    class MFRelativePanelReport;
    class MFRelativePanelWatcher;
    class MFCameraOcclusionStateReport;
    class MFCameraOcclusionStateReportCallback;
    class MFCameraOcclusionStateMonitor;
    class MFVideoCaptureSampleAllocator;
    class MFSampleAllocatorControl;




    class MFMediaSession : public MFMediaEventGenerator
    {
    public:
        HCC_COM_STANDARD_METHODS_IMPL(MFMediaSession, MFMediaEventGenerator, IMFMediaSession, IMFMediaEventGenerator)
    public:
        static MFMediaSession Create(IMFAttributes* configuration = nullptr)
        {
            IMFMediaSession* itf = nullptr;
            auto hr = MFCreateMediaSession(configuration, &itf);
            HCC_COM_CHECK_HRESULT(hr);
            return MFMediaSession(itf);
        }

        void SetTopology( DWORD setTopologyFlags, IMFTopology* topology) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->SetTopology(setTopologyFlags, topology);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        inline void SetTopology( DWORD setTopologyFlags, const MFTopology& topology ) const;

        void ClearTopologies( ) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->ClearTopologies();
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        void Start(const GUID* timeFormatId, const PROPVARIANT* startPosition) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->Start(timeFormatId, startPosition);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        void Pause( ) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->Pause();
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        void Stop( ) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->Stop();
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        void Close( ) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->Close();
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        void Shutdown( ) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->Shutdown();
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        void GetClock(IMFClock** clock) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->GetClock(clock);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }


        template<typename T = MFClock>
            requires std::is_base_of_v<MFClock,T>
        T GetClock( )
        {
            using ItfT = typename T::InterfaceType;
            ItfT* ptr = nullptr;
            GetClock( &ptr );
            return T( ptr );
        }

        void GetSessionCapabilities( DWORD* capabilities) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->GetSessionCapabilities(capabilities);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        void GetFullTopology( DWORD getFullTopologyFlags, TOPOID topoId, IMFTopology** fullTopology) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->GetFullTopology(getFullTopologyFlags, topoId, fullTopology);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        template<typename T>
            requires std::is_base_of_v<Unknown,T>
        T GetService(const Guid& serviceId) const
        {
            using ItfT = typename T::InterfaceType;
            ItfT* itf = nullptr;
            InterfaceType* pInterface = GetInterface();
            auto hr = ::MFGetService(pInterface, serviceId, __uuidof(ItfT),(void**)&itf);
            HCC_COM_CHECK_HRESULT(hr);
            return T(itf);
        }

    };


    class MFSourceResolver : public Unknown
    {
    public:
        HCC_COM_STANDARD_METHODS_IMPL(MFSourceResolver, Unknown, IMFSourceResolver, IUnknown)
    public:
        static MFSourceResolver Create()
        {
            IMFSourceResolver* itf = nullptr;
            auto hr = MFCreateSourceResolver(&itf);
            HCC_COM_CHECK_HRESULT(hr);
            return MFSourceResolver(itf);
        }

        void CreateObjectFromURL( LPCWSTR url, DWORD flags, IPropertyStore* props, MF_OBJECT_TYPE* objectType, IUnknown** object) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->CreateObjectFromURL(url, flags, props, objectType, object);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }
        void CreateObjectFromURL(LPCWSTR url, DWORD flags, IUnknown** object) const
        {
            MF_OBJECT_TYPE objectType = MF_OBJECT_INVALID;
            CreateObjectFromURL(url, flags, nullptr, &objectType, object);
        }
        Unknown CreateObjectFromURL(LPCWSTR url, DWORD flags) const
        {
            IUnknown* itf = nullptr;
            CreateObjectFromURL(url, flags, &itf);
            return Unknown(itf);
        }
        Unknown CreateObjectFromURL( const WideString& url, DWORD flags ) const
        {
            IUnknown* itf = nullptr;
            CreateObjectFromURL( url.c_str(), flags, &itf );
            return Unknown( itf );
        }



        void CreateObjectFromByteStream( IMFByteStream* byteStream, LPCWSTR url, DWORD flags, IPropertyStore* props, MF_OBJECT_TYPE* objectType, IUnknown** object) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->CreateObjectFromByteStream(byteStream, url, flags, props, objectType, object);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        void BeginCreateObjectFromURL( LPCWSTR url, DWORD flags, IPropertyStore* props, IUnknown** cancelCookie, IMFAsyncCallback* callback, IUnknown* state) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->BeginCreateObjectFromURL(url, flags, props, cancelCookie, callback, state);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        void EndCreateObjectFromURL( IMFAsyncResult* result, MF_OBJECT_TYPE* objectType, IUnknown** object) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->EndCreateObjectFromURL(result, objectType, object);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        void BeginCreateObjectFromByteStream( IMFByteStream* byteStream, LPCWSTR url, DWORD flags, IPropertyStore* props, IUnknown** cancelCookie, IMFAsyncCallback* callback, IUnknown* state) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->BeginCreateObjectFromByteStream(byteStream, url, flags, props, cancelCookie, callback, state);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        void EndCreateObjectFromByteStream( IMFAsyncResult* result, MF_OBJECT_TYPE* objectType, IUnknown** object) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->EndCreateObjectFromByteStream(result, objectType, object);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        void CancelObjectCreation( IUnknown* cancelCookie) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->CancelObjectCreation(cancelCookie);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }
    };

    
    class MFMediaSource : public MFMediaEventGenerator
    {
    public:
        HCC_COM_STANDARD_METHODS_IMPL(MFMediaSource, MFMediaEventGenerator, IMFMediaSource, IMFMediaEventGenerator)
    public:
        static MFMediaSource CreateDeviceSource(IMFAttributes* attributes)
        {
            IMFMediaSource* itf = nullptr;
            auto hr = MFCreateDeviceSource(attributes, &itf);
            HCC_COM_CHECK_HRESULT(hr);
            return MFMediaSource(itf);
        }
        static MFMediaSource CreateAggregateSource(IMFCollection* sourceCollection)
        {
            IMFMediaSource* itf = nullptr;
            auto hr = MFCreateAggregateSource(sourceCollection, &itf);
            HCC_COM_CHECK_HRESULT(hr);
            return MFMediaSource(itf);
        }
        
        void GetCharacteristics( DWORD* characteristics ) const
        {
            InterfaceType* pInterface = GetInterface( );
            HRESULT hr = pInterface->GetCharacteristics( characteristics );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

        void CreatePresentationDescriptor( IMFPresentationDescriptor** presentationDescriptor) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->CreatePresentationDescriptor(presentationDescriptor);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }
        MFPresentationDescriptor CreatePresentationDescriptor() const;
        

        void Start( IMFPresentationDescriptor* presentationDescriptor, const GUID* timeFormatId, const PROPVARIANT* startPosition) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->Start(presentationDescriptor, timeFormatId, startPosition);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        void Stop( ) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->Stop();
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        void Pause( ) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->Pause();
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        void Shutdown( ) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->Shutdown();
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        };
    };

    class MFMediaSourceEx : public MFMediaSource
    {
    public:
        HCC_COM_STANDARD_METHODS_IMPL(MFMediaSourceEx, MFMediaSource, IMFMediaSourceEx, IMFMediaSource)
    public:
        void GetSourceAttributes(IMFAttributes** attributes) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->GetSourceAttributes(attributes);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        void GetStreamAttributes( DWORD streamIdentifier, IMFAttributes** attributes) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->GetStreamAttributes(streamIdentifier, attributes);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        void SetD3DManager( IUnknown* manager) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->SetD3DManager(manager);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }
    };

    class MFClockConsumer : public Unknown
    {
    public:
        HCC_COM_STANDARD_METHODS_IMPL(MFClockConsumer, Unknown, IMFClockConsumer, IUnknown)
    public:
        void SetPresentationClock(IMFPresentationClock* presentationClock) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->SetPresentationClock(presentationClock);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        void GetPresentationClock( IMFPresentationClock** presentationClock) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->GetPresentationClock(presentationClock);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }
    };

    class MFMediaStream : public MFMediaEventGenerator
    {
    public:
        HCC_COM_STANDARD_METHODS_IMPL(MFMediaStream, MFMediaEventGenerator, IMFMediaStream, IMFMediaEventGenerator)
    public:
        void GetMediaSource(IMFMediaSource** mediaSource) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->GetMediaSource(mediaSource);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        void GetStreamDescriptor( IMFStreamDescriptor** streamDescriptor) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->GetStreamDescriptor(streamDescriptor);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        void RequestSample( IUnknown* token) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->RequestSample(token);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }
    };


    class MFMediaSink : public Unknown
    {
    public:
        HCC_COM_STANDARD_METHODS_IMPL(MFMediaSink, Unknown, IMFMediaSink, IUnknown)
    public:
        static MFMediaSink CreateAudioRenderer(IMFAttributes* audioAttributes)
        {
            IMFMediaSink* itf = nullptr;
            auto hr = MFCreateAudioRenderer(audioAttributes, &itf);
            HCC_COM_CHECK_HRESULT(hr);
            return MFMediaSink(itf);
        }
        static MFMediaSink CreateMPEG4MediaSink(IMFByteStream* byteStream, IMFMediaType* videoMediaType, IMFMediaType* audioMediaType )
        {
            IMFMediaSink* itf = nullptr;
            auto hr = MFCreateMPEG4MediaSink(byteStream, videoMediaType, audioMediaType, &itf);
            HCC_COM_CHECK_HRESULT(hr);
            return MFMediaSink(itf);
        }
        static MFMediaSink Create3GPMediaSink(IMFByteStream* byteStream, IMFMediaType* videoMediaType, IMFMediaType* audioMediaType)
        {
            IMFMediaSink* itf = nullptr;
            auto hr = MFCreate3GPMediaSink(byteStream, videoMediaType, audioMediaType, &itf);
            HCC_COM_CHECK_HRESULT(hr);
            return MFMediaSink(itf);
        }
        static MFMediaSink CreateMP3MediaSink(IMFByteStream* targetByteStream)
        {
            IMFMediaSink* itf = nullptr;
            auto hr = MFCreateMP3MediaSink(targetByteStream, &itf);
            HCC_COM_CHECK_HRESULT(hr);
            return MFMediaSink(itf);
        }
        static MFMediaSink CreateAC3MediaSink(IMFByteStream* targetByteStream, IMFMediaType* audioMediaType)
        {
            IMFMediaSink* itf = nullptr;
            auto hr = MFCreateAC3MediaSink(targetByteStream, audioMediaType, &itf);
            HCC_COM_CHECK_HRESULT(hr);
            return MFMediaSink(itf);
        }
        static MFMediaSink CreateADTSMediaSink(IMFByteStream* targetByteStream, IMFMediaType* audioMediaType)
        {
            IMFMediaSink* itf = nullptr;
            auto hr = MFCreateADTSMediaSink(targetByteStream, audioMediaType, &itf);
            HCC_COM_CHECK_HRESULT(hr);
            return MFMediaSink(itf);
        }
        static MFMediaSink CreateMuxSink(GUID outputSubType, IMFAttributes* outputAttributes, IMFByteStream* outputByteStream)
        {
            IMFMediaSink* itf = nullptr;
            auto hr = MFCreateMuxSink(outputSubType, outputAttributes, outputByteStream, &itf);
            HCC_COM_CHECK_HRESULT(hr);
            return MFMediaSink(itf);
        }
        static MFMediaSink CreateFMPEG4MediaSink(IMFByteStream* byteStream, IMFMediaType* videoMediaType, IMFMediaType* audioMediaType)
        {
            IMFMediaSink* itf = nullptr;
            auto hr = MFCreateFMPEG4MediaSink(byteStream, videoMediaType, audioMediaType, &itf);
            HCC_COM_CHECK_HRESULT(hr);
            return MFMediaSink(itf);
        }
        static MFMediaSink CreateAVIMediaSink(IMFByteStream* byteStream, IMFMediaType* videoMediaType, IMFMediaType* audioMediaType)
        {
            IMFMediaSink* itf = nullptr;
            auto hr = MFCreateAVIMediaSink(byteStream, videoMediaType, audioMediaType, &itf);
            HCC_COM_CHECK_HRESULT(hr);
            return MFMediaSink(itf);
        }
        static MFMediaSink CreateWAVEMediaSink(IMFByteStream* targetByteStream, IMFMediaType* audioMediaType)
        {
            IMFMediaSink* itf = nullptr;
            auto hr = MFCreateWAVEMediaSink(targetByteStream, audioMediaType, &itf);
            HCC_COM_CHECK_HRESULT(hr);
            return MFMediaSink(itf);
        }


        void GetCharacteristics( DWORD* characteristics) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->GetCharacteristics(characteristics);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        void AddStreamSink( DWORD streamSinkIdentifier, IMFMediaType* mediaType, IMFStreamSink** streamSink) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->AddStreamSink(streamSinkIdentifier, mediaType, streamSink);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        void RemoveStreamSink( DWORD streamSinkIdentifier) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->RemoveStreamSink(streamSinkIdentifier);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        void GetStreamSinkCount( DWORD* streamSinkCount) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->GetStreamSinkCount(streamSinkCount);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        void GetStreamSinkByIndex( DWORD index, IMFStreamSink** streamSink) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->GetStreamSinkByIndex(index, streamSink);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        void GetStreamSinkById( DWORD streamSinkIdentifier, IMFStreamSink** streamSink) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->GetStreamSinkById(streamSinkIdentifier, streamSink);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        void SetPresentationClock( IMFPresentationClock* presentationClock) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->SetPresentationClock(presentationClock);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        void GetPresentationClock( IMFPresentationClock** presentationClock) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->GetPresentationClock(presentationClock);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        void Shutdown( ) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->Shutdown();
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }
    };


    class MFStreamSink : public MFMediaEventGenerator
    {
    public:
        HCC_COM_STANDARD_METHODS_IMPL(MFStreamSink, MFMediaEventGenerator, IMFStreamSink, IMFMediaEventGenerator)
    public:
        void GetMediaSink( IMFMediaSink** mediaSink) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->GetMediaSink(mediaSink);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        void GetIdentifier( DWORD* identifier) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->GetIdentifier(identifier);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        void GetMediaTypeHandler( IMFMediaTypeHandler** handler) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->GetMediaTypeHandler(handler);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        void ProcessSample( IMFSample* sample) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->ProcessSample(sample);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        void PlaceMarker( MFSTREAMSINK_MARKER_TYPE markerType, const PROPVARIANT* markerValue, const PROPVARIANT* contextValue) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->PlaceMarker(markerType, markerValue, contextValue);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        void Flush( ) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->Flush();
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }
    };

    class MFVideoSampleAllocator : public Unknown
    {
    public:
        HCC_COM_STANDARD_METHODS_IMPL(MFVideoSampleAllocator, Unknown, IMFVideoSampleAllocator, IUnknown)
    public:
        void SetDirectXManager(IUnknown* manager) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->SetDirectXManager(manager);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        void UninitializeSampleAllocator( ) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->UninitializeSampleAllocator();
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        void InitializeSampleAllocator( DWORD numberOfRequestedFrames, IMFMediaType* mediaType) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->InitializeSampleAllocator(numberOfRequestedFrames, mediaType);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        void AllocateSample( IMFSample** sample) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->AllocateSample(sample);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }
    };


    class MFVideoSampleAllocatorNotify : public Unknown
    {
    public:
        HCC_COM_STANDARD_METHODS_IMPL(MFVideoSampleAllocatorNotify, Unknown, IMFVideoSampleAllocatorNotify, IUnknown)
    public:
        void NotifyRelease()
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->NotifyRelease( );
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }
    };


    class MFVideoSampleAllocatorNotifyEx : public MFVideoSampleAllocatorNotify
    {
    public:
        HCC_COM_STANDARD_METHODS_IMPL(MFVideoSampleAllocatorNotifyEx, MFVideoSampleAllocatorNotify, IMFVideoSampleAllocatorNotifyEx, IMFVideoSampleAllocatorNotify)
    public:
        void NotifyPrune(IMFSample* sample) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->NotifyPrune(sample);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }
    };


    class MFVideoSampleAllocatorCallback : public Unknown
    {
    public:
        HCC_COM_STANDARD_METHODS_IMPL(MFVideoSampleAllocatorCallback, Unknown, IMFVideoSampleAllocatorCallback, IUnknown)
    public:
        void SetCallback(IMFVideoSampleAllocatorNotify* notify) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->SetCallback(notify);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        void GetFreeSampleCount(LONG* freeSampleCount) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->GetFreeSampleCount(freeSampleCount);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }
    };

    class MFVideoSampleAllocatorEx : public MFVideoSampleAllocator
    {
    public:
        HCC_COM_STANDARD_METHODS_IMPL(MFVideoSampleAllocatorEx, MFVideoSampleAllocator, IMFVideoSampleAllocatorEx, IMFVideoSampleAllocator)
    public:
        void InitializeSampleAllocatorEx( DWORD numberOfInitialSamples, DWORD maximumSamples, IMFAttributes* attributes, IMFMediaType* mediaType) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->InitializeSampleAllocatorEx(numberOfInitialSamples, maximumSamples, attributes, mediaType);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }
    };

    class MFDXGIDeviceManagerSource : public Unknown
    {
    public:
        HCC_COM_STANDARD_METHODS_IMPL(MFDXGIDeviceManagerSource, Unknown, IMFDXGIDeviceManagerSource, IUnknown)
    public:
        void GetManager(IMFDXGIDeviceManager** manager) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->GetManager(manager);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }
    };


    class MFVideoProcessorControl : public Unknown
    {
    public:
        HCC_COM_STANDARD_METHODS_IMPL(MFVideoProcessorControl, Unknown, IMFVideoProcessorControl, IUnknown)
    public:
        void SetBorderColor( MFARGB* borderColor) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->SetBorderColor(borderColor);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        void SetSourceRectangle( RECT* sourceRectangle) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->SetSourceRectangle(sourceRectangle);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        void SetDestinationRectangle( RECT* destinationRectangle) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->SetDestinationRectangle(destinationRectangle);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        void SetMirror( MF_VIDEO_PROCESSOR_MIRROR mirror) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->SetMirror(mirror);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        void SetRotation( MF_VIDEO_PROCESSOR_ROTATION rotation) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->SetRotation(rotation);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        void SetConstrictionSize( SIZE* constrictionSize) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->SetConstrictionSize(constrictionSize);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

    };

    class MFVideoProcessorControl2 : public MFVideoProcessorControl
    {
    public:
        HCC_COM_STANDARD_METHODS_IMPL(MFVideoProcessorControl2, MFVideoProcessorControl, IMFVideoProcessorControl2, IMFVideoProcessorControl)
    public:
        void SetRotationOverride( UINT rotation) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->SetRotationOverride(rotation);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        void EnableHardwareEffects( BOOL enabled) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->EnableHardwareEffects(enabled);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        void GetSupportedHardwareEffects( UINT* supportedHardwareEffects) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->GetSupportedHardwareEffects(supportedHardwareEffects);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }
    };


    class MFVideoProcessorControl3 : public MFVideoProcessorControl2
    {
    public:
        HCC_COM_STANDARD_METHODS_IMPL(MFVideoProcessorControl3, MFVideoProcessorControl2, IMFVideoProcessorControl3, IMFVideoProcessorControl2)
    public:
        void GetNaturalOutputType(IMFMediaType** mediaType) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->GetNaturalOutputType(mediaType);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        void EnableSphericalVideoProcessing(BOOL enable, MFVideoSphericalFormat videoSphericalFormat, MFVideoSphericalProjectionMode videoSphericalProjectionMode) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->EnableSphericalVideoProcessing(enable, videoSphericalFormat, videoSphericalProjectionMode);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        void SetSphericalVideoProperties(float x, float y, float z, float w, float fieldOfView) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->SetSphericalVideoProperties(x, y, z, w, fieldOfView);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        void SetOutputDevice(IUnknown* outputDevice) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->SetOutputDevice(outputDevice);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }
    };

    class MFVideoRendererEffectControl : public Unknown
    {
    public:
        HCC_COM_STANDARD_METHODS_IMPL(MFVideoRendererEffectControl, Unknown, IMFVideoRendererEffectControl, IUnknown)
    public:
        void OnAppServiceConnectionEstablished(IUnknown* appServiceConnection) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->OnAppServiceConnectionEstablished(appServiceConnection);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }
    };


    class MFTopology : public MFAttributes
    {
    public:
        HCC_COM_STANDARD_METHODS_IMPL(MFTopology, MFAttributes, IMFTopology, IMFAttributes)
    public:
        static MFTopology Create()
        {
            IMFTopology* itf = nullptr;
            auto hr = MFCreateTopology(&itf);
            HCC_COM_CHECK_HRESULT(hr);
            return MFTopology(itf);
        }


        void GetTopologyID(TOPOID* topoId) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->GetTopologyID(topoId);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }
        TOPOID GetTopologyID() const
        {
            TOPOID result{};
            GetTopologyID(&result);
            return result;
        }


        void AddNode(IMFTopologyNode* node) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->AddNode(node);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        void RemoveNode(IMFTopologyNode* node) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->RemoveNode(node);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        void GetNodeCount(WORD* nodes) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->GetNodeCount(nodes);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }
        WORD GetNodeCount() const
        {
            WORD result = 0;
            GetNodeCount(&result);
            return result;
        }



        void GetNode(WORD index, IMFTopologyNode** node) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->GetNode(index, node);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }
        inline MFTopologyNode GetNode(WORD index) const;



        void Clear() const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->Clear();
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        void CloneFrom(IMFTopology* topology) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->CloneFrom(topology);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        void GetNodeByID(TOPOID topoNodeID, IMFTopologyNode** node) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->GetNodeByID(topoNodeID, node);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }
        inline MFTopologyNode GetNodeByID(TOPOID topoNodeID) const;

        void GetSourceNodeCollection(IMFCollection** collection) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->GetSourceNodeCollection(collection);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }
        inline MFCollectionT<MFTopologyNode> GetSourceNodeCollection() const;

        void GetOutputNodeCollection(IMFCollection** collection) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->GetOutputNodeCollection(collection);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }
        inline MFCollectionT<MFTopologyNode> GetOutputNodeCollection() const;

    };

    inline void MFMediaSession::SetTopology( DWORD setTopologyFlags, const MFTopology& topology ) const
    {
        SetTopology( setTopologyFlags, topology.GetInterfacePointer<IMFTopology>( ) );
    }


    class MFTopologyNode : public MFAttributes
    {
    public:
        HCC_COM_STANDARD_METHODS_IMPL(MFTopologyNode, MFAttributes, IMFTopologyNode, IMFAttributes)
    public:
        static MFTopologyNode Create(MF_TOPOLOGY_TYPE nodeType)
        {
            IMFTopologyNode* itf = nullptr;
            auto hr = MFCreateTopologyNode(nodeType, &itf);
            HCC_COM_CHECK_HRESULT(hr);
            return MFTopologyNode(itf);
        }

        static MFTopologyNode CreateOutputNode()
        {
            return Create(MF_TOPOLOGY_OUTPUT_NODE);
        }
        static MFTopologyNode CreateSourceStreamNode()
        {
            return Create(MF_TOPOLOGY_SOURCESTREAM_NODE);
        }
        static MFTopologyNode CreateTransformNode()
        {
            return Create(MF_TOPOLOGY_TRANSFORM_NODE);
        }
        static MFTopologyNode CreateTeeNode()
        {
            return Create(MF_TOPOLOGY_TEE_NODE);
        }


        void SetObject( IUnknown* object) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->SetObject(object);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        void GetObject( IUnknown** object) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->GetObject(object);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        Unknown GetObject() const
        {
            IUnknown* itf = nullptr;
            GetObject(&itf);
            return Unknown(itf);
        }


        void GetNodeType( MF_TOPOLOGY_TYPE* topologyType) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->GetNodeType(topologyType);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }
        MF_TOPOLOGY_TYPE GetNodeType() const
        {
            MF_TOPOLOGY_TYPE result{};
            GetNodeType(&result);
            return result;
        }


        void GetTopoNodeID( TOPOID* topoNodeID) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->GetTopoNodeID(topoNodeID);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        void SetTopoNodeID( TOPOID topoNodeID) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->SetTopoNodeID(topoNodeID);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        void GetInputCount( DWORD* inputCount) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->GetInputCount(inputCount);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        void GetOutputCount( DWORD* outputCount) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->GetOutputCount(outputCount);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        void ConnectOutput( DWORD outputIndex, IMFTopologyNode* downstreamNode, DWORD inputIndexOnDownstreamNode) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->ConnectOutput(outputIndex, downstreamNode, inputIndexOnDownstreamNode);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        void DisconnectOutput( DWORD outputIndex) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->DisconnectOutput(outputIndex);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        void GetInput( DWORD inputIndex, IMFTopologyNode** upstreamNode, DWORD* outputIndexOnUpstreamNode) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->GetInput(inputIndex, upstreamNode, outputIndexOnUpstreamNode);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        void GetOutput( DWORD outputIndex, IMFTopologyNode** downstreamNode, DWORD* inputIndexOnDownstreamNode) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->GetOutput(outputIndex, downstreamNode, inputIndexOnDownstreamNode);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        void SetOutputPrefType( DWORD outputIndex, IMFMediaType* mediaType) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->SetOutputPrefType(outputIndex, mediaType);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        void GetOutputPrefType( DWORD outputIndex, IMFMediaType** mediaType) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->GetOutputPrefType(outputIndex, mediaType);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        void SetInputPrefType( DWORD inputIndex, IMFMediaType* mediaType) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->SetInputPrefType(inputIndex, mediaType);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        void GetInputPrefType( DWORD inputIndex, IMFMediaType** mediaType) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->GetInputPrefType(inputIndex, mediaType);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        void CloneFrom( IMFTopologyNode* node) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->CloneFrom(node);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }
    };

    inline MFTopologyNode MFTopology::GetNode(WORD index) const
    {
        IMFTopologyNode* itf = nullptr;
        GetNode(index, &itf);
        return MFTopologyNode(itf);
    }
    inline MFTopologyNode MFTopology::GetNodeByID(TOPOID topoNodeID) const
    {
        IMFTopologyNode* itf = nullptr;
        GetNodeByID(topoNodeID, &itf);
        return MFTopologyNode(itf);
    }

    inline MFCollectionT<MFTopologyNode> MFTopology::GetSourceNodeCollection() const
    {
        IMFCollection* itf = nullptr;
        GetSourceNodeCollection(&itf);
        return MFCollectionT<MFTopologyNode>(itf);
    }

    inline MFCollectionT<MFTopologyNode> MFTopology::GetOutputNodeCollection() const
    {
        IMFCollection* itf = nullptr;
        GetOutputNodeCollection(&itf);
        return MFCollectionT<MFTopologyNode>(itf);
    }



    class MFGetService : public Unknown
    {
    public:
        HCC_COM_STANDARD_METHODS_IMPL(MFGetService, Unknown, IMFGetService, IUnknown)
    public:
        void GetService(const Guid& guidService, const Guid& riid, LPVOID* object) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->GetService(guidService, riid, object);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        template<typename T>
            requires std::is_base_of_v<Unknown, T>
        T GetService(const Guid& guidService) const
        {
            using ItfT = typename T::InterfaceType;
            ItfT* itf = nullptr;
            const Guid riid = __uuidof(ItfT);
            GetService(guidService, riid, (void**)&itf);
            return T(itf);
        }

        template<typename T>
            requires std::is_base_of_v<IUnknown, T>
        void GetService(const Guid& guidService, T** result) const
        {
            const Guid riid = __uuidof(T);
            GetService(guidService, riid, (void**)&result);
        }
    };


    class MFClock : public Unknown
    {
    public:
        HCC_COM_STANDARD_METHODS_IMPL(MFClock, Unknown, IMFClock, IUnknown)
    public:
        void GetClockCharacteristics( DWORD* characteristics) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->GetClockCharacteristics(characteristics);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        void GetCorrelatedTime( DWORD reserved, LONGLONG* clockTime, MFTIME* systemTime) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->GetCorrelatedTime(reserved, clockTime, systemTime);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        void GetContinuityKey( DWORD* continuityKey) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->GetContinuityKey(continuityKey);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        void GetState( DWORD reserved, MFCLOCK_STATE* clockState) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->GetState(reserved, clockState);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        void GetProperties( MFCLOCK_PROPERTIES* clockProperties) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->GetProperties(clockProperties);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }
    };



    class MFPresentationClock : public MFClock
    {
    public:
        HCC_COM_STANDARD_METHODS_IMPL(MFPresentationClock, MFClock, IMFPresentationClock, IMFClock)
    public:
        static MFPresentationClock Create()
        {
            IMFPresentationClock* itf = nullptr;
            auto hr = MFCreatePresentationClock(&itf);
            HCC_COM_CHECK_HRESULT(hr);
            return MFPresentationClock(itf);
        }


        void SetTimeSource( IMFPresentationTimeSource* timeSource) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->SetTimeSource(timeSource);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        void GetTimeSource( IMFPresentationTimeSource** timeSource) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->GetTimeSource(timeSource);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        void GetTime( MFTIME* clockTime) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->GetTime(clockTime);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        void AddClockStateSink( IMFClockStateSink* stateSink) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->AddClockStateSink(stateSink);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        void RemoveClockStateSink( IMFClockStateSink* stateSink) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->RemoveClockStateSink(stateSink);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        void Start( LONGLONG clockStartOffset) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->Start(clockStartOffset);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        void Stop( ) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->Stop();
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        void Pause( ) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->Pause();
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }
    };

    class MFPresentationTimeSource : public MFClock
    {
    public:
        HCC_COM_STANDARD_METHODS_IMPL(MFPresentationTimeSource, MFClock, IMFPresentationTimeSource, IMFClock)
    public:
        static MFPresentationTimeSource Create()
        {
            IMFPresentationTimeSource* itf = nullptr;
            auto hr = MFCreateSystemTimeSource(&itf);
            HCC_COM_CHECK_HRESULT(hr);
            return MFPresentationTimeSource(itf);
        }

        void GetUnderlyingClock(IMFClock** clock) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->GetUnderlyingClock(clock);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }
    };

    class MFClockStateSink : public Unknown
    {
    public:
        HCC_COM_STANDARD_METHODS_IMPL(MFClockStateSink, Unknown, IMFClockStateSink, IUnknown)
    public:
        void OnClockStart( MFTIME systemTime, LONGLONG clockStartOffset) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->OnClockStart(systemTime, clockStartOffset);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        void OnClockStop( MFTIME systemTime) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->OnClockStop(systemTime);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        void OnClockPause( MFTIME systemTime) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->OnClockPause(systemTime);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        void OnClockRestart( MFTIME systemTime) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->OnClockRestart(systemTime);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        void OnClockSetRate( MFTIME systemTime, float rate) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->OnClockSetRate(systemTime, rate);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }
    };


    
    class MFPresentationDescriptor : public MFAttributes
    {
    public:
        HCC_COM_STANDARD_METHODS_IMPL(MFPresentationDescriptor, MFAttributes, IMFPresentationDescriptor, IMFAttributes)
    public:
        static MFPresentationDescriptor Create(DWORD numberOfStreamDescriptors, IMFStreamDescriptor** streamDescriptors)
        {
            IMFPresentationDescriptor* itf = nullptr;
            auto hr = MFCreatePresentationDescriptor(numberOfStreamDescriptors, streamDescriptors, &itf);
            HCC_COM_CHECK_HRESULT(hr);
            return MFPresentationDescriptor(itf);
        }


        void GetStreamDescriptorCount( DWORD* descriptorCount) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->GetStreamDescriptorCount(descriptorCount);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }
        DWORD GetStreamDescriptorCount() const
        {
            DWORD result = 0;
            GetStreamDescriptorCount(&result);
            return result;
        }

        void GetStreamDescriptorByIndex( DWORD index, BOOL* selected, IMFStreamDescriptor** descriptor) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->GetStreamDescriptorByIndex(index, selected, descriptor);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }
        MFStreamDescriptor GetStreamDescriptorByIndex(DWORD index, BOOL* selected) const;


        void SelectStream( DWORD descriptorIndex) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->SelectStream(descriptorIndex);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        void DeselectStream( DWORD descriptorIndex) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->DeselectStream(descriptorIndex);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        void Clone( IMFPresentationDescriptor** presentationDescriptor) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->Clone(presentationDescriptor);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }
    };
    inline MFPresentationDescriptor MFMediaSource::CreatePresentationDescriptor() const
    {
        IMFPresentationDescriptor* itf;
        CreatePresentationDescriptor(&itf);
        return MFPresentationDescriptor(itf);
    }

    
    class MFStreamDescriptor : public MFAttributes
    {
    public:
        HCC_COM_STANDARD_METHODS_IMPL(MFStreamDescriptor, MFAttributes, IMFStreamDescriptor, IMFAttributes)
    public:
        static MFStreamDescriptor Create(DWORD streamIdentifier, DWORD numberOfMediaTypes, IMFMediaType** mediaTypes)
        {
            IMFStreamDescriptor* itf = nullptr;
            auto hr = MFCreateStreamDescriptor(streamIdentifier, numberOfMediaTypes, mediaTypes, &itf);
            HCC_COM_CHECK_HRESULT(hr);
            return MFStreamDescriptor(itf);
        }


        void GetStreamIdentifier(DWORD* streamIdentifier) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->GetStreamIdentifier(streamIdentifier);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }
        DWORD GetStreamIdentifier() const
        {
            DWORD result = 0;
            GetStreamIdentifier(&result);
            return result;
        }

        void GetMediaTypeHandler( IMFMediaTypeHandler** mediaTypeHandler) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->GetMediaTypeHandler(mediaTypeHandler);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }
        MFMediaTypeHandler GetMediaTypeHandler() const;
    };
    inline MFStreamDescriptor MFPresentationDescriptor::GetStreamDescriptorByIndex(DWORD index, BOOL* selected) const
    {
        IMFStreamDescriptor* itf = nullptr;
        GetStreamDescriptorByIndex(index, selected, &itf);
        return MFStreamDescriptor(itf);
    }



    class MFMediaTypeHandler : public Unknown
    {
    public:
        HCC_COM_STANDARD_METHODS_IMPL(MFMediaTypeHandler, Unknown, IMFMediaTypeHandler, IUnknown)
    public:
        static MFMediaTypeHandler Create()
        {
            IMFMediaTypeHandler* itf = nullptr;
            auto hr = MFCreateSimpleTypeHandler(&itf);
            HCC_COM_CHECK_HRESULT(hr);
            return MFMediaTypeHandler(itf);
        }


        bool IsMediaTypeSupported(IMFMediaType* mediaType, IMFMediaType** closestMediaType) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->IsMediaTypeSupported(mediaType, closestMediaType);
            if (hr != MF_E_INVALIDMEDIATYPE)
            {
                HCC_COM_CHECK_HRESULT2(hr, pInterface);
            }
            return hr == S_OK;
        }

        void GetMediaTypeCount( DWORD* mediaTypeCount) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->GetMediaTypeCount(mediaTypeCount);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        void GetMediaTypeByIndex( DWORD index, IMFMediaType** mediaType) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->GetMediaTypeByIndex(index, mediaType);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        void SetCurrentMediaType( IMFMediaType* mediaType) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->SetCurrentMediaType(mediaType);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        void GetCurrentMediaType( IMFMediaType** mediaType) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->GetCurrentMediaType(mediaType);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        void GetMajorType( Guid* guidMajorType) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->GetMajorType((GUID *)guidMajorType);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }
        Guid GetMajorType() const
        {
            Guid result;
            GetMajorType(&result);
            return result;
        }
    };
    inline MFMediaTypeHandler MFStreamDescriptor::GetMediaTypeHandler() const
    {
        IMFMediaTypeHandler* itf = nullptr;
        GetMediaTypeHandler(&itf);
        return MFMediaTypeHandler(itf);
    }


    class MFTimer : public Unknown
    {
    public:
        HCC_COM_STANDARD_METHODS_IMPL(MFTimer, Unknown, IMFTimer, IUnknown)
    public:
        void SetTimer( DWORD flags, LONGLONG clockTime, IMFAsyncCallback* callback, IUnknown* state, IUnknown** key) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->SetTimer(flags, clockTime, callback, state, key);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        void CancelTimer(IUnknown* key) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->CancelTimer(key);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }
    };


    class MFShutdown : public Unknown
    {
    public:
        HCC_COM_STANDARD_METHODS_IMPL(MFShutdown, Unknown, IMFShutdown, IUnknown)
    public:
        void Shutdown() const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->Shutdown();
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        void GetShutdownStatus(MFSHUTDOWN_STATUS* status) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->GetShutdownStatus(status);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }
    };


    class MFTopoLoader : public Unknown
    {
    public:
        HCC_COM_STANDARD_METHODS_IMPL(MFTopoLoader, Unknown, IMFTopoLoader, IUnknown)
    public:
        static MFTopoLoader Create()
        {
            IMFTopoLoader* itf = nullptr;
            auto hr = MFCreateTopoLoader(&itf);
            HCC_COM_CHECK_HRESULT(hr);
            return MFTopoLoader(itf);
        }

        void Load(IMFTopology* inputTopo, IMFTopology** outputTopo, IMFTopology* currentTopo) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->Load(inputTopo, outputTopo, currentTopo);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }
    };

    class MFContentProtectionManager : public Unknown
    {
    public:
        HCC_COM_STANDARD_METHODS_IMPL(MFContentProtectionManager, Unknown, IMFContentProtectionManager, IUnknown)
    public:
        void BeginEnableContent( IMFActivate* enablerActivate, IMFTopology* topology, IMFAsyncCallback* callback, IUnknown* state) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->BeginEnableContent(enablerActivate, topology, callback, state);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        void EndEnableContent(IMFAsyncResult* result) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->EndEnableContent(result);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }
    };

    class MFContentEnabler : public Unknown
    {
    public:
        HCC_COM_STANDARD_METHODS_IMPL(MFContentEnabler, Unknown, IMFContentEnabler, IUnknown)
    public:
        void GetEnableType(Guid* type) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->GetEnableType((GUID *) type);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        void GetEnableURL( LPWSTR* url, DWORD* urlLength, MF_URL_TRUST_STATUS* trustStatus) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->GetEnableURL(url, urlLength, trustStatus);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        void GetEnableData( BYTE** data, DWORD* dataLength) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->GetEnableData(data, dataLength);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        void IsAutomaticSupported( BOOL* automaticSupported) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->IsAutomaticSupported(automaticSupported);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        void AutomaticEnable( ) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->AutomaticEnable( );
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        void MonitorEnable( ) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->MonitorEnable();
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        void Cancel( ) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->Cancel();
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }
    };


    class MFMetadata : public Unknown
    {
    public:
        HCC_COM_STANDARD_METHODS_IMPL(MFMetadata, Unknown, IMFMetadata, IUnknown)
    public:
        void SetLanguage( LPCWSTR rfc1766) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->SetLanguage(rfc1766);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        void GetLanguage( LPWSTR* rfc1766) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->GetLanguage(rfc1766);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        void GetAllLanguages( PROPVARIANT* languages) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->GetAllLanguages(languages);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        void SetProperty( LPCWSTR name, const PROPVARIANT* value) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->SetProperty(name, value);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        void GetProperty( LPCWSTR name, PROPVARIANT* value) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->GetProperty(name, value);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        void DeleteProperty( LPCWSTR name) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->DeleteProperty(name);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        void GetAllPropertyNames( PROPVARIANT* names) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->GetAllPropertyNames(names);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }
    };


    class MFMetadataProvider : public Unknown
    {
    public:
        HCC_COM_STANDARD_METHODS_IMPL(MFMetadataProvider, Unknown, IMFMetadataProvider, IUnknown)
    public:
        void GetMFMetadata( IMFPresentationDescriptor* presentationDescriptor, DWORD streamIdentifier, DWORD flags, IMFMetadata** metadata) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->GetMFMetadata(presentationDescriptor, streamIdentifier, flags, metadata);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }
    };


    class MFRateSupport : public Unknown
    {
    public:
        HCC_COM_STANDARD_METHODS_IMPL(MFRateSupport, Unknown, IMFRateSupport, IUnknown)
    public:
        void GetSlowestRate( MFRATE_DIRECTION direction, BOOL thin, float* rate) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->GetSlowestRate(direction, thin, rate);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        void GetFastestRate( MFRATE_DIRECTION direction, BOOL thin, float* rate) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->GetFastestRate(direction, thin, rate);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        void IsRateSupported( BOOL thin, float rate, float* nearestSupportedRate) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->IsRateSupported(thin, rate, nearestSupportedRate);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }
    };

    class MFRateControl : public Unknown
    {
    public:
        HCC_COM_STANDARD_METHODS_IMPL(MFRateControl, Unknown, IMFRateControl, IUnknown)
    public:
        void SetRate(BOOL thin, float rate) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->SetRate(thin, rate);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        void GetRate( BOOL* thin, float* rate) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->GetRate(thin, rate);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }
    };


    class MFTimecodeTranslate : public Unknown
    {
    public:
        HCC_COM_STANDARD_METHODS_IMPL(MFTimecodeTranslate, Unknown, IMFTimecodeTranslate, IUnknown)
    public:
        void BeginConvertTimecodeToHNS( const PROPVARIANT* propVarTimecode, IMFAsyncCallback* callback, IUnknown* state) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->BeginConvertTimecodeToHNS(propVarTimecode, callback, state);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        void EndConvertTimecodeToHNS( IMFAsyncResult* result, MFTIME* time) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->EndConvertTimecodeToHNS(result, time);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        void BeginConvertHNSToTimecode( MFTIME time, IMFAsyncCallback* callback, IUnknown* state) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->BeginConvertHNSToTimecode(time, callback, state);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        void EndConvertHNSToTimecode( IMFAsyncResult* result, PROPVARIANT* propVarTimecode) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->EndConvertHNSToTimecode(result, propVarTimecode);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }
    };

    class MFSeekInfo : public Unknown
    {
    public:
        HCC_COM_STANDARD_METHODS_IMPL(MFSeekInfo, Unknown, IMFSeekInfo, IUnknown)
    public:
        void GetNearestKeyFrames( const Guid& timeFormatId, const PROPVARIANT* startPosition, PROPVARIANT* previousKeyFrame, PROPVARIANT* nextKeyFrame) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->GetNearestKeyFrames((GUID*)&timeFormatId, startPosition, previousKeyFrame, nextKeyFrame);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }
    };

    class MFSimpleAudioVolume : public Unknown
    {
    public:
        HCC_COM_STANDARD_METHODS_IMPL(MFSimpleAudioVolume, Unknown, IMFSimpleAudioVolume, IUnknown)
    public:
        void SetMasterVolume(float level) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->SetMasterVolume(level);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        void GetMasterVolume( float* level) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->GetMasterVolume(level);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        void SetMute( const BOOL mute) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->SetMute(mute);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        void GetMute( BOOL* mute) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->GetMute(mute);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }
    };


    class MFAudioStreamVolume : public Unknown
    {
    public:
        HCC_COM_STANDARD_METHODS_IMPL(MFAudioStreamVolume, Unknown, IMFAudioStreamVolume, IUnknown)
    public:
        void GetChannelCount( UINT32* channelCount) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->GetChannelCount(channelCount);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        void SetChannelVolume( UINT32 index, const float level) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->SetChannelVolume(index, level);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        void GetChannelVolume( UINT32 index, float* level) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->GetChannelVolume(index, level);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        void SetAllVolumes( UINT32 volumesCount, const float* volumes) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->SetAllVolumes(volumesCount, volumes);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        void GetAllVolumes( UINT32 volumesCount, float* volumes) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->GetAllVolumes(volumesCount, volumes);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }
    };

    class MFAudioPolicy : public Unknown
    {
    public:
        HCC_COM_STANDARD_METHODS_IMPL(MFAudioPolicy, Unknown, IMFAudioPolicy, IUnknown)
    public:
        void SetGroupingParam( const Guid& guidClass) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->SetGroupingParam(guidClass);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        void GetGroupingParam( Guid* guidClass) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->GetGroupingParam((GUID *) guidClass);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        void SetDisplayName( LPCWSTR name) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->SetDisplayName(name);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        void GetDisplayName( LPWSTR* name) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->GetDisplayName(name);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        void SetIconPath( LPCWSTR path) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->SetIconPath(path);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        void GetIconPath( LPWSTR* path) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->GetIconPath(path);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }
    };


    class MFSampleGrabberSinkCallback : public MFClockStateSink
    {
    public:
        HCC_COM_STANDARD_METHODS_IMPL(MFSampleGrabberSinkCallback, MFClockStateSink, IMFSampleGrabberSinkCallback, IMFClockStateSink)
    public:
        void OnSetPresentationClock(IMFPresentationClock* presentationClock) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->OnSetPresentationClock(presentationClock);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        void OnProcessSample( const Guid& majorMediaType, DWORD sampleFlags, LONGLONG sampleTime, LONGLONG sampleDuration, const BYTE* sampleBuffer, DWORD sampleSize) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->OnProcessSample(majorMediaType, sampleFlags, sampleTime, sampleDuration, sampleBuffer, sampleSize);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        void OnShutdown() const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->OnShutdown();
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }
    };


    class MFSampleGrabberSinkCallback2 : public MFSampleGrabberSinkCallback
    {
    public:
        HCC_COM_STANDARD_METHODS_IMPL(MFSampleGrabberSinkCallback2, MFSampleGrabberSinkCallback, IMFSampleGrabberSinkCallback2, IMFSampleGrabberSinkCallback)
    public:
        void OnProcessSampleEx( const Guid& majorMediaType, DWORD sampleFlags, LONGLONG sampleTime, LONGLONG sampleDuration, const BYTE* sampleBuffer, DWORD sampleSize, IMFAttributes* attributes) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->OnProcessSampleEx(majorMediaType, sampleFlags, sampleTime, sampleDuration, sampleBuffer, sampleSize, attributes);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }
    };

    class MFWorkQueueServices : public Unknown
    {
    public:
        HCC_COM_STANDARD_METHODS_IMPL(MFWorkQueueServices, Unknown, IMFWorkQueueServices, IUnknown)
    public:
        void BeginRegisterTopologyWorkQueuesWithMMCSS( IMFAsyncCallback* callback, IUnknown* state) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->BeginRegisterTopologyWorkQueuesWithMMCSS(callback, state);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        void EndRegisterTopologyWorkQueuesWithMMCSS( IMFAsyncResult* result) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->EndRegisterTopologyWorkQueuesWithMMCSS(result);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        void BeginUnregisterTopologyWorkQueuesWithMMCSS( IMFAsyncCallback* callback, IUnknown* state) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->BeginUnregisterTopologyWorkQueuesWithMMCSS(callback, state);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        void EndUnregisterTopologyWorkQueuesWithMMCSS( IMFAsyncResult* result) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->EndUnregisterTopologyWorkQueuesWithMMCSS(result);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        void GetTopologyWorkQueueMMCSSClass( DWORD topologyWorkQueueId, LPWSTR className, DWORD* classNameLength) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->GetTopologyWorkQueueMMCSSClass(topologyWorkQueueId, className, classNameLength);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        void GetTopologyWorkQueueMMCSSTaskId( DWORD topologyWorkQueueId, DWORD* taskId) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->GetTopologyWorkQueueMMCSSTaskId(topologyWorkQueueId, taskId);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        void BeginRegisterPlatformWorkQueueWithMMCSS( DWORD platformWorkQueue, LPCWSTR className, DWORD taskId, IMFAsyncCallback* callback, IUnknown* state) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->BeginRegisterPlatformWorkQueueWithMMCSS(platformWorkQueue, className, taskId, callback, state);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        void EndRegisterPlatformWorkQueueWithMMCSS( IMFAsyncResult* result, DWORD* taskId) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->EndRegisterPlatformWorkQueueWithMMCSS(result, taskId);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        void BeginUnregisterPlatformWorkQueueWithMMCSS( DWORD platformWorkQueue, IMFAsyncCallback* callback, IUnknown* state) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->BeginUnregisterPlatformWorkQueueWithMMCSS(platformWorkQueue, callback, state);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        void EndUnregisterPlatformWorkQueueWithMMCSS( IMFAsyncResult* result) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->EndUnregisterPlatformWorkQueueWithMMCSS(result);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        void GetPlaftormWorkQueueMMCSSClass( DWORD platformWorkQueueId, LPWSTR className, DWORD* classNameLength) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->GetPlaftormWorkQueueMMCSSClass(platformWorkQueueId, className, classNameLength);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        void GetPlatformWorkQueueMMCSSTaskId( DWORD platformWorkQueueId, DWORD* taskId) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->GetPlatformWorkQueueMMCSSTaskId(platformWorkQueueId, taskId);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }
    };

    class MFWorkQueueServicesEx : public MFWorkQueueServices
    {
    public:
        HCC_COM_STANDARD_METHODS_IMPL(MFWorkQueueServicesEx, MFWorkQueueServices, IMFWorkQueueServicesEx, IMFWorkQueueServices)
    public:
        void GetTopologyWorkQueueMMCSSPriority( DWORD topologyWorkQueueId, LONG* priority) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->GetTopologyWorkQueueMMCSSPriority(topologyWorkQueueId, priority);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        void BeginRegisterPlatformWorkQueueWithMMCSSEx( DWORD platformWorkQueue, LPCWSTR className, DWORD taskId, LONG priority, IMFAsyncCallback* callback, IUnknown* state) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->BeginRegisterPlatformWorkQueueWithMMCSSEx(platformWorkQueue, className, taskId, priority, callback, state);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        };

        void GetPlatformWorkQueueMMCSSPriority(DWORD platformWorkQueueId, LONG* priority) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->GetPlatformWorkQueueMMCSSPriority(platformWorkQueueId, priority);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }
    };

    class MFQualityManager : public Unknown
    {
    public:
        HCC_COM_STANDARD_METHODS_IMPL(MFQualityManager, Unknown, IMFQualityManager, IUnknown)
    public:
        static MFQualityManager Create()
        {
            IMFQualityManager* itf = nullptr;
            auto hr = MFCreateStandardQualityManager(&itf);
            HCC_COM_CHECK_HRESULT(hr);
            return MFQualityManager(itf);
        }

        void NotifyTopology( IMFTopology* topology) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->NotifyTopology(topology);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        void NotifyPresentationClock( IMFPresentationClock* clock) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->NotifyPresentationClock(clock);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        void NotifyProcessInput( IMFTopologyNode* topologyNode, long inputIndex, IMFSample* sample) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->NotifyProcessInput(topologyNode, inputIndex, sample);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        void NotifyProcessOutput( IMFTopologyNode* topologyNode, long outputIndex, IMFSample* sample) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->NotifyProcessOutput(topologyNode, outputIndex, sample);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        void NotifyQualityEvent( IUnknown* object, IMFMediaEvent* mediaEvent) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->NotifyQualityEvent(object, mediaEvent);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        void Shutdown( ) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->Shutdown();
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }
    };


    class MFQualityAdvise : public Unknown
    {
    public:
        HCC_COM_STANDARD_METHODS_IMPL(MFQualityAdvise, Unknown, IMFQualityAdvise, IUnknown)
    public:
        void SetDropMode(MF_QUALITY_DROP_MODE dropMode) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->SetDropMode(dropMode);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        void SetQualityLevel(MF_QUALITY_LEVEL qualityLevel) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->SetQualityLevel(qualityLevel);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        void GetDropMode(MF_QUALITY_DROP_MODE* dropMode) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->GetDropMode(dropMode);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        void GetQualityLevel( MF_QUALITY_LEVEL* qualityLevel) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->GetQualityLevel(qualityLevel);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        void DropTime( LONGLONG amountToDrop) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->DropTime(amountToDrop);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }
    };


    class MFQualityAdvise2 : public MFQualityAdvise
    {
    public:
        HCC_COM_STANDARD_METHODS_IMPL(MFQualityAdvise2, MFQualityAdvise, IMFQualityAdvise2, IMFQualityAdvise)
    public:
        void NotifyQualityEvent(IMFMediaEvent* mediaEvent, DWORD* flags) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->NotifyQualityEvent(mediaEvent, flags);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }
    };


    class MFQualityAdviseLimits : public Unknown
    {
    public:
        HCC_COM_STANDARD_METHODS_IMPL(MFQualityAdviseLimits, Unknown, IMFQualityAdviseLimits, IUnknown)
    public:
        void GetMaximumDropMode(MF_QUALITY_DROP_MODE* dropMode) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->GetMaximumDropMode(dropMode);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        void GetMinimumQualityLevel( MF_QUALITY_LEVEL* qualityLevel) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->GetMinimumQualityLevel(qualityLevel);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }
    };

    class MFRealTimeClient : public Unknown
    {
    public:
        HCC_COM_STANDARD_METHODS_IMPL(MFRealTimeClient, Unknown, IMFRealTimeClient, IUnknown)
    public:
        void RegisterThreads(DWORD taskIndex, LPCWSTR className) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->RegisterThreads(taskIndex, className);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        void UnregisterThreads( ) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->UnregisterThreads();
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        void SetWorkQueue( DWORD workQueueId) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->SetWorkQueue(workQueueId);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }
    };

    class MFRealTimeClientEx : public Unknown
    {
    public:
        HCC_COM_STANDARD_METHODS_IMPL(MFRealTimeClientEx, Unknown, IMFRealTimeClientEx, IUnknown)
    public:
        void RegisterThreadsEx( DWORD* taskIndex, LPCWSTR className, LONG basePriority) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->RegisterThreadsEx(taskIndex, className, basePriority);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        void UnregisterThreads( ) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->UnregisterThreads();
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        void SetWorkQueueEx( DWORD multithreadedWorkQueueId, LONG workItemBasePriority) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->SetWorkQueueEx(multithreadedWorkQueueId, workItemBasePriority);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }
    };

    class MFSequencerSource : public Unknown
    {
    public:
        HCC_COM_STANDARD_METHODS_IMPL(MFSequencerSource, Unknown, IMFSequencerSource, IUnknown)
    public:
        static MFSequencerSource Create()
        {
            IMFSequencerSource* itf = nullptr;
            auto hr = MFCreateSequencerSource(nullptr, &itf);
            HCC_COM_CHECK_HRESULT(hr);
            return MFSequencerSource(itf);
        }

        void AppendTopology( IMFTopology* topology, DWORD flags, MFSequencerElementId* sequencerElementId) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->AppendTopology(topology, flags, sequencerElementId);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        void DeleteTopology( MFSequencerElementId sequencerElementId) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->DeleteTopology(sequencerElementId);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        void GetPresentationContext( IMFPresentationDescriptor* presentationDescriptor, MFSequencerElementId* sequencerElementId, IMFTopology** topology) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->GetPresentationContext(presentationDescriptor, sequencerElementId, topology);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        void UpdateTopology( MFSequencerElementId sequencerElementId, IMFTopology* topology) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->UpdateTopology(sequencerElementId, topology);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        void UpdateTopologyFlags( MFSequencerElementId sequencerElementId, DWORD flags) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->UpdateTopologyFlags(sequencerElementId, flags);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }
    };


    class MFMediaSourceTopologyProvider : public Unknown
    {
    public:
        HCC_COM_STANDARD_METHODS_IMPL(MFMediaSourceTopologyProvider, Unknown, IMFMediaSourceTopologyProvider, IUnknown)
    public:
        void GetMediaSourceTopology(IMFPresentationDescriptor* presentationDescriptor, IMFTopology** topology) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->GetMediaSourceTopology(presentationDescriptor, topology);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }
    };

    class MFMediaSourcePresentationProvider : public Unknown
    {
    public:
        HCC_COM_STANDARD_METHODS_IMPL(MFMediaSourcePresentationProvider, Unknown, IMFMediaSourcePresentationProvider, IUnknown)
    public:
        void ForceEndOfPresentation(IMFPresentationDescriptor* presentationDescriptor) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->ForceEndOfPresentation(presentationDescriptor);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }
    };


    class MFTopologyNodeAttributeEditor : public Unknown
    {
    public:
        HCC_COM_STANDARD_METHODS_IMPL(MFTopologyNodeAttributeEditor, Unknown, IMFTopologyNodeAttributeEditor, IUnknown)
    public:
        void UpdateNodeAttributes(TOPOID topoId, DWORD numberOfUpdates, MFTOPONODE_ATTRIBUTE_UPDATE* updates) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->UpdateNodeAttributes(topoId, numberOfUpdates, updates);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }
    };


    class MFByteStreamBuffering : public Unknown
    {
    public:
        HCC_COM_STANDARD_METHODS_IMPL(MFByteStreamBuffering, Unknown, IMFByteStreamBuffering, IUnknown)
    public:
        void SetBufferingParams(MFBYTESTREAM_BUFFERING_PARAMS* params) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->SetBufferingParams(params);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        void EnableBuffering( BOOL enable) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->EnableBuffering(enable);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        void StopBuffering( ) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->StopBuffering();
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }
    };

    class MFByteStreamCacheControl : public Unknown
    {
    public:
        HCC_COM_STANDARD_METHODS_IMPL(MFByteStreamCacheControl, Unknown, IMFByteStreamCacheControl, IUnknown)
    public:
        void StopBackgroundTransfer() const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->StopBackgroundTransfer();
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }
    };

    class MFByteStreamTimeSeek : public Unknown
    {
    public:
        HCC_COM_STANDARD_METHODS_IMPL(MFByteStreamTimeSeek, Unknown, IMFByteStreamTimeSeek, IUnknown)
    public:
        void IsTimeSeekSupported(BOOL* timeSeekIsSupported) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->IsTimeSeekSupported(timeSeekIsSupported);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        void TimeSeek( QWORD timePosition) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->TimeSeek(timePosition);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        void GetTimeSeekResult( QWORD* startTime, QWORD* stopTime, QWORD* duration) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->GetTimeSeekResult(startTime, stopTime, duration);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }
    };

    class MFByteStreamCacheControl2 : public MFByteStreamCacheControl
    {
    public:
        HCC_COM_STANDARD_METHODS_IMPL(MFByteStreamCacheControl2, MFByteStreamCacheControl, IMFByteStreamCacheControl2, IMFByteStreamCacheControl)
    public:
        void GetByteRanges( DWORD* numberOfRanges, MF_BYTE_STREAM_CACHE_RANGE** ranges) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->GetByteRanges(numberOfRanges, ranges);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        void SetCacheLimit(QWORD bytes) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->SetCacheLimit(bytes);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        void IsBackgroundTransferActive( BOOL* active) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->IsBackgroundTransferActive(active);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }
    };

    class MFNetCredential : public Unknown
    {
    public:
        HCC_COM_STANDARD_METHODS_IMPL(MFNetCredential, Unknown, IMFNetCredential, IUnknown)
    public:
        void SetUser( BYTE* data, DWORD dataSize, BOOL dataIsEncrypted) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->SetUser(data, dataSize, dataIsEncrypted);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        void SetPassword( BYTE* data, DWORD dataSize, BOOL dataIsEncrypted) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->SetPassword(data, dataSize, dataIsEncrypted);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        void GetUser( BYTE* data, DWORD* dataSize, BOOL encryptData) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->GetUser(data, dataSize, encryptData);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        void GetPassword( BYTE* data, DWORD* dataSize, BOOL encryptData) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->GetPassword(data, dataSize, encryptData);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        void LoggedOnUser( BOOL* loggedOnUser) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->LoggedOnUser(loggedOnUser);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }
    };

    class MFNetCredentialManager : public Unknown
    {
    public:
        HCC_COM_STANDARD_METHODS_IMPL(MFNetCredentialManager, Unknown, IMFNetCredentialManager, IUnknown)
    public:
        void BeginGetCredentials( MFNetCredentialManagerGetParam* param, IMFAsyncCallback* callback, IUnknown* state) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->BeginGetCredentials(param, callback, state);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        void EndGetCredentials( IMFAsyncResult* result, IMFNetCredential** credential) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->EndGetCredentials(result, credential);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        void SetGood( IMFNetCredential* credential, BOOL good) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->SetGood(credential, good);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }
    };


    class MFNetCredentialCache : public Unknown
    {
    public:
        HCC_COM_STANDARD_METHODS_IMPL(MFNetCredentialCache, Unknown, IMFNetCredentialCache, IUnknown)
    public:
        static MFNetCredentialCache Create()
        {
            IMFNetCredentialCache* itf = nullptr;
            auto hr = MFCreateCredentialCache(&itf);
            HCC_COM_CHECK_HRESULT(hr);
            return MFNetCredentialCache(itf);
        }

        void GetCredential( LPCWSTR url, LPCWSTR realm, DWORD authenticationFlags, IMFNetCredential** credential, DWORD* requirementsFlags) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->GetCredential(url, realm, authenticationFlags, credential, requirementsFlags);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        void SetGood( IMFNetCredential* credential, BOOL good) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->SetGood(credential, good);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        void SetUserOptions( IMFNetCredential* credential, DWORD optionsFlags) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->SetUserOptions(credential, optionsFlags);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }
    };


    class MFSSLCertificateManager : public Unknown
    {
    public:
        HCC_COM_STANDARD_METHODS_IMPL(MFSSLCertificateManager, Unknown, IMFSSLCertificateManager, IUnknown)
    public:
        void GetClientCertificate(LPCWSTR url, BYTE** data, DWORD* dataSize) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->GetClientCertificate(url, data, dataSize);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        void BeginGetClientCertificate( LPCWSTR url, IMFAsyncCallback* callback, IUnknown* state) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->BeginGetClientCertificate(url, callback, state);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        void EndGetClientCertificate( IMFAsyncResult* result, BYTE** data, DWORD* dataSize) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->EndGetClientCertificate(result, data, dataSize);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        void GetCertificatePolicy( LPCWSTR url, BOOL* overrideAutomaticCheck, BOOL* clientCertificateAvailable) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->GetCertificatePolicy(url, overrideAutomaticCheck, clientCertificateAvailable);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        void OnServerCertificate( LPCWSTR url, BYTE* data, DWORD dataSize, BOOL* isGood) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->OnServerCertificate(url, data, dataSize, isGood);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }
    };


    class MFNetResourceFilter : public Unknown
    {
    public:
        HCC_COM_STANDARD_METHODS_IMPL(MFNetResourceFilter, Unknown, IMFNetResourceFilter, IUnknown)
    public:
        void OnRedirect(LPCWSTR url, VARIANT_BOOL* cancel) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->OnRedirect(url, cancel);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        void OnSendingRequest( LPCWSTR url) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->OnSendingRequest(url);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }
    };


    class MFSourceOpenMonitor : public Unknown
    {
    public:
        HCC_COM_STANDARD_METHODS_IMPL(MFSourceOpenMonitor, Unknown, IMFSourceOpenMonitor, IUnknown)
    public:
        void OnSourceEvent(IMFMediaEvent* mediaEvent) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->OnSourceEvent(mediaEvent);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }
    };

    class MFNetProxyLocator : public Unknown
    {
    public:
        HCC_COM_STANDARD_METHODS_IMPL(MFNetProxyLocator, Unknown, IMFNetProxyLocator, IUnknown)
    public:
        static MFNetProxyLocator Create(LPCWSTR protocolName, IPropertyStore* proxyConfig)
        {
            IMFNetProxyLocator* itf = nullptr;
            auto hr = MFCreateProxyLocator(protocolName, proxyConfig, &itf);
            HCC_COM_CHECK_HRESULT(hr);
            return MFNetProxyLocator(itf);
        }

        void FindFirstProxy(LPCWSTR host, LPCWSTR url, BOOL reserved = false) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->FindFirstProxy(host, url, reserved);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        void FindNextProxy( ) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->FindNextProxy();
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        void RegisterProxyResult( HRESULT hrOp) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->RegisterProxyResult(hrOp);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        void GetCurrentProxy( LPWSTR str, DWORD* strLength) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->GetCurrentProxy(str, strLength);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        void Clone( IMFNetProxyLocator** proxyLocator) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->Clone(proxyLocator);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }
    };

    class MFNetProxyLocatorFactory : public Unknown
    {
    public:
        HCC_COM_STANDARD_METHODS_IMPL(MFNetProxyLocatorFactory, Unknown, IMFNetProxyLocatorFactory, IUnknown)
    public:
        void CreateProxyLocator(LPCWSTR protocol, IMFNetProxyLocator** proxyLocator) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->CreateProxyLocator(protocol, proxyLocator);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }
    };

    class MFSaveJob : public Unknown
    {
    public:
        HCC_COM_STANDARD_METHODS_IMPL(MFSaveJob, Unknown, IMFSaveJob, IUnknown)
    public:
        void BeginSave( IMFByteStream* stream, IMFAsyncCallback* callback, IUnknown* state) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->BeginSave(stream, callback, state);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        void EndSave( IMFAsyncResult* result) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->EndSave(result);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        void CancelSave( ) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->CancelSave( );
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        void GetProgress( DWORD* percentComplete) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->GetProgress(percentComplete);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }
    };

    class MFNetSchemeHandlerConfig : public Unknown
    {
    public:
        HCC_COM_STANDARD_METHODS_IMPL(MFNetSchemeHandlerConfig, Unknown, IMFNetSchemeHandlerConfig, IUnknown)
    public:
        void GetNumberOfSupportedProtocols(ULONG* numberOfSupportedProtocols) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->GetNumberOfSupportedProtocols(numberOfSupportedProtocols);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        void GetSupportedProtocolType( ULONG protocolIndex, MFNETSOURCE_PROTOCOL_TYPE* protocolType) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->GetSupportedProtocolType(protocolIndex, protocolType);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        void ResetProtocolRolloverSettings( ) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->ResetProtocolRolloverSettings( );
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }
    };


    class MFSchemeHandler : public Unknown
    {
    public:
        HCC_COM_STANDARD_METHODS_IMPL(MFSchemeHandler, Unknown, IMFSchemeHandler, IUnknown)
    public:
        static void Create(const Guid& riid, LPVOID* handler)
        {
            auto hr = MFCreateNetSchemePlugin(riid, handler);
            HCC_COM_CHECK_HRESULT(hr);
        }
        template<typename T = MFSchemeHandler>
            requires std::is_base_of_v<Unknown,T>
        static T Create()
        {
            using ItfT = typename T::InterfaceType;
            Guid riid = __uuidof(ItfT);
            ItfT* itf = nullptr;
            Create(riid, (void**)&itf);
            return T(itf);
        }


        void BeginCreateObject( LPCWSTR url, DWORD flags, IPropertyStore* props, IUnknown** cancelCookie, IMFAsyncCallback* callback, IUnknown* state) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->BeginCreateObject(url, flags, props, cancelCookie, callback, state);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        void EndCreateObject( IMFAsyncResult* result, MF_OBJECT_TYPE* objectType, IUnknown** object) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->EndCreateObject(result, objectType, object);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        void CancelObjectCreation( IUnknown* cancelCookie) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->CancelObjectCreation(cancelCookie);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }
    };


    class MFByteStreamHandler : public Unknown
    {
    public:
        HCC_COM_STANDARD_METHODS_IMPL(MFByteStreamHandler, Unknown, IMFByteStreamHandler, IUnknown)
    public:
        void BeginCreateObject( IMFByteStream* byteStream, LPCWSTR url, DWORD flags, IPropertyStore* props, IUnknown** cancelCookie, IMFAsyncCallback* callback, IUnknown* state) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->BeginCreateObject(byteStream, url, flags, props, cancelCookie, callback, state);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        void EndCreateObject( IMFAsyncResult* result, MF_OBJECT_TYPE* objectType, IUnknown** object) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->EndCreateObject(result, objectType, object);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        void CancelObjectCreation( IUnknown* cancelCookie) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->CancelObjectCreation(cancelCookie);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        void GetMaxNumberOfBytesRequiredForResolution( QWORD* maxNumberOfBytesRequiredForResolution) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->GetMaxNumberOfBytesRequiredForResolution(maxNumberOfBytesRequiredForResolution);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }
    };

    class MFTrustedInput : public Unknown
    {
    public:
        HCC_COM_STANDARD_METHODS_IMPL(MFTrustedInput, Unknown, IMFTrustedInput, IUnknown)
    public:
        void GetInputTrustAuthority( DWORD streamID, const Guid& riid, IUnknown** object) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->GetInputTrustAuthority(streamID, riid, object);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }
    };


    class MFInputTrustAuthority : public Unknown
    {
    public:
        HCC_COM_STANDARD_METHODS_IMPL(MFInputTrustAuthority, Unknown, IMFInputTrustAuthority, IUnknown)
    public:
        void GetDecrypter( const Guid& riid, void** ppv) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->GetDecrypter(riid, ppv);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        void RequestAccess( MFPOLICYMANAGER_ACTION action, IMFActivate** contentEnablerActivate) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->RequestAccess(action, contentEnablerActivate);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        void GetPolicy( MFPOLICYMANAGER_ACTION action, IMFOutputPolicy** policy) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->GetPolicy(action, policy);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        void BindAccess( MFINPUTTRUSTAUTHORITY_ACCESS_PARAMS* param) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->BindAccess(param);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        void UpdateAccess( MFINPUTTRUSTAUTHORITY_ACCESS_PARAMS* param) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->UpdateAccess(param);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        void Reset( ) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->Reset();
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }
    };


    class MFTrustedOutput : public Unknown
    {
    public:
        HCC_COM_STANDARD_METHODS_IMPL(MFTrustedOutput, Unknown, IMFTrustedOutput, IUnknown)
    public:
        void GetOutputTrustAuthorityCount(DWORD* outputTrustAuthorityCount) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->GetOutputTrustAuthorityCount(outputTrustAuthorityCount);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        void GetOutputTrustAuthorityByIndex( DWORD index, IMFOutputTrustAuthority** authority) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->GetOutputTrustAuthorityByIndex(index, authority);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        void IsFinal( BOOL* isFinal) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->IsFinal(isFinal);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }
    };

    class MFOutputTrustAuthority : public Unknown
    {
    public:
        HCC_COM_STANDARD_METHODS_IMPL(MFOutputTrustAuthority, Unknown, IMFOutputTrustAuthority, IUnknown)
    public:
        void GetAction(MFPOLICYMANAGER_ACTION* action) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->GetAction(action);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        void SetPolicy( IMFOutputPolicy** policy, DWORD nPolicy, BYTE** ticket, DWORD* ticketSize) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->SetPolicy(policy, nPolicy, ticket, ticketSize);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }
    };

    class MFOutputPolicy : public MFAttributes
    {
    public:
        HCC_COM_STANDARD_METHODS_IMPL(MFOutputPolicy, MFAttributes, IMFOutputPolicy, IMFAttributes)
    public:
        void GenerateRequiredSchemas(DWORD attributes, Guid outputSubType, Guid* protectionSchemasSupported, DWORD numberOfProtectionSchemasSupported, IMFCollection** requiredProtectionSchemas) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->GenerateRequiredSchemas(attributes, outputSubType, (GUID*)protectionSchemasSupported, numberOfProtectionSchemasSupported, requiredProtectionSchemas);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        void GetOriginatorID( Guid* originatorID) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->GetOriginatorID((GUID*)originatorID);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        void GetMinimumGRLVersion( DWORD* minimumGRLVersion) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->GetMinimumGRLVersion(minimumGRLVersion);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }
    };

    class MFOutputSchema : public MFAttributes
    {
    public:
        HCC_COM_STANDARD_METHODS_IMPL(MFOutputSchema, MFAttributes, IMFOutputSchema, IMFAttributes)
    public:
        void GetSchemaType( Guid* schemaType) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->GetSchemaType((GUID*)schemaType);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        void GetConfigurationData( DWORD* configurationData) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->GetConfigurationData(configurationData);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        void GetOriginatorID( Guid* originatorID) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->GetOriginatorID((GUID*)originatorID);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }
    };

    class MFSecureChannel : public Unknown
    {
    public:
        HCC_COM_STANDARD_METHODS_IMPL(MFSecureChannel, Unknown, IMFSecureChannel, IUnknown)
    public:
        void GetCertificate(BYTE** certificate, DWORD* certificateSize) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->GetCertificate(certificate, certificateSize);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        void SetupSession( BYTE* encryptedSessionKey, DWORD encryptedSessionKeySize) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->SetupSession(encryptedSessionKey, encryptedSessionKeySize);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }
    };

    class MFSampleProtection : public Unknown
    {
    public:
        HCC_COM_STANDARD_METHODS_IMPL(MFSampleProtection, Unknown, IMFSampleProtection, IUnknown)
    public:
        void GetInputProtectionVersion( DWORD* inputProtectionVersion) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->GetInputProtectionVersion(inputProtectionVersion);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        void GetOutputProtectionVersion( DWORD* outputProtectionVersion) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->GetOutputProtectionVersion(outputProtectionVersion);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        void GetProtectionCertificate( DWORD version, BYTE** certificate, DWORD* certificateSize) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->GetProtectionCertificate(version, certificate, certificateSize);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        void InitOutputProtection( DWORD version, DWORD outputId, BYTE* certificate, DWORD certificateSize, BYTE** seed, DWORD* seedSize) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->InitOutputProtection(version, outputId, certificate, certificateSize, seed, seedSize);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        void InitInputProtection( DWORD version, DWORD inputId, BYTE* seed, DWORD seedSize) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->InitInputProtection(version, inputId, seed, seedSize);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }
    };

    class MFMediaSinkPreroll : public Unknown
    {
    public:
        HCC_COM_STANDARD_METHODS_IMPL(MFMediaSinkPreroll, Unknown, IMFMediaSinkPreroll, IUnknown)
    public:
        void NotifyPreroll(MFTIME upcomingStartTime) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->NotifyPreroll(upcomingStartTime);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }
    };

    class MFFinalizableMediaSink : public MFMediaSink
    {
    public:
        HCC_COM_STANDARD_METHODS_IMPL(MFFinalizableMediaSink, MFMediaSink, IMFFinalizableMediaSink, IMFMediaSink)
    public:
        void BeginFinalize( IMFAsyncCallback* callback, IUnknown* state) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->BeginFinalize(callback, state);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        void EndFinalize( IMFAsyncResult* result) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->EndFinalize(result);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }
    };

    class MFStreamingSinkConfig : public Unknown
    {
    public:
        HCC_COM_STANDARD_METHODS_IMPL(MFStreamingSinkConfig, Unknown, IMFStreamingSinkConfig, IUnknown)
    public:
        void StartStreaming(BOOL seekOffsetIsByteOffset, QWORD seekOffset) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->StartStreaming(seekOffsetIsByteOffset, seekOffset);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }
    };

    class MFRemoteProxy : public Unknown
    {
    public:
        HCC_COM_STANDARD_METHODS_IMPL(MFRemoteProxy, Unknown, IMFRemoteProxy, IUnknown)
    public:
        void GetRemoteObject(const Guid& riid, void** ppv) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->GetRemoteObject(riid, ppv);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        void GetRemoteHost( const Guid& riid, void** ppv) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->GetRemoteHost(riid, ppv);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }
    };

    class MFObjectReferenceStream : public Unknown
    {
    public:
        HCC_COM_STANDARD_METHODS_IMPL(MFObjectReferenceStream, Unknown, IMFObjectReferenceStream, IUnknown)
    public:
        void SaveReference( const Guid& riid, IUnknown* object) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->SaveReference(riid, object);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        void LoadReference( const Guid& riid, void** ppv) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->LoadReference(riid, ppv);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }
    };

    class MFPMPHost : public Unknown
    {
    public:
        HCC_COM_STANDARD_METHODS_IMPL(MFPMPHost, Unknown, IMFPMPHost, IUnknown)
    public:
        void LockProcess() const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->LockProcess();
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        void UnlockProcess() const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->UnlockProcess();
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        void CreateObjectByCLSID(const Guid& clsid, IStream* pStream, const Guid& riid, void** ppv) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->CreateObjectByCLSID(clsid, pStream, riid, ppv);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }
    };

    class MFPMPClient : public Unknown
    {
    public:
        HCC_COM_STANDARD_METHODS_IMPL(MFPMPClient, Unknown, IMFPMPClient, IUnknown)
    public:
        void SetPMPHost(IMFPMPHost* pmpHost) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->SetPMPHost(pmpHost);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }
    };

    class MFPMPServer : public Unknown
    {
    public:
        HCC_COM_STANDARD_METHODS_IMPL(MFPMPServer, Unknown, IMFPMPServer, IUnknown)
    public:
        static MFPMPServer Create(DWORD creationFlags)
        {
            IMFPMPServer* itf = nullptr;
            auto hr = MFCreatePMPServer(creationFlags, &itf);
            HCC_COM_CHECK_HRESULT(hr);
            return MFPMPServer(itf);
        }

        void LockProcess() const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->LockProcess();
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        void UnlockProcess() const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->UnlockProcess();
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        void CreateObjectByCLSID(const Guid& clsid, const Guid& riid, void** ppv) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->CreateObjectByCLSID(clsid, riid, ppv);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }
    };


    class MFRemoteDesktopPlugin : public Unknown
    {
    public:
        HCC_COM_STANDARD_METHODS_IMPL(MFRemoteDesktopPlugin, Unknown, IMFRemoteDesktopPlugin, IUnknown)
    public:
        static MFRemoteDesktopPlugin Create()
        {
            IMFRemoteDesktopPlugin* itf = nullptr;
            auto hr = MFCreateRemoteDesktopPlugin(&itf);
            HCC_COM_CHECK_HRESULT(hr);
            return MFRemoteDesktopPlugin(itf);
        }

        void UpdateTopology(IMFTopology* topology) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->UpdateTopology(topology);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }
    };


    class MFSAMIStyle : public Unknown
    {
    public:
        HCC_COM_STANDARD_METHODS_IMPL(MFSAMIStyle, Unknown, IMFSAMIStyle, IUnknown)
    public:
        void GetStyleCount(DWORD* styleCount) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->GetStyleCount(styleCount);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        void GetStyles( PROPVARIANT* styleArray) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->GetStyles(styleArray);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        void SetSelectedStyle( LPCWSTR style) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->SetSelectedStyle(style);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        void GetSelectedStyle( LPWSTR* style) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->GetSelectedStyle(style);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }
    };


    class MFTranscodeProfile : public Unknown
    {
    public:
        HCC_COM_STANDARD_METHODS_IMPL(MFTranscodeProfile, Unknown, IMFTranscodeProfile, IUnknown)
    public:
        void SetAudioAttributes( IMFAttributes* attributes) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->SetAudioAttributes(attributes);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        void GetAudioAttributes( IMFAttributes** attributes) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->GetAudioAttributes(attributes);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        void SetVideoAttributes( IMFAttributes* attributes) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->SetVideoAttributes(attributes);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        void GetVideoAttributes( IMFAttributes** attributes) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->GetVideoAttributes(attributes);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        void SetContainerAttributes( IMFAttributes* attributes) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->SetContainerAttributes(attributes);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        void GetContainerAttributes( IMFAttributes** attributes) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->GetContainerAttributes(attributes);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }
    };

    class MFTranscodeSinkInfoProvider : public Unknown
    {
    public:
        HCC_COM_STANDARD_METHODS_IMPL(MFTranscodeSinkInfoProvider, Unknown, IMFTranscodeSinkInfoProvider, IUnknown)
    public:
        void SetOutputFile( LPCWSTR fileName) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->SetOutputFile(fileName);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        void SetOutputByteStream( IMFActivate* byteStreamActivate) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->SetOutputByteStream(byteStreamActivate);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        void SetProfile( IMFTranscodeProfile* profile) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->SetProfile(profile);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        void GetSinkInfo( MF_TRANSCODE_SINK_INFO* sinkInfo) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->GetSinkInfo(sinkInfo);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }
    };

    class MFFieldOfUseMFTUnlock : public Unknown
    {
    public:
        HCC_COM_STANDARD_METHODS_IMPL(MFFieldOfUseMFTUnlock, Unknown, IMFFieldOfUseMFTUnlock, IUnknown)
    public:
        void Unlock(IUnknown* pUnkMFT) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->Unlock(pUnkMFT);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }
    };


    class MFLocalMFTRegistration : public Unknown
    {
    public:
        HCC_COM_STANDARD_METHODS_IMPL(MFLocalMFTRegistration, Unknown, IMFLocalMFTRegistration, IUnknown)
    public:
        void RegisterMFTs(MFT_REGISTRATION_INFO* pMFTs, DWORD numberOfMFTs) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->RegisterMFTs(pMFTs, numberOfMFTs);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }
    };


    class MFCapturePhotoConfirmation : public Unknown
    {
    public:
        HCC_COM_STANDARD_METHODS_IMPL(MFCapturePhotoConfirmation, Unknown, IMFCapturePhotoConfirmation, IUnknown)
    public:
        void SetPhotoConfirmationCallback(IMFAsyncCallback* notificationCallback) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->SetPhotoConfirmationCallback(notificationCallback);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        void SetPixelFormat( const Guid& subtype) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->SetPixelFormat(subtype);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        void GetPixelFormat( Guid* subtype) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->GetPixelFormat((GUID*)subtype);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }
    };

    class MFPMPHostApp : public Unknown
    {
    public:
        HCC_COM_STANDARD_METHODS_IMPL(MFPMPHostApp, Unknown, IMFPMPHostApp, IUnknown)
    public:
        void LockProcess() const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->LockProcess();
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        void UnlockProcess() const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->UnlockProcess();
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        void ActivateClassById( LPCWSTR id, IStream* stream, const Guid& riid, void** ppv) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->ActivateClassById(id, stream, riid, ppv);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }
    };

    class MFPMPClientApp : public Unknown
    {
    public:
        HCC_COM_STANDARD_METHODS_IMPL(MFPMPClientApp, Unknown, IMFPMPClientApp, IUnknown)
    public:
        void SetPMPHost(IMFPMPHostApp* pmpHost) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->SetPMPHost(pmpHost);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }
    };


    class MFMediaStreamSourceSampleRequest : public Unknown
    {
    public:
        HCC_COM_STANDARD_METHODS_IMPL(MFMediaStreamSourceSampleRequest, Unknown, IMFMediaStreamSourceSampleRequest, IUnknown)
    public:
        void SetSample(IMFSample* value) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->SetSample(value);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }
    };


    class MFTrackedSample : public Unknown
    {
    public:
        HCC_COM_STANDARD_METHODS_IMPL(MFTrackedSample, Unknown, IMFTrackedSample, IUnknown)
    public:
        void SetAllocator( IMFAsyncCallback* sampleAllocator, IUnknown* state) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->SetAllocator(sampleAllocator, state);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }
    };

    class MFProtectedEnvironmentAccess : public Unknown
    {
    public:
        HCC_COM_STANDARD_METHODS_IMPL(MFProtectedEnvironmentAccess, Unknown, IMFProtectedEnvironmentAccess, IUnknown)
    public:
        void Call( UINT32 inputLength, const BYTE* input, UINT32 outputLength, BYTE* output) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->Call(inputLength, input, outputLength, output);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        void ReadGRL( UINT32* outputLength, BYTE** output) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->ReadGRL(outputLength, output);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }
    };

    class MFSignedLibrary : public Unknown
    {
    public:
        HCC_COM_STANDARD_METHODS_IMPL(MFSignedLibrary, Unknown, IMFSignedLibrary, IUnknown)
    public:
        void GetProcedureAddress(LPCSTR name, PVOID* address) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->GetProcedureAddress(name, address);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }
    };


    class MFSystemId : public Unknown
    {
    public:
        HCC_COM_STANDARD_METHODS_IMPL(MFSystemId, Unknown, IMFSystemId, IUnknown)
    public:
        void GetData( UINT32* size, BYTE** data) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->GetData(size, data);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        void Setup( UINT32 stage, UINT32 cbIn, const BYTE* pbIn, UINT32* pcbOut, BYTE** ppbOut) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->Setup(stage, cbIn, pbIn, pcbOut, ppbOut);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }
    };


    class MFContentProtectionDevice : public Unknown
    {
    public:
        HCC_COM_STANDARD_METHODS_IMPL(MFContentProtectionDevice, Unknown, IMFContentProtectionDevice, IUnknown)
    public:
        void InvokeFunction( DWORD functionId, DWORD inputBufferByteCount, const BYTE* inputBuffer, DWORD* outputBufferByteCount, BYTE* outputBuffer) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->InvokeFunction(functionId, inputBufferByteCount, inputBuffer, outputBufferByteCount, outputBuffer);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        void GetPrivateDataByteCount( DWORD* privateInputByteCount, DWORD* privateOutputByteCount) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->GetPrivateDataByteCount(privateInputByteCount, privateOutputByteCount);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }
    };

    class MFContentDecryptorContext : public Unknown
    {
    public:
        HCC_COM_STANDARD_METHODS_IMPL(MFContentDecryptorContext, Unknown, IMFContentDecryptorContext, IUnknown)
    public:
        void InitializeHardwareKey( UINT inputPrivateDataByteCount, const void* inputPrivateData, UINT64* outputPrivateData) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->InitializeHardwareKey(inputPrivateDataByteCount, inputPrivateData, outputPrivateData);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }
    };

    class MFNetCrossOriginSupport : public Unknown
    {
    public:
        HCC_COM_STANDARD_METHODS_IMPL(MFNetCrossOriginSupport, Unknown, IMFNetCrossOriginSupport, IUnknown)
    public:
        void GetCrossOriginPolicy(MF_CROSS_ORIGIN_POLICY* policy) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->GetCrossOriginPolicy(policy);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        void GetSourceOrigin( LPWSTR* sourceOrigin) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->GetSourceOrigin(sourceOrigin);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        void IsSameOrigin( LPCWSTR url, BOOL* isSameOrigin) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->IsSameOrigin(url, isSameOrigin);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }
    };

    class MFHttpDownloadRequest : public Unknown
    {
    public:
        HCC_COM_STANDARD_METHODS_IMPL(MFHttpDownloadRequest, Unknown, IMFHttpDownloadRequest, IUnknown)
    public:
        void AddHeader(LPCWSTR header) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->AddHeader(header);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        void BeginSendRequest( const BYTE* payload, ULONG payloadSize, IMFAsyncCallback* callback, IUnknown* state) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->BeginSendRequest(payload, payloadSize, callback, state);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        void EndSendRequest( IMFAsyncResult* result) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->EndSendRequest(result);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        void BeginReceiveResponse( IMFAsyncCallback* callback, IUnknown* state) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->BeginReceiveResponse(callback, state);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        void EndReceiveResponse( IMFAsyncResult* result) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->EndReceiveResponse(result);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        void BeginReadPayload( BYTE* buffer, ULONG bufferSize, IMFAsyncCallback* callback, IUnknown* state) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->BeginReadPayload(buffer, bufferSize, callback, state);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        void EndReadPayload( IMFAsyncResult* result, QWORD* offset, ULONG* numberOfBytesRead) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->EndReadPayload(result, offset, numberOfBytesRead);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        void QueryHeader( LPCWSTR headerName, DWORD index, LPWSTR* headerValue) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->QueryHeader(headerName, index, headerValue);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        void GetURL(LPWSTR* url) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->GetURL(url);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        void HasNullSourceOrigin( BOOL* nullSourceOrigin) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->HasNullSourceOrigin(nullSourceOrigin);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        void GetTimeSeekResult( QWORD* startTime, QWORD* stopTime, QWORD* duration) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->GetTimeSeekResult(startTime, stopTime, duration);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        void GetHttpStatus(DWORD* httpStatus) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->GetHttpStatus(httpStatus);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        void GetAtEndOfPayload(BOOL* atEndOfPayload) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->GetAtEndOfPayload(atEndOfPayload);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        void GetTotalLength(QWORD* totalLength) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->GetTotalLength(totalLength);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        void GetRangeEndOffset( QWORD* rangeEnd) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->GetRangeEndOffset(rangeEnd);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        void Close( ) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->Close();
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }
    };

    class MFHttpDownloadSession : public Unknown
    {
    public:
        HCC_COM_STANDARD_METHODS_IMPL(MFHttpDownloadSession, Unknown, IMFHttpDownloadSession, IUnknown)
    public:
        void SetServer( LPCWSTR serverName, DWORD portNumber) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->SetServer(serverName, portNumber);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        void CreateRequest( LPCWSTR objectName, BOOL bypassProxyCache, BOOL secure, LPCWSTR verb, LPCWSTR referrer, IMFHttpDownloadRequest** request) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->CreateRequest(objectName, bypassProxyCache, secure, verb, referrer, request);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        void Close( ) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->Close();
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }
    };


    class MFHttpDownloadSessionProvider : public Unknown
    {
    public:
        HCC_COM_STANDARD_METHODS_IMPL(MFHttpDownloadSessionProvider, Unknown, IMFHttpDownloadSessionProvider, IUnknown)
    public:
        void CreateHttpDownloadSession(LPCWSTR scheme, IMFHttpDownloadSession** ppDownloadSession) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->CreateHttpDownloadSession(scheme, ppDownloadSession);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }
    };

    class MFMediaSource2 : public MFMediaSourceEx
    {
    public:
        HCC_COM_STANDARD_METHODS_IMPL(MFMediaSource2, MFMediaSourceEx, IMFMediaSource2, IMFMediaSourceEx)
    public:
        void SetMediaType(DWORD streamID, IMFMediaType* mediaType) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->SetMediaType(streamID, mediaType);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }
    };

    class MFMediaStream2 : public MFMediaStream
    {
    public:
        HCC_COM_STANDARD_METHODS_IMPL(MFMediaStream2, MFMediaStream, IMFMediaStream2, IMFMediaStream)
    public:
        void SetStreamState(MF_STREAM_STATE value) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->SetStreamState(value);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        void GetStreamState(MF_STREAM_STATE* value) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->GetStreamState(value);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }
    };

    class MFSensorDevice : public Unknown
    {
    public:
        HCC_COM_STANDARD_METHODS_IMPL(MFSensorDevice, Unknown, IMFSensorDevice, IUnknown)
    public:
        void GetDeviceId( ULONGLONG* deviceId) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->GetDeviceId(deviceId);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        void GetDeviceType( MFSensorDeviceType* sensorDeviceType) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->GetDeviceType(sensorDeviceType);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        void GetFlags( ULONGLONG* flags) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->GetFlags(flags);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        void GetSymbolicLink( LPWSTR symbolicLinkBuffer, LONG symbolicLinkBufferLength, LONG* symbolicLinkLength) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->GetSymbolicLink(symbolicLinkBuffer, symbolicLinkBufferLength, symbolicLinkLength);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        void GetDeviceAttributes( IMFAttributes** attributes) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->GetDeviceAttributes(attributes);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        void GetStreamAttributesCount( MFSensorStreamType sensorStreamType, DWORD* count) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->GetStreamAttributesCount(sensorStreamType, count);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        void GetStreamAttributes( MFSensorStreamType sensorStreamType, DWORD index, IMFAttributes** attributes) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->GetStreamAttributes(sensorStreamType, index, attributes);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        void SetSensorDeviceMode( MFSensorDeviceMode sensorDeviceMode) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->SetSensorDeviceMode(sensorDeviceMode);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        void GetSensorDeviceMode( MFSensorDeviceMode* sensorDeviceMode) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->GetSensorDeviceMode(sensorDeviceMode);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }
    };


    class MFSensorGroup : public Unknown
    {
    public:
        HCC_COM_STANDARD_METHODS_IMPL(MFSensorGroup, Unknown, IMFSensorGroup, IUnknown)
    public:
        void GetSymbolicLink(LPWSTR symbolicLinkBuffer, LONG symbolicLinkBufferLength, LONG* symbolicLinkLength) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->GetSymbolicLink(symbolicLinkBuffer, symbolicLinkBufferLength, symbolicLinkLength);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        

        void GetFlags( ULONGLONG* flags) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->GetFlags(flags);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        void GetSensorGroupAttributes( IMFAttributes** attributes) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->GetSensorGroupAttributes(attributes);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        void GetSensorDeviceCount( DWORD* sensorDeviceCount) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->GetSensorDeviceCount(sensorDeviceCount);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        void GetSensorDevice( DWORD index, IMFSensorDevice** sensorDevice) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->GetSensorDevice(index, sensorDevice);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        void SetDefaultSensorDeviceIndex( DWORD defaultSensorDeviceIndex) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->SetDefaultSensorDeviceIndex(defaultSensorDeviceIndex);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        void GetDefaultSensorDeviceIndex( DWORD* defaultSensorDeviceIndex) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->GetDefaultSensorDeviceIndex(defaultSensorDeviceIndex);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        void CreateMediaSource( IMFMediaSource** mediaSource) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->CreateMediaSource(mediaSource);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }
    };

    class MFSensorStream : public MFAttributes
    {
    public:
        HCC_COM_STANDARD_METHODS_IMPL(MFSensorStream, MFAttributes, IMFSensorStream, IMFAttributes)
    public:
        void GetMediaTypeCount( DWORD* mediaTypeCount) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->GetMediaTypeCount(mediaTypeCount);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        void GetMediaType( DWORD index, IMFMediaType** mediaType) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->GetMediaType(index, mediaType);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        void CloneSensorStream( IMFSensorStream** stream) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->CloneSensorStream(stream);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }
    };

    class MFSensorTransformFactory : public Unknown
    {
    public:
        HCC_COM_STANDARD_METHODS_IMPL(MFSensorTransformFactory, Unknown, IMFSensorTransformFactory, IUnknown)
    public:
        void GetFactoryAttributes( IMFAttributes** attributes) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->GetFactoryAttributes(attributes);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        void InitializeFactory( DWORD maxTransformCount, IMFCollection* sensorDevices, IMFAttributes* attributes) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->InitializeFactory(maxTransformCount, sensorDevices, attributes);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        void GetTransformCount( DWORD* transformCount) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->GetTransformCount(transformCount);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        void GetTransformInformation( DWORD transformIndex, Guid* transformId, IMFAttributes** attributes, IMFCollection** streamInformation) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->GetTransformInformation(transformIndex, (GUID*)transformId, attributes, streamInformation);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        void CreateTransform( const Guid& sensorTransformID, IMFAttributes* attributes, IMFDeviceTransform** deviceTransform) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->CreateTransform(sensorTransformID, attributes, deviceTransform);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }
    };


    class MFSensorProfile : public Unknown
    {
    public:
        HCC_COM_STANDARD_METHODS_IMPL(MFSensorProfile, Unknown, IMFSensorProfile, IUnknown)
    public:
        void GetProfileId( SENSORPROFILEID* sensorProfileId) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->GetProfileId(sensorProfileId);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        void AddProfileFilter( UINT32 streamId, LPCWSTR filterSetString) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->AddProfileFilter(streamId, filterSetString);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        void IsMediaTypeSupported( UINT32 streamId, IMFMediaType* mediaType, BOOL* supported) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->IsMediaTypeSupported(streamId, mediaType, supported);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        void AddBlockedControl( LPCWSTR blockedControl) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->AddBlockedControl(blockedControl);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }
    };

    class MFSensorProfileCollection : public Unknown
    {
    public:
        HCC_COM_STANDARD_METHODS_IMPL(MFSensorProfileCollection, Unknown, IMFSensorProfileCollection, IUnknown)
    public:
        void GetProfileCount() const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->GetProfileCount();
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        void GetProfile( DWORD index, IMFSensorProfile** sensorProfile) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->GetProfile(index, sensorProfile);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        void AddProfile( IMFSensorProfile* sensorProfile) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->AddProfile(sensorProfile);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        void FindProfile( SENSORPROFILEID* sensorProfileId, IMFSensorProfile** sensorProfile) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->FindProfile(sensorProfileId, sensorProfile);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        void RemoveProfileByIndex( DWORD index) const
        {
            InterfaceType* pInterface = GetInterface();
            pInterface->RemoveProfileByIndex(index);
        }

        void RemoveProfile( SENSORPROFILEID* sensorProfileId) const
        {
            InterfaceType* pInterface = GetInterface();
            pInterface->RemoveProfile(sensorProfileId);
        }
    };

    class MFSensorProcessActivity : public Unknown
    {
    public:
        HCC_COM_STANDARD_METHODS_IMPL(MFSensorProcessActivity, Unknown, IMFSensorProcessActivity, IUnknown)
    public:
        void GetProcessId( ULONG* processId) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->GetProcessId(processId);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        void GetStreamingState( BOOL* streaming) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->GetStreamingState(streaming);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        void GetStreamingMode( MFSensorDeviceMode* streamingMode) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->GetStreamingMode(streamingMode);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        void GetReportTime( FILETIME* reportTime) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->GetReportTime(reportTime);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }
    };


    class MFSensorActivityReport : public Unknown
    {
    public:
        HCC_COM_STANDARD_METHODS_IMPL(MFSensorActivityReport, Unknown, IMFSensorActivityReport, IUnknown)
    public:
        void GetFriendlyName( LPWSTR friendlyNameBuffer, ULONG friendlyNameBufferSize, ULONG* friendlyNameLength) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->GetFriendlyName(friendlyNameBuffer, friendlyNameBufferSize, friendlyNameLength);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        void GetSymbolicLink(LPWSTR symbolicLinkBuffer, LONG symbolicLinkBufferLength, ULONG* symbolicLinkLength) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->GetSymbolicLink(symbolicLinkBuffer, symbolicLinkBufferLength, symbolicLinkLength);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }


        void GetProcessCount( ULONG* processCount) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->GetProcessCount(processCount);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        void GetProcessActivity( ULONG index, IMFSensorProcessActivity** processActivity) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->GetProcessActivity(index, processActivity);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }
    };


    class MFSensorActivitiesReport : public Unknown
    {
    public:
        HCC_COM_STANDARD_METHODS_IMPL(MFSensorActivitiesReport, Unknown, IMFSensorActivitiesReport, IUnknown)
    public:
        void GetCount( ULONG* count) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->GetCount(count);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        void GetActivityReport( ULONG index, IMFSensorActivityReport** sensorActivityReport) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->GetActivityReport(index, sensorActivityReport);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        void GetActivityReportByDeviceName( LPCWSTR symbolicName, IMFSensorActivityReport** sensorActivityReport) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->GetActivityReportByDeviceName(symbolicName, sensorActivityReport);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }
    };


    class MFSensorActivitiesReportCallback : public Unknown
    {
    public:
        HCC_COM_STANDARD_METHODS_IMPL(MFSensorActivitiesReportCallback, Unknown, IMFSensorActivitiesReportCallback, IUnknown)
    public:
        void OnActivitiesReport(IMFSensorActivitiesReport* sensorActivitiesReport) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->OnActivitiesReport(sensorActivitiesReport);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }
    };

    class MFSensorActivityMonitor : public Unknown
    {
    public:
        HCC_COM_STANDARD_METHODS_IMPL(MFSensorActivityMonitor, Unknown, IMFSensorActivityMonitor, IUnknown)
    public:
        void Start() const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->Start();
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        void Stop( ) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->Stop();
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }
    };


    class MFExtendedCameraIntrinsicModel : public Unknown
    {
    public:
        HCC_COM_STANDARD_METHODS_IMPL(MFExtendedCameraIntrinsicModel, Unknown, IMFExtendedCameraIntrinsicModel, IUnknown)
    public:
        void GetModel( MFExtendedCameraIntrinsic_IntrinsicModel* intrinsicModel) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->GetModel(intrinsicModel);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        void SetModel( const MFExtendedCameraIntrinsic_IntrinsicModel* intrinsicModel) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->SetModel(intrinsicModel);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        void GetDistortionModelType( MFCameraIntrinsic_DistortionModelType* distortionModelType) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->GetDistortionModelType(distortionModelType);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }
    };


    class MFExtendedCameraIntrinsicsDistortionModel6KT : public Unknown
    {
    public:
        HCC_COM_STANDARD_METHODS_IMPL(MFExtendedCameraIntrinsicsDistortionModel6KT, Unknown, IMFExtendedCameraIntrinsicsDistortionModel6KT, IUnknown)
    public:
        void GetDistortionModel(MFCameraIntrinsic_DistortionModel6KT* distortionModel) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->GetDistortionModel(distortionModel);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        void SetDistortionModel( const MFCameraIntrinsic_DistortionModel6KT* distortionModel) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->SetDistortionModel(distortionModel);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }
    };

    class MFExtendedCameraIntrinsicsDistortionModelArcTan : public Unknown
    {
    public:
        HCC_COM_STANDARD_METHODS_IMPL(MFExtendedCameraIntrinsicsDistortionModelArcTan, Unknown, IMFExtendedCameraIntrinsicsDistortionModelArcTan, IUnknown)
    public:
        void GetDistortionModel(MFCameraIntrinsic_DistortionModelArcTan* distortionModel) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->GetDistortionModel(distortionModel);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        void SetDistortionModel( const MFCameraIntrinsic_DistortionModelArcTan* distortionModel) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->SetDistortionModel(distortionModel);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }
    };

    class MFExtendedCameraIntrinsics : public Unknown
    {
    public:
        HCC_COM_STANDARD_METHODS_IMPL(MFExtendedCameraIntrinsics, Unknown, IMFExtendedCameraIntrinsics, IUnknown)
    public:
        void InitializeFromBuffer( BYTE* buffer, DWORD bufferSize) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->InitializeFromBuffer(buffer, bufferSize);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        void GetBufferSize( DWORD* bufferSize) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->GetBufferSize(bufferSize);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        void SerializeToBuffer( BYTE* buffer, DWORD* bufferSize) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->SerializeToBuffer(buffer, bufferSize);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        void GetIntrinsicModelCount( DWORD* intrinsicModelCount) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->GetIntrinsicModelCount(intrinsicModelCount);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        void GetIntrinsicModelByIndex( DWORD index, IMFExtendedCameraIntrinsicModel** intrinsicModel) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->GetIntrinsicModelByIndex(index, intrinsicModel);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        void AddIntrinsicModel( IMFExtendedCameraIntrinsicModel* intrinsicModel) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->AddIntrinsicModel(intrinsicModel);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }
    };



    class MFExtendedCameraControl : public Unknown
    {
    public:
        HCC_COM_STANDARD_METHODS_IMPL(MFExtendedCameraControl, Unknown, IMFExtendedCameraControl, IUnknown)
    public:
        ULONGLONG GetCapabilities() const
        {
            InterfaceType* pInterface = GetInterface();
            return pInterface->GetCapabilities();
        }

        void SetFlags( ULONGLONG flags) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->SetFlags(flags);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        ULONGLONG GetFlags( ) const
        {
            InterfaceType* pInterface = GetInterface();
            return pInterface->GetFlags();
        }

        void LockPayload( BYTE** payload, ULONG* payloadSize) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->LockPayload(payload, payloadSize);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        void UnlockPayload( ) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->UnlockPayload();
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        void CommitSettings( ) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->CommitSettings();
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }
    };


    class MFExtendedCameraController : public Unknown
    {
    public:
        HCC_COM_STANDARD_METHODS_IMPL(MFExtendedCameraController, Unknown, IMFExtendedCameraController, IUnknown)
    public:
        void GetExtendedCameraControl(DWORD streamIndex, ULONG propertyId, IMFExtendedCameraControl** extendedCameraControl) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->GetExtendedCameraControl(streamIndex, propertyId, extendedCameraControl);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }
    };


    class MFRelativePanelReport : public Unknown
    {
    public:
        HCC_COM_STANDARD_METHODS_IMPL(MFRelativePanelReport, Unknown, IMFRelativePanelReport, IUnknown)
    public:
        void GetRelativePanel(ULONG* panel) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->GetRelativePanel(panel);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }
    };


    class MFRelativePanelWatcher : public MFShutdown
    {
    public:
        HCC_COM_STANDARD_METHODS_IMPL(MFRelativePanelWatcher, MFShutdown, IMFRelativePanelWatcher, IMFShutdown)
    public:
        void BeginGetReport(IMFAsyncCallback* callback, IUnknown* state) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->BeginGetReport(callback, state);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        void EndGetReport( IMFAsyncResult* result, IMFRelativePanelReport** relativePanelReport) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->EndGetReport(result, relativePanelReport);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        void GetReport( IMFRelativePanelReport** relativePanelReport) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->GetReport(relativePanelReport);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }
    };

    class MFCameraOcclusionStateReport : public Unknown
    {
    public:
        HCC_COM_STANDARD_METHODS_IMPL(MFCameraOcclusionStateReport, Unknown, IMFCameraOcclusionStateReport, IUnknown)
    public:
        void GetOcclusionState(DWORD* occlusionState) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->GetOcclusionState(occlusionState);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }
    };

    class MFCameraOcclusionStateReportCallback : public Unknown
    {
    public:
        HCC_COM_STANDARD_METHODS_IMPL(MFCameraOcclusionStateReportCallback, Unknown, IMFCameraOcclusionStateReportCallback, IUnknown)
    public:
        void OnOcclusionStateReport(IMFCameraOcclusionStateReport* occlusionStateReport) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->OnOcclusionStateReport(occlusionStateReport);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }
    };

    class MFCameraOcclusionStateMonitor : public Unknown
    {
    public:
        HCC_COM_STANDARD_METHODS_IMPL(MFCameraOcclusionStateMonitor, Unknown, IMFCameraOcclusionStateMonitor, IUnknown)
    public:
        void Start() const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->Start();
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        void Stop() const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->Stop();
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        DWORD GetSupportedStates() const
        {
            InterfaceType* pInterface = GetInterface();
            return pInterface->GetSupportedStates();
        }
    };

    class MFVideoCaptureSampleAllocator : public MFVideoSampleAllocator
    {
    public:
        HCC_COM_STANDARD_METHODS_IMPL(MFVideoCaptureSampleAllocator, MFVideoSampleAllocator, IMFVideoCaptureSampleAllocator, IMFVideoSampleAllocator)
    public:
        void InitializeCaptureSampleAllocator( DWORD sampleSize, DWORD captureMetadataSize, DWORD alignment, DWORD minimumSamples, IMFAttributes* attributes, IMFMediaType* mediaType) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->InitializeCaptureSampleAllocator(sampleSize, captureMetadataSize, alignment, minimumSamples, attributes, mediaType);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }
    };

    class MFSampleAllocatorControl : public Unknown
    {
    public:
        HCC_COM_STANDARD_METHODS_IMPL(MFSampleAllocatorControl, Unknown, IMFSampleAllocatorControl, IUnknown)
    public:
        void SetDefaultAllocator( DWORD outputStreamID, IUnknown* allocator) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->SetDefaultAllocator(outputStreamID, allocator);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        void GetAllocatorUsage( DWORD outputStreamID, DWORD* inputStreamID, MFSampleAllocatorUsage* usage) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->GetAllocatorUsage(outputStreamID, inputStreamID, usage);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }
    };


    


}

#endif
