#pragma once
#ifndef HARLINN_MEDIA_HWMGSTMESSAGE_H_
#define HARLINN_MEDIA_HWMGSTMESSAGE_H_
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

#include "HWMGstMiniObject.h"
#include "HWMGstStructure.h"
#include "HWMGstTagList.h"
#include <glib/gobject/HWMgvalue.h>

namespace Harlinn::Media::GStreamer
{
    namespace Internal
    {
        template<typename BaseT>
        class MessageImpl : public BaseT
        {
        public:
            using Base = BaseT;
            HWM_GSTMINIOBJECT_IMPLEMENT_STANDARD_MEMBERS( MessageImpl, GstMessage )

            GstMessageType MessageType( ) const
            {
                return GST_MESSAGE_TYPE( get( ) );
            }

            bool IsExtended( ) const
            {
                return GST_MESSAGE_TYPE_IS_EXTENDED( get( ) ) != 0;
            }

            const char* MessageTypeName( ) const
            {
                return GST_MESSAGE_TYPE_NAME( get() );
            }

            UInt64 Timestamp( ) const
            {
                return GST_MESSAGE_TIMESTAMP( get( ) );
            }

            BasicObject Source( ) const;

            UInt32 SequenceNumber( ) const
            {
                return GST_MESSAGE_SEQNUM( get( ) );
            }

            void SetSequenceNumber( UInt32 sequenceNumber ) const
            {
                gst_message_set_seqnum( get( ), sequenceNumber );
            }

            Message Copy( ) const
            {
                return Message( gst_message_copy( get( ) ) );
            }

            bool HasName( const char* name ) const
            {
                return gst_message_has_name( get( ), name ) != 0;
            }

            GStreamer::Structure Structure( ) const
            {
                return GStreamer::Structure( gst_message_get_structure( get( ) ) );
            }

            GStreamer::Structure WritableStructure( ) const
            {
                return GStreamer::Structure( gst_message_writable_structure( get( ) ) );
            }


            void ParseError( GError** gerror, char** debug ) const
            {
                gst_message_parse_error( get(), gerror, debug );
            }
            void ParseErrorDetails( const GstStructure** structure ) const
            {
                gst_message_parse_error_details( get(), structure );
            }

            void ParseWarning( GError** gerror, char** debug ) const
            {
                gst_message_parse_warning( get( ), gerror, debug );
            }
            void ParseWarningDetails( const GstStructure** structure ) const
            {
                gst_message_parse_warning_details( get( ), structure );
            }

            void ParseInfo( GError** gerror, char** debug ) const
            {
                gst_message_parse_info( get( ), gerror, debug );
            }
            void ParseInfoDetails( const GstStructure** structure ) const
            {
                gst_message_parse_info_details( get( ), structure );
            }

            void ParseTag( GstTagList** tagList ) const
            {
                gst_message_parse_tag( get(), tagList );
            }

            void ParseBuffering( Int32* percent ) const
            {
                gst_message_parse_buffering( get( ), percent );
            }

            void SetBufferingStats( GstMessage* message, GstBufferingMode mode, Int32 avgIn, Int32 avgOut, Int64 bufferingLeft ) const
            {
                gst_message_set_buffering_stats( get(), mode, avgIn, avgOut, bufferingLeft );
            }

            void ParseBufferingStats( GstBufferingMode* mode, Int32* avgIn, Int32* avgOut, Int64* bufferingLeft ) const
            {
                gst_message_parse_buffering_stats( get( ), mode, avgIn, avgOut, bufferingLeft );
            }

            void ParseStateChanged( GstState* oldstate, GstState* newstate, GstState* pending ) const
            {
                gst_message_parse_state_changed( get(), oldstate, newstate, pending );
            }

            void ParseStepDone( GstMessage* message, GstFormat* format, Int64* amount, double* rate, bool* flush, bool* intermediate, Int64* duration, bool* eos ) const
            {
                gst_message_parse_step_done( get(), format, amount, rate, flush, intermediate, duration, eos );
            }

            void ParseClockProvide( GstClock** clock, bool* ready ) const
            {
                gst_message_parse_clock_provide( get(), clock, ready );
            }

            void ParseClockLost( GstClock** clock ) const
            {
                gst_message_parse_clock_lost( get(), clock );
            }

