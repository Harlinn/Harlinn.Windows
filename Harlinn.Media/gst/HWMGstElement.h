#pragma once
#ifndef HARLINN_MEDIA_GST_HWMGSTELEMENT_H_
#define HARLINN_MEDIA_GST_HWMGSTELEMENT_H_

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


#include "HWMGstConstants.h"
#include "HWMGstObject.h"
#include "HWMGstBus.h"
#include "HWMGstPad.h"
#include "HWMGstPadTemplate.h"
#include "HWMGstClock.h"
#include "HWMGstContext.h"
#include "HWMGstIterator.h"
#include "HWMGstQuery.h"
#include "HWMGstMessage.h"
#include <glib/HWMglist.h>

namespace Harlinn::Media::GStreamer
{

    inline GstState StateGetNext( GstState currentState, GstState pendingState )
    {
        return GST_STATE_GET_NEXT( currentState, pendingState );
    }

    inline GstStateChange StateTransition( GstState currentState, GstState nextState )
    {
        return GST_STATE_TRANSITION( currentState, nextState );
    }

    inline GstState StateTransitionCurrent( GstStateChange stateChange )
    {
        return GST_STATE_TRANSITION_CURRENT( stateChange );
    }

    inline GstState StateTransitionNext( GstStateChange stateChange )
    {
        return GST_STATE_TRANSITION_NEXT( stateChange );
    }



    namespace Internal
    {
        template<typename BaseT>
        class ElementImpl : public BaseT
        {
        public:
            using Base = BaseT;
            HWM_GOBJECT_IMPLEMENT_STANDARD_MEMBERS( ElementImpl, GstElement )

            GLib::RecMutex& StateLock( ) const
            {
                return reinterpret_cast< GLib::RecMutex& >( get( )->state_lock );
            }
            GLib::Cond& StateCond( ) const
            {
                return reinterpret_cast< GLib::Cond& >( get( )->state_cond );
            }

            GstState State( ) const
            {
                return get( )->current_state;
            }

            GstState StateNext( ) const
            {
                return get( )->next_state;
            }

            GstState StatePending( ) const
            {
                return get( )->pending_state;
            }

            GstState StateTarget( ) const
            {
                return get( )->target_state;
            }
            
            GstStateChangeReturn LastReturn( ) const
            {
                return get( )->last_return;
            }



            BasicBus Bus( GLib::ReferenceType referenceType = GLib::ReferenceType::None ) const
            {
                auto bus = get( )->bus;
                if ( bus )
                {
                    return BasicBus( bus, referenceType );
                }
                return {};
            }

            BasicClock Clock( GLib::ReferenceType referenceType = GLib::ReferenceType::None ) const
            {
                auto clock = get( )->clock;
                if ( clock )
                {
                    return BasicClock( clock, referenceType );
                }
                return {};
            }

            GstClockTimeDiff BaseTime( ) const
            {
                return get( )->base_time;
            }

            GstClockTime StartTimeNotLocked( ) const
            {
                return get( )->start_time;
            }

            GStreamer::Clock ProvideClock( ) const
            {
                auto clock = gst_element_provide_clock( get( ) );
                if ( clock )
                {
                    return GStreamer::Clock( clock );
                }
                return {};
            }

            GStreamer::Clock Clock( ) const
            {
                auto clock = gst_element_get_clock( get( ) );
                if ( clock )
                {
                    return GStreamer::Clock( clock );
                }
                return {};
            }

            bool SetClock( GstClock* clock ) const
            {
                return gst_element_set_clock( get( ), clock );
            }
            template<typename T>
                requires IsClock<T>
            bool SetClock( const T& clock ) const
            {
                return SetClock( clock.get( ) );
            }


            void SetBaseTime( GstClockTime time ) const
            {
                gst_element_set_base_time( get(), time );
            }
            

            GstClockTime BaseTime( ) const
            {
                return gst_element_get_base_time( get( ) );
            }

            void SetStartTime( GstClockTime time ) const
            {
                gst_element_set_start_time( get(), time );
            }

            GstClockTime StartTime( ) const
            {
                return gst_element_get_start_time( get( ) );
            }

            GstClockTime CurrentRunningTime( ) const
            {
                return gst_element_get_current_running_time( get() );
            }

            GstClockTime CurrentClockTime( ) const
            {
                return gst_element_get_current_clock_time( get( ) );
            }

            void SetBus( GstBus* bus ) const
            {
                gst_element_set_bus( get(), bus );
            }
            template<typename T>
                requires IsBus<T>
            void SetBus( const T& bus ) const
            {
                gst_element_set_bus( get( ), bus.get() );
            }

            GStreamer::Bus Bus( ) const
            {
                auto bus = gst_element_get_bus( get( ) );
                if ( bus )
                {
                    return GStreamer::Bus( bus );
                }
                return {};
            }

            void SetContext( GstContext* context ) const
            {
                gst_element_set_context( get( ), context );
            }

            template<typename T>
                requires IsContext<T>
            void SetContext( const T& context ) const
            {
                gst_element_set_context( get( ), context.get() );
            }


            GLib::List<GstContext> Contexts( ) const
            {
                auto list = gst_element_get_contexts( get() );
                if ( list )
                {
                    return GLib::List<GstContext>( list );
                }
                return {};
            }

