#pragma once 
#ifndef HARLINN_MEDIA_GST_RTSP_HWMGSTRTSPURL_H_
#define HARLINN_MEDIA_GST_RTSP_HWMGSTRTSPURL_H_

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

#include "HWMgstrtspmemory.h"
#include "HWMGstRTSPException.h"

namespace Harlinn::Media::GStreamer::Rtsp
{
    class RTSPUrl : public GLib::ReferenceBase< RTSPUrl, GstRTSPUrl>
    {
    public:
        using Base = GLib::ReferenceBase< RTSPUrl, GstRTSPUrl>;

        RTSPUrl( ) = default;
        explicit RTSPUrl( WrappedType* impl, GLib::ReferenceType referenceType = GLib::ReferenceType::None )
            : Base( impl, referenceType )
        {
        }

        GstRTSPLowerTrans Transports( ) const
        {
            auto impl = get( );
            if ( impl )
            {
                return impl->transports;
            }
            return GstRTSPLowerTrans::GST_RTSP_LOWER_TRANS_UNKNOWN;
        }

        GstRTSPFamily Family( ) const
        {
            auto impl = get( );
            if ( impl )
            {
                return impl->family;
            }
            return GstRTSPFamily::GST_RTSP_FAM_NONE;
        }

        const gchar* User( ) const
        {
            auto impl = get( );
            if ( impl )
            {
                return impl->user;
            }
            return nullptr;
        }

        const gchar* Password( ) const
        {
            auto impl = get( );
            if ( impl )
            {
                return impl->passwd;
            }
            return nullptr;
        }

        const gchar* Host( ) const
        {
            auto impl = get( );
            if ( impl )
            {
                return impl->host;
            }
            return nullptr;
        }

        const guint16 Port( ) const
        {
            auto impl = get( );
            if ( impl )
            {
                return impl->port;
            }
            return 0;
        }

        const gchar* AbsolutePath( ) const
        {
            auto impl = get( );
            if ( impl )
            {
                return impl->abspath;
            }
            return nullptr;
        }

        const gchar* Query( ) const
        {
            auto impl = get( );
            if ( impl )
            {
                return impl->query;
            }
            return nullptr;
        }


        RTSPUrl Clone( ) const
        {
            return RTSPUrl( gst_rtsp_url_copy( get( ) ) );
        }


        using PathComponentsPtr = std::unique_ptr<gchar*, void( * )( gchar** )>;
        [[nodiscard]]
        PathComponentsPtr DecodePathComponents( ) const
        {
            PathComponentsPtr result( gst_rtsp_url_decode_path_components( get( ) ), g_strfreev );
            return result;
        }
        using UriPtr = std::unique_ptr<gchar, void( * )( gpointer )>;
        [[nodiscard]]
        UriPtr RequestUri( ) const
        {
            UriPtr result( gst_rtsp_url_get_request_uri( get( ) ), g_free );
            return result;
        }
        [[nodiscard]]
        UriPtr RequestUriWithControl( const gchar* controlPath ) const
        {
            UriPtr result( gst_rtsp_url_get_request_uri_with_control( get( ), controlPath ), g_free );
            return result;
        }

        void SetPort( guint16 port )
        {
            gst_rtsp_url_set_port( get( ), port );
        }

        static RTSPUrl Parse( const gchar* urlstr )
        {
            GstRTSPUrl* ptr = nullptr;
            if ( gst_rtsp_url_parse( urlstr, &ptr ) == GstRTSPResult::GST_RTSP_OK )
            {
                return RTSPUrl( ptr );
            }
            return {};
        }
    };
    
}
#endif
