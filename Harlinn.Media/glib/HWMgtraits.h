#pragma once 
#ifndef HARLINN_MEDIA_GLIB_HWMGTRAITS_H_
#define HARLINN_MEDIA_GLIB_HWMGTRAITS_H_
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

#include <HWMdef.h>

namespace Harlinn::Media::GLib
{
    template<typename T>
    struct ObjectTraits : std::false_type
    {
        using WrappedType = void;
    };


    template<typename DerivedTraitsT, typename T>
    struct SimpleObjectTraits : public std::true_type
    {
        using DerivedTraitsType = DerivedTraitsT;
        using WrappedType = T;

        static constexpr bool IsFloating( WrappedType* wrapped )
        {
            return false;
        }

        static constexpr WrappedType* RefSink( WrappedType* wrapped )
        {
            return wrapped;
        }

        static constexpr WrappedType* TakeRef( WrappedType* wrapped )
        {
            return DerivedTraitsType::Ref( wrapped );
        }

        static constexpr WrappedType* Ref( WrappedType* wrapped )
        {
            return wrapped;
        }


        static constexpr void Unref( WrappedType* wrapped )
        {

        }
    };

    struct GObjectTraits : std::true_type
    {
        static constexpr bool IsDerived = false;
        using WrappedType = GObject;

        static bool IsFloating( WrappedType* wrapped )
        {
            return g_object_is_floating( wrapped ) != 0;
        }

        static WrappedType* RefSink( WrappedType* wrapped )
        {
            return reinterpret_cast< WrappedType* >( g_object_ref_sink( wrapped ) );
        }

        static WrappedType* TakeRef( WrappedType* wrapped )
        {
            return reinterpret_cast< WrappedType* >( g_object_take_ref( wrapped ) );
        }

        static WrappedType* Ref( WrappedType* wrapped )
        {
            return reinterpret_cast< WrappedType* >( g_object_ref( wrapped ) );
        }

        static void Unref( WrappedType* wrapped )
        {
            g_object_unref( wrapped );
        }

    };

    

    template<>
    struct ObjectTraits<GObject> : public GObjectTraits
    {
        
    };

    template<typename DerivedT, typename BaseT>
    struct DerivedObjectTraits : public ObjectTraits<BaseT>
    {
        static constexpr bool IsDerived = true;
        using WrappedType = DerivedT;
        using BaseTraits = ObjectTraits<BaseT>;
        using BaseWrappedType = typename BaseTraits::WrappedType;

        static bool IsFloating( WrappedType* wrapped )
        {
            return BaseTraits::IsFloating( reinterpret_cast< BaseWrappedType* >( wrapped ) );
        }

        static WrappedType* RefSink( WrappedType* wrapped )
        {
            return reinterpret_cast< WrappedType* >( BaseTraits::RefSink( reinterpret_cast< BaseWrappedType* >( wrapped ) ) );
        }

        static WrappedType* TakeRef( WrappedType* wrapped )
        {
            return reinterpret_cast< WrappedType* >( BaseTraits::TakeRef( reinterpret_cast< BaseWrappedType* >( wrapped ) ) );
        }

        static WrappedType* Ref( WrappedType* wrapped )
        {
            return reinterpret_cast< WrappedType* >( BaseTraits::Ref( reinterpret_cast< BaseWrappedType* >( wrapped ) ) );
        }

        static void Unref( WrappedType* wrapped )
        {
            BaseTraits::Unref( reinterpret_cast< BaseWrappedType* >( wrapped ) );
        }
    };


    template<>
    struct ObjectTraits<GBinding> : public DerivedObjectTraits<GBinding, GObject >
    {
        static void Unref( WrappedType* wrapped )
        {
            g_binding_unbind( wrapped );
        }
    };



    template<>
    struct ObjectTraits<GClosure> : public SimpleObjectTraits< ObjectTraits<GClosure>, GClosure >
    {
        static WrappedType* RefSink( WrappedType* wrapped )
        {
            if ( wrapped )
            {
                g_closure_ref( wrapped );
                g_closure_sink( wrapped );
            }
            return wrapped;
        }

        static WrappedType* Ref( WrappedType* wrapped )
        {
            return reinterpret_cast< WrappedType* >( g_closure_ref( wrapped ) );
        }

        static void Unref( WrappedType* wrapped )
        {
            g_closure_unref( wrapped );
        }
    };

