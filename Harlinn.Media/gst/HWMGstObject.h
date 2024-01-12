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

#include "HWMGstTraits.h"
#include <glib/gobject/HWMgobject.h>
#include <glib/HWMgthread.h>

namespace Harlinn::Media::GStreamer
{
    namespace Internal
    {
        template<typename BaseT>
        class Object : public BaseT
        {
        public:
            using Base = BaseT;
            HWM_GOBJECT_IMPLEMENT_STANDARD_MEMBERS( Object, GstObject )

            GLib::Mutex& Lock( ) const
            {
                return reinterpret_cast< GLib::Mutex& >( get( )->lock );
            }

            const char* Name( ) const
            {
                return get( )->name;
            }

            Object Parent( GLib::ReferenceType referenceType = GLib::ReferenceType::None ) const
            {
                auto parent = get( )->parent;
                if ( parent )
                {
                    return Object( parent, referenceType );
                }
                return {};
            }

            template<typename T>
                requires std::is_base_of_v<Object, T>
            T Parent( GLib::ReferenceType referenceType = GLib::ReferenceType::None ) const
            {
                auto parent = reinterpret_cast< typename T::WrappedType* >( get( )->parent );
                if ( parent )
                {
                    return T( parent, referenceType );
                }
                return {};
            }
        };
    }
    class BasicObject : public Internal::Object<GLib::BasicInitiallyUnowned>
    {
    public:
        using Base = Internal::Object<GLib::BasicInitiallyUnowned>;
        HWM_GOBJECT_IMPLEMENT_STANDARD_MEMBERS( BasicObject, GstObject )
    };

    class Object : public Internal::Object<GLib::InitiallyUnowned>
    {
    public:
        using Base = Internal::Object<GLib::InitiallyUnowned>;
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
    
}


#endif
