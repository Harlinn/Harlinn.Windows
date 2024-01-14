#pragma once 
#ifndef HARLINN_MEDIA_GLIB_GIO_HWMGIOFORWARDS_H_
#define HARLINN_MEDIA_GLIB_GIO_HWMGIOFORWARDS_H_
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

#include <glib/gobject/HWMgforwards.h>

namespace Harlinn::Media::GLib::GIO
{
    namespace Internal
    {
        template<typename BaseT>
        class IOStreamImpl;
    }
    using BasicIOStream = Internal::IOStreamImpl<BasicObject>;
    using IOStream = Internal::IOStreamImpl<Object>;

    template<typename T>
    constexpr bool IsIOStream = std::is_base_of_v<BasicIOStream, T> || std::is_base_of_v<IOStream, T>;


    namespace Internal
    {
        template<typename BaseT>
        class InputStreamImpl;
    }
    using BasicInputStream = Internal::InputStreamImpl<BasicObject>;
    using InputStream = Internal::InputStreamImpl<Object>;

    template<typename T>
    constexpr bool IsInputStream = std::is_base_of_v<BasicInputStream, T> || std::is_base_of_v<InputStream, T>;

    namespace Internal
    {
        template<typename BaseT>
        class FilterInputStreamImpl;
    }
    using BasicFilterInputStream = Internal::FilterInputStreamImpl<BasicInputStream>;
    using FilterInputStream = Internal::FilterInputStreamImpl<InputStream>;

    template<typename T>
    constexpr bool IsFilterInputStream = std::is_base_of_v<BasicFilterInputStream, T> || std::is_base_of_v<FilterInputStream, T>;

    namespace Internal
    {
        template<typename BaseT>
        class BufferedInputStreamImpl;
    }
    using BasicBufferedInputStream = Internal::BufferedInputStreamImpl<BasicFilterInputStream>;
    using BufferedInputStream = Internal::BufferedInputStreamImpl<FilterInputStream>;

    template<typename T>
    constexpr bool IsBufferedInputStream = std::is_base_of_v<BasicBufferedInputStream, T> || std::is_base_of_v<BufferedInputStream, T>;

    namespace Internal
    {
        template<typename BaseT>
        class ConverterInputStreamImpl;
    }
    using BasicConverterInputStream = Internal::ConverterInputStreamImpl<BasicFilterInputStream>;
    using ConverterInputStream = Internal::ConverterInputStreamImpl<FilterInputStream>;

    template<typename T>
    constexpr bool IsConverterInputStream = std::is_base_of_v<BasicConverterInputStream, T> || std::is_base_of_v<ConverterInputStream, T>;

    namespace Internal
    {
        template<typename BaseT>
        class DataInputStreamImpl;
    }
    using BasicDataInputStream = Internal::DataInputStreamImpl<BasicBufferedInputStream>;
    using DataInputStream = Internal::DataInputStreamImpl<BufferedInputStream>;

    template<typename T>
    constexpr bool IsDataInputStream = std::is_base_of_v<BasicDataInputStream, T> || std::is_base_of_v<DataInputStream, T>;


    namespace Internal
    {
        template<typename BaseT>
        class OutputStreamImpl;
    }
    using BasicOutputStream = Internal::OutputStreamImpl<BasicObject>;
    using OutputStream = Internal::OutputStreamImpl<Object>;

    template<typename T>
    constexpr bool IsOutputStream = std::is_base_of_v<BasicOutputStream, T> || std::is_base_of_v<OutputStream, T>;

    namespace Internal
    {
        template<typename BaseT>
        class FilterOutputStreamImpl;
    }
    using BasicFilterOutputStream = Internal::FilterOutputStreamImpl<BasicOutputStream>;
    using FilterOutputStream = Internal::FilterOutputStreamImpl<OutputStream>;

    template<typename T>
    constexpr bool IsFilterOutputStream = std::is_base_of_v<BasicFilterOutputStream, T> || std::is_base_of_v<FilterOutputStream, T>;

    namespace Internal
    {
        template<typename BaseT>
        class BufferedOutputStreamImpl;
    }
    using BasicBufferedOutputStream = Internal::BufferedOutputStreamImpl<BasicFilterOutputStream>;
    using BufferedOutputStream = Internal::BufferedOutputStreamImpl<FilterOutputStream>;

    template<typename T>
    constexpr bool IsBufferedOutputStream = std::is_base_of_v<BasicBufferedOutputStream, T> || std::is_base_of_v<BufferedOutputStream, T>;