    template<>
    struct ObjectTraits<GParamSpec> : public DerivedObjectTraits<GParamSpec, GObject >
    {
        static WrappedType* RefSink( WrappedType* wrapped )
        {
            if ( wrapped )
            {
                return g_param_spec_ref_sink( wrapped );
            }
            return wrapped;
        }

        static WrappedType* Ref( WrappedType* wrapped )
        {
            return reinterpret_cast< WrappedType* >( g_param_spec_ref( wrapped ) );
        }

        static void Unref( WrappedType* wrapped )
        {
            g_param_spec_unref( wrapped );
        }
    };

    template<>
    struct ObjectTraits<GParamSpecBoolean> : public DerivedObjectTraits<GParamSpecBoolean, GParamSpec >
    {

    };

    template<>
    struct ObjectTraits<GParamSpecBoxed> : public DerivedObjectTraits<GParamSpecBoxed, GParamSpec >
    {

    };

    template<>
    struct ObjectTraits<GParamSpecChar> : public DerivedObjectTraits<GParamSpecChar, GParamSpec >
    {

    };

    template<>
    struct ObjectTraits<GParamSpecDouble> : public DerivedObjectTraits<GParamSpecDouble, GParamSpec >
    {

    };

    template<>
    struct ObjectTraits<GParamSpecEnum> : public DerivedObjectTraits<GParamSpecEnum, GParamSpec >
    {

    };

    template<>
    struct ObjectTraits<GParamSpecFlags> : public DerivedObjectTraits<GParamSpecFlags, GParamSpec >
    {

    };

    template<>
    struct ObjectTraits<GParamSpecFloat> : public DerivedObjectTraits<GParamSpecFloat, GParamSpec >
    {

    };

    template<>
    struct ObjectTraits<GParamSpecGType> : public DerivedObjectTraits<GParamSpecGType, GParamSpec >
    {

    };

    template<>
    struct ObjectTraits<GParamSpecInt> : public DerivedObjectTraits<GParamSpecInt, GParamSpec >
    {

    };

    template<>
    struct ObjectTraits<GParamSpecInt64> : public DerivedObjectTraits<GParamSpecInt64, GParamSpec >
    {

    };

    template<>
    struct ObjectTraits<GParamSpecLong> : public DerivedObjectTraits<GParamSpecLong, GParamSpec >
    {

    };

    template<>
    struct ObjectTraits<GParamSpecObject> : public DerivedObjectTraits<GParamSpecObject, GParamSpec >
    {

    };

    template<>
    struct ObjectTraits<GParamSpecOverride> : public DerivedObjectTraits<GParamSpecOverride, GParamSpec >
    {

    };

    template<>
    struct ObjectTraits<GParamSpecParam> : public DerivedObjectTraits<GParamSpecParam, GParamSpec >
    {

    };

    template<>
    struct ObjectTraits<GParamSpecPointer> : public DerivedObjectTraits<GParamSpecPointer, GParamSpec >
    {

    };

    template<>
    struct ObjectTraits<GParamSpecString> : public DerivedObjectTraits<GParamSpecString, GParamSpec >
    {

    };

    template<>
    struct ObjectTraits<GParamSpecUChar> : public DerivedObjectTraits<GParamSpecUChar, GParamSpec >
    {

    };

    template<>
    struct ObjectTraits<GParamSpecUInt> : public DerivedObjectTraits<GParamSpecUInt, GParamSpec >
    {

    };

    template<>
    struct ObjectTraits<GParamSpecUInt64> : public DerivedObjectTraits<GParamSpecUInt64, GParamSpec >
    {

    };

    template<>
    struct ObjectTraits<GParamSpecULong> : public DerivedObjectTraits<GParamSpecULong, GParamSpec >
    {

    };

    template<>
    struct ObjectTraits<GParamSpecUnichar> : public DerivedObjectTraits<GParamSpecUnichar, GParamSpec >
    {

    };

    template<>
    struct ObjectTraits<GParamSpecValueArray> : public DerivedObjectTraits<GParamSpecValueArray, GParamSpec >
    {

    };

    template<>
    struct ObjectTraits<GParamSpecVariant> : public DerivedObjectTraits<GParamSpecVariant, GParamSpec >
    {

    };


    template<>
    struct ObjectTraits<GMainContext> : public SimpleObjectTraits< ObjectTraits<GMainContext>, GMainContext >
    {
        static WrappedType* Ref( WrappedType* wrapped )
        {
            return reinterpret_cast< WrappedType* >( g_main_context_ref( wrapped ) );
        }

