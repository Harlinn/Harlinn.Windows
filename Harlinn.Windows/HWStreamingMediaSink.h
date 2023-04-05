#pragma once
#ifndef HARLINN_WINDOWS_HWSTREAMINGMEDIASINK_H_
#define HARLINN_WINDOWS_HWSTREAMINGMEDIASINK_H_

#include "HWMediaFoundation.h"

namespace Harlinn::Windows::MF
{
    class StreamingStreamSink;
    class StreamingMediaSink;

    class StreamingStreamSinkData
    {
        Guid sinkId_;
        DWORD streamId_ = 0;

    };



    class StreamingStreamSink : public Com::IUknownImpl<StreamingStreamSink, IMFStreamSink, IMFMediaTypeHandler>
    {
        DWORD streamId_ = 0;

    public:

        // IMFMediaEventGenerator


        /// <summary>
        /// Retrieves the next event in the queue. This method is synchronous.
        /// </summary>
        /// <param name="dwFlags">
        /// <p>
        /// Specifies one of the following values:
        /// </p>
        /// <ul>
        /// <li>0: The method blocks until the event generator queues an event.</li>
        /// <li>MF_EVENT_FLAG_NO_WAIT: The method returns immediately.</li>
        /// </ul>
        /// </param>
        /// <param name="ppEvent">
        /// Receives a pointer to the IMFMediaEvent interface. The caller must release the interface.
        /// </param>
        /// <returns>
        /// <p>
        /// The method returns an HRESULT. Possible values include, but are not limited to, the following:
        /// </p>
        /// <ul>
        /// <li>S_OK: The method succeeded.</li>
        /// <li>E_INVALIDARG: NULL pointer argument.</li>
        /// <li>MF_E_MULTIPLE_SUBSCRIBERS: There is a pending request.</li>
        /// <li>MF_E_NO_EVENTS_AVAILABLE: There are no events in the queue.</li>
        /// <li>MF_E_SHUTDOWN: The object was shut down.</li>
        /// </ul>
        /// </returns>
        /// <remarks>
        /// <p>
        /// This method executes synchronously.
        /// </p>
        /// <p>
        /// If the queue already contains an event, the method returns S_OK immediately. 
        /// If the queue does not contain an event, the behavior depends on the value of 
        /// dwFlags:
        /// </p>
        /// <ul>
        /// <li>
        /// If dwFlags is 0, the method blocks indefinitely until a new event is queued, 
        /// or until the event generator is shut down.
        /// </li>
        /// <li>
        /// If dwFlags is MF_EVENT_FLAG_NO_WAIT, the method fails immediately with the 
        /// return code MF_E_NO_EVENTS_AVAILABLE.
        /// </li>
        /// </ul>
        /// <p>
        /// This method returns MF_E_MULTIPLE_SUBSCRIBERS if you previously called 
        /// IMFMediaEventGenerator::BeginGetEvent and have not yet called 
        /// IMFMediaEventGenerator::EndGetEvent.
        /// </p>
        /// </remarks>
        virtual HRESULT STDMETHODCALLTYPE GetEvent(DWORD dwFlags, __RPC__deref_out_opt IMFMediaEvent** ppEvent) override
        {
            try
            {
            }
            HCC_COM_CATCH_ALL_REPORT_EXCEPTION_AND_RETURN_HRESULT();
        }

        /// <summary>
        /// Begins an asynchronous request for the next event in the queue.
        /// </summary>
        /// <param name="pCallback">
        /// Pointer to the IMFAsyncCallback interface of a callback object. The client must 
        /// implement this interface.
        /// </param>
        /// <param name="punkState">
        /// Pointer to the IUnknown interface of a state object, defined by the caller. This 
        /// parameter can be NULL. You can use this object to hold state information. The 
        /// object is returned to the caller when the callback is invoked.
        /// </param>
        /// <returns>
        /// <p>
        /// The method returns an HRESULT. Possible values include, but are not limited to, the following:
        /// </p>
        /// <ul>
        /// <li>
        /// S_OK: The method succeeded.
        /// </li>
        /// <li>
        /// E_INVALIDARG: NULL pointer argument.
        /// </li>
        /// <li>
        /// MF_E_MULTIPLE_BEGIN: There is a pending request with the same callback pointerand a different state object.
        /// </li>
        /// <li>
        /// MF_E_MULTIPLE_SUBSCRIBERS: There is a pending request with a different callback pointer.
        /// </li>
        /// <li>
        /// MF_E_SHUTDOWN: The object was shut down.
        /// </li>
        /// <li>
        /// MF_S_MULTIPLE_BEGIN: There is a pending request with the same callback pointerand state object.
        /// </li>
        /// </ul>
        /// </returns>
        /// <remarks>
        /// <p>
        /// When a new event is available, the event generator calls the IMFAsyncCallback::Invoke method. 
        /// The Invoke method should call IMFMediaEventGenerator::EndGetEvent to get a pointer to the 
        /// IMFMediaEvent interface, and use that interface to examine the event.
        /// </p>
        /// <p>
        /// Do not call BeginGetEvent a second time before calling EndGetEvent. While the first call is 
        /// still pending, additional calls to the same object will fail. Also, the 
        /// IMFMediaEventGenerator::GetEvent method fails if an asynchronous request is still pending.
        /// </p>
        /// </remarks>
        virtual HRESULT STDMETHODCALLTYPE BeginGetEvent(IMFAsyncCallback* pCallback, IUnknown* punkState) override
        {
            try
            {
            }
            HCC_COM_CATCH_ALL_REPORT_EXCEPTION_AND_RETURN_HRESULT();
        }

        /// <summary>
        /// Completes an asynchronous request for the next event in the queue.
        /// </summary>
        /// <param name="pResult">
        /// Pointer to the IMFAsyncResult interface. Pass in the same pointer that your callback object 
        /// received in the Invoke method.
        /// </param>
        /// <param name="ppEvent">
        /// Receives a pointer to the IMFMediaEvent interface. The caller must release the interface.
        /// </param>
        /// <returns>
        /// <p>
        /// The method returns an HRESULT. Possible values include, but are not limited to, the following:
        /// </p>
        /// <ul>
        /// <li>
        /// S_OK: The method succeeded.
        /// </li>
        /// <li>
        /// MF_E_SHUTDOWN: The object was shut down.
        /// </li>
        /// </ul>
        /// </returns>
        /// <remarks>
        /// Call this method from inside your application's IMFAsyncCallback::Invoke method.
        /// </remarks>
        virtual HRESULT STDMETHODCALLTYPE EndGetEvent(IMFAsyncResult* pResult, _Out_  IMFMediaEvent** ppEvent) override
        {
            try
            {
            }
            HCC_COM_CATCH_ALL_REPORT_EXCEPTION_AND_RETURN_HRESULT();
        }

