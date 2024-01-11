#pragma once
#ifndef HARLINN_MEDIA_GLIB_GOBJECT_HWMGOBJECT_H_
#define HARLINN_MEDIA_GLIB_GOBJECT_HWMGOBJECT_H_

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

#include "HWMgtype.h"
#include "HWMgvalue.h"
#include "HWMgbinding.h"

namespace Harlinn::Media::GLib
{
    class BasicObject
    {
    public:
        using WrappedType = void;
    private:
        GObject* wrapped_ = nullptr;
    public:
        BasicObject( ) = default;
    
        template<typename T, typename WrappedTraitsT = ObjectTraits<T>>
            requires ObjectTraits_v<T>
        explicit BasicObject( T* wrapped, ReferenceType referenceType = ReferenceType::None )
            : wrapped_( reinterpret_cast< GObject* >( wrapped ) )
        {
            if ( wrapped_ )
            {
                using WrappedTraits = WrappedTraitsT;
                switch ( referenceType )
                {
                    case ReferenceType::Ref:
                        WrappedTraits::Ref( reinterpret_cast< T* >( wrapped_ ) );
                        break;
                    case ReferenceType::RefSink:
                        WrappedTraits::RefSink( reinterpret_cast< T* >( wrapped_ ) );
                        break;
                    case ReferenceType::TakeRef:
                        WrappedTraits::TakeRef( reinterpret_cast< T* >( wrapped_ ) );
                        break;
                }
            }
        }
    
        BasicObject( const BasicObject& other ) = delete;
        BasicObject( BasicObject&& other ) noexcept
            : wrapped_( other.wrapped_ )
        {
            other.wrapped_ = nullptr;
        }


        BasicObject& operator = ( const BasicObject& other ) = delete;

        BasicObject& operator = ( BasicObject&& other ) noexcept
        {
            std::swap( wrapped_, other.wrapped_ );
            return *this;
        }
    protected:
        template<bool unref, typename T, typename WrappedTraitsT = ObjectTraits<T>>
            requires ObjectTraits_v<T>
        void Assign( T* wrapped, ReferenceType referenceType = ReferenceType::None ) noexcept
        {
            if ( reinterpret_cast< T* >( wrapped_ ) != wrapped )
            {
                using WrappedTraits = WrappedTraitsT;
                if constexpr ( unref )
                {
                    if ( wrapped_ )
                    {
                        WrappedTraits::Unref( reinterpret_cast< T* >( wrapped_ ) );
                    }
                }
                wrapped_ = reinterpret_cast<GObject*>( wrapped );
                if ( wrapped_ )
                {
                    using WrappedTraits = WrappedTraitsT;
                    switch ( referenceType )
                    {
                        case ReferenceType::Ref:
                            WrappedTraits::Ref( reinterpret_cast< T* >( wrapped_ ) );
                            break;
                        case ReferenceType::RefSink:
                            WrappedTraits::RefSink( reinterpret_cast< T* >( wrapped_ ) );
                            break;
                        case ReferenceType::TakeRef:
                            WrappedTraits::TakeRef( reinterpret_cast< T* >( wrapped_ ) );
                            break;
                    }
                }
            }
        }
    public:
        [[nodiscard]]
        GObject* get( ) const
        {
            return reinterpret_cast< GObject* >( wrapped_ );
        }

        explicit operator bool( ) const noexcept
        {
            return wrapped_ != nullptr;
        }

        [[nodiscard]]
        GObject* Detach( )
        {
            auto tmp = reinterpret_cast< GObject* >( wrapped_ );
            wrapped_ = nullptr;
            return tmp;
        }

        operator GObject* ( ) const
        {
            return reinterpret_cast< GObject* >( wrapped_ );
        }

        void AddToggleRef( GToggleNotify notify, gpointer userData = nullptr ) const
        {
            g_object_add_toggle_ref( get( ), notify, userData );
        }

        void AddWeakPointer( gpointer* weakPointerLocation ) const
        {
            g_object_add_weak_pointer( get( ), weakPointerLocation );
        }


