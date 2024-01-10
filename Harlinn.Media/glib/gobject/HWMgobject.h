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
    

    class ObjectBase
    {
    public:
        
    private:
        gpointer impl_ = nullptr;
        bool disableObjectUnref_ = false;
    public:
        using WrappedType = void;
        ObjectBase( ) = default;
        explicit ObjectBase( gpointer impl, bool disableObjectUnref = false )
            : impl_( impl ), disableObjectUnref_( disableObjectUnref )
        {
        }
        ObjectBase( const ObjectBase& other ) = delete;
        ObjectBase( ObjectBase&& other ) noexcept
            : impl_( other.impl_ ), disableObjectUnref_( other.disableObjectUnref_ )
        {
            other.impl_ = nullptr;
            other.disableObjectUnref_ = false;
        }

        ~ObjectBase( )
        {
            if ( impl_ && disableObjectUnref_ == false )
            {
                g_object_unref( impl_ );
            }
        }

        ObjectBase& operator = ( const ObjectBase& other ) = delete;

        ObjectBase& operator = ( ObjectBase&& other ) noexcept
        {
            std::swap( impl_, other.impl_ );
            std::swap( disableObjectUnref_, other.disableObjectUnref_ );
            return *this;
        }

        void Assign( gpointer impl, bool disableObjectUnref = false ) noexcept
        {
            if ( impl_ != impl )
            {
                if ( impl_ && disableObjectUnref_ == false )
                {
                    g_object_unref( impl_ );
                }
                impl_ = impl;
            }
            disableObjectUnref_ = disableObjectUnref;
        }


        ObjectBase& operator = ( gpointer impl ) noexcept
        {
            Assign( impl );
            return *this;
        }

        [[nodiscard]]
        gpointer get( ) const
        {
            return impl_;
        }

        explicit operator bool( ) const noexcept
        {
            return impl_ != nullptr;
        }

        [[nodiscard]]
        gpointer Detach( )
        {
            gpointer tmp = impl_;
            impl_ = nullptr;
            disableObjectUnref_ = false;
            return tmp;
        }

        operator gpointer ( ) const
        {
            return impl_;
        }

        [[nodiscard]]
        bool DisableObjectUnref( ) const
        {
            return disableObjectUnref_;
        }
        void SetDisableObjectUnref( bool disableObjectUnref = true )
        {
            disableObjectUnref_ = disableObjectUnref;
        }
    protected:

    };

#define HWM_GOBJECT_IMPLEMENT_STANDARD_MEMBERS( TypeName, WrappedTypeName ) \
    using WrappedType = WrappedTypeName; \
    TypeName( ) = default; \
    explicit TypeName( WrappedType* impl, bool disableObjectUnref = false ) \
        : Base( reinterpret_cast< Base::WrappedType* >( impl ), disableObjectUnref ) \
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
    void Assign( WrappedType* impl, bool disableObjectUnref = false ) noexcept \
    { \
        Base::Assign( reinterpret_cast< Base::WrappedType* >( impl ), disableObjectUnref ); \
    } \
    TypeName& operator = ( WrappedType* impl ) noexcept \
    { \
        Assign( impl ); \
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


    class Object : public ObjectBase
    {
    public:
        using Base = ObjectBase;
        HWM_GOBJECT_IMPLEMENT_STANDARD_MEMBERS( Object, GObject )

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
                return T( reinterpret_cast<typename T::WrappedType*>( newObject ) );
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

    using InitiallyUnowned = Object;



    inline Binding::Binding( const Object& source, const gchar* sourceProperty, const Object& target, const gchar* targetProperty, GBindingFlags flags )
        : Base( g_object_bind_property( source.get(), sourceProperty, target.get( ), targetProperty, flags ) )
    {
    }

    inline Binding::Binding( const Object& source, const char* sourceProperty, const Object& target, const char* targetProperty, GBindingFlags flags, GBindingTransformFunc transformTo, GBindingTransformFunc transformFrom, gpointer userData, GDestroyNotify notify )
        : Base( g_object_bind_property_full( source.get(), sourceProperty, target.get( ), targetProperty, flags, transformTo, transformFrom, userData, notify ) )
    {
    }

    inline Binding::Binding( const Object& source, const char* sourceProperty, const Object& target, const char* targetProperty, GBindingFlags flags, const Closure& transformTo, const Closure& transformFrom )
        : Base( g_object_bind_property_with_closures( source.get(), sourceProperty, target.get( ), targetProperty, flags, transformTo.get( ), transformFrom.get( ) ) )
    {
    }

    template<typename T>
        requires std::is_base_of_v<Object, T>
    inline T Binding::Source( ) const
    {
        auto source = reinterpret_cast<typename T::WrappedType* >( g_binding_dup_source( get( ) ) );
        if ( source )
        {
            return T( source );
        }
        return {};
    }

    template<typename T>
        requires std::is_base_of_v<Object, T>
    inline T Binding::Target( ) const
    {
        auto source = reinterpret_cast< typename T::WrappedType* >( g_binding_dup_target( get( ) ) );
        if ( source )
        {
            return T( source );
        }
        return {};
    }
    


}

#endif
