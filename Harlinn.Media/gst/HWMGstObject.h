#pragma once
#ifndef HARLINN_MEDIA_HWMGSTOBJECT_H_
#define HARLINN_MEDIA_HWMGSTOBJECT_H_

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

#include "HWMGstForwards.h"
#include <glib/gobject/HWMgobject.h>
#include <glib/HWMgthread.h>
#include <glib/HWMgstring.h>
#include "HWMGstMessage.h"

namespace Harlinn::Media::GStreamer
{
    class BasicObject;
    class Object;

    namespace Internal
    {
        template<typename BaseT>
        class ObjectImpl : public BaseT
        {
        public:
            using Base = BaseT;
            HWM_GOBJECT_IMPLEMENT_STANDARD_MEMBERS( ObjectImpl, GstObject )

            GLib::Mutex& Lock( ) const
            {
                return reinterpret_cast< GLib::Mutex& >( get( )->lock );
            }

            GLib::StringPtr Name( ) const
            {
                return GLib::StringPtr( gst_object_get_name( get( ) ) );
            }
            bool SetName( const char* name ) const
            {
                return gst_object_set_name( get( ), name ) != 0;
            }
            template<typename T>
                requires requires(const T& t)
                { 
                    { t.c_str( ) }->std::convertible_to<const char*>;
                }
            bool SetName( const T& name ) const
            {
                SetName( name.c_str() );
            }


            Object Parent( GLib::ReferenceType referenceType = GLib::ReferenceType::None ) const;

            template<typename T>
                requires std::is_base_of_v<Object, T>
            T Parent( GLib::ReferenceType referenceType = GLib::ReferenceType::None ) const
            {
                auto parent = reinterpret_cast< typename T::WrappedType* >( gst_object_get_parent( get( ) ) );
                if ( parent )
                {
                    return T( parent, referenceType );
                }
                return {};
            }

            bool SetParent( GstObject* parent ) const
            {
                return gst_object_set_parent( get( ), parent ) != 0;
            }
            template< typename T >
                requires std::is_base_of_v<BasicObject,T>
            bool SetParent( const T& parent ) const
            {
                return gst_object_set_parent( get( ), reinterpret_cast< GstObject* >( parent.get() )) != 0;
            }

            void Unparent( ) const
            {
                gst_object_unparent( get( ) );
            }

            bool HasAsParent( GstObject* parent ) const
            {
                return gst_object_has_as_parent( get( ), parent ) != 0;
            }
            template< typename T >
                requires std::is_base_of_v<BasicObject, T>
            bool HasAsParent( const T& parent ) const
            {
                return gst_object_has_as_parent( get( ), reinterpret_cast< GstObject* >( parent.get( ) ) ) != 0;
            }


            bool HasAsAncestor( GstObject* ancestor ) const
            {
                return gst_object_has_as_ancestor( get( ), ancestor ) != 0;
            }
            template< typename T >
                requires std::is_base_of_v<BasicObject, T>
            bool HasAsAncestor( const T& ancestor ) const
            {
                return gst_object_has_as_ancestor( get( ), reinterpret_cast< GstObject* >( ancestor.get( ) ) ) != 0;
            }


            void DefaultDeepNotify( GstObject* notificationOrigin, GParamSpec* paramSpec, const char** excludedProperties ) const
            {
                gst_object_default_deep_notify( get( ), notificationOrigin, paramSpec, const_cast< char** >( excludedProperties ) );
            }
            template< typename T >
                requires std::is_base_of_v<BasicObject, T>
            void DefaultDeepNotify( const T& notificationOrigin, GParamSpec* paramSpec, const char** excludedProperties ) const
            {
                gst_object_default_deep_notify( get( ), reinterpret_cast< GstObject* >( notificationOrigin.get( ) ), paramSpec, const_cast< char** >( excludedProperties ) );
            }

            GLib::StringPtr PathString( ) const
            {
                return GLib::StringPtr( gst_object_get_path_string( get() ) );
            }

            GstClockTime SuggestNextSync( ) const
            {
                return gst_object_suggest_next_sync( get( ) );
            }

            bool SyncValues( GstClockTime timestamp ) const
            {
                return gst_object_sync_values( get( ), timestamp ) != 0;
            }

