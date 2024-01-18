#pragma once
#ifndef HARLINN_MEDIA_GST_RTSP_HWMGSTRTSPTRANSPORT_H_
#define HARLINN_MEDIA_GST_RTSP_HWMGSTRTSPTRANSPORT_H_

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
    class RTSPTransport : public GLib::ReferenceBase< RTSPTransport, GstRTSPTransport>
    {
    public:
        using Base = GLib::ReferenceBase< RTSPTransport, GstRTSPTransport>;

        RTSPTransport( ) = default;
        explicit RTSPTransport( WrappedType* impl, GLib::ReferenceType referenceType = GLib::ReferenceType::None )
            : Base( impl, referenceType )
        {
        }
        
        static RTSPTransport Create( GLib::ReferenceType referenceType = GLib::ReferenceType::None )
        {
            GstRTSPTransport* rtspTransport = nullptr;
            auto rc = gst_rtsp_transport_new( &rtspTransport );
            CheckRTSPResult( rc, CURRENT_FUNCTION, CURRENT_FILE, __LINE__ );
            if ( rtspTransport )
            {
                return RTSPTransport( rtspTransport, referenceType );
            }
            return {};
        }

        static RTSPTransport Create( const char* str, GLib::ReferenceType referenceType = GLib::ReferenceType::None )
        {
            GstRTSPTransport* rtspTransport = nullptr;
            auto rc = gst_rtsp_transport_new( &rtspTransport );
            CheckRTSPResult( rc, CURRENT_FUNCTION, CURRENT_FILE, __LINE__ );
            if ( rtspTransport )
            {
                RTSPTransport rtspTransport( rtspTransport, referenceType );
                rc = gst_rtsp_transport_parse( str, rtspTransport.get( ) );
                CheckRTSPResult( rc, CURRENT_FUNCTION, CURRENT_FILE, __LINE__ );
                return rtspTransport;
            }
            return {};
        }


        bool Parse( const char* str ) const
        {
            auto rc = gst_rtsp_transport_parse( str, get( ) );
            return rc == GstRTSPResult::GST_RTSP_OK;
        }

        GLib::StringPtr AsText( ) const
        {
            auto text = gst_rtsp_transport_as_text( get( ) );
            return GLib::StringPtr( text );
        }

        WideString AsWideString( ) const
        {
            auto text = AsText( );
            return ToWideString( text.c_str() );
        }
        AnsiString AsAnsiString( ) const
        {
            auto text = AsText( );
            return ToAnsiString( text.c_str( ) );
        }


        static const char* Manager( GstRTSPTransMode rtspTransportMode, UInt32 option )
        {
            char* manager = nullptr;
            // gst_rtsp_transport_get_manager only fails if second argument is nullptr ...
            gst_rtsp_transport_get_manager( rtspTransportMode, &manager, option );
            return manager;
        }

        const char* MediaType( ) const
        {
            char* mediaType = nullptr;
            // gst_rtsp_transport_get_media_type only fails if first or second argument is nullptr ...
            auto rc = gst_rtsp_transport_get_media_type( get( ), &mediaType );
            CheckRTSPResult( rc, CURRENT_FUNCTION, CURRENT_FILE, __LINE__ );
            return mediaType;
        }
        
        

    };
    
}
#endif
