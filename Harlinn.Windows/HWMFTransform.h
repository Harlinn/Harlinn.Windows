#pragma once
#ifndef HARLINN_WINDOWS_HWMFTRANSFORM_H_
#define HARLINN_WINDOWS_HWMFTRANSFORM_H_

#include "HWMFObjects.h"
#include "HCCCom.h"

#pragma comment(lib, "wmcodecdspuuid.lib")

namespace Harlinn::Windows
{
    namespace MF
    {
        /// <summary>
        /// Returned by MFTransform::ProcessOutput
        /// </summary>
        enum class TransformOutputResult
        {
            /// <summary>
            /// The method succeeded.
            /// </summary>
            Success = 0,
            /// <summary>
            /// The transform cannot produce output data until it 
            /// receives more input data.
            /// </summary>
            NeedMoreInput,
            /// <summary>
            /// The format has changed on an output stream, or there is a 
            /// new preferred format, or there is a new output stream.
            /// </summary>
            StreamChange
        };


        /// <summary>
        /// This class is binary compatible with MFT_OUTPUT_DATA_BUFFER
        /// </summary>
        class TransformOutputDataBuffer
        {
            DWORD streamID_ = 0;
            MFSample sample_;
            DWORD status_ = 0;
            MFCollection events_;
        public:
            TransformOutputDataBuffer()
            { }
            explicit TransformOutputDataBuffer(DWORD streamID)
                : streamID_(streamID)
            {
            }

            TransformOutputDataBuffer(const TransformOutputDataBuffer& other) = delete;
            TransformOutputDataBuffer& operator = (const TransformOutputDataBuffer& other) = delete;

            TransformOutputDataBuffer(TransformOutputDataBuffer&& other) noexcept
                : streamID_(other.streamID_), sample_(std::move(other.sample_)), status_(other.status_), events_(std::move(other.events_))
            {

            }
            TransformOutputDataBuffer& operator = (TransformOutputDataBuffer&& other) noexcept
            {
                std::swap(streamID_,other.streamID_);
                std::swap(sample_, other.sample_);
                std::swap(status_, other.status_);
                std::swap(events_, other.events_);
                return *this;
            }

            constexpr DWORD StreamID() const noexcept
            {
                return streamID_;
            }
            void SetStreamId(DWORD streamID)
            {
                streamID_ = streamID;
            }

            const MFSample& Sample() const noexcept
            {
                return sample_;
            }
            void MoveSampleTo(MFSample& sample)
            {
                sample = std::move(sample_);
            }
            void SetSample(const MFSample& sample)
            {
                sample_ = sample;
            }
            void SetSample(MFSample&& sample)
            {
                sample_ = std::move(sample);
            }

            constexpr DWORD Status() const noexcept
            {
                return status_;
            }

            const MFCollection& Events() const noexcept
            {
                return events_;
            }
            void MoveEventsTo(MFCollection& events)
            {
                events = std::move(events_);
            }


        };

        static_assert(sizeof(TransformOutputDataBuffer) == sizeof(MFT_OUTPUT_DATA_BUFFER));


    }


    class MFTransform : public Unknown
    {
    public:
        HCC_COM_STANDARD_METHODS_IMPL(MFTransform, Unknown, IMFTransform, IUnknown)
    public:

        struct StreamLimits
        {
            DWORD InputMinimum; 
            DWORD InputMaximum; 
            DWORD OutputMinimum; 
            DWORD OutputMaximum;
        };

        void GetStreamLimits( __RPC__out DWORD* pdwInputMinimum, __RPC__out DWORD* pdwInputMaximum, __RPC__out DWORD* pdwOutputMinimum, __RPC__out DWORD* pdwOutputMaximum) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->GetStreamLimits(pdwInputMinimum, pdwInputMaximum, pdwOutputMinimum, pdwOutputMaximum);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }
        StreamLimits GetStreamLimits() const
        {
            StreamLimits result{};
            GetStreamLimits(&result.InputMinimum, &result.InputMaximum, &result.OutputMinimum, &result.OutputMaximum);
            return result;
        }


        struct StreamCount
        {
            DWORD InputStreams;
            DWORD OutputStreams;
        };