            bool HasActiveControlBindings( ) const
            {
                return gst_object_has_active_control_bindings( get() ) != 0;
            }

            void SetControlBindingsDisabled( bool disabled ) const
            {
                gst_object_set_control_bindings_disabled( get( ), disabled ? TRUE : FALSE );
            }

            void SetControlBindingDisabled( const char* propertyName, bool disabled ) const
            {
                gst_object_set_control_binding_disabled( get(), propertyName, disabled ? TRUE : FALSE );
            }

            bool AddControlBinding( GstControlBinding* binding ) const
            {
                return gst_object_add_control_binding( get(), binding ) != 0;
            }
            template< typename T>
                requires IsControlBinding<T>
            bool AddControlBinding( T&& binding ) const
            {
                auto result = AddControlBinding( reinterpret_cast< GstControlBinding* >( binding.get( ) ) );
                if ( result )
                {
                    ( void )binding.Detach( );
                }
                return result;
            }
            template< typename T>
                requires IsControlBinding<T>
            bool AddControlBinding( const T& binding ) const
            {
                auto result = AddControlBinding( reinterpret_cast< GstControlBinding* >( binding.get( ) ) );
                return result;
            }

            GStreamer::ControlBinding ControlBinding( const char* propertyName ) const;

            bool RemoveControlBinding( GstControlBinding* binding ) const
            {
                return gst_object_remove_control_binding( get(), binding ) != 0;
            }
            template< typename T>
                requires IsControlBinding<T>
            bool RemoveControlBinding( const T& binding ) const
            {
                auto result = RemoveControlBinding( reinterpret_cast< GstControlBinding* >( binding.get( ) ) );
                return result;
            }

            GLib::Value Value( const char* propertyName, GstClockTime timestamp ) const
            {
                auto value = gst_object_get_value( get(), propertyName, timestamp );
                if ( value )
                {
                    return GLib::Value( value );
                }
                return {};
            }

            bool ValueArray( const char* propertyName, GstClockTime timestamp, GstClockTime interval, guint numberOfvalues, gpointer values ) const
            {
                return gst_object_get_value_array( get(), propertyName, timestamp, interval, numberOfvalues, values ) != 0;
            }

            bool ValueArray( const char* propertyName, GstClockTime timestamp, GstClockTime interval, guint numberOfvalues, GValue* values ) const
            {
                return gst_object_get_g_value_array( get( ), propertyName, timestamp, interval, numberOfvalues, values ) != 0;
            }

            GstClockTime ControlRate( ) const
            {
                return gst_object_get_control_rate( get() );
            }

            void SetControlRate( GstClockTime controlRate ) const
            {
                gst_object_set_control_rate( get(), controlRate );
            }


        };
    }
    class BasicObject : public Internal::ObjectImpl<GLib::BasicInitiallyUnowned>
    {
    public:
        using Base = Internal::ObjectImpl<GLib::BasicInitiallyUnowned>;
        HWM_GOBJECT_IMPLEMENT_STANDARD_MEMBERS( BasicObject, GstObject )
    };

    class Object : public Internal::ObjectImpl<GLib::InitiallyUnowned>
    {
    public:
        using Base = Internal::ObjectImpl<GLib::InitiallyUnowned>;
        HWM_GOBJECT_IMPLEMENT_STANDARD_MEMBERS( Object, GstObject )
        ~Object( )
        {
            auto tmp = Detach( );
            if ( tmp )
            {
                GLib::ObjectTraits<WrappedType>::Unref( tmp );
            }
        }

        Object& operator = ( WrappedType* wrapped )
        {
            Assign<true, WrappedType>( wrapped );
            return *this;
        }
    };
    static_assert( sizeof( Object ) == sizeof( GstObject* ) );

    namespace Internal
    {
        template<typename BaseT>
        inline Object ObjectImpl<BaseT>::Parent( GLib::ReferenceType referenceType ) const
        {
            auto parent = gst_object_get_parent( get( ) );
            if ( parent )
            {
                return Object( parent, referenceType );
            }
            return {};
        }

        template<typename BaseT>
        BasicObject MessageImpl<BaseT>::Source( ) const
        {
            auto src = get( )->src;
            if ( src )
            {
                return BasicObject( src );
            }
            return {};
        }


    }
    
}


#endif