        /// <summary>
        /// Puts a new event in the object's queue.
        /// </summary>
        /// <param name="met">
        /// Specifies the event type. The event type is returned by the event's 
        /// IMFMediaEvent::GetType method. For a list of event types, see <a href="https://docs.microsoft.com/en-us/windows/desktop/medfound/media-foundation-events">Media Foundation Events</h>.
        /// </param>
        /// <param name="guidExtendedType">
        /// The extended type. If the event does not have an extended type, use the value 
        /// GUID_NULL. The extended type is returned by the event's IMFMediaEvent::GetExtendedType method.
        /// </param>
        /// <param name="hrStatus">
        /// A success or failure code indicating the status of the event. This value is returned by the event's IMFMediaEvent::GetStatus method.
        /// </param>
        /// <param name="pvValue">
        /// Pointer to a PROPVARIANT that contains the event value. This parameter can be NULL. This value is returned by the event's IMFMediaEvent::GetValue method.
        /// </param>
        /// <returns></returns>
        virtual HRESULT STDMETHODCALLTYPE QueueEvent(MediaEventType met, __RPC__in REFGUID guidExtendedType, HRESULT hrStatus, __RPC__in_opt const PROPVARIANT* pvValue) override
        {
            try
            {
            }
            HCC_COM_CATCH_ALL_REPORT_EXCEPTION_AND_RETURN_HRESULT();
        }


        // IMFStreamSink interface


        /// <summary>
        /// Retrieves the media sink that owns this stream sink.
        /// </summary>
        /// <param name="ppMediaSink">
        /// Receives a pointer to the media sink's IMFMediaSink interface. 
        /// The caller must release the interface.
        /// </param>
        /// <returns>
        /// <p>
        /// The method returns an HRESULT. Possible values include, but are not limited to, the following:
        /// </p>
        /// <ul>
        /// <li>
        /// S_OK: The method succeeded.
        /// </li>
        /// <li>
        /// MF_E_SHUTDOWN: The media sink's Shutdown method has been called.
        /// </li>
        /// <li>
        /// MF_E_STREAMSINK_REMOVED: This stream was removed from the media sinkand is no longer valid.
        /// </li>
        /// </ul>
        /// </returns>
        virtual HRESULT STDMETHODCALLTYPE GetMediaSink(__RPC__deref_out_opt IMFMediaSink** ppMediaSink) override
        {
            try
            {
            }
            HCC_COM_CATCH_ALL_REPORT_EXCEPTION_AND_RETURN_HRESULT();
        }


        /// <summary>
        /// Retrieves the stream identifier for this stream sink.
        /// </summary>
        /// <param name="pdwIdentifier">
        /// Receives the stream identifier. If this stream sink was added by calling 
        /// IMFMediaSink::AddStreamSink, the stream identifier is in the dwStreamSinkIdentifier 
        /// parameter of that method. Otherwise, the media sink defines the identifier.
        /// </param>
        /// <returns>
        /// <p>
        /// The method returns an HRESULT. Possible values include, but are not limited to, the following:
        /// </p>
        /// <ul>
        /// <li>
        /// S_OK: The method succeeded.
        /// </li>
        /// <li>
        /// MF_E_SHUTDOWN: The media sink's Shutdown method has been called.
        /// </li>
        /// <li>
        /// MF_E_STREAMSINK_REMOVED: This stream was removed from the media sinkand is no longer valid.
        /// </li>
        /// </ul>
        /// </returns>
        virtual HRESULT STDMETHODCALLTYPE GetIdentifier(__RPC__out DWORD* pdwIdentifier) override
        {
            try
            {
            }
            HCC_COM_CATCH_ALL_REPORT_EXCEPTION_AND_RETURN_HRESULT();
        }

        /// <summary>
        /// Retrieves the media type handler for the stream sink. You can use the media type handler 
        /// to find which formats the stream supports, and to set the media type on the stream.
        /// </summary>
        /// <param name="ppHandler">
        /// Receives a pointer to the IMFMediaTypeHandler interface. The caller must release the interface.
        /// </param>
        /// <returns>
        /// <p>
        /// The method returns an HRESULT. Possible values include, but are not limited to, the following:
        /// </p>
        /// <ul>
        /// <li>
        /// S_OK: The method succeeded.
        /// </li>
        /// <li>
        /// MF_E_SHUTDOWN: The media sink's Shutdown method has been called.
        /// </li>
        /// <li>
        /// MF_E_STREAMSINK_REMOVED: This stream was removed from the media sinkand is no longer valid.
        /// </li>
        /// </ul>
        /// </returns>
        /// <remarks>
        /// If the stream sink currently does not support any media types, this method returns a media 
        /// type handler that fails any calls to IMFMediaTypeHandler::GetCurrentMediaType and 
        /// IMFMediaTypeHandler::IsMediaTypeSupported.
        /// </remarks>
        virtual HRESULT STDMETHODCALLTYPE GetMediaTypeHandler(__RPC__deref_out_opt IMFMediaTypeHandler** ppHandler) override
        {
            try
            {
            }
            HCC_COM_CATCH_ALL_REPORT_EXCEPTION_AND_RETURN_HRESULT();
        }

        /// <summary>
        /// Delivers a sample to the stream. The media sink processes the sample.
        /// </summary>
        /// <param name="pSample">
        /// Pointer to the IMFSample interface of a sample that contains valid data for the stream.
        /// </param>
        /// <returns>
        /// The method returns an HRESULT. Possible values include, but are not limited to, the following:
        /// <ul>
        /// <li>
        /// S_OK: The method succeeded.
        /// </li>
        /// <li>
        /// MF_E_INVALID_STATE_TRANSITION: The media sink is in the wrong state to receive a sample. 
        /// For example, preroll is complete but the presentation clock has not started yet.
        /// </li>
        /// <li>
        /// MF_E_INVALID_TIMESTAMP: The sample has an invalid time stamp.See Remarks.
        /// </li>
        /// <li>
        /// MF_E_INVALIDREQUEST: The media sink is paused or stopped and cannot process the sample.
        /// </li>
        /// <li>
        /// MF_E_NO_CLOCK: The presentation clock was not set.Call IMFMediaSink::SetPresentationClock.
        /// </li>
        /// <li>
        /// MF_E_NO_SAMPLE_TIMESTAMP: The sample does not have a time stamp.
        /// </li>
        /// <li>
        /// MF_E_NOT_INITIALIZED: The stream sink has not been initialized.
        /// </li>
        /// <li>
        /// MF_E_SHUTDOWN: The media sink's Shutdown method has been called.
        /// </li>
        /// <li>
        /// MF_E_STREAMSINK_REMOVED: This stream was removed from the media sinkand is no longer valid.
        /// </li>
        /// </ul>
        /// </returns>
        /// <remarks>
        /// <p>
        /// Call this method when the stream sink sends an MEStreamSinkRequestSample event.
        /// </p>
        /// <p>
        /// This method can return MF_E_INVALID_TIMESTAMP for various reasons, depending 
        /// on the implementation of the media sink:
        /// </p>
        /// <ul>
        /// <li>
        /// Negative time stamps.
        /// </li>
        /// <li>
        /// Time stamps that jump backward (within the same stream).
        /// </li>
        /// <li>
        /// The time stamps for one stream have drifted too far from the time stamps on another 
        /// stream within the same media sink (for example, an archive sink that multiplexes the streams).
        /// </li>
        /// </ul>
        /// <p>
        /// Not every media sink returns an error code in these situations.
        /// </p>
        /// </remarks>
        virtual HRESULT STDMETHODCALLTYPE ProcessSample(__RPC__in_opt IMFSample* pSample) override
        {
            try
            {
            }
            HCC_COM_CATCH_ALL_REPORT_EXCEPTION_AND_RETURN_HRESULT();
        }

