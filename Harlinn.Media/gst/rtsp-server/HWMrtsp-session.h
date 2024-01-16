#pragma once
#ifndef HARLINN_MEDIA_GST_RTSP_SERVER_HWMRTSP_SESSION_H_
#define HARLINN_MEDIA_GST_RTSP_SERVER_HWMRTSP_SESSION_H_

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

#include <glib/HWMgstring.h>
#include <glib/HWMglist.h>
#include <glib/gobject/HWMgobject.h>
#include "HWMrtsp-server-forwards.h"
#include "HWMrtsp-session-media.h"
#include "HWMrtsp-media.h"

namespace Harlinn::Media::GStreamer::RtspServer
{
    namespace Internal
    {
        template<typename BaseT>
        class RTSPSessionImpl : public BaseT
        {
        public:
            using Base = BaseT;
            HWM_GOBJECT_IMPLEMENT_STANDARD_MEMBERS( RTSPSessionImpl, GstRTSPSession )

            static RTSPSession Create( const char* sessionid, GLib::ReferenceType referenceType = GLib::ReferenceType::None )
            {
                auto session = gst_rtsp_session_new( sessionid );
                if ( session )
                {
                    return RTSPSession( session, referenceType );
                }
                return {};
            }

            /// <summary>
            /// Retrieves the session id.
            /// </summary>
            /// <returns>pointer to the id of the session, the value is valid for as long as the session is alive.</returns>
            const char* SessionId( ) const
            {
                return gst_rtsp_session_get_sessionid( get( ) );
            }

            /// <summary>
            /// Get the string that can be placed in the Session header field.
            /// </summary>
            /// <returns>A GLib::StringPtr to the header string.</returns>
            GLib::StringPtr Header( ) const
            {
                return GLib::StringPtr( gst_rtsp_session_get_header( get( ) ) );
            }

            void SetTimeout( UInt32 timeout ) const
            {
                gst_rtsp_session_set_timeout( get( ), timeout );
            }
            void SetTimeout( TimeSpan timeout ) const
            {
                SetTimeout( static_cast< UInt32 >( timeout.Ticks( ) / TimeSpan::TicksPerSecond ) );
            }
            TimeSpan Timeout( ) const
            {
                return TimeSpan(static_cast< Int64 >( gst_rtsp_session_get_timeout( get( ) ) )* TimeSpan::TicksPerSecond);
            }

            void Touch( ) const
            {
                gst_rtsp_session_touch( get( ) );
            }

            void PreventExpire( ) const
            {
                gst_rtsp_session_prevent_expire( get( ) );
            }

            void AllowExpire( ) const
            {
                gst_rtsp_session_allow_expire( get( ) );
            }

            TimeSpan NextTimeout( DateTime now ) const
            {
                return TimeSpan( static_cast< Int64 >( gst_rtsp_session_next_timeout_usec( get(), ( now.Ticks() - DateTime::UnixEpoch ) / DateTime::TicksPerMicrosecond ) ) * TimeSpan::TicksPerMillisecond );
            }
            UInt32 NextTimeoutInMicroseconds( Int64 now ) const
            {
                return gst_rtsp_session_next_timeout_usec( get( ), now );
            }

            bool IsExpired( DateTime now ) const
            {
                return gst_rtsp_session_is_expired_usec( get( ), ( now.Ticks( ) - DateTime::UnixEpoch ) / DateTime::TicksPerMicrosecond ) != 0;
            }
            bool IsExpiredInMicroseconds( Int64 now ) const
            {
                return gst_rtsp_session_is_expired_usec( get( ), now ) != 0;
            }


            BasicRTSPSessionMedia ManageMedia( const char* path, GstRTSPMedia* media ) const
            {
                auto sessionMedia = gst_rtsp_session_manage_media( get( ), path, media );
                return BasicRTSPSessionMedia( sessionMedia );
            }
            template<typename T>
                requires IsRTSPMedia<T>
            BasicRTSPSessionMedia ManageMedia( const char* path, T&& media ) const
            {
                auto sessionMedia = gst_rtsp_session_manage_media( get( ), path, reinterpret_cast< GstRTSPMedia* >( media.get() ) );
                if ( sessionMedia )
                {
                    media.Detach( );
                    return BasicRTSPSessionMedia( sessionMedia );
                }
            }

            bool ReleaseMedia( GstRTSPSessionMedia* media ) const
            {
                return gst_rtsp_session_release_media( get(), media ) != 0;
            }
            template<typename T>
                requires IsRTSPSessionMedia<T>
            bool ReleaseMedia( T&& media ) const
            {
                return gst_rtsp_session_release_media( get( ), reinterpret_cast< GstRTSPSessionMedia* >( media.Detach( ) ) ) != 0;
            }

            BasicRTSPSessionMedia Media( const char* path, Int32* matched )
            {
                auto sessionMedia = gst_rtsp_session_get_media( get( ), path, matched );
                if ( sessionMedia )
                {
                    return BasicRTSPSessionMedia( sessionMedia );
                }
                return {};
            }

            RTSPSessionMedia DupMedia( const char* path, Int32* matched )
            {
                auto sessionMedia = gst_rtsp_session_dup_media( get( ), path, matched );
                if ( sessionMedia )
                {
                    return RTSPSessionMedia( sessionMedia );
                }
                return {};
            }

            GLib::List<GstRTSPSessionMedia> MediaFilterList( GstRTSPSessionFilterFunc func, gpointer userData ) const
            {
                auto list = gst_rtsp_session_filter( get( ), func, userData );
                if ( list )
                {
                    return GLib::List<GstRTSPSessionMedia>( list );
                }
                return {};
            }
        };
    }

    using BasicRTSPSession = Internal::RTSPSessionImpl<GLib::BasicObject>;
    using RTSPSession = Internal::RTSPSessionImpl<GLib::Object>;

}
#endif

