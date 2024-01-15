#pragma once 
#ifndef HARLINN_MEDIA_GST_RTSP_SERVER_HWMRTSP_SERVER_FORWARDS_H_
#define HARLINN_MEDIA_GST_RTSP_SERVER_HWMRTSP_SERVER_FORWARDS_H_

#include <gst/HWMGstForwards.h>

namespace Harlinn::Media::GStreamer::RtspServer
{
    namespace Internal
    {
        template<typename BaseT>
        class RTSPAddressPoolImpl;
    }

    using BasicRTSPAddressPool = Internal::RTSPAddressPoolImpl<GLib::BasicObject>;
    using RTSPAddressPool = Internal::RTSPAddressPoolImpl<GLib::Object>;

    template<typename T>
    constexpr bool IsRTSPAddressPool = std::is_base_of_v<BasicRTSPAddressPool, T> || std::is_base_of_v<RTSPAddressPool, T>;

    namespace Internal
    {
        template<typename BaseT>
        class RTSPAuthImpl;
    }

    using BasicRTSPAuth = Internal::RTSPAuthImpl<GLib::BasicObject>;
    using RTSPAuth = Internal::RTSPAuthImpl<GLib::Object>;

    template<typename T>
    constexpr bool IsRTSPAuth = std::is_base_of_v<BasicRTSPAuth, T> || std::is_base_of_v<RTSPAuth, T>;

    namespace Internal
    {
        template<typename BaseT>
        class RTSPClientImpl;
    }

    using BasicRTSPClient = Internal::RTSPClientImpl<GLib::BasicObject>;
    using RTSPClient = Internal::RTSPClientImpl<GLib::Object>;

    template<typename T>
    constexpr bool IsRTSPClient = std::is_base_of_v<BasicRTSPClient, T> || std::is_base_of_v<RTSPClient, T>;

    namespace Internal
    {
        template<typename BaseT>
        class RTSPMediaImpl;
    }

    using BasicRTSPMedia = Internal::RTSPMediaImpl<GLib::BasicObject>;
    using RTSPMedia = Internal::RTSPMediaImpl<GLib::Object>;

    template<typename T>
    constexpr bool IsRTSPMedia = std::is_base_of_v<BasicRTSPMedia, T> || std::is_base_of_v<RTSPMedia, T>;

    namespace Internal
    {
        template<typename BaseT>
        class RTSPMediaFactoryImpl;
    }

    using BasicRTSPMediaFactory = Internal::RTSPMediaFactoryImpl<GLib::BasicObject>;
    using RTSPMediaFactory = Internal::RTSPMediaFactoryImpl<GLib::Object>;

    template<typename T>
    constexpr bool IsRTSPMediaFactory = std::is_base_of_v<BasicRTSPMediaFactory, T> || std::is_base_of_v<RTSPMediaFactory, T>;

    namespace Internal
    {
        template<typename BaseT>
        class RTSPMediaFactoryURIImpl;
    }

    using BasicRTSPMediaFactoryURI = Internal::RTSPMediaFactoryURIImpl<BasicRTSPMediaFactory>;
    using RTSPMediaFactoryURI = Internal::RTSPMediaFactoryURIImpl<RTSPMediaFactory>;

    template<typename T>
    constexpr bool IsRTSPMediaFactoryURI = std::is_base_of_v<BasicRTSPMediaFactoryURI, T> || std::is_base_of_v<RTSPMediaFactoryURI, T>;

    namespace Internal
    {
        template<typename BaseT>
        class RTSPMountPointsImpl;
    }

    using BasicRTSPMountPoints = Internal::RTSPMountPointsImpl<GLib::BasicObject>;
    using RTSPMountPoints = Internal::RTSPMountPointsImpl<GLib::Object>;

    template<typename T>
    constexpr bool IsRTSPMountPoints = std::is_base_of_v<BasicRTSPMountPoints, T> || std::is_base_of_v<RTSPMountPoints, T>;

    namespace Internal
    {
        template<typename BaseT>
        class RTSPServerImpl;
    }

    using BasicRTSPServer = Internal::RTSPServerImpl<GLib::BasicObject>;
    using RTSPServer = Internal::RTSPServerImpl<GLib::Object>;

    template<typename T>
    constexpr bool IsRTSPServer = std::is_base_of_v<BasicRTSPServer, T> || std::is_base_of_v<RTSPServer, T>;

    namespace Internal
    {
        template<typename BaseT>
        class RTSPPermissionsImpl;
    }

    using BasicRTSPPermissions = Internal::RTSPPermissionsImpl<BasicMiniObject>;
    using RTSPPermissions = Internal::RTSPPermissionsImpl<MiniObject>;

    template<typename T>
    constexpr bool IsRTSPPermissions = std::is_base_of_v<BasicRTSPPermissions, T> || std::is_base_of_v<RTSPPermissions, T>;

    namespace Internal
    {
        template<typename BaseT>
        class RTSPSessionImpl;
    }

    using BasicRTSPSession = Internal::RTSPSessionImpl<GLib::BasicObject>;
    using RTSPSession = Internal::RTSPSessionImpl<GLib::Object>;

    template<typename T>
    constexpr bool IsRTSPSession = std::is_base_of_v<BasicRTSPSession, T> || std::is_base_of_v<RTSPSession, T>;