        /// <summary>
        /// Places a marker in the stream.
        /// </summary>
        /// <param name="eMarkerType">
        /// Specifies the marker type, as a member of the MFSTREAMSINK_MARKER_TYPE enumeration.
        /// </param>
        /// <param name="pvarMarkerValue">
        /// Optional pointer to a PROPVARIANT that contains additional information related to 
        /// the marker. The meaning of this value depends on the marker type. This parameter 
        /// can be NULL.
        /// </param>
        /// <param name="pvarContextValue">
        /// Optional pointer to a PROPVARIANT that is attached to the MEStreamSinkMarker event. 
        /// Call IMFMediaEvent::GetValue to get this value from the event. The caller can use 
        /// this information for any purpose. This parameter can be NULL.
        /// </param>
        /// <returns>
        /// <p>
        /// The method returns an HRESULT. Possible values include, but are not limited to, the following:
        /// </p>
        /// <ul>
        /// <li>
        /// S_OK: The method succeeded.
        /// </li>
        /// <li>
        /// MF_E_SHUTDOWN: The media sink's Shutdown method has been called.
        /// </li>
        /// <li>
        /// MF_E_STREAMSINK_REMOVED: This stream was removed from the media sinkand is no longer valid.
        /// </li>
        /// </ul>
        /// </returns>
        /// <remarks>
        /// This method causes the stream sink to send an MEStreamSinkMarker event after the stream 
        /// sink consumes all of the samples that were delivered up to this point (before the call to PlaceMarker).
        /// </remarks>
        virtual HRESULT STDMETHODCALLTYPE PlaceMarker(MFSTREAMSINK_MARKER_TYPE eMarkerType, __RPC__in const PROPVARIANT* pvarMarkerValue, __RPC__in const PROPVARIANT* pvarContextValue) override
        {
            try
            {
            }
            HCC_COM_CATCH_ALL_REPORT_EXCEPTION_AND_RETURN_HRESULT();
        }

        /// <summary>
        /// Causes the stream sink to drop any samples that it has received 
        /// and has not rendered yet.
        /// </summary>
        /// <returns>
        /// <p>
        /// The method returns an HRESULT. Possible values include, but are not limited to, the following:
        /// </p>
        /// <ul>
        /// <li>
        /// S_OK: The method succeeded.
        /// </li>
        /// <li>
        /// MF_E_NOT_INITIALIZED: The stream sink has not been initialized yet.You might need to set a media type.
        /// </li>
        /// <li>
        /// MF_E_SHUTDOWN: The media sink's Shutdown method has been called.
        /// </li>
        /// <li>
        /// MF_E_STREAMSINK_REMOVED: This stream was removed from the media sinkand is no longer valid.
        /// </li>
        /// </ul>
        /// </returns>
        /// <remarks>
        /// <p>
        /// If any samples are still queued from previous calls to the IMFStreamSink::ProcessSample 
        /// method, the media sink immediately discards them, without processing them. This can 
        /// cause a glitch in the rendered output. The running state of the sink (running, paused, 
        /// or stopped) does not change.
        /// </p>
        /// <p>
        /// Any pending marker events from the IMFStreamSink::PlaceMarker method are dispatched 
        /// immediately, with the status code E_ABORT.
        /// </p>
        /// <p>
        /// This method is synchronous. It does not return until the sink has discarded all 
        /// pending samples.
        /// </p>
        /// </remarks>
        virtual HRESULT STDMETHODCALLTYPE Flush() override
        {
            try
            {
            }
            HCC_COM_CATCH_ALL_REPORT_EXCEPTION_AND_RETURN_HRESULT();
        }

        // IMFMediaTypeHandler interface:

        /// <summary>
        /// Queries whether the object supports a specified media type.
        /// </summary>
        /// <param name="pMediaType">
        /// Pointer to the IMFMediaType interface of the media type to check.
        /// </param>
        /// <param name="ppMediaType">
        /// Receives a pointer to the IMFMediaType interface of the closest matching media 
        /// type, or receives the value NULL. If non-NULL, the caller must release the 
        /// interface. This parameter can be NULL. See Remarks.
        /// </param>
        /// <returns>
        /// <p>
        /// The method returns an HRESULT. Possible values include, but are not limited to, the following:
        /// </p>
        /// <ul>
        /// <li>
        /// S_OK: The method succeeded.
        /// </li>
        /// <li>
        /// MF_E_INVALIDMEDIATYPE: The object does not support this media type.
        /// </li>
        /// </ul>
        /// </returns>
        /// <remarks>
        /// <p>
        /// If the object supports the media type given in pMediaType, the method returns S_OK. 
        /// For a media source, it means the source can generate data that conforms to that media type. 
        /// For a media sink, it means the sink can receive data that conforms to that media type. 
        /// If the object does not support the media type, the method fails.
        /// </p>
        /// <p>
        /// The ppMediaType parameter is optional. If the method fails, the object might use ppMediaType 
        /// to return a media type that the object does support, and which closely matches the one given 
        /// in pMediaType. The method is not guaranteed to return a media type in ppMediaType. If no type 
        /// is returned, this parameter receives a NULL pointer. If the method succeeds, this parameter 
        /// receives a NULL pointer. If the caller sets ppMediaType to NULL, this parameter is ignored.
        /// </p>
        /// </remarks>
        virtual HRESULT STDMETHODCALLTYPE IsMediaTypeSupported(IMFMediaType* pMediaType, _Outptr_opt_result_maybenull_  IMFMediaType** ppMediaType) override
        {
            try
            {
            }
            HCC_COM_CATCH_ALL_REPORT_EXCEPTION_AND_RETURN_HRESULT();
        }

        /// <summary>
        /// Retrieves the number of media types in the object's list of supported media types.
        /// </summary>
        /// <param name="pdwTypeCount">
        /// Receives the number of media types in the list.
        /// </param>
        /// <returns>
        /// If this method succeeds, it returns S_OK. Otherwise, it returns an HRESULT error code.
        /// </returns>
        /// <remarks>
        /// <p>
        /// To get the supported media types, call IMFMediaTypeHandler::GetMediaTypeByIndex.
        /// </p>
        /// <p>
        /// For a media source, the media type handler for each stream must contain at least one supported 
        /// media type. For media sinks, the media type handler for each stream might contain zero media 
        /// types. In that case, the application must provide the media type. To test whether a particular 
        /// media type is supported, call IMFMediaTypeHandler::IsMediaTypeSupported.
        /// </p>
        /// </remarks>
        virtual HRESULT STDMETHODCALLTYPE GetMediaTypeCount(__RPC__out DWORD* pdwTypeCount) override
        {
            try
            {
            }
            HCC_COM_CATCH_ALL_REPORT_EXCEPTION_AND_RETURN_HRESULT();
        }

