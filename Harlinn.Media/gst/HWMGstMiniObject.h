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
#include "HWMGstTraits.h"
#include <glib/HWMgmemory.h>

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

    class MiniObject;

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

        constexpr bool operator == ( nullptr_t ) const noexcept
        {
            return impl_ == nullptr;
        }
        constexpr bool operator != ( nullptr_t ) const noexcept
        {
            return impl_ != nullptr;
        }

        constexpr bool operator == ( const WrappedType* other ) const noexcept
        {
            return impl_ == other;
        }
        constexpr bool operator != ( const WrappedType* other ) const noexcept
        {
            return impl_ != other;
        }

        bool Lock( GstLockFlags flags ) const
        {
            return gst_mini_object_lock( get( ), flags ) != 0;
        }

        void Unlock( GstLockFlags flags ) const
        {
            gst_mini_object_unlock( get( ), flags );
        }

        bool IsWritable( ) const
        {
            return gst_mini_object_is_writable( get( ) );
        }

        template<typename T>
            requires std::is_base_of_v<MiniObject,T>
        T MakeWritable( ) const
        {
            auto obj = reinterpret_cast< typename T::WrappedType* >( gst_mini_object_make_writable( get() ) );
            if ( obj )
            {
                return T( obj );
            }
            return {};
        }

        template<typename T>
            requires std::is_base_of_v<MiniObject, T>
        T Copy( ) const
        {
            auto obj = reinterpret_cast< typename T::WrappedType* >( gst_mini_object_copy( get( ) ) );
            if ( obj )
            {
                return T( obj );
            }
            return {};
        }

        void AddParent( GstMiniObject* parent ) const
        {
            gst_mini_object_add_parent( get(), parent );
        }

        void AddParent( const BasicMiniObject& parent ) const
        {
            gst_mini_object_add_parent( get( ), parent.get() );
        }

        void RemoveParent( GstMiniObject* parent ) const
        {
            gst_mini_object_remove_parent( get( ), parent );
        }
        void RemoveParent( const BasicMiniObject& parent ) const
        {
            gst_mini_object_remove_parent( get( ), parent.get() );
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

    static_assert( sizeof( BasicMiniObject ) == sizeof( GstMiniObject* ) );
    static_assert( sizeof( MiniObject ) == sizeof( GstMiniObject* ) );

}

#endif

