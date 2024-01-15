#pragma once
#ifndef HARLINN_MEDIA_GST_RTSP_SERVER_HWMRTSP_SERVER_OBJECT_H_
#define HARLINN_MEDIA_GST_RTSP_SERVER_HWMRTSP_SERVER_OBJECT_H_

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
#include <glib/HWMgmain.h>
#include <glib/gobject/HWMgobject.h>
#include <glib/gio/HWMGSocket.h>
#include <glib/gio/HWMGCancellable.h>
#include "HWMrtsp-session-pool.h"
#include "HWMrtsp-mount-points.h"
#include "HWMrtsp-auth.h"
#include "HWMrtsp-thread-pool.h"

namespace Harlinn::Media::GStreamer::RtspServer
{
    namespace Internal
    {
        template<typename BaseT>
        class RTSPServerImpl : public BaseT
        {
        public:
            using Base = BaseT;
            HWM_GOBJECT_IMPLEMENT_STANDARD_MEMBERS( RTSPServerImpl, GstRTSPServer )

            static RTSPServer Create( GLib::ReferenceType referenceType = GLib::ReferenceType::None )
            {
                auto server = gst_rtsp_server_new( );
                if ( server )
                {
                    return RTSPServer( server, referenceType );
                }
                return {};
            }

            void SetAddress( const char* address ) const
            {
                gst_rtsp_server_set_address( get(), address );
            }

            GLib::StringPtr Address( ) const
            {
                return GLib::StringPtr( gst_rtsp_server_get_address( get( ) ) );
            }

            void SetService( const char* service ) const
            {
                gst_rtsp_server_set_service( get( ), service );
            }

            GLib::StringPtr Service( ) const
            {
                return GLib::StringPtr( gst_rtsp_server_get_service( get( ) ) );
            }

            void SetBacklog( Int32 backlog ) const
            {
                gst_rtsp_server_set_backlog( get( ), backlog );
            }
            /// <summary>
            /// Retrieves the maximum amount of queued requests for the server.
            /// </summary>
            /// <returns>
            /// The server backlog
            /// </returns>
            Int32 Backlog( ) const
            {
                return gst_rtsp_server_get_backlog( get( ) );
            }

            Int32 BoundPort( ) const
            {
                return gst_rtsp_server_get_bound_port( get( ) );
            }

            /// <summary>
            /// Configure pool to be used as the session pool of server.
            /// </summary>
            /// <param name="pool">
            /// A GstRTSPSessionPool.
            /// </param>
            void SetSessionPool( GstRTSPSessionPool* pool ) const
            {
                gst_rtsp_server_set_session_pool( get( ), pool );
            }
            template<typename T>
                requires IsRTSPSessionPool<T>
            void SetSessionPool( const T& pool ) const
            {
                gst_rtsp_server_set_session_pool( get( ), reinterpret_cast< GstRTSPSessionPool* >( pool.get() ) );
            }

            RTSPSessionPool SessionPool( GLib::ReferenceType referenceType = GLib::ReferenceType::None ) const
            {
                auto sessionPool = gst_rtsp_server_get_session_pool( get( ) );
                if ( sessionPool )
                {
                    return RTSPSessionPool( sessionPool, referenceType );
                }
                return {};
            }


            void SetMountPoints( GstRTSPMountPoints* mounts ) const
            {
                gst_rtsp_server_set_mount_points( get( ), mounts );
            }
            template<typename T>
                requires IsRTSPMountPoints<T>
            void SetMountPoints( const T& mounts ) const
            {
                gst_rtsp_server_set_mount_points( get( ), reinterpret_cast< GstRTSPMountPoints* >( mounts.get( ) ) );
            }

            RTSPMountPoints MountPoints( GLib::ReferenceType referenceType = GLib::ReferenceType::None ) const
            {
                auto mountPoints = gst_rtsp_server_get_mount_points( get( ) );
                if ( mountPoints )
                {
                    return RTSPMountPoints( mountPoints, referenceType );
                }
                return {};
            }

            void SetContentLengthLimit( UInt32 limit ) const
            {
                gst_rtsp_server_set_content_length_limit( get( ), limit );
            }
            UInt32 ContentLengthLimit( ) const
            {
                return gst_rtsp_server_get_content_length_limit( get( ) );
            }

            void SetAuth( GstRTSPAuth* auth ) const
            {
                gst_rtsp_server_set_auth( get( ), auth );
            }
            template<typename T>
                requires IsRTSPAuth<T>
            void SetAuth( const T& auth ) const
            {
                gst_rtsp_server_set_auth( get( ), reinterpret_cast< GstRTSPAuth* >( auth.get( ) ) );
            }

            RTSPAuth Auth( GLib::ReferenceType referenceType = GLib::ReferenceType::None ) const
            {
                auto auth = gst_rtsp_server_get_auth( get( ) );
                if ( auth )
                {
                    return RTSPAuth( auth, referenceType );
                }
                return {};
            }

            void SetThreadPool( GstRTSPThreadPool* pool ) const
            {
                gst_rtsp_server_set_thread_pool( get(), pool );
            }
            template<typename T>
                requires IsRTSPThreadPool<T>
            void SetThreadPool( const T& pool ) const
            {
                gst_rtsp_server_set_session_pool( get( ), reinterpret_cast< GstRTSPThreadPool* >( pool.get( ) ) );
            }

            RTSPThreadPool ThreadPool( GLib::ReferenceType referenceType = GLib::ReferenceType::None ) const
            {
                auto pool = gst_rtsp_server_get_thread_pool( get( ) );
                if ( pool )
                {
                    return RTSPThreadPool( pool, referenceType );
                }
                return {};
            }

            bool TransferConnection( GSocket* socket, const char* ip, Int32 port, const char* initialBuffer ) const
            {
                return gst_rtsp_server_transfer_connection( get( ), socket, ip, port, initialBuffer ) != 0;
            }
            template<typename T>
                requires GLib::GIO::IsSocket<T>
            bool TransferConnection( T&& socket, const char* ip, Int32 port, const char* initialBuffer ) const
            {
                auto result = gst_rtsp_server_transfer_connection( get( ), reinterpret_cast< GSocket* >( socket.get() ), ip, port, initialBuffer ) != 0;
                if ( result )
                {
                    socket.Detach( );
                }
                return result;
            }

            GLib::GIO::Socket CreateSocket( GCancellable* cancellable, GError** error ) const
            {
                auto socket = gst_rtsp_server_create_socket( get(), cancellable, error );
                if ( socket )
                {
                    return GLib::GIO::Socket( socket );
                }
                return {};
            }
            GLib::GIO::Socket CreateSocket( const GLib::GIO::Cancellable& cancellable, GError** error ) const
            {
                return CreateSocket( cancellable.get( ), error );
            }



            GLib::Source CreateSource( GCancellable* cancellable, GError** error ) const
            {
                auto source = gst_rtsp_server_create_source( get( ), cancellable, error );
                if ( source )
                {
                    return GLib::Source( source );
                }
                return {};
            }
            GLib::Source CreateSource( const GLib::GIO::Cancellable& cancellable, GError** error ) const
            {
                return CreateSource( cancellable.get( ), error );
            }

            UInt32 Attach( GMainContext* context ) const
            {
                return gst_rtsp_server_attach( get(), context );
            }

            UInt32 Attach( const GLib::MainContext& context ) const
            {
                return Attach( context.get( ) );
            }

        };
    }

    using BasicRTSPServer = Internal::RTSPServerImpl<GLib::BasicObject>;
    using RTSPServer = Internal::RTSPServerImpl<GLib::Object>;
}
#endif