        /// <summary>
        /// Retrieves a media type from the object's list of supported media types.
        /// </summary>
        /// <param name="dwIndex">
        /// Zero-based index of the media type to retrieve. To get the number of media types in the list, 
        /// call IMFMediaTypeHandler::GetMediaTypeCount.
        /// </param>
        /// <param name="ppType">
        /// Receives a pointer to the IMFMediaType interface. The caller must release the interface.
        /// </param>
        /// <returns>
        /// <p>
        /// The method returns an HRESULT. Possible values include, but are not limited to, the following:
        /// </p>
        /// <ul>
        /// <li>
        /// S_OK: The method succeeded.
        /// </li>
        /// <li>
        /// MF_E_NO_MORE_TYPES: The dwIndex parameter is out of range.
        /// </li>
        /// </ul>
        /// </returns>
        /// <remarks>
        /// Media types are returned in the approximate order of preference. The list of supported types is 
        /// not guaranteed to be complete. To test whether a particular media type is supported, call 
        /// IMFMediaTypeHandler::IsMediaTypeSupported.
        /// </remarks>
        virtual HRESULT STDMETHODCALLTYPE GetMediaTypeByIndex(DWORD dwIndex, _Outptr_  IMFMediaType** ppType) override
        {
            try
            {
            }
            HCC_COM_CATCH_ALL_REPORT_EXCEPTION_AND_RETURN_HRESULT();
        }

        /// <summary>
        /// Sets the object's media type.
        /// </summary>
        /// <param name="pMediaType">
        /// Pointer to the IMFMediaType interface of the new media type.
        /// </param>
        /// <returns>
        /// <p>
        /// The method returns an HRESULT. Possible values include, but are not limited to, the following:
        /// </p>
        /// <ul>
        /// <li>
        /// S_OK: The method succeeded.
        /// </li>
        /// <li>
        /// MF_E_INVALIDREQUEST: Invalid request.
        /// </li>
        /// </ul>
        /// </returns>
        /// <remarks>
        /// <p>
        /// For media sources, setting the media type means the source will generate data that conforms to 
        /// that media type. For media sinks, setting the media type means the sink can receive data that 
        /// conforms to that media type.
        /// </p>
        /// <p>
        /// Any implementation of this method should check whether pMediaType differs from the object's 
        /// current media type. If the types are identical, the method should return S_OK but avoid 
        /// releasing and recreating resources unnecessarily. If the types are not identical, the 
        /// method should validate the new type.
        /// </p>
        /// </remakrs>
        virtual HRESULT STDMETHODCALLTYPE SetCurrentMediaType(IMFMediaType* pMediaType) override
        {
            try
            {
            }
            HCC_COM_CATCH_ALL_REPORT_EXCEPTION_AND_RETURN_HRESULT();
        }

        /// <summary>
        /// Retrieves the current media type of the object.
        /// </summary>
        /// <param name="ppMediaType">
        /// Receives a pointer to the IMFMediaType interface. The caller must release the interface.
        /// </param>
        /// <returns>
        /// <p>
        /// The method returns an HRESULT. Possible values include, but are not limited to, the following:
        /// </p>
        /// <ul>
        /// <li>
        /// S_OK: The method succeeded.
        /// </li>
        /// <li>
        /// MF_E_NOT_INITIALIZED: No media type is set.
        /// </li>
        /// </ul>
        /// </returns>
        virtual HRESULT STDMETHODCALLTYPE GetCurrentMediaType(_Outptr_  IMFMediaType** ppMediaType) override
        {
            try
            {
            }
            HCC_COM_CATCH_ALL_REPORT_EXCEPTION_AND_RETURN_HRESULT();
        }

        /// <summary>
        /// Gets the major media type of the object.
        /// </summary>
        /// <param name="pguidMajorType">
        /// Receives a GUID that identifies the major type. For a list of 
        /// possible values, see <a href="https://docs.microsoft.com/en-us/windows/desktop/medfound/media-type-guids">Major Media Types</a>.
        /// </param>
        /// <returns>
        /// If this method succeeds, it returns S_OK. Otherwise, it returns an HRESULT error code.
        /// </returns>
        /// <remarks>
        /// The major type identifies what kind of data is in the stream, such as audio or video. To 
        /// get the specific details of the format, call IMFMediaTypeHandler::GetCurrentMediaType.
        /// </remarks>
        virtual HRESULT STDMETHODCALLTYPE GetMajorType(__RPC__out GUID* pguidMajorType) override
        {
            try
            {
            }
            HCC_COM_CATCH_ALL_REPORT_EXCEPTION_AND_RETURN_HRESULT();
        }
    };

    class StreamingMediaSink : public Com::IUknownImpl<StreamingMediaSink, IMFFinalizableMediaSink, IMFClockStateSink, IMFAsyncCallback>
    {
    public:
        // IMFMediaSink interface:

        /// <summary>
        /// Gets the characteristics of the media sink.
        /// </summary>
        /// <param name="pdwCharacteristics">
        /// <p>
        /// Receives a bitwise OR of zero or more flags. The following flags are defined:
        /// </p>
        /// <ul>
        /// <li>
        /// MEDIASINK_FIXED_STREAMS (0x00000001): The media sink has a fixed number of streams. It 
        /// does not support the IMFMediaSink::AddStreamSink and IMFMediaSink::RemoveStreamSink 
        /// methods.This flag is a hint to the application.
        /// </li>
        /// <li>
        /// <p>
        /// MEDIASINK_CANNOT_MATCH_CLOCK (0x00000002):The media sink cannot match rates with an 
        /// external clock. For best results, this media sink should be used as the time source 
        /// for the presentation clock. If any other time source is used, the media sink cannot 
        /// match rates with the clock, with poor results(for example, glitching).
        /// </p>
        /// <p>
        /// This flag should be used sparingly, because it limits how the pipeline can be configured.
        /// </p>
        /// </li>
        /// <li>
        /// MEDIASINK_RATELESS (0x00000004): The media sink is rateless. It consumes samples as 
        /// quickly as possible, and does not synchronize itself to a presentation clock. Most 
        /// archiving sinks are rateless.
        /// </li>
        /// <li>
        /// <p>
        /// MEDIASINK_CLOCK_REQUIRED (0x00000008): The media sink requires a presentation clock. 
        /// The presentation clock is set by calling the media sink's IMFMediaSink::SetPresentationClock 
        /// method.
        /// </p>
        /// <p>
        /// This flag is obsolete, because all media sinks must support the SetPresentationClock method, 
        /// even if the media sink ignores the clock (as in a rateless media sink).
        /// </p>
        /// </li>
        /// <li>
        /// MEDIASINK_CAN_PREROLL (0x00000010): The media sink can accept preroll samples before the 
        /// presentation clock starts. The media sink exposes the IMFMediaSinkPreroll interface.
        /// </li>
        /// <li>
        /// MEDIASINK_REQUIRE_REFERENCE_MEDIATYPE (0x00000020): The first stream sink (index 0) is 
        /// a reference stream. The reference stream must have a media type before the media types 
        /// can be set on the other stream sinks.
        /// </li>
        /// </ul>
        /// </param>
        /// <returns>
        /// <p>
        /// The method returns an HRESULT. Possible values include, but are not limited to, the following:
        /// </p>
        /// <ul>
        /// <li>
        /// S_OK: The method succeeded.
        /// </li>
        /// <li>
        /// MF_E_SHUTDOWN: The media sink's Shutdown method has been called.
        /// </li>
        /// </ul>
        /// </returns>
        virtual HRESULT STDMETHODCALLTYPE GetCharacteristics(__RPC__out DWORD* pdwCharacteristics) override
        {
            try
            {
            }
            HCC_COM_CATCH_ALL_REPORT_EXCEPTION_AND_RETURN_HRESULT();
        }

