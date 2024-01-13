#pragma once 
#ifndef HARLINN_MEDIA_HWMGSTALLOCATOR_H_
#define HARLINN_MEDIA_HWMGSTALLOCATOR_H_
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

#include "HWMGstObject.h"
#include "HWMGstBuffer.h"

namespace Harlinn::Media::GStreamer
{
    class AllocationParams : public GstAllocationParams
    {
    public:
        using Base = GstAllocationParams;
        AllocationParams( )
            : Base{}
        {
            gst_allocation_params_init( this );
        }
    };


    namespace Internal
    {
        template<typename BaseT>
        class AllocatorImpl : public BaseT
        {
        public:
            using Base = BaseT;
            HWM_GOBJECT_IMPLEMENT_STANDARD_MEMBERS( AllocatorImpl, GstAllocator )

            GStreamer::Buffer AllocateBuffer( size_t size, const GstAllocationParams* params ) const
            {
                auto buffer = gst_buffer_new_allocate( get( ), size, const_cast< GstAllocationParams* >(params) );
                if ( buffer )
                {
                    return GStreamer::Buffer( buffer );
                }
                return {};
            }
            GStreamer::Buffer AllocateBuffer( size_t size, const GstAllocationParams& params ) const
            {
                return AllocateBuffer( size, &params );
            }

        };

        template<typename BaseT>
        inline BasicAllocator MemoryImpl<BaseT>::Allocator( GLib::ReferenceType referenceType ) const
        {
            return BasicAllocator( get( )->allocator, referenceType );
        }

        

    }

    

}

#endif
