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

    template<>
    struct ObjectTraits<GObject> : std::true_type
    {
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
    struct ObjectTraits<GBinding> : public SimpleObjectTraits< ObjectTraits<GBinding>, GBinding >
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
    struct ObjectTraits<GParamSpec> : public SimpleObjectTraits< ObjectTraits<GParamSpec>, GParamSpec >
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
    struct ObjectTraits<GstIterator> : public SimpleObjectTraits< ObjectTraits<GstIterator>, GstIterator >
    {
        static void Unref( WrappedType* wrapped )
        {
            gst_iterator_free( wrapped );
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


}

#endif


