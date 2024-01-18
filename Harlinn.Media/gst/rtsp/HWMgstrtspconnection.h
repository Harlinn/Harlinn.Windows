#pragma once 
#ifndef HARLINN_MEDIA_GST_RTSP_HWMGSTRTSPCONNECTION_H_
#define HARLINN_MEDIA_GST_RTSP_HWMGSTRTSPCONNECTION_H_

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

#include "HWMgstrtspurl.h"
#include "HWMgstrtspmessage.h"
#include <glib/gio/HWMGSocket.h>
#include <glib/gio/HWMGCancellable.h>
#include <glib/gio/HWMGTlsConnection.h>

namespace Harlinn::Media::GStreamer::Rtsp
{
    class RTSPConnection : public GLib::ReferenceBase< RTSPConnection, GstRTSPConnection>
    {
    public:
        using Base = GLib::ReferenceBase< RTSPConnection, GstRTSPConnection>;

        RTSPConnection( ) = default;
        explicit RTSPConnection( WrappedType* impl, GLib::ReferenceType referenceType = GLib::ReferenceType::None )
            : Base( impl, referenceType )
        {
        }

        static RTSPConnection Create( const GstRTSPUrl* url )
        {
            GstRTSPConnection* connection = nullptr;
            auto rc = gst_rtsp_connection_create( url, &connection );
            CheckRTSPResult( rc, CURRENT_FUNCTION, CURRENT_FILE, __LINE__ );
            if ( connection )
            {
                return RTSPConnection( connection );
            }
            return {};
        }
        static RTSPConnection Create( const RTSPUrl& url )
        {
            return Create( url.get() );
        }

        static RTSPConnection Create( GSocket* socket, const char* ip, UInt16 port, const char* initialBuffer )
        {
            GstRTSPConnection* connection = nullptr;
            auto rc = gst_rtsp_connection_create_from_socket( socket, ip, port, initialBuffer, &connection );
            CheckRTSPResult( rc, CURRENT_FUNCTION, CURRENT_FILE, __LINE__ );
            if ( connection )
            {
                return RTSPConnection( connection );
            }
            return {};
        }

        template<typename T>
            requires GLib::GIO::IsSocket<T>
        static RTSPConnection Create( const T& socket, const char* ip, UInt16 port, const char* initialBuffer )
        {
            GstRTSPConnection* connection = nullptr;
            auto rc = gst_rtsp_connection_create_from_socket( reinterpret_cast< GSocket *>( socket.get() ), ip, port, initialBuffer, &connection );
            CheckRTSPResult( rc, CURRENT_FUNCTION, CURRENT_FILE, __LINE__ );
            if ( connection )
            {
                return RTSPConnection( connection );
            }
            return {};
        }

        static RTSPConnection Accept( GSocket* socket, GCancellable* cancellable )
        {
            GstRTSPConnection* connection = nullptr;
            auto rc = gst_rtsp_connection_accept( socket, &connection, cancellable );
            CheckRTSPResult( rc, CURRENT_FUNCTION, CURRENT_FILE, __LINE__ );
            if ( connection )
            {
                return RTSPConnection( connection );
            }
            return {};
        }

        template<typename SocketT, typename CancellableT >
            requires GLib::GIO::IsSocket<SocketT> && GLib::GIO::IsCancellable<CancellableT>
        static RTSPConnection Accept( const SocketT& socket, const CancellableT& cancellable )
        {
            return Accept( reinterpret_cast< GSocket* >( socket.get( ) ), reinterpret_cast< GCancellable* >( cancellable.get( ) ) );
        }


        bool Connect( Int64 usecTimeout ) const
        {
            auto rc = gst_rtsp_connection_connect_usec( get( ), usecTimeout );
            if ( rc == GstRTSPResult::GST_RTSP_ETIMEOUT )
            {
                return false;
            }
            CheckRTSPResult( rc, CURRENT_FUNCTION, CURRENT_FILE, __LINE__ );
            return true;
        }

        bool Connect( TimeSpan timeout ) const
        {
            auto usecTimeout = timeout.Ticks( ) / TimeSpan::TicksPerMicrosecond;
            return Connect( usecTimeout );
        }

        bool Connect( Int64 usecTimeout, GstRTSPMessage* response ) const
        {
            auto rc = gst_rtsp_connection_connect_with_response_usec( get( ), usecTimeout, response );
            if ( rc == GstRTSPResult::GST_RTSP_ETIMEOUT )
            {
                return false;
            }
            CheckRTSPResult( rc, CURRENT_FUNCTION, CURRENT_FILE, __LINE__ );
            return true;
        }

        bool Connect( TimeSpan timeout, GstRTSPMessage* response ) const
        {
            auto usecTimeout = timeout.Ticks( ) / TimeSpan::TicksPerMicrosecond;
            return Connect( usecTimeout, response );
        }

        bool Connect( Int64 usecTimeout, const RTSPMessage& response ) const
        {
            return Connect( usecTimeout, response.get( ) );
        }
        bool Connect( TimeSpan timeout, const RTSPMessage& response ) const
        {
            auto usecTimeout = timeout.Ticks( ) / TimeSpan::TicksPerMicrosecond;
            return Connect( usecTimeout, response.get( ) );
        }

        void Close( ) const
        {
            auto rc = gst_rtsp_connection_close( get( ) );
            CheckRTSPResult( rc, CURRENT_FUNCTION, CURRENT_FILE, __LINE__ );
        }

        void Free( )
        {
            auto rc = gst_rtsp_connection_free( get( ) );
            CheckRTSPResult( rc, CURRENT_FUNCTION, CURRENT_FILE, __LINE__ );
            ( void )Detach( );
        }

        GLib::GIO::BasicTlsConnection Tls( GError** error ) const
        {
            GLib::GIO::BasicTlsConnection::WrappedType* tlsConnection = gst_rtsp_connection_get_tls( get( ), error );
            if ( tlsConnection )
            {
                
                GLib::GIO::BasicTlsConnection result( tlsConnection, GLib::ReferenceType::None );
                return result;
            }
            return {};
        }




    };
}
#endif