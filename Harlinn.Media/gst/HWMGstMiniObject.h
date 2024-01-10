#pragma once
#ifndef HARLINN_MEDIA_GST_HWMGSTMINIOBJECT_H_
#define HARLINN_MEDIA_GST_HWMGSTMINIOBJECT_H_

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
#include "HWMGstConstants.h"

namespace Harlinn::Media::GStreamer
{
#define HWM_GSTMINIOBJECT_IMPLEMENT_STANDARD_MEMBERS( TypeName, WrappedTypeName ) \
    using WrappedType = WrappedTypeName; \
    TypeName( ) = default; \
    TypeName( WrappedType* impl ) \
        : Base( reinterpret_cast< Base::WrappedType* >( impl ) ) \
    { \
    } \
    TypeName( TypeName&& other ) noexcept \
        : Base( std::move( other ) ) \
    { \
    } \
    TypeName& operator = ( TypeName&& other ) noexcept \
    { \
        Base::operator=( std::move( other ) ); \
        return *this; \
    } \
    void Assign( WrappedType* impl ) noexcept \
    { \
        Base::Assign( reinterpret_cast< Base::WrappedType* >( impl ) ); \
    } \
    TypeName& operator = ( WrappedType* impl ) noexcept \
    { \
        Assign( impl ); \
        return *this; \
    } \
    WrappedType* get( ) const \
    { \
        return reinterpret_cast< WrappedType* >( Base::get( ) ); \
    } \
    WrappedType* Detach( ) \
    { \
        return reinterpret_cast< WrappedType* >( Base::Detach( ) ); \
    } \
    operator WrappedType* ( ) const \
    { \
        return reinterpret_cast< WrappedType* >( Base::get( ) ); \
    }



    class MiniObject
    {
    public:
        using WrappedType = GstMiniObject;
    private:
        WrappedType* impl_ = nullptr;
    public:
        
        MiniObject( ) = default;
        MiniObject( WrappedType* impl )
            : impl_( impl )
        {
        }
        MiniObject( const MiniObject& other ) = delete;
        MiniObject( MiniObject&& other ) noexcept
            : impl_( other.impl_ )
        {
            other.impl_ = nullptr;
        }

        ~MiniObject( )
        {
            if ( impl_ )
            {
                gst_mini_object_unref( impl_ );
            }
        }

        MiniObject& operator = ( const MiniObject& other ) = delete;

        MiniObject& operator = ( MiniObject&& other ) noexcept
        {
            std::swap( impl_, other.impl_ );
            return *this;
        }

        void Assign( WrappedType* impl ) noexcept
        {
            if ( impl_ != impl )
            {
                if ( impl_ )
                {
                    g_object_unref( impl_ );
                }
                impl_ = impl;
            }
        }


        MiniObject& operator = ( WrappedType* impl ) noexcept
        {
            Assign( impl );
            return *this;
        }

        WrappedType* get( ) const
        {
            return impl_;
        }

        explicit operator bool( ) const noexcept
        {
            return impl_ != nullptr;
        }

        WrappedType* Detach( )
        {
            WrappedType* tmp = impl_;
            impl_ = nullptr;
            return tmp;
        }

        operator WrappedType* ( ) const
        {
            return impl_;
        }
    };
}

#endif