        static void Unref( WrappedType* wrapped )
        {
            g_main_context_unref( wrapped );
        }
    };

    template<>
    struct ObjectTraits<GMainLoop> : public SimpleObjectTraits< ObjectTraits<GMainLoop>, GMainLoop >
    {
        static WrappedType* Ref( WrappedType* wrapped )
        {
            return reinterpret_cast< WrappedType* >( g_main_loop_ref( wrapped ) );
        }

        static void Unref( WrappedType* wrapped )
        {
            g_main_loop_unref( wrapped );
        }
    };

    template<>
    struct ObjectTraits<GSource> : public SimpleObjectTraits< ObjectTraits<GSource>, GSource >
    {
        static WrappedType* Ref( WrappedType* wrapped )
        {
            return reinterpret_cast< WrappedType* >( g_source_ref( wrapped ) );
        }

        static void Unref( WrappedType* wrapped )
        {
            g_source_unref( wrapped );
        }
    };

    template<>
    struct ObjectTraits<GThread> : public SimpleObjectTraits< ObjectTraits<GThread>, GThread >
    {
        static WrappedType* Ref( WrappedType* wrapped )
        {
            return reinterpret_cast< WrappedType* >( g_thread_ref( wrapped ) );
        }

        static void Unref( WrappedType* wrapped )
        {
            g_thread_unref( wrapped );
        }
    };






    template<typename T>
    constexpr bool ObjectTraits_v = ObjectTraits<T>::value;


    template<>
    struct ObjectTraits<GInputStream> : public DerivedObjectTraits<GInputStream, GObject>
    {

    };

    template<>
    struct ObjectTraits<GFileInputStream> : public DerivedObjectTraits<GFileInputStream, GInputStream>
    {

    };

    template<>
    struct ObjectTraits<GFilterInputStream> : public DerivedObjectTraits<GFilterInputStream, GInputStream>
    {

    };

    template<>
    struct ObjectTraits<GBufferedInputStream> : public DerivedObjectTraits<GBufferedInputStream, GFilterInputStream >
    {

    };

    template<>
    struct ObjectTraits<GDataInputStream> : public DerivedObjectTraits<GDataInputStream, GBufferedInputStream>
    {

    };

    template<>
    struct ObjectTraits<GConverterInputStream> : public DerivedObjectTraits<GConverterInputStream, GFilterInputStream >
    {

    };

    template<>
    struct ObjectTraits<GMemoryInputStream> : public DerivedObjectTraits<GMemoryInputStream, GInputStream>
    {

    };

    template<>
    struct ObjectTraits<GOutputStream> : public DerivedObjectTraits<GOutputStream, GObject>
    {

    };

    template<>
    struct ObjectTraits<GFileOutputStream> : public DerivedObjectTraits<GFileOutputStream, GOutputStream>
    {

    };

    template<>
    struct ObjectTraits<GFilterOutputStream> : public DerivedObjectTraits<GFilterOutputStream, GOutputStream>
    {

    };


    template<>
    struct ObjectTraits<GBufferedOutputStream> : public DerivedObjectTraits<GBufferedOutputStream, GFilterOutputStream >
    {

    };



    template<>
    struct ObjectTraits<GConverterOutputStream> : public DerivedObjectTraits<GConverterOutputStream, GFilterOutputStream >
    {

    };

    template<>
    struct ObjectTraits<GDataOutputStream> : public DerivedObjectTraits<GDataOutputStream, GFilterOutputStream>
    {

    };

    template<>
    struct ObjectTraits<GMemoryOutputStream> : public DerivedObjectTraits<GMemoryOutputStream, GOutputStream>
    {

    };


    template<>
    struct ObjectTraits<GSignalGroup> : public DerivedObjectTraits<GSignalGroup, GObject >
    {

    };

    template<>
    struct ObjectTraits<GTypeModule> : public DerivedObjectTraits<GTypeModule, GObject >
    {

    };

    template<>
    struct ObjectTraits<GIOModule> : public DerivedObjectTraits<GIOModule, GTypeModule>
    {

    };

    template<>
    struct ObjectTraits<GAppInfoMonitor> : public DerivedObjectTraits<GAppInfoMonitor, GObject >
    {

    };

    template<>
    struct ObjectTraits<GAppLaunchContext> : public DerivedObjectTraits<GAppLaunchContext, GObject >
    {

    };