        void GetStreamCount( __RPC__out DWORD* pcInputStreams, __RPC__out DWORD* pcOutputStreams) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->GetStreamCount(pcInputStreams, pcOutputStreams);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }
        StreamCount GetStreamCount() const
        {
            StreamCount result{};
            GetStreamCount(&result.InputStreams, &result.OutputStreams);
            return result;
        }



        void GetStreamIDs( DWORD dwInputIDArraySize, __RPC__out_ecount_full(dwInputIDArraySize) DWORD* pdwInputIDs, DWORD dwOutputIDArraySize, __RPC__out_ecount_full(dwOutputIDArraySize) DWORD* pdwOutputIDs) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->GetStreamIDs(dwInputIDArraySize, pdwInputIDs, dwOutputIDArraySize, pdwOutputIDs);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        void GetInputStreamInfo( DWORD dwInputStreamID, __RPC__out MFT_INPUT_STREAM_INFO* pStreamInfo) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->GetInputStreamInfo(dwInputStreamID, pStreamInfo);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }
        MFT_INPUT_STREAM_INFO GetInputStreamInfo(DWORD dwInputStreamID) const
        {
            MFT_INPUT_STREAM_INFO result{};
            GetInputStreamInfo(dwInputStreamID, &result);
            return result;
        }


        void GetOutputStreamInfo( DWORD dwOutputStreamID, __RPC__out MFT_OUTPUT_STREAM_INFO* pStreamInfo) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->GetOutputStreamInfo(dwOutputStreamID, pStreamInfo);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }
        MFT_OUTPUT_STREAM_INFO GetOutputStreamInfo(DWORD dwOutputStreamID) const
        {
            MFT_OUTPUT_STREAM_INFO result{};
            GetOutputStreamInfo(dwOutputStreamID, &result);
            return result;
        }


        bool GetAttributes( __RPC__deref_out_opt IMFAttributes** pAttributes) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->GetAttributes(pAttributes);
            if ( hr != E_NOTIMPL )
            {
                HCC_COM_CHECK_HRESULT2( hr, pInterface );
                return true;
            }
            return false;
        }
        MFAttributes GetAttributes() const
        {
            IMFAttributes* itf = nullptr;
            if ( GetAttributes( &itf ) )
            {
                return MFAttributes( itf );
            }
            else
            {
                return {};
            }
        }


        void GetInputStreamAttributes( DWORD dwInputStreamID, __RPC__deref_out_opt IMFAttributes** pAttributes) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->GetInputStreamAttributes(dwInputStreamID, pAttributes);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }
        MFAttributes GetInputStreamAttributes(DWORD dwInputStreamID) const
        {
            IMFAttributes* itf = nullptr;
            GetInputStreamAttributes(dwInputStreamID,&itf);
            return MFAttributes(itf);
        }


        void GetOutputStreamAttributes( DWORD dwOutputStreamID, __RPC__deref_out_opt IMFAttributes** pAttributes) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->GetOutputStreamAttributes(dwOutputStreamID, pAttributes);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }
        MFAttributes GetOutputStreamAttributes(DWORD dwOutputStreamID) const
        {
            IMFAttributes* itf = nullptr;
            GetOutputStreamAttributes(dwOutputStreamID, &itf);
            return MFAttributes(itf);
        }


        void DeleteInputStream( DWORD dwStreamID) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->DeleteInputStream(dwStreamID);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        void AddInputStreams( DWORD cStreams, __RPC__in DWORD* adwStreamIDs) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->AddInputStreams(cStreams, adwStreamIDs);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        bool GetInputAvailableType( DWORD inputStreamID, DWORD typeIndex, __RPC__deref_out_opt IMFMediaType** ppType) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->GetInputAvailableType( inputStreamID, typeIndex, ppType);
            if ( hr != MF_E_NO_MORE_TYPES )
            {
                HCC_COM_CHECK_HRESULT2( hr, pInterface );
                return true;
            }
            return false;
        }
        MFMediaType GetInputAvailableType( DWORD inputStreamID, DWORD typeIndex ) const
        {
            IMFMediaType* itf = nullptr;
            if ( GetInputAvailableType( inputStreamID, typeIndex, &itf ) )
            {
                return MFMediaType( itf );
            }
            return {};
        }
        std::vector<MFMediaType> GetInputAvailableTypes( DWORD inputStreamID ) const
        {
            std::vector<MFMediaType> result;
            DWORD i = 0;
            while ( true )
            {
                auto mediaType = GetInputAvailableType( inputStreamID, i );
                if ( mediaType )
                {
                    result.emplace_back( std::move( mediaType ) );
                    i++;
                }
                else
                {
                    break;
                }
            }
            return result;
        }

        bool GetOutputAvailableType( DWORD dwOutputStreamID, DWORD dwTypeIndex, __RPC__deref_out_opt IMFMediaType** ppType) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->GetOutputAvailableType(dwOutputStreamID, dwTypeIndex, ppType);
            if ( hr != MF_E_NO_MORE_TYPES )
            {
                HCC_COM_CHECK_HRESULT2( hr, pInterface );
                return true;
            }
            return false;
        }
        MFMediaType GetOutputAvailableType(DWORD dwOutputStreamID, DWORD dwTypeIndex) const
        {
            IMFMediaType* itf = nullptr;
            if ( GetOutputAvailableType( dwOutputStreamID, dwTypeIndex, &itf ) )
            {
                return MFMediaType( itf );
            }
            return {};
        }
        std::vector<MFMediaType> GetOutputAvailableTypes( DWORD inputStreamID ) const
        {
            std::vector<MFMediaType> result;
            DWORD i = 0;
            while ( true )
            {
                auto mediaType = GetOutputAvailableType( inputStreamID, i );
                if ( mediaType )
                {
                    result.emplace_back( std::move( mediaType ) );
                    i++;
                }
                else
                {
                    break;
                }
            }
            return result;
        }

        void SetInputType( DWORD dwInputStreamID, __RPC__in_opt IMFMediaType* pType, DWORD dwFlags = 0) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->SetInputType(dwInputStreamID, pType, dwFlags);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        void SetOutputType( DWORD dwOutputStreamID, __RPC__in_opt IMFMediaType* pType, DWORD dwFlags = 0) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->SetOutputType(dwOutputStreamID, pType, dwFlags);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        void GetInputCurrentType( DWORD dwInputStreamID, __RPC__deref_out_opt IMFMediaType** ppType) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->GetInputCurrentType(dwInputStreamID, ppType);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }
        MFMediaType GetInputCurrentType(DWORD dwInputStreamID) const
        {
            IMFMediaType* itf = nullptr;
            GetInputCurrentType(dwInputStreamID, &itf);
            return MFMediaType(itf);
        }


        void GetOutputCurrentType( DWORD dwOutputStreamID, __RPC__deref_out_opt IMFMediaType** ppType) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->GetOutputCurrentType(dwOutputStreamID, ppType);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }
        MFMediaType GetOutputCurrentType(DWORD dwOutputStreamID) const
        {
            IMFMediaType* itf = nullptr;
            GetOutputCurrentType(dwOutputStreamID, &itf);
            return MFMediaType(itf);
        }

        void GetInputStatus( DWORD dwInputStreamID, __RPC__out DWORD* pdwFlags) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->GetInputStatus(dwInputStreamID, pdwFlags);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }
        DWORD GetInputStatus(DWORD dwInputStreamID) const
        {
            DWORD result = 0;
            GetInputStatus(dwInputStreamID, &result);
            return result;
        }


        void GetOutputStatus( __RPC__out DWORD* pdwFlags) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->GetOutputStatus(pdwFlags);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }
        DWORD GetOutputStatus() const
        {
            DWORD result = 0;
            GetOutputStatus(&result);
            return result;
        }


        void SetOutputBounds( LONGLONG hnsLowerBound, LONGLONG hnsUpperBound) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->SetOutputBounds(hnsLowerBound, hnsUpperBound);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        void ProcessEvent( DWORD dwInputStreamID, __RPC__in_opt IMFMediaEvent* pEvent) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->ProcessEvent(dwInputStreamID, pEvent);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        void ProcessMessage( MFT_MESSAGE_TYPE eMessage, ULONG_PTR ulParam = 0) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->ProcessMessage(eMessage, ulParam);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        void ProcessInput( DWORD dwInputStreamID, IMFSample* pSample, DWORD dwFlags) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->ProcessInput(dwInputStreamID, pSample, dwFlags);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        MF::TransformOutputResult ProcessOutput( DWORD dwFlags, DWORD cOutputBufferCount, MFT_OUTPUT_DATA_BUFFER* pOutputSamples, DWORD* pdwStatus) const
        {
            MF::TransformOutputResult result = MF::TransformOutputResult::Success;
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->ProcessOutput(dwFlags, cOutputBufferCount, pOutputSamples, pdwStatus);
            switch (hr)
            {
                case S_OK:
                    break;
                case MF_E_TRANSFORM_NEED_MORE_INPUT:
                    result = MF::TransformOutputResult::NeedMoreInput;
                    break;
                case MF_E_TRANSFORM_STREAM_CHANGE:
                    result = MF::TransformOutputResult::StreamChange;
                    break;
                default:
                    HCC_COM_CHECK_HRESULT2(hr, pInterface);
                break;
            }
            return result;
        }
        MF::TransformOutputResult ProcessOutput(DWORD flags, DWORD outputBufferCount, MF::TransformOutputDataBuffer* outputSamples, DWORD* status) const
        {
            return ProcessOutput(flags, outputBufferCount, reinterpret_cast<MFT_OUTPUT_DATA_BUFFER*>(outputSamples), status);
        }

        MF::TransformOutputResult ProcessOutput(DWORD flags, MF::TransformOutputDataBuffer& outputSamples, DWORD* status) const
        {
            return ProcessOutput(flags, 1 ,&outputSamples, status);
        }


    };


    class MFDeviceTransform : public Unknown
    {
    public:
        HCC_COM_STANDARD_METHODS_IMPL(MFDeviceTransform, Unknown, IMFDeviceTransform, IUnknown)
    public:
        void InitializeTransform( IMFAttributes* pAttributes) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->InitializeTransform(pAttributes);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        void GetInputAvailableType( DWORD dwInputStreamID, DWORD dwTypeIndex, _COM_Outptr_  IMFMediaType** pMediaType) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->GetInputAvailableType(dwInputStreamID, dwTypeIndex, pMediaType);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        void GetInputCurrentType( DWORD dwInputStreamID, _COM_Outptr_  IMFMediaType** pMediaType) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->GetInputCurrentType(dwInputStreamID, pMediaType);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        void GetInputStreamAttributes( DWORD dwInputStreamID, _COM_Outptr_  IMFAttributes** ppAttributes) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->GetInputStreamAttributes(dwInputStreamID, ppAttributes);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        void GetOutputAvailableType( DWORD dwOutputStreamID, DWORD dwTypeIndex, _COM_Outptr_  IMFMediaType** pMediaType) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->GetOutputAvailableType(dwOutputStreamID, dwTypeIndex, pMediaType);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        void GetOutputCurrentType( DWORD dwOutputStreamID, _COM_Outptr_  IMFMediaType** pMediaType) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->GetOutputCurrentType(dwOutputStreamID, pMediaType);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        void GetOutputStreamAttributes( DWORD dwOutputStreamID, _COM_Outptr_  IMFAttributes** ppAttributes) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->GetOutputStreamAttributes(dwOutputStreamID, ppAttributes);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        void GetStreamCount( _Out_  DWORD* pcInputStreams, _Out_  DWORD* pcOutputStreams) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->GetStreamCount(pcInputStreams, pcOutputStreams);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        void GetStreamIDs( DWORD dwInputIDArraySize, _Out_  DWORD* pdwInputStreamIds, DWORD dwOutputIDArraySize, _Out_  DWORD* pdwOutputStreamIds) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->GetStreamIDs(dwInputIDArraySize, pdwInputStreamIds, dwOutputIDArraySize, pdwOutputStreamIds);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        void ProcessEvent( DWORD dwInputStreamID, _In_  IMFMediaEvent* pEvent) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->ProcessEvent(dwInputStreamID, pEvent);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        void ProcessInput( DWORD dwInputStreamID, IMFSample* pSample, DWORD dwFlags) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->ProcessInput(dwInputStreamID, pSample, dwFlags);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        void ProcessMessage( MFT_MESSAGE_TYPE eMessage, ULONG_PTR ulParam) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->ProcessMessage(eMessage, ulParam);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        void ProcessOutput( DWORD dwFlags, DWORD cOutputBufferCount, MFT_OUTPUT_DATA_BUFFER* pOutputSample, _Out_  DWORD* pdwStatus) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->ProcessOutput(dwFlags, cOutputBufferCount, pOutputSample, pdwStatus);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        void SetInputStreamState( DWORD dwStreamID, IMFMediaType* pMediaType, DeviceStreamState value, DWORD dwFlags) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->SetInputStreamState(dwStreamID, pMediaType, value, dwFlags);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        void GetInputStreamState( DWORD dwStreamID, _Out_  DeviceStreamState* value) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->GetInputStreamState(dwStreamID, value);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        void SetOutputStreamState( DWORD dwStreamID, IMFMediaType* pMediaType, DeviceStreamState value, DWORD dwFlags) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->SetOutputStreamState(dwStreamID, pMediaType, value, dwFlags);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        void GetOutputStreamState( DWORD dwStreamID, DeviceStreamState* value) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->GetOutputStreamState(dwStreamID, value);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        void GetInputStreamPreferredState( DWORD dwStreamID, _Out_  DeviceStreamState* value, _COM_Outptr_  IMFMediaType** ppMediaType) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->GetInputStreamPreferredState(dwStreamID, value, ppMediaType);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        void FlushInputStream( DWORD dwStreamIndex, DWORD dwFlags) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->FlushInputStream(dwStreamIndex, dwFlags);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        void FlushOutputStream( DWORD dwStreamIndex, DWORD dwFlags) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->FlushOutputStream(dwStreamIndex, dwFlags);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }
    };

    class MFDeviceTransformCallback : public Unknown
    {
    public:
        HCC_COM_STANDARD_METHODS_IMPL(MFDeviceTransformCallback, Unknown, IMFDeviceTransformCallback, IUnknown)
    public:
        void OnBufferSent( IMFAttributes* pCallbackAttributes, DWORD pinId) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->OnBufferSent(pCallbackAttributes, pinId);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }
    };

}

#endif