            void ParseNewClock( GstClock** clock ) const
            {
                gst_message_parse_new_clock( get( ), clock );
            }

            void ParseSegmentStart( GstFormat* format, Int64* position ) const
            {
                gst_message_parse_segment_start( get(), format, position );
            }

            void parse_segment_done( GstFormat* format, Int64* position ) const
            {
                gst_message_parse_segment_done( get(), format, position );
            }

            void ParseAsyncDone( GstClockTime* runningTime ) const
            {
                gst_message_parse_async_done( get(), runningTime );
            }

            void ParseStructureChange( GstStructureChangeType* type, GstElement** owner, bool* busy ) const
            {
                gst_message_parse_structure_change( get(), type, owner, busy );
            }

            void ParseStreamStatus( GstStreamStatusType* type, GstElement** owner ) const
            {
                gst_message_parse_stream_status( get( ), type, owner );
            }

            void SetStreamStatusObject( const GValue* object ) const
            {
                gst_message_set_stream_status_object( get(), object );
            }

            void SetStreamStatusObject( GLib::Value& object ) const
            {
                gst_message_set_stream_status_object( get( ), object );
            }

            const GLib::Value* StreamStatusObject( ) const
            {
                return reinterpret_cast< const GLib::Value* >( gst_message_get_stream_status_object( get( ) ) );
            }

            void ParseRequestState( GstState* state ) const
            {
                gst_message_parse_request_state( get( ), state );
            }

            void ParseStepStart( bool* active, GstFormat* format, UInt64* amount, double* rate, bool* flush, bool* intermediate ) const
            {
                gst_message_parse_step_start( get( ), active, format, amount, rate, flush, intermediate );
            }

            void SetQosValues( Int64 jitter, double proportion, Int32 quality ) const
            {
                gst_message_set_qos_values( get( ), jitter, proportion, quality );
            }
            void SetQosStats( GstFormat format, UInt64 processed, UInt64 dropped ) const
            {
                gst_message_set_qos_stats( get( ), format, processed, dropped );
            }
            void ParseQos( bool* live, UInt64* runningTime, UInt64* streamTime, UInt64* timestamp, UInt64* duration ) const
            {
                gst_message_parse_qos( get( ), live, runningTime, streamTime, timestamp, duration );
            }
            void ParseQosValues( Int64* jitter, double* proportion, Int32* quality ) const
            {
                gst_message_parse_qos_values( get( ), jitter, proportion, quality );
            }
            void ParseQosStats( GstFormat* format, UInt64* processed, UInt64* dropped ) const
            {
                gst_message_parse_qos_stats( get( ), format, processed, dropped );
            }

            void ParseProgress( GstProgressType* type, char** code, char** text ) const
            {
                gst_message_parse_progress( get( ), type, code, text );
            }

            void ParseToc( GstToc** toc, bool* updated ) const
            {
                gst_message_parse_toc( get( ), toc, updated );
            }

            void ParseResetTime( GstClockTime* runningTime ) const
            {
                gst_message_parse_reset_time( get( ), runningTime );
            }

            void SetGroupId( UInt32 groupId ) const
            {
                gst_message_set_group_id( get( ), groupId );
            }

            bool ParseGroupId( UInt32* groupId ) const
            {
                return gst_message_parse_group_id( get(), groupId ) != 0;
            }

            bool gst_message_parse_context_type( const char** contextType ) const
            {
                return gst_message_parse_context_type( get(), contextType ) != 0;
            }

            void ParseHaveContext( GstContext** context ) const
            {
                void gst_message_parse_have_context( get(), context );
            }

            void ParseDeviceAdded( GstDevice** device ) const
            {
                gst_message_parse_device_added( get( ), device );
            }

            void ParseDeviceRemoved( GstDevice** device ) const
            {
                gst_message_parse_device_removed( get( ), device );
            }

            void ParseDeviceChanged( GstDevice** device, GstDevice** changedDevice ) const
            {
                gst_message_parse_device_changed( get( ), device, changedDevice );
            }

            void ParsePropertyNotify( GstObject** object, const char** propertyName, const GValue** propertyValue ) const
            {
                gst_message_parse_property_notify( get(), object, propertyName, propertyValue );
            }

