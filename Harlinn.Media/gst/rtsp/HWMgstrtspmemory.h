#pragma once 
#ifndef HARLINN_MEDIA_GST_RTSP_HWMGSTRTSPMEMORY_H_
#define HARLINN_MEDIA_GST_RTSP_HWMGSTRTSPMEMORY_H_

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

namespace Harlinn::Media::GLib
{
    template<>
    struct ObjectTraits<GstRTSPConnection> : public SimpleObjectTraits< ObjectTraits<GstRTSPConnection>, GstRTSPConnection >
    {
        static void Unref( WrappedType* wrapped )
        {
            gst_rtsp_connection_free( wrapped );
        }
    };

    template<>
    struct ObjectTraits<GstRTSPAuthCredential> : public SimpleObjectTraits< ObjectTraits<GstRTSPAuthCredential>, GstRTSPAuthCredential >
    {
        static void Unref( WrappedType* wrapped )
        {
            auto tmp = wrapped;
            gst_rtsp_auth_credentials_free( &tmp );
        }
    };

    template<>
    struct ObjectTraits<GstRTSPMessage> : public SimpleObjectTraits< ObjectTraits<GstRTSPMessage>, GstRTSPMessage >
    {
        static void Unref( WrappedType* wrapped )
        {
            gst_rtsp_message_free( wrapped );
        }
    };

    template<>
    struct ObjectTraits<GstRTSPTransport> : public SimpleObjectTraits< ObjectTraits<GstRTSPTransport>, GstRTSPTransport >
    {
        static void Unref( WrappedType* wrapped )
        {
            gst_rtsp_transport_free( wrapped );
        }
    };

    template<>
    struct ObjectTraits<GstRTSPUrl> : public SimpleObjectTraits< ObjectTraits<GstRTSPUrl>, GstRTSPUrl >
    {
        static void Unref( WrappedType* wrapped )
        {
            gst_rtsp_url_free( wrapped );
        }
    };

}

namespace Harlinn::Media::GStreamer::Rtsp
{
}
#endif
