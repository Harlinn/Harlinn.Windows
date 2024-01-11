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
#include "HWMGstMemory.h"

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



    class BasicMiniObject
    {
    public:
        using WrappedType = GstMiniObject;
    private:
        WrappedType* impl_ = nullptr;
    public:
        
        BasicMiniObject( ) = default;
        explicit BasicMiniObject( WrappedType* impl )
            : impl_( impl )
        {
        }
        BasicMiniObject( const BasicMiniObject& other ) = delete;
        BasicMiniObject( BasicMiniObject&& other ) noexcept
            : impl_( other.impl_ )
        {
            other.impl_ = nullptr;
        }

        

        BasicMiniObject& operator = ( const BasicMiniObject& other ) = delete;

        BasicMiniObject& operator = ( BasicMiniObject&& other ) noexcept
        {
            std::swap( impl_, other.impl_ );
            return *this;
        }
    protected:
        template<bool unref, typename T, typename WrappedTraitsT = GLib::ObjectTraits<T>>
            requires GLib::ObjectTraits_v<T>
        void Assign( T* impl ) noexcept
        {
            if ( impl_ != impl )
            {
                if constexpr ( unref )
                {
                    if ( impl_ )
                    {
                        WrappedTraitsT::Unref( impl_ );
                    }
                }
                impl_ = impl;
            }
        }
    public:
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

    class MiniObject : public BasicMiniObject
    {
    public:
        using Base = BasicMiniObject;

        MiniObject( ) = default;
        explicit MiniObject( WrappedType* impl )
            : Base( impl )
        {
        }

        MiniObject( MiniObject&& other ) noexcept
            : Base( std::move( other ) )
        {
        }

        ~MiniObject( )
        {
            auto tmp = Detach( );
            if ( tmp )
            {
                gst_mini_object_unref( tmp );
            }
        }

        MiniObject& operator = ( MiniObject&& other ) noexcept
        {
            Base::operator=( std::move( other ) ); 
            return *this;
        }

        MiniObject& operator = ( WrappedType* impl ) noexcept
        {
            Assign<true, WrappedType>( impl );
            return *this;
        }

    };

}

#endif