    namespace Internal
    {
        template<typename BaseT>
        class RTSPSessionMediaImpl;
    }

    using BasicRTSPSessionMedia = Internal::RTSPSessionMediaImpl<GLib::BasicObject>;
    using RTSPSessionMedia = Internal::RTSPSessionMediaImpl<GLib::Object>;

    template<typename T>
    constexpr bool IsRTSPSessionMedia = std::is_base_of_v<BasicRTSPSessionMedia, T> || std::is_base_of_v<RTSPSessionMedia, T>;

    namespace Internal
    {
        template<typename BaseT>
        class RTSPSessionPoolImpl;
    }

    using BasicRTSPSessionPool = Internal::RTSPSessionPoolImpl<GLib::BasicObject>;
    using RTSPSessionPool = Internal::RTSPSessionPoolImpl<GLib::Object>;

    template<typename T>
    constexpr bool IsRTSPSessionPool = std::is_base_of_v<BasicRTSPSessionPool, T> || std::is_base_of_v<RTSPSessionPool, T>;

    namespace Internal
    {
        template<typename BaseT>
        class RTSPStreamImpl;
    }

    using BasicRTSPStream = Internal::RTSPStreamImpl<GLib::BasicObject>;
    using RTSPStream = Internal::RTSPStreamImpl<GLib::Object>;

    template<typename T>
    constexpr bool IsRTSPStream = std::is_base_of_v<BasicRTSPStream, T> || std::is_base_of_v<RTSPStream, T>;

    namespace Internal
    {
        template<typename BaseT>
        class RTSPStreamTransportImpl;
    }

    using BasicRTSPStreamTransport = Internal::RTSPStreamTransportImpl<GLib::BasicObject>;
    using RTSPStreamTransport = Internal::RTSPStreamTransportImpl<GLib::Object>;

    template<typename T>
    constexpr bool IsRTSPStreamTransport = std::is_base_of_v<BasicRTSPStreamTransport, T> || std::is_base_of_v<RTSPStreamTransport, T>;

    namespace Internal
    {
        template<typename BaseT>
        class RTSPThreadPoolImpl;
    }

    using BasicRTSPThreadPool = Internal::RTSPThreadPoolImpl<GLib::BasicObject>;
    using RTSPThreadPool = Internal::RTSPThreadPoolImpl<GLib::Object>;

    template<typename T>
    constexpr bool IsRTSPThreadPool = std::is_base_of_v<BasicRTSPThreadPool, T> || std::is_base_of_v<RTSPThreadPool, T>;

    namespace Internal
    {
        template<typename BaseT>
        class RTSPTokenImpl;
    }

    using BasicRTSPToken = Internal::RTSPTokenImpl<BasicMiniObject>;
    using RTSPToken = Internal::RTSPTokenImpl<MiniObject>;

    template<typename T>
    constexpr bool IsRTSPToken = std::is_base_of_v<BasicRTSPToken, T> || std::is_base_of_v<RTSPToken, T>;

    namespace Internal
    {
        template<typename BaseT>
        class RTSPOnvifClientImpl;
    }

    using BasicRTSPOnvifClient = Internal::RTSPOnvifClientImpl<BasicRTSPClient>;
    using RTSPOnvifClient = Internal::RTSPOnvifClientImpl<RTSPClient>;

    template<typename T>
    constexpr bool IsRTSPOnvifClient = std::is_base_of_v<BasicRTSPOnvifClient, T> || std::is_base_of_v<RTSPOnvifClient, T>;

    namespace Internal
    {
        template<typename BaseT>
        class RTSPOnvifMediaImpl;
    }

    using BasicRTSPOnvifMedia = Internal::RTSPOnvifMediaImpl<BasicRTSPMedia>;
    using RTSPOnvifMedia = Internal::RTSPOnvifMediaImpl<RTSPMedia>;

    template<typename T>
    constexpr bool IsRTSPOnvifMedia = std::is_base_of_v<BasicRTSPOnvifMedia, T> || std::is_base_of_v<RTSPOnvifMedia, T>;

    namespace Internal
    {
        template<typename BaseT>
        class RTSPOnvifMediaFactoryImpl;
    }

    using BasicRTSPOnvifMediaFactory = Internal::RTSPOnvifMediaFactoryImpl<BasicRTSPMediaFactory>;
    using RTSPOnvifMediaFactory = Internal::RTSPOnvifMediaFactoryImpl<RTSPMediaFactory>;

    template<typename T>
    constexpr bool IsRTSPOnvifMediaFactory = std::is_base_of_v<BasicRTSPOnvifMediaFactory, T> || std::is_base_of_v<RTSPOnvifMediaFactory, T>;

    namespace Internal
    {
        template<typename BaseT>
        class RTSPOnvifServerImpl;
    }

    using BasicRTSPOnvifServer = Internal::RTSPOnvifServerImpl<BasicRTSPServer>;
    using RTSPOnvifServer = Internal::RTSPOnvifServerImpl<RTSPServer>;

    template<typename T>
    constexpr bool IsRTSPOnvifServer = std::is_base_of_v<BasicRTSPOnvifServer, T> || std::is_base_of_v<RTSPOnvifServer, T>;

}
#endif
