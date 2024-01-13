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

            Message Copy( ) const
            {
                return Message( gst_message_copy( get( ) ) );
            }

            bool HasName( const char* name ) const
            {
                return gst_message_has_name( get( ), name ) != 0;
            }
        };
    }

    using BasicMessage = Internal::MessageImpl<BasicMiniObject>;
    using Message = Internal::MessageImpl<MiniObject>;

    namespace Messages
    {
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
    }



}

#endif