            void ParseStreamCollection( GstStreamCollection** collection ) const
            {
                gst_message_parse_stream_collection( get(), collection );
            }

            void StreamsSelectedAdd( GstStream* stream ) const
            {
                gst_message_streams_selected_add( get( ), stream );
            }

            void StreamsSelected( GstStreamCollection** collection ) const
            {
                gst_message_parse_streams_selected( get(), collection );
            }


            UInt32 StreamsSelectedSize( ) const
            {
                return gst_message_streams_selected_get_size( get( ) );
            }

            GstStream* StreamsSelectedStream( UInt32 idx ) const
            {
                return gst_message_streams_selected_get_stream( get(), idx );
            }

            void AddRedirectEntry( const char* location, GstTagList* tagList, const GstStructure* entryStruct ) const
            {
                gst_message_add_redirect_entry( get( ), location, tagList, entryStruct );
            }

            void ParseRedirectEntry( size_t entryIndex, const char** location, GstTagList** tagList, const GstStructure** entryStruct ) const
            {
                gst_message_parse_redirect_entry( get( ), entryIndex, location, tagList, entryStruct );
            }

            size_t NumberOfRedirectEntries( ) const
            {
                return gst_message_get_num_redirect_entries( get( ) );
            }

            void ParseInstantRateRequest( GstMessage* message, double* rateMultiplier ) const
            {
                gst_message_parse_instant_rate_request( get( ), rateMultiplier );
            }


        };
    }

    using BasicMessage = Internal::MessageImpl<BasicMiniObject>;
    using Message = Internal::MessageImpl<MiniObject>;

    namespace Messages
    {

        inline Message Custom( GstMessageType type, GstObject* src, GstStructure* structure )
        {
            return Message( gst_message_new_custom( type, src, structure ) );
        }
        inline BasicMessage BasicCustom( GstMessageType type, GstObject* src, GstStructure* structure )
        {
            return BasicMessage( gst_message_new_custom( type, src, structure ) );
        }


        inline Message Eos( GstObject* src )
        {
            return Message( gst_message_new_eos( src ) );
        }
        inline BasicMessage BasicEos( GstObject* src )
        {
            return BasicMessage( gst_message_new_eos( src ) );
        }

        inline Message Error( GstObject* src, GError* error, const char* debug )
        {
            return Message( gst_message_new_error( src, error, debug ) );
        }
        inline BasicMessage BasicError( GstObject* src, GError* error, const char* debug )
        {
            return BasicMessage( gst_message_new_error( src, error, debug ) );
        }

        inline Message Error( GstObject* src, GError* error, const char* debug, GstStructure* details )
        {
            return Message( gst_message_new_error_with_details( src, error, debug, details ) );
        }
        inline BasicMessage BasicError( GstObject* src, GError* error, const char* debug, GstStructure* details )
        {
            return BasicMessage( gst_message_new_error_with_details( src, error, debug, details ) );
        }

        inline Message Warning( GstObject* src, GError* error, const char* debug )
        {
            return Message( gst_message_new_warning( src, error, debug ) );
        }
        inline BasicMessage BasicWarning( GstObject* src, GError* error, const char* debug )
        {
            return BasicMessage( gst_message_new_warning( src, error, debug ) );
        }

        inline Message Warning( GstObject* src, GError* error, const char* debug, GstStructure* details )
        {
            return Message( gst_message_new_warning_with_details( src, error, debug, details ) );
        }
        inline BasicMessage BasicWarning( GstObject* src, GError* error, const char* debug, GstStructure* details )
        {
            return BasicMessage( gst_message_new_warning_with_details( src, error, debug, details ) );
        }


        inline Message Info( GstObject* src, GError* error, const char* debug )
        {
            return Message( gst_message_new_info( src, error, debug ) );
        }
        inline BasicMessage BasicInfo( GstObject* src, GError* error, const char* debug )
        {
            return BasicMessage( gst_message_new_info( src, error, debug ) );
        }

        inline Message Info( GstObject* src, GError* error, const char* debug, GstStructure* details )
        {
            return Message( gst_message_new_info_with_details( src, error, debug, details ) );
        }
        inline BasicMessage BasicInfo( GstObject* src, GError* error, const char* debug, GstStructure* details )
        {
            return BasicMessage( gst_message_new_info_with_details( src, error, debug, details ) );
        }