            GStreamer::Context Context( const gchar* contextType ) const
            {
                auto context = gst_element_get_context( get( ), contextType );
                if ( context )
                {
                    return GStreamer::Context( context );
                }
                return {};
            }

            GStreamer::Context UnlockedContext( const gchar* contextType ) const
            {
                auto context = gst_element_get_context_unlocked( get( ), contextType );
                if ( context )
                {
                    return GStreamer::Context( context );
                }
                return {};
            }


            bool AddPad( GstPad* pad ) const
            {
                return gst_element_add_pad( get( ), pad ) != 0;
            }

            template<typename T>
                requires IsPad<T>
            bool AddPad( const T& pad ) const
            {
                return gst_element_add_pad( get( ), pad.get() ) != 0;
            }
            template<typename T>
                requires IsPad<T>
            bool AddPad( T&& pad ) const
            {
                auto result = gst_element_add_pad( get( ), pad.get( ) ) != 0;
                if ( result )
                {
                    (void)pad.Detach( );
                }
                return result;
            }

            bool RemovePad( GstPad* pad ) const
            {
                return gst_element_remove_pad( get( ), pad ) != 0;
            }
            template<typename T>
                requires IsPad<T>
            bool RemovePad( const T& pad ) const
            {
                return gst_element_remove_pad( get( ), pad.get() ) != 0;
            }

            void NoMorePads( ) const
            {
                gst_element_no_more_pads( get( ) );
            }

            GStreamer::Pad StaticPad( const char* name ) const
            {
                auto pad = gst_element_get_static_pad( get( ), name );
                if ( pad )
                {
                    return GStreamer::Pad( pad );
                }
                return {};
            }

            Pad RequestPad( const char* name ) const
            {
                auto pad = gst_element_request_pad_simple( get( ), name );
                if ( pad )
                {
                    return Pad( pad );
                }
                return {};
            }

            Pad RequestPad( GstPadTemplate* templ, const char* name = nullptr, const GstCaps* caps = nullptr ) const
            {
                auto pad = gst_element_request_pad( get( ), templ, name, caps );
                if ( pad )
                {
                    return Pad( pad );
                }
                return {};
            }

            template<typename PadTemplateT>
                requires IsPadTemplate<PadTemplateT>
            Pad RequestPad( const PadTemplateT& templ, const char* name = nullptr, const GstCaps* caps = nullptr ) const
            {
                auto pad = gst_element_request_pad( get( ), templ.get(), name, caps );
                if ( pad )
                {
                    return Pad( pad );
                }
                return {};
            }

            void ReleaseRequestPad( GstPad* pad ) const
            {
                gst_element_release_request_pad( get( ), pad );
            }
            template<typename T>
                requires IsPad<T>
            void ReleaseRequestPad( T&& pad ) const
            {
                gst_element_release_request_pad( get( ), pad.Detach() );
            }

            Iterator IteratePads( ) const
            {
                auto iterator = gst_element_iterate_pads( get() );
                return Iterator( iterator );
            }

            Iterator IterateSourcePads( ) const
            {
                auto iterator = gst_element_iterate_src_pads( get( ) );
                return Iterator( iterator );
            }

            Iterator IterateSinkPads( ) const
            {
                auto iterator = gst_element_iterate_sink_pads( get( ) );
                return Iterator( iterator );
            }

            bool ForEachSinkPad( GstElementForeachPadFunc func, gpointer userData ) const
            {
                return gst_element_foreach_sink_pad( get(), func, userData ) != 0;
            }

            bool ForEachSourcePad( GstElementForeachPadFunc func, gpointer userData ) const
            {
                return gst_element_foreach_src_pad( get( ), func, userData ) != 0;
            }

            bool ForEachPad( GstElementForeachPadFunc func, gpointer userData ) const
            {
                return gst_element_foreach_pad( get( ), func, userData ) != 0;
            }

            bool SendEvent( GstEvent* event ) const
            {
                return gst_element_send_event( get(), event ) != 0;
            }

            template<typename T>
                requires IsEvent<T>
            bool SendEvent( T&& event ) const
            {
                return gst_element_send_event( get( ), event.Detach() ) != 0;
            }

            bool Seek( double rate, GstFormat format, GstSeekFlags flags, GstSeekType startType, Int64 start, GstSeekType stopType, Int64 stop ) const
            {
                return gst_element_seek( get( ), rate, format, flags, startType, start, stopType, stop ) != 0;
            }

            bool Query( GstQuery* query ) const
            {
                return gst_element_query( get(), query ) != 0;
            }

            template<typename T>
                requires IsQuery<T>
            bool Query( const T& query ) const
            {
                return gst_element_query( get( ), query.get() ) != 0;
            }


            bool PostMesssage( GstMessage* message ) const
            {
                gst_element_post_message( get(), message );
            }

            template<typename T>
                requires IsMessage<T>
            bool PostMesssage( T&& message ) const
            {
                return gst_element_post_message( get( ), message.Detach() ) != 0;
            }


        };
    }

    using BasicElement = Internal::ElementImpl<BasicObject>;
    using Element = Internal::ElementImpl<Object>;


}

#endif
