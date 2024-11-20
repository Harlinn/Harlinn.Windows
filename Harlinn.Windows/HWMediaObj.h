#pragma once
#ifndef HARLINN_WINDOWS_HWMEDIAOBJ_H_
#define HARLINN_WINDOWS_HWMEDIAOBJ_H_
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

#include <HWDef.h>
#include <HCCCOM.h>
#include <HWCommon.h>

namespace Harlinn::Windows
{
    /// <summary>
    /// Wrapper for the IMediaBuffer interface which provides methods 
    /// for manipulating a data buffer. Buffers passed to the IMediaObject::ProcessInput 
    /// and ProcessOutput methods must implement this interface.
    /// </summary>
    class MediaBuffer : public Unknown
    {
    public:
        HCC_COM_STANDARD_METHODS_IMPL(MediaBuffer, Unknown, IMediaBuffer, IUnknown)
    public:
        /// <summary>
        /// Specifies the length of the data currently in the buffer.
        /// </summary>
        /// <param name="length">
        /// Size of the data, in bytes. The value must not exceed the buffer's 
        /// maximum size. Call the MediaBuffer::GetMaxLength function to obtain 
        /// the maximum size.
        /// </param>
        void SetLength(DWORD length) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->SetLength(length);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        /// <summary>
        /// Retrieves the maximum number of bytes this buffer can hold.
        /// </summary>
        /// <param name="maxLength">
        /// Pointer to a variable that receives the buffer's maximum size, in bytes.
        /// </param>
        void GetMaxLength(DWORD* maxLength) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->GetMaxLength(maxLength);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }
        DWORD GetMaxLength() const
        {
            DWORD result = 0;
            GetMaxLength(&result);
            return result;
        }