        /// <summary>
        /// Adds a new stream sink to the media sink.
        /// </summary>
        /// <param name="dwStreamSinkIdentifier">
        /// Identifier for the new stream. The value is arbitrary but must be unique
        /// </param>
        /// <param name="pMediaType">
        /// Pointer to the IMFMediaType interface, specifying the media type for the stream. This parameter can be NULL.
        /// </param>
        /// <param name="ppStreamSink">
        /// Receives a pointer to the new stream sink's IMFStreamSink interface. The caller must release the interface.
        /// </param>
        /// <returns>
        /// <p>
        /// The method returns an HRESULT. Possible values include, but are not limited to, the following:
        /// </p>
        /// <ul>
        /// <li>
        /// S_OK: The method succeeded.
        /// </li>
        /// <li>
        /// MF_E_INVALIDSTREAMNUMBER: The specified stream identifier is not valid.
        /// </li>
        /// <li>
        /// MF_E_SHUTDOWN: The media sink's Shutdown method has been called.
        /// </li>
        /// <li>
        /// MF_E_STREAMSINK_EXISTS: There is already a stream sink with the same stream identifier.
        /// </li>
        /// <li>
        /// MF_E_STREAMSINKS_FIXED: This media sink has a fixed set of stream sinks.New stream sinks cannot be added.
        /// </li>
        /// </ul>
        /// </returns>
        /// <remarks>
        /// <p>
        /// Not all media sinks support this method. If the media sink does not support this method, the 
        /// IMFMediaSink::GetCharacteristics method returns the MEDIASINK_FIXED_STREAMS flag.
        /// </p>
        /// <p>
        /// If pMediaType is NULL, use the IMFMediaTypeHandler interface to set the media type. Call 
        /// IMFStreamSink::GetMediaTypeHandler to get a pointer to the interface.
        /// </p>
        /// </remakrs>
        virtual HRESULT STDMETHODCALLTYPE AddStreamSink(DWORD dwStreamSinkIdentifier, __RPC__in_opt IMFMediaType* pMediaType, __RPC__deref_out_opt IMFStreamSink** ppStreamSink) override
        {
            try
            {
            }
            HCC_COM_CATCH_ALL_REPORT_EXCEPTION_AND_RETURN_HRESULT();
        }

        /// <summary>
        /// Removes a stream sink from the media sink.
        /// </summary>
        /// <param name="dwStreamSinkIdentifier">
        /// Identifier of the stream to remove. The stream identifier is defined when 
        /// you call IMFMediaSink::AddStreamSink to add the stream sink.
        /// </param>
        /// <returns>
        /// <p>
        /// The method returns an HRESULT. Possible values include, but are not limited to, the following:
        /// </p>
        /// <ul>
        /// <li>
        /// S_OK: The method succeeded.
        /// </li>
        /// <li>
        /// E_INVALIDARG: This particular stream sink cannot be removed.
        /// </li>
        /// <li>
        /// MF_E_INVALIDSTREAMNUMBER: The stream number is not valid.
        /// </li>
        /// <li>
        /// MF_E_NOT_INITIALIZED: The media sink has not been initialized.
        /// </li>
        /// <li>
        /// MF_E_SHUTDOWN: The media sink's Shutdown method has been called.
        /// </li>
        /// <li>
        /// MF_E_STREAMSINKS_FIXED: This media sink has a fixed set of stream sinks.Stream sinks cannot be removed.
        /// </li>
        /// </ul>
        /// </returns>
        virtual HRESULT STDMETHODCALLTYPE RemoveStreamSink(DWORD dwStreamSinkIdentifier) override
        {
            try
            {
            }
            HCC_COM_CATCH_ALL_REPORT_EXCEPTION_AND_RETURN_HRESULT();
        }

        /// <summary>
        /// Gets the number of stream sinks on this media sink.
        /// </summary>
        /// <param name="pcStreamSinkCount">
        /// Receives the number of stream sinks.
        /// </param>
        /// <returns>
        /// <ul>
        /// <li>
        /// S_OK: The method succeeded.
        /// </li>
        /// <li>
        /// MF_E_SHUTDOWN: The media sink's Shutdown method has been called.
        /// </li>
        /// </ul>
        /// </returns>
        virtual HRESULT STDMETHODCALLTYPE GetStreamSinkCount(__RPC__out DWORD* pcStreamSinkCount) override
        {
            try
            {
            }
            HCC_COM_CATCH_ALL_REPORT_EXCEPTION_AND_RETURN_HRESULT();
        }

        /// <summary>
        /// Gets a stream sink, specified by index.
        /// </summary>
        /// <param name="dwIndex">
        /// Zero-based index of the stream. To get the number of streams, call IMFMediaSink::GetStreamSinkCount.
        /// </param>
        /// <param name="ppStreamSink">
        /// Receives a pointer to the stream's IMFStreamSink interface. The caller must release the interface.
        /// </param>
        /// <returns>
        /// <p>
        /// The method returns an HRESULT. Possible values include, but are not limited to, the following:
        /// </p>
        /// <ul>
        /// <li>
        /// S_OK: The method succeeded.
        /// </li>
        /// <li>
        /// MF_E_INVALIDINDEX: Invalid index.
        /// </li>
        /// <li>
        /// MF_E_SHUTDOWN: The media sink's Shutdown method has been called.
        /// </li>
        /// </ul>
        /// </returns>
        /// <remarks>
        /// Enumerating stream sinks is not a thread-safe operation, because stream sinks can be 
        /// added or removed between calls to this method.
        /// </remarks>
        virtual HRESULT STDMETHODCALLTYPE GetStreamSinkByIndex(DWORD dwIndex, __RPC__deref_out_opt IMFStreamSink** ppStreamSink) override
        {
            try
            {
            }
            HCC_COM_CATCH_ALL_REPORT_EXCEPTION_AND_RETURN_HRESULT();
        }

