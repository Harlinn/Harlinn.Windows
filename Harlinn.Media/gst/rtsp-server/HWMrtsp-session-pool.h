#pragma once
#ifndef HARLINN_MEDIA_GST_RTSP_SERVER_HWMRTSP_SESSION_POOL_H_
#define HARLINN_MEDIA_GST_RTSP_SERVER_HWMRTSP_SESSION_POOL_H_ 

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

#include <glib/HWMglist.h>
#include <glib/HWMgmain.h>
#include <glib/gobject/HWMgobject.h>
#include "HWMrtsp-server-forwards.h"
#include "HWMrtsp-session.h"

namespace Harlinn::Media::GStreamer::RtspServer
{
    namespace Internal
    {
        template<typename BaseT>
        class RTSPSessionPoolImpl : public BaseT
        {
        public:
            using Base = BaseT;
            HWM_GOBJECT_IMPLEMENT_STANDARD_MEMBERS( RTSPSessionPoolImpl, GstRTSPSessionPool )

            static RTSPSessionPool Create( GLib::ReferenceType referenceType = GLib::ReferenceType::None )
            {
                auto sessionPool = gst_rtsp_session_pool_new( );
                if ( sessionPool )
                {
                    return RTSPSessionPool( sessionPool, referenceType );
                }
                return {};
            }

            // counting sessions

            void SetMaxSessions( UInt32 max ) const
            {
                gst_rtsp_session_pool_set_max_sessions( get(), max );
            }

            UInt32 MaxSessions( ) const
            {
                return gst_rtsp_session_pool_get_max_sessions( get() );
            }

            UInt32 NumberOfSessions( ) const
            {
                return gst_rtsp_session_pool_get_n_sessions( get( ) );
            }

            // managing sessions 
            RTSPSession Add( ) const
            {
                auto session = gst_rtsp_session_pool_create( get( ) );
                if ( session )
                {
                    return RTSPSession( session );
                }
                return {};
            }

            RTSPSession Find( const char* sessionId ) const
            {
                auto session = gst_rtsp_session_pool_find( get( ), sessionId );
                if ( session )
                {
                    return RTSPSession( session );
                }
                return {};
            }

            bool Remove( GstRTSPSession* session ) const
            {
                return gst_rtsp_session_pool_remove( get(), session ) != 0;
            }
            template<typename T>
                requires IsRTSPSession<T>
            bool Remove( const T& session ) const
            {
                Remove( reinterpret_cast< GstRTSPSession* >( session.get() ) );
            }


            // perform session maintenance 
            GLib::List<GstRTSPSession> SessionPoolFilterList( GstRTSPSessionPoolFilterFunc func, gpointer userData ) const
            {
                auto list = gst_rtsp_session_pool_filter( get( ), func, userData );
                if ( list )
                {
                    return GLib::List<GstRTSPSession>( list );
                }
                return {};
            }


            UInt32 Cleanup( ) const
            {
                return gst_rtsp_session_pool_cleanup( get( ) );
            }

            GLib::Source CreateSource( ) const
            {
                auto source = gst_rtsp_session_pool_create_watch( get( ) );
                if ( source )
                {
                    return GLib::Source( source );
                }
                return {};
            }

        };
    }

    using BasicRTSPSessionPool = Internal::RTSPSessionPoolImpl<GLib::BasicObject>;
    using RTSPSessionPool = Internal::RTSPSessionPoolImpl<GLib::Object>;

}
#endif

