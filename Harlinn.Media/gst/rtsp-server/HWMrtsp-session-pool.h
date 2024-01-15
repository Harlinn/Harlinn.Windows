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
            /*
            guint gst_rtsp_session_pool_get_n_sessions( GstRTSPSessionPool* pool );

            // managing sessions 

            GstRTSPSession* gst_rtsp_session_pool_create( GstRTSPSessionPool* pool );

            GstRTSPSession* gst_rtsp_session_pool_find( GstRTSPSessionPool* pool, const char* sessionid );

            gboolean gst_rtsp_session_pool_remove( GstRTSPSessionPool* pool, GstRTSPSession* sess );

            // perform session maintenance 

            GList* gst_rtsp_session_pool_filter( GstRTSPSessionPool* pool, GstRTSPSessionPoolFilterFunc func, gpointer userData );

            guint gst_rtsp_session_pool_cleanup( GstRTSPSessionPool* pool );

            GSource* gst_rtsp_session_pool_create_watch( GstRTSPSessionPool* pool );
            */
        };
    }

    using BasicRTSPSessionPool = Internal::RTSPSessionPoolImpl<GLib::BasicObject>;
    using RTSPSessionPool = Internal::RTSPSessionPoolImpl<GLib::Object>;

}
#endif