        void GetProperty( const char* propertyName, GValue* value ) const
        {
            g_object_get_property( get( ), propertyName, value );
        }
        void GetProperty( const char* propertyName, Value& value ) const
        {
            g_object_get_property( get( ), propertyName, &value );
        }
        Value GetProperty( const char* propertyName ) const
        {
            Value result;
            GetProperty( propertyName, result );
            return result;
        }

        void SetProperty( const char* propertyName, const GValue* value ) const
        {
            g_object_set_property( get( ), propertyName, value );
        }

        void SetProperty( const char* propertyName, const Value& value ) const
        {
            g_object_set_property( get( ), propertyName, &value );
        }



        template<typename ... Args>
        void SetProperties( const char* firstPropertyName, Args&& ... args ) const
        {
            g_object_set( get( ), firstPropertyName, std::forward<Args>( args )... );
        }

        template<typename ... Args>
        void Connect( const char* signalSpec, Args&& ... args ) const
        {
            g_object_connect( get( ), signalSpec, std::forward<Args>( args )... );

        }

        template<typename ... Args>
        void Disconnect( const char* signalSpec, Args&& ... args ) const
        {
            g_object_disconnect( get( ), signalSpec, std::forward<Args>( args )... );

        }
    };

#define HWM_GOBJECT_IMPLEMENT_STANDARD_MEMBERS( TypeName, WrappedTypeName ) \
    using WrappedType = WrappedTypeName; \
    TypeName( ) = default; \
    template<typename T, typename WrappedTraitsT = ObjectTraits<T>> \
        requires Harlinn::Media::GLib::ObjectTraits_v<T> \
    explicit TypeName( T* wrapped, Harlinn::Media::GLib::ReferenceType referenceType = Harlinn::Media::GLib::ReferenceType::None ) \
        : Base( wrapped, referenceType ) \
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
    [[nodiscard]] \
    WrappedType* get( ) const \
    { \
        return reinterpret_cast< WrappedType* >( Base::get( ) ); \
    } \
    [[nodiscard]] \
    WrappedType* Detach( ) \
    { \
        return reinterpret_cast< WrappedType* >( Base::Detach( ) ); \
    } \
    operator WrappedType* ( ) const \
    { \
        return reinterpret_cast< WrappedType* >( Base::get( ) ); \
    }


    class Object : public BasicObject
    {
    public:
        using Base = BasicObject;
        HWM_GOBJECT_IMPLEMENT_STANDARD_MEMBERS( Object, GObject )

        ~Object( )
        {
            auto tmp = Detach( );
            if ( tmp )
            {
                ObjectTraits<WrappedType>::Unref( tmp );
            }
        }

        Object& operator = ( WrappedType* wrapped )
        {
            Assign<true, WrappedType>( wrapped );
            return *this;
        }
    };
    static_assert( sizeof( Object ) == sizeof( GObject* ) );

    class ObjectFactory
    {
    public:
        template<typename T>
            requires std::is_base_of_v<Object, T>
        static T Create( GType objectType, const gchar* first_property_name, ... )
        {
            va_list args;
            va_start( args, first_property_name );
            auto newObject = g_object_new_valist( objectType, first_property_name, args );
            va_end( args );
            if ( newObject )
            {
                return T( reinterpret_cast< typename T::WrappedType* >( newObject ) );
            }
            return {};
        }

        template<typename T>
            requires std::is_base_of_v<Object, T>
        static T CreateV( GType objectType, const gchar* first_property_name, va_list args )
        {
            auto newObject = g_object_new_valist( objectType, first_property_name, args );
            if ( newObject )
            {
                return T( reinterpret_cast< typename T::WrappedType* >( newObject ) );
            }
            return {};
        }

        template<typename T>
            requires std::is_base_of_v<Object, T>
        static T CreateWithProperties( GType objectType, guint numberOfProperties, const char* names[ ], const GValue values[ ] )
        {
            auto newObject = g_object_new_with_properties( objectType, numberOfProperties, names, values );
            if ( newObject )
            {
                return T( reinterpret_cast< typename T::WrappedType* >( newObject ) );
            }
            return {};
        }
    };


    using BasicInitiallyUnowned = BasicObject;
    using InitiallyUnowned = Object;



    
    


}

#endif
