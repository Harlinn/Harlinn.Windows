#pragma once 
#ifndef HARLINN_MEDIA_GST_RTSP_HWMGSTRTSPMESSAGE_H_
#define HARLINN_MEDIA_GST_RTSP_HWMGSTRTSPMESSAGE_H_

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

#include <glib/HWMgmemory.h>

namespace Harlinn::Media::GStreamer::Rtsp
{
    class RTSPAuthCredential : public GLib::Internal::Base< RTSPAuthCredential, GstRTSPAuthCredential>
    {
    public:
        using Base = GLib::Internal::Base< RTSPAuthCredential, GstRTSPAuthCredential>;

        RTSPAuthCredential( ) = default;
        RTSPAuthCredential( InnerType* impl )
            : Base( impl )
        {
        }

        static void ReleaseInner( InnerType* impl )
        {
            auto tmp = impl;
            gst_rtsp_auth_credentials_free( &tmp );
        }

        GstRTSPAuthMethod Scheme( ) const
        {
            auto impl = get( );
            if ( impl )
            {
                return impl->scheme;
            }
            return GstRTSPAuthMethod::GST_RTSP_AUTH_NONE;
        }
        const GstRTSPAuthParam** ParamsPtr( ) const
        {
            auto impl = get( );
            if ( impl )
            {
                return impl->params;
            }
            return nullptr;
        }

        std::span<GstRTSPAuthParam*> Params( ) const
        {
            auto impl = get( );
            if ( impl && impl->params )
            {
                GstRTSPAuthParam** params = impl->params;
                size_t paramCount = 0;
                while ( params[ paramCount ] )
                {
                    paramCount++;
                }
                std::span<GstRTSPAuthParam*> result( params, paramCount );
                return result;
            }
            return {};
        }

        const gchar* Authorization( ) const
        {
            auto impl = get( );
            if ( impl )
            {
                return impl->authorization;
            }
            return nullptr;
        }

    };

    class RTSPMessage : public GLib::Internal::Base< RTSPMessage, GstRTSPMessage>
    {
    public:
        using Base = GLib::Internal::Base< RTSPMessage, GstRTSPMessage>;

        RTSPMessage( ) = default;
        RTSPMessage( InnerType* impl )
            : Base( impl )
        {
        }

        static void ReleaseInner( InnerType* impl )
        {
            gst_rtsp_message_free( impl );
        }

        GstRTSPMsgType MessageType( ) const
        {
            GstRTSPMessage* impl = get( );
            if ( impl )
            {
                return impl->type;
            }
            return GstRTSPMsgType::GST_RTSP_MESSAGE_INVALID;
        }



    };
}
#endif