        inline Message Tag( GstObject* src, GstTagList* tagList )
        {
            return Message( gst_message_new_tag( src, tagList ) );
        }
        inline BasicMessage BasicTag( GstObject* src, GstTagList* tagList )
        {
            return BasicMessage( gst_message_new_tag( src, tagList ) );
        }

        inline Message Buffering( GstObject* src, Int32 percent )
        {
            return Message( gst_message_new_buffering( src, percent ) );
        }
        inline BasicMessage BasicBuffering( GstObject* src, Int32 percent )
        {
            return BasicMessage( gst_message_new_buffering( src, percent ) );
        }

        inline Message StateChanged( GstObject* src, GstState oldstate, GstState newstate, GstState pending )
        {
            return Message( gst_message_new_state_changed( src, oldstate, newstate, pending ) );
        }
        inline BasicMessage BasicStateChanged( GstObject* src, GstState oldstate, GstState newstate, GstState pending )
        {
            return BasicMessage( gst_message_new_state_changed( src, oldstate, newstate, pending ) );
        }

        inline Message StateDirty( GstObject* src )
        {
            return Message( gst_message_new_state_dirty( src ) );
        }
        inline BasicMessage BasicStateDirty( GstObject* src )
        {
            return BasicMessage( gst_message_new_state_dirty( src ) );
        }

        inline Message StepDone( GstObject* src, GstFormat format, UInt64 amount, double rate, bool flush, bool intermediate, UInt64 duration, bool eos )
        {
            return Message( gst_message_new_step_done( src, format, amount, rate, flush, intermediate, duration, eos ) );
        }
        inline BasicMessage BasicStepDone( GstObject* src, GstFormat format, UInt64 amount, double rate, bool flush, bool intermediate, UInt64 duration, bool eos )
        {
            return BasicMessage( gst_message_new_step_done( src, format, amount, rate, flush, intermediate, duration, eos ) );
        }

        inline Message ClockProvide( GstObject* src, GstClock* clock, bool ready )
        {
            return Message( gst_message_new_clock_provide( src, clock, ready ) );
        }
        inline BasicMessage BasicClockProvide( GstObject* src, GstClock* clock, bool ready )
        {
            return BasicMessage( gst_message_new_clock_provide( src, clock, ready ) );
        }

        inline Message ClockLost( GstObject* src, GstClock* clock )
        {
            return Message( gst_message_new_clock_lost( src, clock ) );
        }
        inline BasicMessage BasicClockLost( GstObject* src, GstClock* clock )
        {
            return BasicMessage( gst_message_new_clock_lost( src, clock ) );
        }

        inline Message NewClock( GstObject* src, GstClock* clock )
        {
            return Message( gst_message_new_new_clock( src, clock ) );
        }
        inline BasicMessage BasicNewClock( GstObject* src, GstClock* clock )
        {
            return BasicMessage( gst_message_new_new_clock( src, clock ) );
        }

        inline Message Application( GstObject* src, GstStructure* structure )
        {
            return Message( gst_message_new_application( src, structure ) );
        }
        inline BasicMessage BasicApplication( GstObject* src, GstStructure* structure )
        {
            return BasicMessage( gst_message_new_application( src, structure ) );
        }

        inline Message Element( GstObject* src, GstStructure* structure )
        {
            return Message( gst_message_new_element( src, structure ) );
        }
        inline BasicMessage BasicElement( GstObject* src, GstStructure* structure )
        {
            return BasicMessage( gst_message_new_element( src, structure ) );
        }

        inline Message SegmentStart( GstObject* src, GstFormat format, Int64 position )
        {
            return Message( gst_message_new_segment_start( src, format, position ) );
        }
        inline BasicMessage BasicSegmentStart( GstObject* src, GstFormat format, Int64 position )
        {
            return BasicMessage( gst_message_new_segment_start( src, format, position ) );
        }

        inline Message SegmentDone( GstObject* src, GstFormat format, Int64 position )
        {
            return Message( gst_message_new_segment_done( src, format, position ) );
        }
        inline BasicMessage BasicSegmentDone( GstObject* src, GstFormat format, Int64 position )
        {
            return BasicMessage( gst_message_new_segment_done( src, format, position ) );
        }

