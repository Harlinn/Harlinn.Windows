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

#include "HWMGstConstants.h"
#include <glib/gobject/HWMgobject.h>
#include <glib/HWMgthread.h>

namespace Harlinn::Media::GStreamer
{
    class ObjectBase : public GLib::InitiallyUnowned
    {
    public:
        using Base = GLib::InitiallyUnowned;
        using WrappedType = GstObject;

        ObjectBase( ) = default;

        explicit ObjectBase( WrappedType* impl, bool disableObjectUnref = false )
            : Base( reinterpret_cast< Base::WrappedType* >( impl ), disableObjectUnref )
        { }

        ObjectBase( ObjectBase&& other ) noexcept
            : Base( std::move( other ) )
        { }

        ~ObjectBase( )
        {
            auto impl = Detach( );
            if ( impl && DisableObjectUnref( ) == false )
            {
                gst_object_unref( impl );
            }
        }

        ObjectBase& operator = ( ObjectBase&& other ) noexcept
        {
            Base::operator=( std::move( other ) );
            return *this;
        }

        void Assign( WrappedType* impl, bool disableObjectUnref = false ) noexcept 
        { 
            Base::Assign( reinterpret_cast< Base::WrappedType* >( impl ), disableObjectUnref ); 
        }

        ObjectBase& operator = ( WrappedType* impl ) noexcept
        {
            Assign( impl );
            return *this;
        }

        [[nodiscard]] 
        WrappedType* get( ) const 
        { 
            return reinterpret_cast< WrappedType* >( Base::get( ) ); 
        } 

        [[nodiscard]] 
        WrappedType* Detach( ) 
        {
            return reinterpret_cast< WrappedType* >( Base::Detach( ) );
        }
        operator WrappedType* ( ) const
        {
            return reinterpret_cast< WrappedType* >( Base::get( ) );
        }
    };


    class Object : public ObjectBase
    {
    public:
        using Base = ObjectBase;
        
        HWM_GOBJECT_IMPLEMENT_STANDARD_MEMBERS( Object, GstObject )
        
        GLib::Mutex& Lock( ) const
        {
            return reinterpret_cast< GLib::Mutex& >( get( )->lock );
        }

        const char* Name( ) const
        {
            return get( )->name;
        }

        Object Parent( ) const
        {
            auto parent = get( )->parent;
            if ( parent )
            {
                return Object( parent, true );
            }
            return {};
        }

        template<typename T>
            requires std::is_base_of_v<Object,T>
        T Parent( ) const
        {
            auto parent = reinterpret_cast<typename T::WrappedType* >( get( )->parent );
            if ( parent )
            {
                return T( parent, true );
            }
            return {};
        }

    };
    
}


#endif