        /// <summary>
        /// Retrieves the buffer and the size of the valid data in the buffer.
        /// </summary>
        /// <param name="buffer">
        /// Address of a pointer that receives the buffer array. Can be nullptr if length is not nullptr.
        /// </param>
        /// <param name="length">
        /// Pointer to a variable that receives the size of the valid data, in bytes. Can be nullptr if buffer is not nullptr.
        /// </param>
        void GetBufferAndLength(BYTE** buffer, DWORD* length) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->GetBufferAndLength(buffer, length);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }
        std::span<BYTE> GetBufferAndLength() const
        {
            BYTE* buffer = nullptr;
            DWORD length = 0;
            GetBufferAndLength(&buffer, &length);
            return { buffer, length };
        }
    };





    /// <summary>
    /// The MediaObject class provides functions for manipulating a Microsoft DirectX Media Object
    /// </summary>
    class MediaObject : public Unknown
    {
    public:
        HCC_COM_STANDARD_METHODS_IMPL(MediaObject, Unknown, IMediaObject, IUnknown)
    public:
        class MediaType
        {
            std::unique_ptr<DMO_MEDIA_TYPE> data_;
        public:
            MediaType()
                : data_(new DMO_MEDIA_TYPE{})
            {}

        };

        /// <summary>
        /// Retrieves the number of input and output streams.
        /// </summary>
        /// <param name="numberOfInputStreams">
        /// Pointer to a variable that receives the number of input streams.
        /// </param>
        /// <param name="numberOfOutputStreams">
        /// Pointer to a variable that receives the number of output streams.
        /// </param>
        /// <returns></returns>
        void GetStreamCount(DWORD* numberOfInputStreams, DWORD* numberOfOutputStreams) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->GetStreamCount(numberOfInputStreams, numberOfOutputStreams);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }
        struct StreamCount
        {
            DWORD InputStreams;
            DWORD OutputStreams;
        };
        StreamCount GetStreamCount() const
        {
            StreamCount result{};
            GetStreamCount(&result.InputStreams, &result.OutputStreams);
            return result;
        }

        /// <summary>
        /// Retrieves information about an input stream, such as any restrictions 
        /// on the number of samples per buffer, and whether the stream performs 
        /// lookahead on the input data. This information never changes.
        /// </summary>
        /// <param name="inputStreamIndex">
        /// Zero-based index of an input stream.
        /// </param>
        /// <param name="flags">
        /// Pointer to a variable that receives a bitwise combination of zero or 
        /// more _DMO_INPUT_STREAM_INFO_FLAGS flags.
        /// </param>
        void GetInputStreamInfo(DWORD inputStreamIndex, DWORD* flags) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->GetInputStreamInfo(inputStreamIndex, flags);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        DWORD GetInputStreamInfo(DWORD inputStreamIndex) const
        {
            DWORD result = 0;
            GetInputStreamInfo(inputStreamIndex, &result);
            return result;
        }


        /// <summary>
        /// Retrieves information about an output stream; for example, whether 
        /// the stream is discardable, and whether it uses a fixed sample size. 
        /// This information never changes.
        /// </summary>
        /// <param name="outputStreamIndex">
        /// Zero-based index of an output stream
        /// </param>
        /// <param name="flags">
        /// Pointer to a variable that receives a bitwise combination of zero or 
        /// more _DMO_OUTPUT_STREAM_INFO_FLAGS flags.
        /// </param>
        void GetOutputStreamInfo(DWORD outputStreamIndex, DWORD* flags) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->GetOutputStreamInfo(outputStreamIndex, flags);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }
        DWORD GetOutputStreamInfo(DWORD outputStreamIndex) const
        {
            DWORD result = 0;
            GetOutputStreamInfo(outputStreamIndex, &result);
            return result;
        }

        /// <summary>
        /// Retrieves a preferred media type for a specified input stream.
        /// </summary>
        /// <param name="inputStreamIndex">
        /// Zero-based index of an input stream
        /// </param>
        /// <param name="typeIndex">
        /// Zero-based index on the set of acceptable media types.
        /// </param>
        /// <param name="mediaType">
        /// Pointer to a DMO_MEDIA_TYPE structure allocated by the caller, 
        /// or nullptr. If this parameter is non-NULL, the method fills the 
        /// structure with the media type. You can use the value NULL to test 
        /// whether the type index is in range, by checking the return code.
        /// </param>
        /// <returns>
        /// true on success, or false if the typeIndex is out of range.
        /// </returns>
        /// <remarks>
        /// <p>
        /// Call this method to enumerate an input stream's preferred media types. 
        /// The DMO assigns each media type an index value in order of preference. 
        /// The most preferred type has an index of zero. To enumerate all the types, 
        /// make successive calls while incrementing the type index until the method 
        /// returns false. The DMO is not guaranteed to enumerate every media type 
        /// that it supports.
        /// </p>
        /// <p>
        /// The format block in the returned type might be NULL. If so, the format type 
        /// is GUID_NULL. Check the format type before dereferencing the format block.
        /// </p>
        /// <p>
        /// If the method succeeds, call MoFreeMediaType to free the format block. 
        /// (This function is also safe to call when the format block is NULL.)
        /// </p>
        /// <p>
        /// To set the media type, call the MediaObject::SetInputType method. Setting 
        /// the media type on one stream can change another stream's preferred types. 
        /// In fact, a stream might not have a preferred type until the type is set 
        /// on another stream. For example, a decoder might not have a preferred output 
        /// type until the input type is set. However, the DMO is not required to 
        /// update its preferred types dynamically in this fashion. Thus, the types 
        /// returned by this method are not guaranteed to be valid; they might fail 
        /// when used in the SetInputType method.
        /// </p>
        /// <p>
        /// To test whether a particular media type is acceptable, call SetInputType 
        /// with the DMO_SET_TYPEF_TEST_ONLY flag.
        /// </p>
        /// <p>
        /// To test whether the typeIndex parameter is in range, set mediaType to NULL. 
        /// The method returns true if the index is in range, or false if the index is 
        /// out of range.
        /// </p>
        /// </remarks>
        bool GetInputType(DWORD inputStreamIndex, DWORD typeIndex, DMO_MEDIA_TYPE* mediaType) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->GetInputType(inputStreamIndex, typeIndex, mediaType);
            if (hr != S_OK && hr != DMO_E_NO_MORE_ITEMS)
            {
                HCC_COM_CHECK_HRESULT2(hr, pInterface);
            }
            return hr == S_OK;
        }

        /// <summary>
        /// Retrieves a preferred media type for a specified output stream.
        /// </summary>
        /// <param name="outputStreamIndex">
        /// Zero-based index of an output stream
        /// </param>
        /// <param name="typeIndex">
        /// Zero-based index on the set of acceptable media types.
        /// </param>
        /// <param name="mediaType">
        /// Pointer to a DMO_MEDIA_TYPE structure allocated by the caller, or NULL. 
        /// If this parameter is non-NULL, the method fills the structure with the 
        /// media type. You can use the value NULL to test whether the type index is 
        /// in range, by checking the return code.
        /// </param>
        /// <returns>
        /// true on success, or false if the typeIndex is out of range.
        /// </returns>
        /// <remarks>
        /// <p>
        /// Call this method to enumerate an output stream's preferred media types. 
        /// The DMO assigns each media type an index value, in order of preference. 
        /// The most preferred type has an index of zero. To enumerate all the types, 
        /// make successive calls while incrementing the type index, until the method 
        /// returns false. The DMO is not guaranteed to enumerate every media type 
        /// that it supports.
        /// </p>
        /// <p>
        /// The format block in the returned type might be NULL. If so, the format type 
        /// is GUID_NULL. You should check the format type before dereferencing the format block.
        /// </p>
        /// <p>
        /// If the method succeeds, call MoFreeMediaType to free the format block. 
        /// (This function is also safe to call when the format block is NULL.)
        /// </p>
        /// <p>
        /// To set the media type, call the MediaObject::SetOutputType method. Setting 
        /// the media type on one stream can change another stream's preferred types. 
        /// In fact, a stream might not have a preferred type until the type is set on 
        /// another stream. For example, a decoder might not have a preferred output type 
        /// until the input type is set. However, the DMO is not required to update 
        /// its preferred types dynamically in this fashion. Thus, the types returned 
        /// by this method are not guaranteed to be valid; they might fail when used in 
        /// the SetOutputType method.
        /// </p>
        /// <p>
        /// To test whether a particular media type is acceptable, call SetOutputType with 
        /// the DMO_SET_TYPEF_TEST_ONLY flag.
        /// </p>
        /// <p>
        /// To test whether the typeIndex parameter is in range, set mediaType to NULL. 
        /// The method returns true if the index is in range, or false if the index is 
        /// out of range.
        /// </p>
        /// </remarks>
        bool GetOutputType(DWORD outputStreamIndex, DWORD typeIndex, DMO_MEDIA_TYPE* mediaType) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->GetInputType(outputStreamIndex, typeIndex, mediaType);
            if (hr != S_OK && hr != DMO_E_NO_MORE_ITEMS)
            {
                HCC_COM_CHECK_HRESULT2(hr, pInterface);
            }
            return hr == S_OK;
        }

        /// <summary>
        /// Sets the media type on an input stream, or tests whether a media type is acceptable.
        /// </summary>
        /// <param name="inputStreamIndex">
        /// Zero-based index of an input stream
        /// </param>
        /// <param name="mediaType">
        /// Pointer to a DMO_MEDIA_TYPE structure that specifies the media type.
        /// </param>
        /// <param name="flags">
        /// Bitwise combination of zero or more flags from the DMO_SET_TYPE_FLAGS enumeration.
        /// </param>
        /// <returns>
        /// true on success, false if flags was equal to DMO_SET_TYPEF_TEST_ONLY and the
        /// mediaType was not acceptable.
        /// </returns>
        /// <remarks>
        /// <p>
        /// Call this method to test, set, or clear the media type on an input stream:
        /// </p>
        /// <ul>
        /// <li>
        /// To test the media type without setting it, use the DMO_SET_TYPEF_TEST_ONLY flag. If 
        /// the media type is not acceptable, the method returns false.
        /// </li>
        /// <li>
        /// To set the media type, set flags to zero. If the media type is not acceptable, 
        /// the method throws an exception for DMO_E_TYPE_NOT_ACCEPTED.
        /// </li>
        /// <li>
        /// To clear the current media type (if any), use the DMO_SET_TYPEF_CLEAR flag 
        /// and set mediaType to NULL. When the method returns, the stream no longer 
        /// has a media type. The DMO cannot process samples until the application 
        /// sets a new media type.
        /// </li>
        /// </ul>
        /// <p>
        /// The media types that are currently set on other streams can affect 
        /// whether the media type is acceptable.
        /// </p>
        /// </remarks>
        bool SetInputType(DWORD inputStreamIndex, const DMO_MEDIA_TYPE* mediaType, DWORD flags = 0) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->SetInputType(inputStreamIndex, mediaType, flags);
            if (hr != S_OK && hr != S_FALSE)
            {
                HCC_COM_CHECK_HRESULT2(hr, pInterface);
            }
            return hr == S_OK;
        }

        bool IsValidInputType(DWORD inputStreamIndex, const DMO_MEDIA_TYPE* mediaType)
        {
            return SetInputType(inputStreamIndex, mediaType, _DMO_SET_TYPE_FLAGS::DMO_SET_TYPEF_TEST_ONLY);
        }
        void ClearInputType(DWORD inputStreamIndex)
        {
            SetInputType(inputStreamIndex, nullptr, _DMO_SET_TYPE_FLAGS::DMO_SET_TYPEF_CLEAR);
        }

        /// <summary>
        /// Sets the media type on an output stream, or tests whether a media type is acceptable.
        /// </summary>
        /// <param name="outputStreamIndex">
        /// Zero-based index of an output stream
        /// </param>
        /// <param name="mediaType">
        /// ointer to a DMO_MEDIA_TYPE structure that specifies the media type.
        /// </param>
        /// <param name="flags">
        /// Bitwise combination of zero or more flags from the DMO_SET_TYPE_FLAGS enumeration.
        /// </param>
        /// <returns>
        /// true on success, false if flags was equal to DMO_SET_TYPEF_TEST_ONLY and the
        /// mediaType was not acceptable.
        /// </returns>
        /// <remarks>
        /// <p>
        /// Call this method to test, set, or clear the media type on an input stream:
        /// </p>
        /// <ul>
        /// <li>
        /// To test the media type without setting it, use the DMO_SET_TYPEF_TEST_ONLY flag. If 
        /// the media type is not acceptable, the method returns false.
        /// </li>
        /// <li>
        /// To set the media type, set flags to zero. If the media type is not acceptable, 
        /// the method throws an exception for DMO_E_TYPE_NOT_ACCEPTED.
        /// </li>
        /// <li>
        /// To clear the current media type (if any), use the DMO_SET_TYPEF_CLEAR flag 
        /// and set mediaType to NULL. When the method returns, the stream no longer 
        /// has a media type. The DMO cannot process samples until the application 
        /// sets a new media type.
        /// </li>
        /// </ul>
        /// <p>
        /// The media types that are currently set on other streams can affect 
        /// whether the media type is acceptable.
        /// </p>
        /// </remarks>
        bool SetOutputType( DWORD outputStreamIndex, const DMO_MEDIA_TYPE* mediaType, DWORD flags) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->SetOutputType(outputStreamIndex, mediaType, flags);
            if (hr != S_OK && hr != S_FALSE)
            {
                HCC_COM_CHECK_HRESULT2(hr, pInterface);
            }
            return hr == S_OK;
        }

        bool IsValidOutputType(DWORD outputStreamIndex, const DMO_MEDIA_TYPE* mediaType)
        {
            return SetOutputType(outputStreamIndex, mediaType, _DMO_SET_TYPE_FLAGS::DMO_SET_TYPEF_TEST_ONLY);
        }
        void ClearOutputType(DWORD outputStreamIndex)
        {
            SetOutputType(outputStreamIndex, nullptr, _DMO_SET_TYPE_FLAGS::DMO_SET_TYPEF_CLEAR);
        }


        /// <summary>
        /// Retrieves the media type that was set for an input stream, if any.
        /// </summary>
        /// <param name="inputStreamIndex">
        /// Zero-based index of an input stream
        /// </param>
        /// <param name="mediaType">
        /// Pointer to a DMO_MEDIA_TYPE structure allocated by the caller. 
        /// The method fills the structure with the media type.
        /// </param>
        /// <returns>
        /// true on success, false if media type was not set.
        /// </returns>
        /// <remarks>
        /// <p>
        /// The caller must set the media type for the stream before calling 
        /// this method. To set the media type, call the MediaObject::SetInputType method.
        /// </p>
        /// <p>
        /// If the method succeeds, call MoFreeMediaType to free the format block.
        /// </p>
        /// </remarks>
        bool GetInputCurrentType(DWORD inputStreamIndex, DMO_MEDIA_TYPE* mediaType) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->GetInputCurrentType(inputStreamIndex, mediaType);
            if (hr != S_OK && hr != DMO_E_TYPE_NOT_SET)
            {
                HCC_COM_CHECK_HRESULT2(hr, pInterface);
            }
            return hr == S_OK;
        }

        bool GetOutputCurrentType(DWORD outputStreamIndex, DMO_MEDIA_TYPE* mediaType) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->GetOutputCurrentType(outputStreamIndex, mediaType);
            if (hr != S_OK && hr != DMO_E_TYPE_NOT_SET)
            {
                HCC_COM_CHECK_HRESULT2(hr, pInterface);
            }
            return hr == S_OK;
        }

        void GetInputSizeInfo( DWORD iputStreamIndex, DWORD* size, DWORD* maxLookahead, DWORD* alignment) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->GetInputSizeInfo(iputStreamIndex, size, maxLookahead, alignment);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        void GetOutputSizeInfo(DWORD outputStreamIndex,DWORD* size, DWORD* alignment) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->GetOutputSizeInfo(outputStreamIndex, size, alignment);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        void GetInputMaxLatency( DWORD inputStreamIndex, REFERENCE_TIME* maxLatency) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->GetInputMaxLatency(inputStreamIndex, maxLatency);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        void SetInputMaxLatency(DWORD inputStreamIndex, REFERENCE_TIME maxLatency) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->SetInputMaxLatency(inputStreamIndex, maxLatency);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        void Flush() const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->Flush( );
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        void Discontinuity(DWORD inputStreamIndex) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->Discontinuity(inputStreamIndex);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        void AllocateStreamingResources() const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->AllocateStreamingResources( );
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        void FreeStreamingResources() const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->FreeStreamingResources();
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        void GetInputStatus( DWORD inputStreamIndex, DWORD* flags) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->GetInputStatus(inputStreamIndex, flags);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        void ProcessInput( DWORD inputStreamIndex, IMediaBuffer* buffer, DWORD flags, REFERENCE_TIME timestamp, REFERENCE_TIME timelength) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->ProcessInput(inputStreamIndex, buffer, flags, timestamp, timelength);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        void ProcessOutput( DWORD flags, DWORD outputBufferCount, DMO_OUTPUT_DATA_BUFFER* outputBuffers, DWORD* status) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->ProcessOutput(flags, outputBufferCount, outputBuffers, status);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        void Lock(LONG lock) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->Lock(lock);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }
    };

    /// <summary>
    /// This class provides methods for enumerating Microsoft DirectX Media Objects (DMOs). 
    /// </summary>
    class EnumDMO : public Unknown
    {
    public:
        HCC_COM_STANDARD_METHODS_IMPL(EnumDMO, Unknown, IEnumDMO, IUnknown)
    public:
        void Next( DWORD numberOfItemsToFetch, CLSID* classIds, LPWSTR* names, DWORD* itemsFetched) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->Next(numberOfItemsToFetch, classIds, names, itemsFetched);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        void Skip( DWORD numberOfToItemsToSkip) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->Skip(numberOfToItemsToSkip);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        void Reset( ) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->Reset( );
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        void Clone( IEnumDMO** result) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->Clone(result);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        EnumDMO Clone() const
        {
            IEnumDMO* itf = nullptr;
            Clone(&itf);
            return EnumDMO(itf);
        }
    };

    /// <summary>
    /// The MediaObjectInPlace class provides methods for processing data in place. 
    /// </summary>
    class MediaObjectInPlace : public Unknown
    {
    public:
        HCC_COM_STANDARD_METHODS_IMPL(MediaObjectInPlace, Unknown, IMediaObjectInPlace, IUnknown)
    public:
        void Process( ULONG dataSize, BYTE* data, REFERENCE_TIME refTimeStart, DWORD flags) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->Process(dataSize, data, refTimeStart, flags);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        void Clone( IMediaObjectInPlace** result ) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->Clone(result);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }
        MediaObjectInPlace Clone() const
        {
            IMediaObjectInPlace* itf = nullptr;
            Clone(&itf);
            return MediaObjectInPlace(itf);
        }


        void GetLatency( REFERENCE_TIME* latencyTime) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->GetLatency(latencyTime);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        TimeSpan GetLatency() const
        {
            REFERENCE_TIME result = 0;
            GetLatency(&result);
            return TimeSpan(result);
        }

    };

    /// <summary>
    /// The DMOQualityControl class supports quality control on a Microsoft DirectX Media Object (DMO).
    /// </summary>
    class DMOQualityControl : public Unknown
    {
    public:
        HCC_COM_STANDARD_METHODS_IMPL(DMOQualityControl, Unknown, IDMOQualityControl, IUnknown)
    public:
        void SetNow(REFERENCE_TIME now) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->SetNow(now);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }
        void SetNow(const TimeSpan& now) const
        {
            SetNow(now.Ticks());
        }

        void SetStatus( DWORD flags) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->SetStatus(flags);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        void GetStatus( DWORD* flags) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->GetStatus(flags);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }
        DWORD GetStatus() const
        {
            DWORD result = 0;
            GetStatus(&result);
            return result;
        }
    };

    /// <summary>
    /// The DMOVideoOutputOptimizations class supports video optimizations on a Microsoft DirectX Media Object (DMO).
    /// </summary>
    class DMOVideoOutputOptimizations : public Unknown
    {
    public:
        HCC_COM_STANDARD_METHODS_IMPL(DMOVideoOutputOptimizations, Unknown, IDMOVideoOutputOptimizations, IUnknown)
    public:
        void QueryOperationModePreferences( ULONG outputStreamIndex, DWORD* requestedCapabilities) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->QueryOperationModePreferences(outputStreamIndex, requestedCapabilities);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        void SetOperationMode( ULONG outputStreamIndex, DWORD enabledFeatures) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->SetOperationMode(outputStreamIndex, enabledFeatures);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        void GetCurrentOperationMode( ULONG outputStreamIndex, DWORD* enabledFeatures) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->GetCurrentOperationMode(outputStreamIndex, enabledFeatures);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        void GetCurrentSampleRequirements( ULONG outputStreamIndex, DWORD* requestedFeatures) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->GetCurrentSampleRequirements(outputStreamIndex, requestedFeatures);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }
    };


}


#endif