        /// <summary>
        /// Gets a stream sink, specified by stream identifier.
        /// </summary>
        /// <param name="dwStreamSinkIdentifier">
        /// Stream identifier of the stream sink.
        /// </param>
        /// <param name="ppStreamSink">
        /// Receives a pointer to the stream's IMFStreamSink interface. 
        /// The caller must release the interface.
        /// </param>
        /// <returns>
        /// <p>
        /// The method returns an HRESULT. Possible values include, but are not limited to, the following:
        /// </p>
        /// <ul>
        /// <li>
        /// S_OK: The method succeeded.
        /// </li>
        /// <li>
        /// MF_E_INVALIDSTREAMNUMBER: The stream identifier is not valid.
        /// </li>
        /// <li>
        /// MF_E_SHUTDOWN: The media sink's Shutdown method has been called.
        /// </li>
        /// </ul>
        /// </returns>
        /// <remarks>
        /// <p>
        /// If you add a stream sink by calling the IMFMediaSink::AddStreamSink method, the stream 
        /// identifier is specified in the dwStreamSinkIdentifier parameter of that method. If the 
        /// media sink has a fixed set of streams, the media sink assigns the stream identifiers.
        /// </p>
        /// <p>
        /// To enumerate the streams by index number instead of stream identifier, call 
        /// IMFMediaSink::GetStreamSinkByIndex.
        /// </p>
        /// </remarks>
        virtual HRESULT STDMETHODCALLTYPE GetStreamSinkById(DWORD dwStreamSinkIdentifier, __RPC__deref_out_opt IMFStreamSink** ppStreamSink) override
        {
            try
            {
            }
            HCC_COM_CATCH_ALL_REPORT_EXCEPTION_AND_RETURN_HRESULT();
        }

        /// <summary>
        /// Sets the presentation clock on the media sink.
        /// </summary>
        /// <param name="pPresentationClock">
        /// Pointer to the IMFPresentationClock interface of the presentation clock, or NULL. 
        /// If the value is NULL, the media sink stops listening to the presentation clock 
        /// that was previously set, if any.
        /// </param>
        /// <returns>
        /// <p>
        /// The method returns an HRESULT. Possible values include, but are not limited to, the following:
        /// </p>
        /// <ul>
        /// <li>
        /// S_OK: The method succeeded.
        /// </li>
        /// <li>
        /// MF_E_CLOCK_NO_TIME_SOURCE: The presentation clock does not have a time source.Call SetTimeSource on the presentation clock.
        /// </li>
        /// <li>
        /// MF_E_SHUTDOWN: The media sink's Shutdown method has been called.
        /// </li>
        /// </ul>
        /// </returns>
        /// <remarks>
        /// <p>
        /// During streaming, the media sink attempts to match rates with the presentation clock. 
        /// Ideally, the media sink presents samples at the correct time according to the presentation 
        /// clock and does not fall behind. Rateless media sinks are an exception to this rule, as 
        /// they consume samples as quickly as possible and ignore the clock. If the sink is rateless, 
        /// the IMFMediaSink::GetCharacteristics method returns the MEDIASINK_RATELESS flag.
        /// </p>
        /// <p>
        /// The presentation clock must have a time source. Before calling this method, call 
        /// IMFPresentationClock::SetTimeSource on the presentation clock to set the presentation 
        /// time source. Some media sinks provide time sources; therefore, the media sink might 
        /// be the time source for its own presentation clock. Regardless of what object provides 
        /// the time source, however, the media sink must attempt to match rates with the clock 
        /// specified in pPresentationClock. If a media sink cannot match rates with an external 
        /// time source, the media sink's IMFMediaSink::GetCharacteristics method retrieves the 
        /// MEDIASINK_CANNOT_MATCH_CLOCK flag. In this case, SetPresentationClock will still succeed, 
        /// but the results will not be optimal. The sink might not render samples quickly enough 
        /// to match rates with the presentation clock.
        /// </p>
        /// <p>
        /// If pPresentationClock is non-NULL, the media sink must register for clock state 
        /// notifications, by calling IMFPresentationClock::AddClockStateSink on the presentation 
        /// clock. If the method is called again with a new presentation clock, or if pPresentationClock 
        /// is NULL, the media sink must call IMFPresentationClock::RemoveClockStateSink to deregister 
        /// itself from the previous clock.
        /// </p>
        /// <p>
        /// All media sinks must support this method.
        /// </p>
        /// </remarks>
        virtual HRESULT STDMETHODCALLTYPE SetPresentationClock(__RPC__in_opt IMFPresentationClock* pPresentationClock) override
        {
            try
            {
            }
            HCC_COM_CATCH_ALL_REPORT_EXCEPTION_AND_RETURN_HRESULT();
        }

        /// <summary>
        /// Gets the presentation clock that was set on the media sink.
        /// </summary>
        /// <param name="ppPresentationClock">
        /// Receives a pointer to the presentation clock's IMFPresentationClock interface. 
        /// The caller must release the interface.
        /// </param>
        /// <returns>
        /// <p>
        /// The method returns an HRESULT. Possible values include, but are not limited to, the following:
        /// </p>
        /// <ul>
        /// <li>
        /// S_OK: The method succeeded.
        /// </li>
        /// <li>
        /// MF_E_NO_CLOCK: No clock has been set.To set the presentation clock, call IMFMediaSink::SetPresentationClock.
        /// </li>
        /// <li>
        /// MF_E_SHUTDOWN: The media sink's Shutdown method has been called.
        /// </li>
        /// </ul>
        /// </returns>
        virtual HRESULT STDMETHODCALLTYPE GetPresentationClock(__RPC__deref_out_opt IMFPresentationClock** ppPresentationClock) override
        {
            try
            {
            }
            HCC_COM_CATCH_ALL_REPORT_EXCEPTION_AND_RETURN_HRESULT();
        }

        /// <summary>
        /// Shuts down the media sink and releases the resources it is using.
        /// </summary>
        /// <returns>
        /// <p>
        /// The method returns an HRESULT. Possible values include, but are not limited to, the following:
        /// </p>
        /// <ul>
        /// <li>
        /// S_OK: The method succeeded.
        /// </li>
        /// <li>
        /// MF_E_SHUTDOWN: The media sink was shut down.
        /// </li>
        /// </ul>
        /// </returns>
        /// <remarks>
        /// <p>
        /// If the application creates the media sink, it is responsible for calling Shutdown to 
        /// avoid memory or resource leaks. In most applications, however, the application creates 
        /// an activation object for the media sink, and the Media Session uses that object to 
        /// create the media sink. In that case, the Media Session — not the application — shuts 
        /// down the media sink. (For more information, see Activation Objects.)
        /// </p>
        /// <p>
        /// After this method returns, all methods on the media sink return MF_E_SHUTDOWN, 
        /// except for IUnknown methods and IMFMediaEventGenerator methods. The sink will 
        /// not raise any events after this method is called.
        /// </p>
        /// </remarks>
        virtual HRESULT STDMETHODCALLTYPE Shutdown() override
        {
            try
            {
            }
            HCC_COM_CATCH_ALL_REPORT_EXCEPTION_AND_RETURN_HRESULT();
        }

        // IMFFinalizableMediaSink interface