    namespace Internal
    {
        template<typename BaseT>
        class ConverterOutputStreamImpl;
    }
    using BasicConverterOutputStream = Internal::ConverterOutputStreamImpl<BasicFilterOutputStream>;
    using ConverterOutputStream = Internal::ConverterOutputStreamImpl<FilterOutputStream>;

    template<typename T>
    constexpr bool IsConverterOutputStream = std::is_base_of_v<BasicConverterOutputStream, T> || std::is_base_of_v<ConverterOutputStream, T>;

    namespace Internal
    {
        template<typename BaseT>
        class DataOutputStreamImpl;
    }
    using BasicDataOutputStream = Internal::DataOutputStreamImpl<BasicFilterOutputStream>;
    using DataOutputStream = Internal::DataOutputStreamImpl<FilterOutputStream>;

    template<typename T>
    constexpr bool IsDataOutputStream = std::is_base_of_v<BasicDataOutputStream, T> || std::is_base_of_v<DataOutputStream, T>;

    namespace Internal
    {
        template<typename BaseT>
        class ApplicationImpl;
    }
    using BasicApplication = Internal::ApplicationImpl<BasicObject>;
    using Application = Internal::ApplicationImpl<Object>;

    template<typename T>
    constexpr bool IsApplication = std::is_base_of_v<BasicApplication, T> || std::is_base_of_v<Application, T>;

    namespace Internal
    {
        template<typename BaseT>
        class AppInfoMonitorImpl;
    }
    using BasicAppInfoMonitor = Internal::AppInfoMonitorImpl<BasicObject>;
    using AppInfoMonitor = Internal::AppInfoMonitorImpl<Object>;

    template<typename T>
    constexpr bool IsAppInfoMonitor = std::is_base_of_v<BasicAppInfoMonitor, T> || std::is_base_of_v<AppInfoMonitor, T>;

    namespace Internal
    {
        template<typename BaseT>
        class AppLaunchContextImpl;
    }
    using BasicAppLaunchContext = Internal::AppLaunchContextImpl<BasicObject>;
    using AppLaunchContext = Internal::AppLaunchContextImpl<Object>;

    template<typename T>
    constexpr bool IsAppLaunchContext = std::is_base_of_v<BasicAppLaunchContext, T> || std::is_base_of_v<AppLaunchContext, T>;

    namespace Internal
    {
        template<typename BaseT>
        class ApplicationCommandLineImpl;
    }
    using BasicApplicationCommandLine = Internal::ApplicationCommandLineImpl<BasicObject>;
    using ApplicationCommandLine = Internal::ApplicationCommandLineImpl<Object>;

    template<typename T>
    constexpr bool IsApplicationCommandLine = std::is_base_of_v<BasicApplicationCommandLine, T> || std::is_base_of_v<ApplicationCommandLine, T>;

    namespace Internal
    {
        template<typename BaseT>
        class CancellableImpl;
    }
    using BasicCancellable = Internal::CancellableImpl<BasicObject>;
    using Cancellable = Internal::CancellableImpl<Object>;

    template<typename T>
    constexpr bool IsCancellable = std::is_base_of_v<BasicCancellable, T> || std::is_base_of_v<Cancellable, T>;

    namespace Internal
    {
        template<typename BaseT>
        class CharsetConverterImpl;
    }
    using BasicCharsetConverter = Internal::CharsetConverterImpl<BasicObject>;
    using CharsetConverter = Internal::CharsetConverterImpl<Object>;

    template<typename T>
    constexpr bool IsCharsetConverter = std::is_base_of_v<BasicCharsetConverter, T> || std::is_base_of_v<CharsetConverter, T>;

    namespace Internal
    {
        template<typename BaseT>
        class ResolverImpl;
    }
    using BasicResolver = Internal::ResolverImpl<BasicObject>;
    using Resolver = Internal::ResolverImpl<Object>;

    template<typename T>
    constexpr bool IsResolver = std::is_base_of_v<BasicResolver, T> || std::is_base_of_v<Resolver, T>;

    namespace Internal
    {
        template<typename BaseT>
        class SocketImpl;
    }
    using BasicSocket = Internal::SocketImpl<BasicObject>;
    using Socket = Internal::SocketImpl<Object>;

    template<typename T>
    constexpr bool IsSocket = std::is_base_of_v<BasicSocket, T> || std::is_base_of_v<Socket, T>;

    namespace Internal
    {
        template<typename BaseT>
        class SocketClientImpl;
    }
    using BasicSocketClient = Internal::SocketClientImpl<BasicObject>;
    using SocketClient = Internal::SocketClientImpl<Object>;

