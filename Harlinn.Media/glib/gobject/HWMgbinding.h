#pragma once 
#ifndef HARLINN_MEDIA_GLIB_GOBJECT_HWMGBINDING_H_
#define HARLINN_MEDIA_GLIB_GOBJECT_HWMGBINDING_H_

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

#include "HWMgclosure.h"

namespace Harlinn::Media::GLib
{
    class Object;
    class Value;

    class Binding : public Internal::Base<Binding, GBinding>
    {
    public:
        using Base = Internal::Base<Binding, GBinding>;

        Binding( ) = default;
        Binding( InnerType* impl )
            : Base( impl )
        {
        }

        Binding( gpointer source, const char* sourceProperty, gpointer target, const char* targetProperty, GBindingFlags flags )
            : Base( g_object_bind_property( source, sourceProperty, target, targetProperty, flags ) )
        { }

        Binding( const Object& source, const char* sourceProperty, const Object& target, const char* targetProperty, GBindingFlags flags );

        Binding( gpointer source, const char* sourceProperty, gpointer target, const char* targetProperty, GBindingFlags flags, GBindingTransformFunc transformTo, GBindingTransformFunc transformFrom, gpointer userData, GDestroyNotify notify )
            : Base( g_object_bind_property_full( source, sourceProperty, target, targetProperty, flags, transformTo, transformFrom, userData, notify ) )
        { }

        Binding( const Object& source, const char* sourceProperty, const Object& target, const char* targetProperty, GBindingFlags flags, GBindingTransformFunc transformTo, GBindingTransformFunc transformFrom, gpointer userData, GDestroyNotify notify );

        Binding( gpointer source, const char* sourceProperty, gpointer target, const char* targetProperty, GBindingFlags flags, GClosure* transformTo, GClosure* transformFrom )
            : Base( g_object_bind_property_with_closures( source, sourceProperty, target, targetProperty, flags, transformTo, transformFrom ) )
        {
        }

        Binding( const Object& source, const char* sourceProperty, const Object& target, const char* targetProperty, GBindingFlags flags, const Closure& transformTo, const Closure& transformFrom );

        static void ReleaseInner( InnerType* impl )
        {
            g_binding_unbind( impl );
        }

        GBindingFlags Flags( ) const
        {
            return g_binding_get_flags( get( ) );
        }

        template<typename T>
            requires std::is_base_of_v<Object,T>
        T Source( ) const;

        const char* SourceProperty( ) const
        {
            return g_binding_get_source_property( get( ) );
        }

        template<typename T>
            requires std::is_base_of_v<Object, T>
        T Target( ) const;

        const char* TargetProperty( ) const
        {
            return g_binding_get_target_property( get( ) );
        }


    };

}
#endif
