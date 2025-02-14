#pragma once
#ifndef HARLINN_WINDOWS_HWMFREADWRITE_H_
#define HARLINN_WINDOWS_HWMFREADWRITE_H_
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

#include "HWMFTransform.h"
#include "HWMFObjects.h"

#pragma comment(lib, "mfreadwrite.lib")

namespace Harlinn::Windows::Media
{
    /// <summary>
    /// Creates an instance of either the sink writer or the source reader.
    /// </summary>
    class MFReadWriteClassFactory : public Unknown
    {
    public:
        HCC_COM_STANDARD_METHODS_IMPL(MFReadWriteClassFactory, Unknown, IMFReadWriteClassFactory, IUnknown)
    public:
        void CreateInstanceFromURL( const Guid& clsid, LPCWSTR pwszURL, _In_opt_  IMFAttributes* pAttributes, const Guid& riid, _Out_  LPVOID* ppvObject) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->CreateInstanceFromURL(clsid, pwszURL, pAttributes, riid, ppvObject);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        void CreateInstanceFromObject( const Guid& clsid, IUnknown* punkObject, _In_opt_  IMFAttributes* pAttributes, const Guid& riid, _Out_  LPVOID* ppvObject) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->CreateInstanceFromObject(clsid, punkObject, pAttributes, riid, ppvObject);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }
    };

    /// <summary>
    /// Microsoft Media Foundation source reader object.
    /// </summary>
    class MFSourceReader : public Unknown
    {
    public:
        HCC_COM_STANDARD_METHODS_IMPL(MFSourceReader, Unknown, IMFSourceReader, IUnknown)
    public:
        static MFSourceReader CreateSourceReaderFromURL(LPCWSTR pwszURL, _In_opt_ IMFAttributes* pAttributes)
        {
            IMFSourceReader* itf = nullptr;
            auto hr = MFCreateSourceReaderFromURL(pwszURL, pAttributes, &itf);
            HCC_COM_CHECK_HRESULT(hr);
            return MFSourceReader(itf);
        }

        static MFSourceReader CreateSourceReaderFromByteStream(IMFByteStream* pByteStream, _In_opt_ IMFAttributes* pAttributes)
        {
            IMFSourceReader* itf = nullptr;
            auto hr = MFCreateSourceReaderFromByteStream(pByteStream, pAttributes, &itf);
            HCC_COM_CHECK_HRESULT(hr);
            return MFSourceReader(itf);
        }

        static MFSourceReader CreateSourceReaderFromMediaSource(IMFMediaSource* pMediaSource, _In_opt_ IMFAttributes* pAttributes)
        {
            IMFSourceReader* itf = nullptr;
            auto hr = MFCreateSourceReaderFromMediaSource(pMediaSource, pAttributes, &itf);
            HCC_COM_CHECK_HRESULT(hr);
            return MFSourceReader(itf);
        }


        void GetStreamSelection( DWORD dwStreamIndex, _Out_  BOOL* pfSelected) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->GetStreamSelection(dwStreamIndex, pfSelected);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }
        bool GetStreamSelection(DWORD streamIndex) const
        {
            BOOL result = FALSE;
            GetStreamSelection(streamIndex, &result);
            return result != FALSE;
        }



        void SetStreamSelection( DWORD dwStreamIndex, BOOL fSelected) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->SetStreamSelection(dwStreamIndex, fSelected);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        void GetNativeMediaType( DWORD dwStreamIndex, DWORD dwMediaTypeIndex, _Out_  IMFMediaType** ppMediaType) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->GetNativeMediaType(dwStreamIndex, dwMediaTypeIndex, ppMediaType);
            if (hr != MF_E_NO_MORE_TYPES)
            {
                HCC_COM_CHECK_HRESULT2(hr, pInterface);
            }
        }

        MFMediaType GetNativeMediaType(DWORD streamIndex, DWORD mediaTypeIndex) const
        {
            IMFMediaType* itf = nullptr;
            GetNativeMediaType(streamIndex, mediaTypeIndex, &itf);
            return MFMediaType(itf);
        }
        std::vector<MFMediaType> GetNativeMediaTypes(DWORD streamIndex) const
        {
            std::vector<MFMediaType> result;
            for (DWORD i = 0;; i++)
            {
                auto mediaType = GetNativeMediaType(streamIndex, i);
                if (mediaType)
                {
                    result.push_back( std::move(mediaType) );
                }
                else
                {
                    break;
                }
            }
            return result;
        }


        void GetCurrentMediaType( DWORD dwStreamIndex, _Out_  IMFMediaType** ppMediaType) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->GetCurrentMediaType(dwStreamIndex, ppMediaType);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }
        MFMediaType GetCurrentMediaType(DWORD dwStreamIndex) const
        {
            IMFMediaType* itf = nullptr;
            GetCurrentMediaType(dwStreamIndex, &itf);
            return MFMediaType(itf);
        }

        void SetCurrentMediaType( DWORD dwStreamIndex, _Reserved_  DWORD* pdwReserved, _In_  IMFMediaType* pMediaType) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->SetCurrentMediaType(dwStreamIndex, pdwReserved, pMediaType);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }
        void SetCurrentMediaType(DWORD dwStreamIndex, _In_  IMFMediaType* pMediaType) const
        {
            SetCurrentMediaType(dwStreamIndex, nullptr, pMediaType);
        }


        void SetCurrentPosition( const Guid& guidTimeFormat, REFPROPVARIANT varPosition) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->SetCurrentPosition(guidTimeFormat, varPosition);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        void ReadSample( DWORD dwStreamIndex, DWORD dwControlFlags, _Out_opt_  DWORD* pdwActualStreamIndex, _Out_opt_  DWORD* pdwStreamFlags, _Out_opt_  LONGLONG* pllTimestamp, _Out_opt_  IMFSample** ppSample) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->ReadSample(dwStreamIndex, dwControlFlags, pdwActualStreamIndex, pdwStreamFlags, pllTimestamp, ppSample);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        MFSample ReadSample(DWORD dwStreamIndex, DWORD dwControlFlags, _Out_opt_  DWORD* pdwActualStreamIndex, _Out_opt_  DWORD* pdwStreamFlags, _Out_opt_  LONGLONG* pllTimestamp) const
        {
            IMFSample* itf = nullptr;
            ReadSample(dwStreamIndex, dwControlFlags, pdwActualStreamIndex, pdwStreamFlags, pllTimestamp, &itf);
            return MFSample(itf);
        }

        void Flush( DWORD dwStreamIndex) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->Flush(dwStreamIndex);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        void GetServiceForStream( DWORD dwStreamIndex, const Guid& guidService, const Guid& riid, _Out_  LPVOID* ppvObject) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->GetServiceForStream(dwStreamIndex, guidService, riid, ppvObject);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        void GetPresentationAttribute( DWORD dwStreamIndex, const Guid& guidAttribute, _Out_  PROPVARIANT* pvarAttribute) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->GetPresentationAttribute(dwStreamIndex, guidAttribute, pvarAttribute);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }
    };

    /// <summary>
    /// Extends the MFSourceReader class.
    /// </summary>
    class MFSourceReaderEx : public MFSourceReader
    {
    public:
        HCC_COM_STANDARD_METHODS_IMPL(MFSourceReaderEx, MFSourceReader, IMFSourceReaderEx, IMFSourceReader)
    public:
        void SetNativeMediaType( DWORD dwStreamIndex, _In_opt_  IMFMediaType* pMediaType, _Out_  DWORD* pdwStreamFlags) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->SetNativeMediaType(dwStreamIndex, pMediaType, pdwStreamFlags);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        void AddTransformForStream( DWORD dwStreamIndex, IUnknown* pTransformOrActivate) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->AddTransformForStream(dwStreamIndex, pTransformOrActivate);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        void RemoveAllTransformsForStream( DWORD dwStreamIndex) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->RemoveAllTransformsForStream(dwStreamIndex);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        void GetTransformForStream( DWORD dwStreamIndex, DWORD dwTransformIndex, _Out_opt_  GUID* pGuidCategory, _Out_  IMFTransform** ppTransform) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->GetTransformForStream(dwStreamIndex, dwTransformIndex, pGuidCategory, ppTransform);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

    };

    /// <summary>
    /// Callback interface for the Microsoft Media Foundation source reader.
    /// </summary>
    class MFSourceReaderCallback : public Unknown
    {
    public:
        HCC_COM_STANDARD_METHODS_IMPL(MFSourceReaderCallback, Unknown, IMFSourceReaderCallback, IUnknown)
    public:
        void OnReadSample( HRESULT hrStatus, DWORD dwStreamIndex, DWORD dwStreamFlags, LONGLONG llTimestamp, _In_opt_  IMFSample* pSample) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->OnReadSample(hrStatus, dwStreamIndex, dwStreamFlags, llTimestamp, pSample);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        void OnFlush( DWORD dwStreamIndex) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->OnFlush(dwStreamIndex);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        void OnEvent( DWORD dwStreamIndex, IMFMediaEvent* pEvent) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->OnEvent(dwStreamIndex, pEvent);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }
    };


    /// <summary>
    /// Extends the MFSourceReaderCallback class.
    /// </summary>
    class MFSourceReaderCallback2 : public MFSourceReaderCallback
    {
    public:
        HCC_COM_STANDARD_METHODS_IMPL(MFSourceReaderCallback2, MFSourceReaderCallback, IMFSourceReaderCallback2, IMFSourceReaderCallback)
    public:
        void OnTransformChange( ) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->OnTransformChange();
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        void OnStreamError( DWORD dwStreamIndex, HRESULT hrStatus) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->OnStreamError(dwStreamIndex, hrStatus);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }
    };

    /// <summary>
    /// Microsoft Media Foundation sink writer
    /// </summary>
    class MFSinkWriter : public Unknown
    {
    public:
        HCC_COM_STANDARD_METHODS_IMPL(MFSinkWriter, Unknown, IMFSinkWriter, IUnknown)
    public:
        static MFSinkWriter CreateSinkWriterFromURL(_In_opt_ LPCWSTR pwszOutputURL, _In_opt_ IMFByteStream* pByteStream, _In_opt_ IMFAttributes* pAttributes)
        {
            IMFSinkWriter* itf = nullptr;
            auto hr = MFCreateSinkWriterFromURL(pwszOutputURL, pByteStream, pAttributes, &itf);
            HCC_COM_CHECK_HRESULT(hr);
            return MFSinkWriter(itf);
        }

        static MFSinkWriter CreateSinkWriterFromMediaSink(IMFMediaSink* pMediaSink, _In_opt_ IMFAttributes* pAttributes)
        {
            IMFSinkWriter* itf = nullptr;
            auto hr = MFCreateSinkWriterFromMediaSink(pMediaSink, pAttributes, &itf);
            HCC_COM_CHECK_HRESULT(hr);
            return MFSinkWriter(itf);
        }


        void AddStream( IMFMediaType* pTargetMediaType, _Out_  DWORD* pdwStreamIndex) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->AddStream(pTargetMediaType, pdwStreamIndex);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        void SetInputMediaType( DWORD dwStreamIndex, IMFMediaType* pInputMediaType, _In_opt_  IMFAttributes* pEncodingParameters) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->SetInputMediaType(dwStreamIndex, pInputMediaType, pEncodingParameters);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        void BeginWriting( ) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->BeginWriting();
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        void WriteSample( DWORD dwStreamIndex, IMFSample* pSample) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->WriteSample(dwStreamIndex, pSample);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        void SendStreamTick( DWORD dwStreamIndex, LONGLONG llTimestamp) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->SendStreamTick(dwStreamIndex, llTimestamp);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        void PlaceMarker( DWORD dwStreamIndex, LPVOID pvContext) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->PlaceMarker(dwStreamIndex, pvContext);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        void NotifyEndOfSegment( DWORD dwStreamIndex) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->NotifyEndOfSegment(dwStreamIndex);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        void Flush( DWORD dwStreamIndex) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->Flush(dwStreamIndex);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        void Finalize( ) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->Finalize();
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        void GetServiceForStream( DWORD dwStreamIndex, const Guid& guidService, const Guid& riid, _Out_  LPVOID* ppvObject) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->GetServiceForStream(dwStreamIndex, guidService, riid, ppvObject);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        void GetStatistics( DWORD dwStreamIndex, _Out_  MF_SINK_WRITER_STATISTICS* pStats) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->GetStatistics(dwStreamIndex, pStats);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }
    };

    /// <summary>
    /// Extends the MFSinkWriter class.
    /// </summary>
    class MFSinkWriterEx : public MFSinkWriter
    {
    public:
        HCC_COM_STANDARD_METHODS_IMPL(MFSinkWriterEx, MFSinkWriter, IMFSinkWriterEx, IMFSinkWriter)
    public:
        void GetTransformForStream( DWORD dwStreamIndex, DWORD dwTransformIndex, _Out_opt_  GUID* pGuidCategory, _Out_  IMFTransform** ppTransform) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->GetTransformForStream(dwStreamIndex, dwTransformIndex, pGuidCategory, ppTransform);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }
    };

    /// <summary>
    /// Provides additional functionality on the sink writer for dynamically changing the media type and encoder configuration.
    /// </summary>
    class MFSinkWriterEncoderConfig : public Unknown
    {
    public:
        HCC_COM_STANDARD_METHODS_IMPL(MFSinkWriterEncoderConfig, Unknown, IMFSinkWriterEncoderConfig, IUnknown)
    public:
        void SetTargetMediaType( DWORD dwStreamIndex, IMFMediaType* pTargetMediaType, _In_opt_  IMFAttributes* pEncodingParameters) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->SetTargetMediaType(dwStreamIndex, pTargetMediaType, pEncodingParameters);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        void PlaceEncodingParameters( DWORD dwStreamIndex, IMFAttributes* pEncodingParameters) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->PlaceEncodingParameters(dwStreamIndex, pEncodingParameters);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }
    };

    /// <summary>
    /// Callback interface for the Microsoft Media Foundation sink writer.
    /// </summary>
    class MFSinkWriterCallback : public Unknown
    {
    public:
        HCC_COM_STANDARD_METHODS_IMPL(MFSinkWriterCallback, Unknown, IMFSinkWriterCallback, IUnknown)
    public:
        void OnFinalize( HRESULT hrStatus) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->OnFinalize(hrStatus);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        void OnMarker( DWORD dwStreamIndex, LPVOID pvContext) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->OnMarker(dwStreamIndex, pvContext);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }
    };

    /// <summary>
    /// Extends the MFSinkWriterCallback class.
    /// </summary>
    class MFSinkWriterCallback2 : public MFSinkWriterCallback
    {
    public:
        HCC_COM_STANDARD_METHODS_IMPL(MFSinkWriterCallback2, MFSinkWriterCallback, IMFSinkWriterCallback2, IMFSinkWriterCallback)
    public:
        void OnTransformChange( ) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->OnTransformChange();
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        void OnStreamError( DWORD dwStreamIndex, HRESULT hrStatus) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->OnStreamError(dwStreamIndex, hrStatus);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }
    };


}


#endif
