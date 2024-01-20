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
    struct ObjectTraits<GstObject> : DerivedObjectTraits<GstObject, GObject >
    {
        static WrappedType* RefSink( WrappedType* wrapped )
        {
            return reinterpret_cast< WrappedType* >( gst_object_ref_sink( wrapped ) );
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
    struct ObjectTraits<GstAllocator> : public DerivedObjectTraits< GstAllocator, GstObject >
    {

    };

    template<>
    struct ObjectTraits<GstBufferPool> : public DerivedObjectTraits< GstBufferPool, GstObject>
    {

    };

    template<>
    struct ObjectTraits<GstBus> : public DerivedObjectTraits< GstBus, GstObject>
    {

    };

    template<>
    struct ObjectTraits<GstClock> : public DerivedObjectTraits<GstClock, GstObject>
    {

    };

    template<>
    struct ObjectTraits<GstSystemClock> : public DerivedObjectTraits<GstSystemClock, GstClock>
    {

    };

    template<>
    struct ObjectTraits<GstControlBinding> : public DerivedObjectTraits<GstControlBinding, GstObject>
    {

    };

    template<>
    struct ObjectTraits<GstControlSource> : public DerivedObjectTraits<GstControlSource, GstObject>
    {

    };

    template<>
    struct ObjectTraits<GstDevice> : public DerivedObjectTraits<GstDevice, GstObject>
    {

    };

    template<>
    struct ObjectTraits<GstDeviceMonitor> : public DerivedObjectTraits<GstDeviceMonitor, GstObject>
    {

    };

    template<>
    struct ObjectTraits<GstDeviceProvider> : public DerivedObjectTraits<GstDeviceProvider, GstObject>
    {

    };

    template<>
    struct ObjectTraits<GstElement> : public DerivedObjectTraits<GstElement, GstObject>
    {

    };

    template<>
    struct ObjectTraits<GstBin> : public DerivedObjectTraits< GstBin, GstElement>
    {

    };

    template<>
    struct ObjectTraits<GstPipeline> : public DerivedObjectTraits<GstPipeline, GstBin>
    {

    };

    template<>
    struct ObjectTraits<GstPad> : public DerivedObjectTraits<GstPad, GstObject>
    {

    };

    template<>
    struct ObjectTraits<GstProxyPad> : public DerivedObjectTraits<GstProxyPad, GstPad>
    {

    };

    template<>
    struct ObjectTraits<GstGhostPad> : public DerivedObjectTraits<GstGhostPad, GstProxyPad>
    {

    };

    template<>
    struct ObjectTraits<GstPadTemplate> : public DerivedObjectTraits<GstPadTemplate, GstObject>
    {

    };

    template<>
    struct ObjectTraits<GstPlugin> : public DerivedObjectTraits<GstPlugin, GstObject>
    {

    };

    template<>
    struct ObjectTraits<GstPluginFeature> : public DerivedObjectTraits<GstPluginFeature, GstObject>
    {

    };

    template<>
    struct ObjectTraits<GstDeviceProviderFactory> : public DerivedObjectTraits<GstDeviceProviderFactory, GstPluginFeature>
    {

    };

    template<>
    struct ObjectTraits<GstDynamicTypeFactory> : public DerivedObjectTraits<GstDynamicTypeFactory, GstPluginFeature>
    {

    };

    template<>
    struct ObjectTraits<GstElementFactory> : public DerivedObjectTraits<GstElementFactory, GstPluginFeature>
    {

    };

    template<>
    struct ObjectTraits<GstTracerFactory> : public DerivedObjectTraits<GstTracerFactory, GstPluginFeature>
    {

    };

    template<>
    struct ObjectTraits<GstTypeFindFactory> : public DerivedObjectTraits<GstTypeFindFactory, GstPluginFeature>
    {

    };

    template<>
    struct ObjectTraits<GstRegistry> : public DerivedObjectTraits<GstRegistry, GstObject>
    {

    };

    template<>
    struct ObjectTraits<GstStreamCollection> : public DerivedObjectTraits<GstStreamCollection, GstObject>
    {

    };

    template<>
    struct ObjectTraits<GstStream> : public DerivedObjectTraits<GstStream, GstObject>
    {

    };

    template<>
    struct ObjectTraits<GstTaskPool> : public DerivedObjectTraits<GstTaskPool, GstObject>
    {

    };

    template<>
    struct ObjectTraits<GstSharedTaskPool> : public DerivedObjectTraits<GstSharedTaskPool, GstTaskPool>
    {

    };

    template<>
    struct ObjectTraits<GstTracer> : public DerivedObjectTraits<GstTracer, GstObject>
    {

    };

    template<>
    struct ObjectTraits<GstTracerRecord> : public DerivedObjectTraits<GstTracerRecord, GstObject>
    {

    };

    template<>
    struct ObjectTraits<GstMiniObject> : std::true_type
    {
        static constexpr bool IsDerived = false;
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
    struct ObjectTraits<GstBuffer> : public DerivedObjectTraits< GstBuffer, GstMiniObject>
    {

    };

    template<>
    struct ObjectTraits<GstCaps> : public DerivedObjectTraits<GstCaps, GstMiniObject>
    {

    };

    template<>
    struct ObjectTraits<GstEvent> : public DerivedObjectTraits<GstEvent, GstMiniObject>
    {

    };

    template<>
    struct ObjectTraits<GstMemory> : public DerivedObjectTraits<GstMemory, GstMiniObject >
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
    struct ObjectTraits<GstMessage> : public DerivedObjectTraits<GstMessage, GstMiniObject>
    {

    };

    template<>
    struct ObjectTraits<GstPromise> : public DerivedObjectTraits<GstPromise, GstMiniObject>
    {

    };

    template<>
    struct ObjectTraits<GstQuery> : public DerivedObjectTraits<GstQuery, GstMiniObject>
    {

    };

    template<>
    struct ObjectTraits<GstSample> : public DerivedObjectTraits<GstSample, GstMiniObject>
    {
        static WrappedType* Ref( WrappedType* wrapped )
        {
            return gst_sample_ref( wrapped );
        }
        static void Unref( WrappedType* wrapped )
        {
            gst_sample_unref( wrapped );
        }
    };


    template<>
    struct ObjectTraits<GstTagList> : public DerivedObjectTraits<GstTagList, GstMiniObject>
    {

    };

    template<>
    struct ObjectTraits<GstUri> : public DerivedObjectTraits<GstUri, GstMiniObject>
    {

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
    struct ObjectTraits<GstBufferList> : public SimpleObjectTraits< ObjectTraits<GstBufferList>, GstBufferList >
    {
        static WrappedType* Ref( WrappedType* wrapped )
        {
            return gst_buffer_list_ref( wrapped );
        }

        static void Unref( WrappedType* wrapped )
        {
            gst_buffer_list_unref( wrapped );
        }
    };

    template<>
    struct ObjectTraits<GstCapsFeatures> : public SimpleObjectTraits< ObjectTraits<GstCapsFeatures>, GstCapsFeatures >
    {
        static void Unref( WrappedType* wrapped )
        {
            gst_caps_features_free( wrapped );
        }
    };

    template<>
    struct ObjectTraits<GstContext> : public SimpleObjectTraits< ObjectTraits<GstContext>, GstContext>
    {
        static WrappedType* Ref( WrappedType* wrapped )
        {
            return gst_context_ref( wrapped );
        }

        static void Unref( WrappedType* wrapped )
        {
            gst_context_unref( wrapped );
        }
    };


    

    


    template<>
    struct ObjectTraits<GstIterator> : public SimpleObjectTraits< ObjectTraits<GstIterator>, GstIterator>
    {
        static void Unref( WrappedType* wrapped )
        {
            gst_iterator_free( wrapped );
        }
    };



    /*
    template<>
    struct ObjectTraits<GstParamArray> : public DerivedObjectTraits<GstParamArray, GParamSpec>
    {

    };

    template<>
    struct ObjectTraits<GstParamFraction> : public DerivedObjectTraits<GstParamFraction, GParamSpec>
    {

    };
    */

    template<>
    struct ObjectTraits<GstParseContext> : public SimpleObjectTraits< ObjectTraits<GstParseContext>, GstParseContext >
    {
        static void Unref( WrappedType* wrapped )
        {
            gst_parse_context_free( wrapped );
        }
    };

    



    template<>
    struct ObjectTraits<GstPoll> : public SimpleObjectTraits< ObjectTraits<GstPoll>, GstPoll>
    {
        static void Unref( WrappedType* wrapped )
        {
            gst_poll_free( wrapped );
        }
    };


    template<>
    struct ObjectTraits<GstSegment> : public SimpleObjectTraits< ObjectTraits<GstSegment>, GstSegment >
    {
        static void Unref( WrappedType* wrapped )
        {
            gst_segment_free( wrapped );
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
