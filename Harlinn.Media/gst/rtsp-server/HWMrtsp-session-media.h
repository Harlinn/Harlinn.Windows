#pragma once
#ifndef HARLINN_MEDIA_GST_RTSP_SERVER_HWMRTSP_SESSION_MEDIA_H_
#define HARLINN_MEDIA_GST_RTSP_SERVER_HWMRTSP_SESSION_MEDIA_H_

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
#include "HWMrtsp-media.h"
#include "HWMrtsp-stream-transport.h"

namespace Harlinn::Media::GStreamer::RtspServer
{
    namespace Internal
    {
        template<typename BaseT>
        class RTSPSessionMediaImpl : public BaseT
        {
        public:
            using Base = BaseT;
            HWM_GOBJECT_IMPLEMENT_STANDARD_MEMBERS( RTSPSessionMediaImpl, GstRTSPSessionMedia )

            static RTSPSessionMedia Create( const char* path, GstRTSPMedia* media, GLib::ReferenceType referenceType = GLib::ReferenceType::None )
            {
                auto sessionMedia = gst_rtsp_session_media_new( path, media );
                if ( sessionMedia )
                {
                    return RTSPSessionMedia( sessionMedia, referenceType );
                }
                return {};
            }
            template<typename T>
                requires IsRTSPMedia<T>
            static RTSPSessionMedia Create( const char* path, T&& media, GLib::ReferenceType referenceType = GLib::ReferenceType::None )
            {
                auto sessionMedia = gst_rtsp_session_media_new( path, reinterpret_cast< GstRTSPMedia* >( media.get() ) );
                if ( sessionMedia )
                {
                    (void)media.Detach( );
                    return RTSPSessionMedia( sessionMedia, referenceType );
                }
                return {};
            }

            bool Matches( const char* path, Int32* matched ) const
            {
                gst_rtsp_session_media_matches(get(), path, matched ) != 0;
            }

            BasicRTSPMedia Media( ) const
            {
                auto media = gst_rtsp_session_media_get_media( get( ) );
                if ( media )
                {
                    return BasicRTSPMedia( media );
                }
                return {};
            }

            GstClockTime BaseTime( ) const
            {
                return gst_rtsp_session_media_get_base_time( get( ) );
            }

            bool SetState( GstState state ) const
            {
                return gst_rtsp_session_media_set_state( get( ), state ) != 0;
            }

            void SetRTSPState( GstRTSPState state ) const
            {
                gst_rtsp_session_media_set_rtsp_state( get( ), state );
            }

            GstRTSPState RTSPState( ) const
            {
                return gst_rtsp_session_media_get_rtsp_state( get() );
            }


        };
    }

    using BasicRTSPSessionMedia = Internal::RTSPSessionMediaImpl<GLib::BasicObject>;
    using RTSPSessionMedia = Internal::RTSPSessionMediaImpl<GLib::Object>;

}
#endif