    template<>
    struct ObjectTraits<GApplication> : public DerivedObjectTraits<GApplication, GObject >
    {

    };

    template<>
    struct ObjectTraits<GApplicationCommandLine> : public DerivedObjectTraits<GApplicationCommandLine, GObject >
    {

    };

    template<>
    struct ObjectTraits<GBytesIcon> : public DerivedObjectTraits<GBytesIcon, GObject >
    {

    };

    template<>
    struct ObjectTraits<GCancellable> : public DerivedObjectTraits<GCancellable, GObject >
    {

    };

    template<>
    struct ObjectTraits<GCharsetConverter> : public DerivedObjectTraits<GCharsetConverter, GObject >
    {

    };

    template<>
    struct ObjectTraits<GCredentials> : public DerivedObjectTraits<GCredentials, GObject>
    {

    };

    template<>
    struct ObjectTraits<GEmblem> : public DerivedObjectTraits<GEmblem, GObject>
    {

    };

    template<>
    struct ObjectTraits<GEmblemedIcon> : public DerivedObjectTraits<GEmblemedIcon, GObject>
    {

    };

    template<>
    struct ObjectTraits<GFileEnumerator> : public DerivedObjectTraits<GFileEnumerator, GObject>
    {

    };

    template<>
    struct ObjectTraits<GFileIcon> : public DerivedObjectTraits<GFileIcon, GObject>
    {

    };

    template<>
    struct ObjectTraits<GFileInfo> : public DerivedObjectTraits<GFileInfo, GObject>
    {

    };

    template<>
    struct ObjectTraits<GFileMonitor> : public DerivedObjectTraits<GFileMonitor, GObject>
    {

    };

    template<>
    struct ObjectTraits<GFilenameCompleter> : public DerivedObjectTraits<GFilenameCompleter, GObject>
    {

    };

    template<>
    struct ObjectTraits<GInetAddress> : public DerivedObjectTraits<GInetAddress, GObject>
    {

    };

    template<>
    struct ObjectTraits<GInetAddressMask> : public DerivedObjectTraits<GInetAddressMask, GObject>
    {

    };

    template<>
    struct ObjectTraits<GIOStream> : public DerivedObjectTraits<GIOStream, GObject>
    {

    };

    template<>
    struct ObjectTraits<GFileIOStream> : public DerivedObjectTraits<GFileIOStream, GIOStream>
    {

    };

    template<>
    struct ObjectTraits<GSimpleIOStream> : public DerivedObjectTraits<GSimpleIOStream, GIOStream>
    {

    };

    template<>
    struct ObjectTraits<GSocketConnection> : public DerivedObjectTraits<GSocketConnection, GIOStream>
    {

    };

    template<>
    struct ObjectTraits<GTcpConnection> : public DerivedObjectTraits<GTcpConnection, GSocketConnection>
    {

    };

    template<>
    struct ObjectTraits<GTcpWrapperConnection > : public DerivedObjectTraits<GTcpWrapperConnection, GTcpConnection>
    {

    };

    template<>
    struct ObjectTraits<GTlsConnection> : public DerivedObjectTraits<GTlsConnection, GIOStream>
    {

    };

    template<>
    struct ObjectTraits<GListStore> : public DerivedObjectTraits<GListStore, GObject>
    {

    };


    template<>
    struct ObjectTraits<GMountOperation> : public DerivedObjectTraits<GMountOperation, GObject>
    {

    };

    template<>
    struct ObjectTraits<GNetworkService> : public DerivedObjectTraits<GNetworkService, GObject>
    {

    };

    template<>
    struct ObjectTraits<GNotification> : public DerivedObjectTraits<GNotification, GObject>
    {

    };



    template<>
    struct ObjectTraits<GPermission> : public DerivedObjectTraits<GPermission, GObject>
    {

    };

    template<>
    struct ObjectTraits<GSimplePermission> : public DerivedObjectTraits<GSimplePermission, GPermission>
    {

    };

    template<>
    struct ObjectTraits<GPropertyAction> : public DerivedObjectTraits<GPropertyAction, GObject>
    {

    };

    template<>
    struct ObjectTraits<GResolver> : public DerivedObjectTraits<GResolver, GObject>
    {

    };

    template<>
    struct ObjectTraits<GSettings> : public DerivedObjectTraits<GSettings, GObject>
    {

    };

    template<>
    struct ObjectTraits<GSettingsBackend> : public DerivedObjectTraits<GSettingsBackend, GObject>
    {

    };