        /// <summary>
        /// Notifies the media sink to asynchronously take any steps it needs to finish its tasks.
        /// </summary>
        /// <param name="pCallback">
        /// Pointer to the IMFAsyncCallback interface of an asynchronous object. 
        /// The caller must implement this interface.
        /// </param>
        /// <param name="punkState">
        /// Pointer to the IUnknown interface of a state object, defined by the caller. This 
        /// parameter can be NULL. You can use this object to hold state information. The object 
        /// is returned to the caller when the callback is invoked.
        /// </param>
        /// <returns>
        /// <p>
        /// The method returns an HRESULT. Possible values include, but are not limited to, the following:
        /// </p>
        /// <ul>
        /// <li>
        /// S_OK: The method succeeded.
        /// </li>
        /// </ul>
        /// </returns>
        /// <remarks>
        /// <p>
        /// Many archive media sinks have steps they need to do at the end of archiving to complete their 
        /// file operations, such as updating the header (for some formats) or flushing all pending writes 
        /// to disk. In some cases, this may include expensive operations such as indexing the content. 
        /// BeginFinalize is an asynchronous way to initiate final tasks.
        /// </p>
        /// <p>
        /// When the finalize operation is complete, the callback object's IMFAsyncCallback::Invoke method 
        /// is called. At that point, the application should call IMFFinalizableMediaSink::EndFinalize to 
        /// complete the asynchronous request.
        /// </p>
        /// </remarks>
        virtual HRESULT STDMETHODCALLTYPE BeginFinalize(IMFAsyncCallback* pCallback, IUnknown* punkState) override
        {
            try
            {
            }
            HCC_COM_CATCH_ALL_REPORT_EXCEPTION_AND_RETURN_HRESULT();
        }

        /// <summary>
        /// Completes an asynchronous finalize operation.
        /// </summary>
        /// <param name="pResult">
        /// Pointer to the IMFAsyncResult interface. Pass in the same pointer that your callback 
        /// object received in the IMFAsyncCallback::Invoke method.
        /// </param>
        /// <returns>
        /// <p>
        /// The method returns an HRESULT. Possible values include, but are not limited to, the following:
        /// </p>
        /// <ul>
        /// <li>
        /// S_OK: The method succeeded.
        /// </li>
        /// </ul>
        /// </returns>
        /// <remarks>
        /// Call this method after the IMFFinalizableMediaSink::BeginFinalize method completes asynchronously.
        /// </remarks>
        virtual HRESULT STDMETHODCALLTYPE EndFinalize(IMFAsyncResult* pResult) override
        {
            try
            {
            }
            HCC_COM_CATCH_ALL_REPORT_EXCEPTION_AND_RETURN_HRESULT();
        }


        // IMFClockStateSink interface:
        // Receives state-change notifications from the presentation clock.

        /// <summary>
        /// Called when the presentation clock starts.
        /// </summary>
        /// <param name="hnsSystemTime">
        /// The system time when the clock started, in 100-nanosecond units.
        /// </param>
        /// <param name="llClockStartOffset">
        /// The new starting time for the clock, in 100-nanosecond units. This 
        /// parameter can also equal PRESENTATION_CURRENT_POSITION, indicating 
        /// the clock has started or restarted from its current position.
        /// </param>
        /// <returns>
        /// If this method succeeds, it returns S_OK. Otherwise, it returns an HRESULT error code.
        /// </returns>
        /// <remarks>
        /// <p>
        /// This method is called when the presentation clock's IMFPresentationClock::Start method 
        /// is called, with the following exception: If the clock is paused and Start is called with 
        /// the value PRESENTATION_CURRENT_POSITION, IMFClockStateSink::OnClockRestart is called 
        /// instead of OnClockStart.
        /// </p>
        /// <p>
        /// The clock notifies the presentation time source by calling the time source's OnClockStart 
        /// method. This call occurs synchronously within the Start method. If the time source returns 
        /// an error from OnClockStart, the presentation clock's Start method returns an error and the 
        /// state change does not take place.
        /// </p>
        /// <p>
        /// For any object that is not the presentation time source, the OnClockStart method is called 
        /// asynchronously, after the state change is completed. In that case, the return value from 
        /// this method is ignored.
        /// </p>
        /// <p>
        /// The value given in llClockStartOffset is the presentation time when the clock starts, so 
        /// it is relative to the start of the presentation. Media sinks should not render any data 
        /// with a presentation time earlier than llClockStartOffSet. If a sample straddles the offset—that 
        /// is, if the offset falls between the sample's start and stop times—the sink should either 
        /// trim the sample so that only data after llClockStartOffset is rendered, or else simply drop the sample.
        /// </p>
        /// </remarks>
        virtual HRESULT STDMETHODCALLTYPE OnClockStart(MFTIME hnsSystemTime, LONGLONG llClockStartOffset) override
        {
            try
            {
            }
            HCC_COM_CATCH_ALL_REPORT_EXCEPTION_AND_RETURN_HRESULT();
        }

        /// <summary>
        /// Called when the presentation clock stops.
        /// </summary>
        /// <param name="hnsSystemTime">
        /// The system time when the clock stopped, in 100-nanosecond units.
        /// </param>
        /// <returns>
        /// <p>
        /// The method returns an HRESULT. Possible values include, but are not limited to, the following:
        /// </p>
        /// <ul>
        /// <li>
        /// S_OK: The method succeeded.
        /// </li>
        /// <li>
        /// MF_E_SINK_ALREADYSTOPPED: Deprecated.Do not use this error code.
        /// </li>
        /// </ul>
        /// </returns>
        /// <remarks>
        /// <p>
        /// When the presentation clock's IMFPresentationClock::Stop method is called, the 
        /// clock notifies the presentation time source by calling the presentation time 
        /// source's OnClockStop method. This call occurs synchronously within the Stop 
        /// method. If the time source returns an error from OnClockStop, the presentation 
        /// clock's Stop method returns an error and the state change does not take place.
        /// </p>
        /// <p>
        /// For any object that is not the presentation time source, the OnClockStop method is 
        /// called asynchronously, after the state change is completed.
        /// </p>
        /// <p>
        /// If an object is already stopped, it should return S_OK from OnClockStop. 
        /// It should not return an error code.
        /// </p>
        /// </remarks>
        virtual HRESULT STDMETHODCALLTYPE OnClockStop(MFTIME hnsSystemTime) override
        {
            try
            {
            }
            HCC_COM_CATCH_ALL_REPORT_EXCEPTION_AND_RETURN_HRESULT();
        }

        /// <summary>
        /// Called when the presentation clock pauses.
        /// </summary>
        /// <param name="hnsSystemTime">
        /// The system time when the clock was paused, in 100-nanosecond units.
        /// </param>
        /// <returns>
        /// If this method succeeds, it returns S_OK. Otherwise, it returns an HRESULT error code
        /// </returns>
        /// <remarks>
        /// <p>
        /// When the presentation clock's IMFPresentationClock::Pause method is called, the 
        /// clock notifies the presentation time source by calling the time source's 
        /// OnClockPause method. This call occurs synchronously within the Pause method. 
        /// If the time source returns an error from OnClockPause, the presentation clock's 
        /// Pause method returns an error and the state change does not take place.
        /// </p>
        /// <p>
        /// For any object that is not the presentation time source, the OnClockPause method 
        /// is called asynchronously, after the state change is completed. In that case, the 
        /// return value from this method is ignored.
        /// </p>
        /// </remarks>
        virtual HRESULT STDMETHODCALLTYPE OnClockPause(MFTIME hnsSystemTime) override
        {
            try
            {
            }
            HCC_COM_CATCH_ALL_REPORT_EXCEPTION_AND_RETURN_HRESULT();
        }