    template<typename T>
    constexpr bool IsSocketClient = std::is_base_of_v<BasicSocketClient, T> || std::is_base_of_v<SocketClient, T>;

    namespace Internal
    {
        template<typename BaseT>
        class SocketListenerImpl;
    }
    using BasicSocketListener = Internal::SocketListenerImpl<BasicObject>;
    using SocketListener = Internal::SocketListenerImpl<Object>;

    template<typename T>
    constexpr bool IsSocketListener = std::is_base_of_v<BasicSocketListener, T> || std::is_base_of_v<SocketListener, T>;

    namespace Internal
    {
        template<typename BaseT>
        class SocketServiceImpl;
    }
    using BasicSocketService = Internal::SocketServiceImpl<BasicSocketListener>;
    using SocketService = Internal::SocketServiceImpl<SocketListener>;

    template<typename T>
    constexpr bool IsSocketService = std::is_base_of_v<BasicSocketService, T> || std::is_base_of_v<SocketService, T>;

    namespace Internal
    {
        template<typename BaseT>
        class ThreadedSocketServiceImpl;
    }
    using BasicThreadedSocketService = Internal::ThreadedSocketServiceImpl<BasicSocketService>;
    using ThreadedSocketService = Internal::ThreadedSocketServiceImpl<SocketService>;

    template<typename T>
    constexpr bool IsThreadedSocketService = std::is_base_of_v<BasicThreadedSocketService, T> || std::is_base_of_v<ThreadedSocketService, T>;

    namespace Internal
    {
        template<typename BaseT>
        class SocketControlMessageImpl;
    }
    using BasicSocketControlMessage = Internal::SocketControlMessageImpl<BasicObject>;
    using SocketControlMessage = Internal::SocketControlMessageImpl<Object>;

    template<typename T>
    constexpr bool IsSocketControlMessage = std::is_base_of_v<BasicSocketControlMessage, T> || std::is_base_of_v<SocketControlMessage, T>;

    namespace Internal
    {
        template<typename BaseT>
        class SocketConnectionImpl;
    }
    using BasicSocketConnection = Internal::SocketConnectionImpl<BasicIOStream>;
    using SocketConnection = Internal::SocketConnectionImpl<IOStream>;

    template<typename T>
    constexpr bool IsSocketConnection = std::is_base_of_v<BasicSocketConnection, T> || std::is_base_of_v<SocketConnection, T>;

    namespace Internal
    {
        template<typename BaseT>
        class TcpConnectionImpl;
    }
    using BasicTcpConnection = Internal::TcpConnectionImpl<BasicSocketConnection>;
    using TcpConnection = Internal::TcpConnectionImpl<SocketConnection>;

    template<typename T>
    constexpr bool IsTcpConnection = std::is_base_of_v<BasicTcpConnection, T> || std::is_base_of_v<TcpConnection, T>;

    namespace Internal
    {
        template<typename BaseT>
        class TcpWrapperConnectionImpl;
    }
    using BasicTcpWrapperConnection = Internal::TcpWrapperConnectionImpl<BasicTcpConnection>;
    using TcpWrapperConnection = Internal::TcpWrapperConnectionImpl<TcpConnection>;

    template<typename T>
    constexpr bool IsTcpWrapperConnection = std::is_base_of_v<BasicTcpWrapperConnection, T> || std::is_base_of_v<TcpWrapperConnection, T>;

    namespace Internal
    {
        template<typename BaseT>
        class TaskImpl;
    }
    using BasicTask = Internal::TaskImpl<BasicObject>;
    using Task = Internal::TaskImpl<Object>;

    template<typename T>
    constexpr bool IsTask = std::is_base_of_v<BasicTask, T> || std::is_base_of_v<Task, T>;

    namespace Internal
    {
        template<typename BaseT>
        class TlsCertificateImpl;
    }
    using BasicTlsCertificate = Internal::TlsCertificateImpl<BasicObject>;
    using TlsCertificate = Internal::TlsCertificateImpl<Object>;

    template<typename T>
    constexpr bool IsTlsCertificate = std::is_base_of_v<BasicTlsCertificate, T> || std::is_base_of_v<TlsCertificate, T>;

    namespace Internal
    {
        template<typename BaseT>
        class TlsConnectionImpl;
    }
    using BasicTlsConnection = Internal::TlsConnectionImpl<BasicIOStream>;
    using TlsConnection = Internal::TlsConnectionImpl<IOStream>;

    template<typename T>
    constexpr bool IsTlsConnection = std::is_base_of_v<BasicTlsConnection, T> || std::is_base_of_v<TlsConnection, T>;



}

#endif