    template<>
    struct ObjectTraits<GSimpleAction> : public DerivedObjectTraits<GSimpleAction, GObject>
    {

    };

    template<>
    struct ObjectTraits<GSimpleActionGroup> : public DerivedObjectTraits<GSimpleActionGroup, GObject>
    {

    };

    template<>
    struct ObjectTraits<GSimpleAsyncResult> : public DerivedObjectTraits<GSimpleAsyncResult, GObject>
    {

    };

    template<>
    struct ObjectTraits<GSimpleProxyResolver> : public DerivedObjectTraits<GSimpleProxyResolver, GObject>
    {

    };

    template<>
    struct ObjectTraits<GSocket> : public DerivedObjectTraits<GSocket, GObject>
    {

    };

    template<>
    struct ObjectTraits<GSocketAddress > : public DerivedObjectTraits<GSocketAddress, GObject>
    {

    };

    template<>
    struct ObjectTraits<GInetSocketAddress> : public DerivedObjectTraits<GInetSocketAddress, GSocketAddress>
    {

    };

    template<>
    struct ObjectTraits<GProxyAddress> : public DerivedObjectTraits<GProxyAddress, GInetSocketAddress>
    {

    };



    template<>
    struct ObjectTraits<GNativeSocketAddress> : public DerivedObjectTraits<GNativeSocketAddress, GSocketAddress>
    {

    };


    template<>
    struct ObjectTraits<GSocketAddressEnumerator> : public DerivedObjectTraits<GSocketAddressEnumerator, GObject>
    {

    };

    template<>
    struct ObjectTraits<GProxyAddressEnumerator> : public DerivedObjectTraits<GProxyAddressEnumerator, GSocketAddressEnumerator>
    {

    };

    template<>
    struct ObjectTraits<GSocketClient> : public DerivedObjectTraits<GSocketClient, GObject>
    {

    };

    template<>
    struct ObjectTraits<GSocketControlMessage> : public DerivedObjectTraits<GSocketControlMessage, GObject>
    {

    };

    template<>
    struct ObjectTraits<GSocketListener> : public DerivedObjectTraits<GSocketListener, GObject>
    {

    };

    template<>
    struct ObjectTraits<GSocketService> : public DerivedObjectTraits<GSocketService, GSocketListener>
    {

    };

    template<>
    struct ObjectTraits<GThreadedSocketService> : public DerivedObjectTraits<GThreadedSocketService, GSocketService>
    {

    };

    template<>
    struct ObjectTraits<GSubprocess> : public DerivedObjectTraits<GSubprocess, GObject>
    {

    };

    template<>
    struct ObjectTraits<GSubprocessLauncher> : public DerivedObjectTraits<GSubprocessLauncher, GObject>
    {

    };

    template<>
    struct ObjectTraits<GTask> : public DerivedObjectTraits<GTask, GObject>
    {

    };

    template<>
    struct ObjectTraits<GThemedIcon > : public DerivedObjectTraits<GThemedIcon, GObject>
    {

    };

    template<>
    struct ObjectTraits<GTlsCertificate> : public DerivedObjectTraits<GTlsCertificate, GObject>
    {

    };

    template<>
    struct ObjectTraits<GTlsDatabase> : public DerivedObjectTraits<GTlsDatabase, GObject>
    {

    };

    template<>
    struct ObjectTraits<GTlsInteraction> : public DerivedObjectTraits<GTlsInteraction, GObject>
    {

    };

    template<>
    struct ObjectTraits<GTlsPassword> : public DerivedObjectTraits<GTlsPassword, GObject>
    {

    };

    template<>
    struct ObjectTraits<GVfs> : public DerivedObjectTraits<GVfs, GObject>
    {

    };

    template<>
    struct ObjectTraits<GVolumeMonitor> : public DerivedObjectTraits<GVolumeMonitor, GObject>
    {

    };

    template<>
    struct ObjectTraits<GNativeVolumeMonitor> : public DerivedObjectTraits<GNativeVolumeMonitor, GVolumeMonitor>
    {

    };

    template<>
    struct ObjectTraits<GZlibCompressor> : public DerivedObjectTraits<GZlibCompressor, GObject>
    {

    };

    template<>
    struct ObjectTraits<GZlibDecompressor> : public DerivedObjectTraits<GZlibDecompressor, GObject>
    {

    };


    

    

    






}

#endif


