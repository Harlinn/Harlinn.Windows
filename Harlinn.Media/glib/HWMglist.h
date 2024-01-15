#pragma once
#ifndef HARLINN_MEDIA_GLIB_HWMGLIST_H_
#define HARLINN_MEDIA_GLIB_HWMGLIST_H_
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

#include <HWMDef.h>
#include "HWMgtraits.h"

namespace Harlinn::Media::GLib
{
    template<typename T>
    struct ListPointerEntry
    {
        T* data;
        ListPointerEntry* next;
        ListPointerEntry* prev;
    };

    static_assert( sizeof( ListPointerEntry<void> ) == sizeof( GList ) );

    template<typename T>
    class List
    {
    public:
        using value_type = T;
        using ValueType = value_type;
        using EntryType = ListPointerEntry<ValueType>;
        using Traits = ObjectTraits<ValueType>;
    private:
        EntryType* head_ = nullptr;
    public:
        List( ) = default;
        List( EntryType* head )
            : head_( head )
        { }
        List( GList* head )
            : head_( reinterpret_cast< EntryType* >( head ) )
        { }
        List( const List& other ) = delete;
        List( List&& other ) noexcept
            : head_( other.head_ )
        {
            other.head_ = nullptr;
        }


        ~List( )
        {
            if ( head_ )
            {
                auto head = reinterpret_cast< GList* >( head_ );
                head_ = nullptr;
                g_list_free_full( g_steal_pointer( &head_ ), Traits::Unref );
            }
        }

        List& operator = ( const List& other ) = delete;
        List& operator = ( List&& other ) noexcept
        {
            std::swap( head_, other.head_ );
            return *this;
        }

        EntryType* Head( ) const
        {
            return head_;
        }

        GList* get( ) const
        {
            return reinterpret_cast< GList* >( head_ );
        }

    };
    


}

#endif