        inline Message DurationChanged( GstObject* src )
        {
            return Message( gst_message_new_duration_changed( src ) );
        }
        inline BasicMessage BasicDurationChanged( GstObject* src )
        {
            return BasicMessage( gst_message_new_duration_changed( src ) );
        }

        inline Message Latency( GstObject* src )
        {
            return Message( gst_message_new_latency( src ) );
        }
        inline BasicMessage BasicLatency( GstObject* src )
        {
            return BasicMessage( gst_message_new_latency( src ) );
        }

        inline Message AsyncStart( GstObject* src )
        {
            return Message( gst_message_new_async_start( src ) );
        }
        inline BasicMessage BasicAsyncStart( GstObject* src )
        {
            return BasicMessage( gst_message_new_async_start( src ) );
        }

        inline Message AsyncDone( GstObject* src, GstClockTime runningTime )
        {
            return Message( gst_message_new_async_done( src, runningTime ) );
        }
        inline BasicMessage BasicAsyncDone( GstObject* src, GstClockTime runningTime )
        {
            return BasicMessage( gst_message_new_async_done( src, runningTime ) );
        }

        inline Message StructureChange( GstObject* src, GstStructureChangeType type, GstElement* owner, bool busy )
        {
            return Message( gst_message_new_structure_change( src, type, owner, busy ) );
        }
        inline BasicMessage BasicStructureChange( GstObject* src, GstStructureChangeType type, GstElement* owner, bool busy )
        {
            return BasicMessage( gst_message_new_structure_change( src, type, owner, busy ) );
        }

        inline Message StreamStatus( GstObject* src, GstStreamStatusType type, GstElement* owner )
        {
            return Message( gst_message_new_stream_status( src, type, owner ) );
        }
        inline BasicMessage BasicStreamStatus( GstObject* src, GstStreamStatusType type, GstElement* owner )
        {
            return BasicMessage( gst_message_new_stream_status( src, type, owner ) );
        }

        inline Message RequestState( GstObject* src, GstState state )
        {
            return Message( gst_message_new_request_state( src, state ) );
        }
        inline BasicMessage BasicRequestState( GstObject* src, GstState state )
        {
            return BasicMessage( gst_message_new_request_state( src, state ) );
        }

        inline Message StepStart( GstObject* src, bool active, GstFormat format, Int64 amount, double rate, bool flush, bool intermediate )
        {
            return Message( gst_message_new_step_start( src, active, format, amount, rate, flush, intermediate ) );
        }
        inline BasicMessage BasicStepStart( GstObject* src, bool active, GstFormat format, Int64 amount, double rate, bool flush, bool intermediate )
        {
            return BasicMessage( gst_message_new_step_start( src, active, format, amount, rate, flush, intermediate ) );
        }

        inline Message Qos( GstObject* src, bool live, UInt64 runningTime, UInt64 streamTime, UInt64 timestamp, UInt64 duration )
        {
            return Message( gst_message_new_qos( src, live, runningTime, streamTime, timestamp, duration ) );
        }
        inline BasicMessage BasicQos( GstObject* src, bool live, UInt64 runningTime, UInt64 streamTime, UInt64 timestamp, UInt64 duration )
        {
            return BasicMessage( gst_message_new_qos( src, live, runningTime, streamTime, timestamp, duration ) );
        }

        inline Message Progress( GstObject* src, GstProgressType type, const char* code, const char* text )
        {
            return Message( gst_message_new_progress( src, type, code, text ) );
        }
        inline BasicMessage BasicProgress( GstObject* src, GstProgressType type, const char* code, const char* text )
        {
            return BasicMessage( gst_message_new_progress( src, type, code, text ) );
        }

        inline Message Toc( GstObject* src, GstToc* toc, bool updated )
        {
            return Message( gst_message_new_toc( src, toc, updated ) );
        }
        inline BasicMessage BasicToc( GstObject* src, GstToc* toc, bool updated )
        {
            return BasicMessage( gst_message_new_toc( src, toc, updated ) );
        }