        /// <summary>
        /// Called when the presentation clock restarts from the same position while paused.
        /// </summary>
        /// <param name="hnsSystemTime">
        /// The system time when the clock restarted, in 100-nanosecond units.
        /// </param>
        /// <returns>
        /// If this method succeeds, it returns S_OK. Otherwise, it returns an HRESULT error code.
        /// </returns>
        /// <remarks>
        /// <p>
        /// This method is called if the presentation clock is paused and the IMFPresentationClock::Start 
        /// method is called with the value PRESENTATION_CURRENT_POSITION.
        /// </p>
        /// <p>
        /// The clock notifies the presentation time source by calling the time source's OnClockRestart 
        /// method. This call occurs synchronously within the Start method. If the time source returns 
        /// an error from OnClockRestart, the presentation clock's Start method returns an error and 
        /// the state change does not take place.
        /// </p>
        /// <p>
        /// For any object that is not the presentation time source, the OnClockRestart method is 
        /// called asynchronously, after the state change is completed. In that case, the return 
        /// value from this method is ignored.
        /// </p>
        /// </remarks>
        virtual HRESULT STDMETHODCALLTYPE OnClockRestart(MFTIME hnsSystemTime) override
        {
            try
            {
            }
            HCC_COM_CATCH_ALL_REPORT_EXCEPTION_AND_RETURN_HRESULT();
        }

        /// <summary>
        /// Called when the rate changes on the presentation clock.
        /// </summary>
        /// <param name="hnsSystemTime">
        ///  The system time when the rate was set, in 100-nanosecond units.
        /// </param>
        /// <param name="flRate">
        /// The new rate, as a multiplier of the normal playback rate.
        /// </param>
        /// <returns>
        /// If this method succeeds, it returns S_OK. Otherwise, it returns 
        /// an HRESULT error code.
        /// </returns>
        /// <remarks>
        /// <p>
        /// When the presentation clock's IMFRateControl::SetRate method is called, the 
        /// clock notifies the presentation time source by calling the time source's 
        /// OnClockSetRate method. This call occurs synchronously within the SetRate 
        /// method. If the time source returns an error from OnClockSetRate, the 
        /// presentation clock's SetRate method returns an error and the state change 
        /// does not take place.
        /// </p>
        /// <p>
        /// For any object that is not the presentation time source, the OnClockSetRate 
        /// method is called asynchronously, after the state change is completed. In 
        /// that case, the return value from this method is ignored.
        /// </p>
        /// </remarks>
        virtual HRESULT STDMETHODCALLTYPE OnClockSetRate(MFTIME hnsSystemTime, float flRate) override
        {
            try
            {
            }
            HCC_COM_CATCH_ALL_REPORT_EXCEPTION_AND_RETURN_HRESULT();
        }

        // IMFAsyncCallback

        /// <summary>
        /// Provides configuration information to the dispatching thread for a callback.
        /// </summary>
        /// <param name="pdwFlags">
        /// <p>
        /// Receives a flag indicating the behavior of the callback object's 
        /// IMFAsyncCallback::Invoke method. The following values are defined. 
        /// The default value is zero.
        /// </p>
        /// <ul>
        /// <li>
        /// Zero: The callback does not take a long time to complete, but has 
        /// no specific restrictions on what system calls it makes. The callback 
        /// generally takes less than 30 milliseconds to complete.
        /// </li>
        /// <li>
        /// <p>
        /// MFASYNC_FAST_IO_PROCESSING_CALLBACK: The callback does very minimal processing. 
        /// It takes less than 1 millisecond to complete.
        /// </p>
        /// <p>
        /// The callback must be invoked from one of the following work queues:
        /// </p>
        /// <ul>
        /// <li>
        /// MFASYNC_CALLBACK_QUEUE_IO
        /// </li>
        /// <li>
        /// MFASYNC_CALLBACK_QUEUE_TIMER
        /// </li>
        /// </ul>
        /// </li>
        /// <li>
        /// <p>
        /// MFASYNC_SIGNAL_CALLBACK: Implies MFASYNC_FAST_IO_PROCESSING_CALLBACK, with the 
        /// additional restriction that the callback does no processing (less than 50 
        /// microseconds), and the only system call it makes is SetEvent.
        /// </p>
        /// <p>
        /// The callback must be invoked from one of the following work queues:
        /// </p>
        /// <ul>
        /// <li>
        /// MFASYNC_CALLBACK_QUEUE_IO
        /// </li>
        /// <li>
        /// MFASYNC_CALLBACK_QUEUE_TIMER
        /// </li>
        /// </ul>
        /// </li>
        /// <li>
        /// MFASYNC_BLOCKING_CALLBACK: Blocking callback.
        /// </li>
        /// <li>
        /// MFASYNC_REPLY_CALLBACK: Reply callback.
        /// </li>
        /// </ul>
        /// </param>
        /// <param name="pdwQueue">
        /// <p>
        /// Receives the identifier of the work queue on which the callback is dispatched.
        /// </p>
        /// <p>
        /// This value can specify one of the standard Media Foundation work queues, or a 
        /// work queue created by the application. For list of standard Media Foundation 
        /// work queues, see Work Queue Identifiers. To create a new work queue, call 
        /// MFAllocateWorkQueue. The default value is MFASYNC_CALLBACK_QUEUE_STANDARD.
        /// </p>
        /// <p>
        /// If the work queue is not compatible with the value returned in pdwFlags, the 
        /// Media Foundation platform returns MF_E_INVALID_WORKQUEUE when it tries to 
        /// dispatch the callback. (See MFPutWorkItem.)
        /// </p>
        /// </param>
        /// <returns>
        /// <p>
        /// The method returns an HRESULT. Possible values include, but are not limited to, the following:
        /// </p>
        /// <ul>
        /// <li>
        /// S_OK: The method succeeded.
        /// </li>
        /// <li>
        /// E_NOTIMPL: Not implemented. Assume the default behavior.
        /// </li>
        /// </ul>
        /// </returns>
        /// <remarks>
        /// <p>
        /// The GetParameters method returns information about the callback so that the dispatching 
        /// thread can optimize the process that it uses to invoke the callback.
        /// </p>
        /// <p>
        /// If the method returns a value other than zero in the pdwFlags parameter, your Invoke 
        /// method must meet the requirements described here. Otherwise, the callback might delay the pipeline.
        /// </p>
        /// <p>
        /// If you want default values for both parameters, return E_NOTIMPL. The default values are 
        /// given in the parameter descriptions on this page.
        /// </p>
        /// </remarks>
        virtual HRESULT STDMETHODCALLTYPE GetParameters(__RPC__out DWORD* pdwFlags, __RPC__out DWORD* pdwQueue) override
        {
            try
            {
            }
            HCC_COM_CATCH_ALL_REPORT_EXCEPTION_AND_RETURN_HRESULT();
        }

        virtual HRESULT STDMETHODCALLTYPE Invoke(__RPC__in_opt IMFAsyncResult* pAsyncResult) override
        {
            try
            {
            }
            HCC_COM_CATCH_ALL_REPORT_EXCEPTION_AND_RETURN_HRESULT();
        }


    };

}

#endif
