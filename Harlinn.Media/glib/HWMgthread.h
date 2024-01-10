#pragma once
#ifndef HARLINN_MEDIA_GLIB_HWMGTHREAD_H_
#define HARLINN_MEDIA_GLIB_HWMGTHREAD_H_
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

#include "HWMgtypes.h"

namespace Harlinn::Media::GLib
{
    class Thread
    {

    };

    class Mutex
    {
        GMutex impl_;
    public:
        Mutex( )
            : impl_{}
        {
            g_mutex_init( &impl_ );
        }

        Mutex( const Mutex& other ) = delete;
        Mutex( Mutex&& other ) = delete;

        ~Mutex( )
        {
            g_mutex_clear( &impl_ );
        }

        Mutex& operator = ( const Mutex& other ) = delete;
        Mutex& operator = ( Mutex&& other ) = delete;

        void lock( )
        {
            g_mutex_lock( &impl_ );
        }
        bool try_lock( )
        {
            return g_mutex_trylock( &impl_ ) != 0;
        }
        void unlock( )
        {
            g_mutex_unlock( &impl_ );
        }
    };

    static_assert( sizeof( Mutex ) == sizeof( GMutex ) );

}

#endif