        inline Message ResetTime( GstObject* src, GstClockTime runningTime )
        {
            return Message( gst_message_new_reset_time( src, runningTime ) );
        }
        inline BasicMessage BasicResetTime( GstObject* src, GstClockTime runningTime )
        {
            return BasicMessage( gst_message_new_reset_time( src, runningTime ) );
        }

        inline Message StreamStart( GstObject* src )
        {
            return Message( gst_message_new_stream_start( src ) );
        }
        inline BasicMessage BasicStreamStart( GstObject* src )
        {
            return BasicMessage( gst_message_new_stream_start( src ) );
        }

        inline Message NeedContext( GstObject* src, const char* contextType )
        {
            return Message( gst_message_new_need_context( src, contextType )  );
        }
        inline BasicMessage BasicNeedContext( GstObject* src, const char* contextType )
        {
            return BasicMessage( gst_message_new_need_context( src, contextType ) );
        }

        inline Message HaveContext( GstObject* src, GstContext* context )
        {
            return Message( gst_message_new_have_context( src, context ) );
        }
        inline BasicMessage BasicHaveContext( GstObject* src, GstContext* context )
        {
            return BasicMessage( gst_message_new_have_context( src, context ) );
        }

        inline Message DeviceAdded( GstObject* src, GstDevice* device )
        {
            return Message( gst_message_new_device_added( src, device ) );
        }
        inline BasicMessage BasicDeviceAdded( GstObject* src, GstDevice* device )
        {
            return BasicMessage( gst_message_new_device_added( src, device ) );
        }

        inline Message DeviceRemoved( GstObject* src, GstDevice* device )
        {
            return Message( gst_message_new_device_removed( src, device ) );
        }
        inline BasicMessage BasicDeviceRemoved( GstObject* src, GstDevice* device )
        {
            return BasicMessage( gst_message_new_device_removed( src, device ) );
        }

        inline Message DeviceChanged( GstObject* src, GstDevice* device, GstDevice* changedDevice )
        {
            return Message( gst_message_new_device_changed( src, device, changedDevice ) );
        }
        inline BasicMessage BasicDeviceChanged( GstObject* src, GstDevice* device, GstDevice* changedDevice )
        {
            return BasicMessage( gst_message_new_device_changed( src, device, changedDevice ) );
        }

        inline Message PropertyNotify( GstObject* src, const char* propertyName, GValue* propertyValue )
        {
            return Message( gst_message_new_property_notify( src, propertyName, propertyValue ) );
        }
        inline BasicMessage BasicPropertyNotify( GstObject* src, const char* propertyName, GValue* propertyValue )
        {
            return BasicMessage( gst_message_new_property_notify( src, propertyName, propertyValue ) );
        }

        inline Message StreamCollection( GstObject* src, GstStreamCollection* collection )
        {
            return Message( gst_message_new_stream_collection( src, collection ) );
        }
        inline BasicMessage BasicStreamCollection( GstObject* src, GstStreamCollection* collection )
        {
            return BasicMessage( gst_message_new_stream_collection( src, collection ) );
        }

        inline Message StreamsSelected( GstObject* src, GstStreamCollection* collection )
        {
            return Message( gst_message_new_streams_selected( src, collection ) );
        }
        inline BasicMessage BasicStreamsSelected( GstObject* src, GstStreamCollection* collection )
        {
            return BasicMessage( gst_message_new_streams_selected( src, collection ) );
        }

        inline Message Redirect( GstObject* src, const char* location, GstTagList* tagList, const GstStructure* entryStruct )
        {
            return Message( gst_message_new_redirect( src, location, tagList, entryStruct ) );
        }
        inline BasicMessage BasicRedirect( GstObject* src, const char* location, GstTagList* tagList, const GstStructure* entryStruct )
        {
            return BasicMessage( gst_message_new_redirect( src, location, tagList, entryStruct ) );
        }

        inline Message InstantRateRequest( GstObject* src, double rateMultiplier )
        {
            return Message( gst_message_new_instant_rate_request( src, rateMultiplier ) );
        }
        inline BasicMessage BasicInstantRateRequest( GstObject* src, double rateMultiplier )
        {
            return BasicMessage( gst_message_new_instant_rate_request( src, rateMultiplier ) );
        }



    }



}

#endif
