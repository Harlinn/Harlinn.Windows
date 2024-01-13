#pragma once //HWMGstTraits.h
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

#include <glib/HWMgtraits.h>

namespace Harlinn::Media::GLib
{
    template<>
    struct ObjectTraits<GstObject> : std::true_type
    {
        using WrappedType = GstObject;

        static bool IsFloating( WrappedType* wrapped )
        {
            return g_object_is_floating( wrapped ) != 0;
        }

        static WrappedType* RefSink( WrappedType* wrapped )
        {
            return reinterpret_cast< WrappedType* >( gst_object_ref_sink( wrapped ) );
        }

        static WrappedType* TakeRef( WrappedType* wrapped )
        {
            return reinterpret_cast< WrappedType* >( g_object_take_ref( wrapped ) );
        }

        static WrappedType* Ref( WrappedType* wrapped )
        {
            return reinterpret_cast< WrappedType* >( gst_object_ref( wrapped ) );
        }


        static void Unref( WrappedType* wrapped )
        {
            gst_object_unref( wrapped );
        }
    };

    template<>
    struct ObjectTraits<GstMiniObject> : std::true_type
    {
        using WrappedType = GstMiniObject;

        static constexpr bool IsFloating( WrappedType* wrapped )
        {
            return false;
        }

        static WrappedType* RefSink( WrappedType* wrapped )
        {
            return wrapped;
        }

        static WrappedType* TakeRef( WrappedType* wrapped )
        {
            return Ref( wrapped );
        }

        static WrappedType* Ref( WrappedType* wrapped )
        {
            return reinterpret_cast< WrappedType* >( gst_mini_object_ref( wrapped ) );
        }


        static void Unref( WrappedType* wrapped )
        {
            gst_mini_object_unref( wrapped );
        }
    };

    template<>
    struct ObjectTraits<GstAtomicQueue> : public SimpleObjectTraits< ObjectTraits<GstAtomicQueue>, GstAtomicQueue >
    {
        static WrappedType* Ref( WrappedType* wrapped )
        {
            gst_atomic_queue_ref( wrapped );
            return wrapped;
        }

        static void Unref( WrappedType* wrapped )
        {
            gst_atomic_queue_unref( wrapped );
        }
    };

    template<>
    struct ObjectTraits<GstMemory> : public SimpleObjectTraits< ObjectTraits<GstMemory>, GstMemory >
    {
        static WrappedType* Ref( WrappedType* wrapped )
        {
            gst_memory_ref( wrapped );
            return wrapped;
        }

        static void Unref( WrappedType* wrapped )
        {
            gst_memory_unref( wrapped );
        }
    };

    template<>
    struct ObjectTraits<GstStructure> : public SimpleObjectTraits< ObjectTraits<GstStructure>, GstStructure >
    {
        static void Unref( WrappedType* wrapped )
        {
            gst_structure_free( wrapped );
        }
    };


}
