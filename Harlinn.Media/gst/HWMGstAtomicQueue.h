#pragma once 
#ifndef HARLINN_MEDIA_HWMGSTATOMICQUEUE_H_
#define HARLINN_MEDIA_HWMGSTATOMICQUEUE_H_
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

#include "HWMGstMemory.h"

namespace Harlinn::Media::GStreamer
{

    

    class BasicAtomicQueue
    {
    public:
        using WrappedType = GstAtomicQueue;
        using WrappedTraits = GLib::ObjectTraits<GstAtomicQueue>;
    private:
        WrappedType* wrapped_ = nullptr;
    public:
        BasicAtomicQueue( ) = default;
        explicit BasicAtomicQueue( WrappedType* wrapped, GLib::ReferenceType referenceType = GLib::ReferenceType::None )
            : wrapped_( wrapped )
        {
            if ( wrapped_ )
            {
                switch ( referenceType )
                {
                    case GLib::ReferenceType::Ref:
                        WrappedTraits::Ref( wrapped_ );
                        break;
                    case GLib::ReferenceType::RefSink:
                        WrappedTraits::RefSink( wrapped_ );
                        break;
                    case GLib::ReferenceType::TakeRef:
                        WrappedTraits::TakeRef( wrapped_ );
                        break;
                }
            }
        }

        BasicAtomicQueue( const BasicAtomicQueue& other ) = delete;
        BasicAtomicQueue( BasicAtomicQueue&& other ) noexcept
            : wrapped_( other.wrapped_ )
        {
            other.wrapped_ = nullptr;
        }
        BasicAtomicQueue& operator = ( const BasicAtomicQueue& other ) = delete;
        BasicAtomicQueue& operator = ( BasicAtomicQueue&& other ) noexcept
        {
            std::swap( wrapped_, other.wrapped_ );
            return *this;
        }

        explicit operator bool( ) const
        {
            return wrapped_ != nullptr;
        }

        WrappedType* get( ) const
        {
            return wrapped_;
        }

        WrappedType* Detach( )
        {
            auto tmp = wrapped_;
            wrapped_ = nullptr;
            return tmp;
        }

        operator WrappedType* ( ) const
        {
            return wrapped_;
        }

        void Push( gpointer data ) const
        {
            gst_atomic_queue_push( get( ), data );
        }

        gpointer Pop( ) const
        {
            return gst_atomic_queue_pop( get( ) );
        }

        gpointer Peek( ) const
        {
            return gst_atomic_queue_peek( get( ) );
        }

        UInt32 Length( ) const
        {
            return gst_atomic_queue_length( get( ) );
        }

    };

    class AtomicQueue : public BasicAtomicQueue
    {
    public:
        using Base = BasicAtomicQueue;

        AtomicQueue( ) = default;
        explicit AtomicQueue( WrappedType* wrapped, GLib::ReferenceType referenceType = GLib::ReferenceType::None )
            : Base( wrapped, referenceType )
        { }
        ~AtomicQueue( )
        {
            auto tmp = Detach( );
            if ( tmp )
            {
                WrappedTraits::Unref( tmp );
            }
        }


        AtomicQueue& operator = ( AtomicQueue&& other ) noexcept
        {
            Base::operator = ( std::move( other ) );
            return *this;
        }

    };

}

#endif
