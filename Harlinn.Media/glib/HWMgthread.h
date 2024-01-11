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
    class BasicThread
    {
    public:
        using WrappedType = GThread;
        using WrappedTraits = ObjectTraits<GThread>;
    private:
        WrappedType* wrapped_ = nullptr;
    public:
        BasicThread( ) = default;
        explicit BasicThread( WrappedType* wrapped, ReferenceType referenceType = ReferenceType::None )
            : wrapped_( wrapped )
        {
            if ( wrapped_ )
            {
                switch ( referenceType )
                {
                    case ReferenceType::Ref:
                        WrappedTraits::Ref( wrapped_ );
                        break;
                    case ReferenceType::RefSink:
                        WrappedTraits::RefSink( wrapped_ );
                        break;
                    case ReferenceType::TakeRef:
                        WrappedTraits::TakeRef( wrapped_ );
                        break;
                }
            }
        }

        BasicThread( const BasicThread& other ) = delete;
        BasicThread( BasicThread&& other ) noexcept
            : wrapped_( other.wrapped_ )
        {
            other.wrapped_ = nullptr;
        }
        BasicThread& operator = ( const BasicThread& other ) = delete;
        BasicThread& operator = ( BasicThread&& other ) noexcept
        {
            std::swap( wrapped_, other.wrapped_ );
            return *this;
        }

        explicit operator bool( ) const
        {
            return wrapped_ != nullptr;
        }

        WrappedType* get( ) const
        {
            return wrapped_;
        }

        WrappedType* Detach( )
        {
            auto tmp = wrapped_;
            wrapped_ = nullptr;
            return tmp;
        }

        operator WrappedType* ( ) const
        {
            return wrapped_;
        }

        static BasicThread Current( )
        {
            BasicThread result( g_thread_self( ) );
            return result;
        }
        static BasicThread Self( )
        {
            return Current( );
        }

    };

    class Thread : public BasicThread
    {
    public:
        using Base = BasicThread;
        Thread( ) = default;
        explicit Thread( WrappedType* wrapped, ReferenceType referenceType = ReferenceType::None )
            : Base( wrapped, referenceType )
        {
        }

        Thread( const char* name, GThreadFunc func, gpointer userData )
            : Base( g_thread_new( name, func, userData ) )
        { }

        Thread( const char* name, GThreadFunc func, gpointer userData, GError** error )
            : Base( g_thread_try_new( name, func, userData, error ) )
        { }

        Thread( Thread&& other ) noexcept
            : Base( std::move( other ) )
        { }

        ~Thread( )
        {
            auto tmp = Detach( );
            if ( tmp )
            {
                WrappedTraits::Unref( tmp );
            }
        }

        Thread& operator = ( BasicThread&& other ) noexcept
        {
            Base::operator = ( std::move( other ) );
            return *this;
        }

    };

    class Cond;
    class Mutex
    {
        friend class Cond;
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

    class RecMutex
    {
        GRecMutex impl_;
    public:
        RecMutex( )
            : impl_{}
        {
            g_rec_mutex_init( &impl_ );
        }

        RecMutex( const RecMutex& other ) = delete;
        RecMutex( RecMutex&& other ) = delete;

        ~RecMutex( )
        {
            g_rec_mutex_clear( &impl_ );
        }

        RecMutex& operator = ( const RecMutex& other ) = delete;
        RecMutex& operator = ( RecMutex&& other ) = delete;

        void lock( )
        {
            g_rec_mutex_lock( &impl_ );
        }
        bool try_lock( )
        {
            return g_rec_mutex_trylock( &impl_ ) != 0;
        }
        void unlock( )
        {
            g_rec_mutex_unlock( &impl_ );
        }
    };

    class RWLock
    {
        GRWLock impl_;
    public:
        RWLock( )
            : impl_{}
        {
            g_rw_lock_init( &impl_ );
        }

        RWLock( const RWLock& other ) = delete;
        RWLock( RWLock&& other ) = delete;

        ~RWLock( )
        {
            g_rw_lock_clear( &impl_ );
        }

        RWLock& operator = ( const RWLock& other ) = delete;
        RWLock& operator = ( RWLock&& other ) = delete;

        void lock( )
        {
            g_rw_lock_writer_lock( &impl_ );
        }
        bool try_lock( )
        {
            return g_rw_lock_writer_trylock( &impl_ ) != 0;
        }
        void unlock( )
        {
            g_rw_lock_writer_unlock( &impl_ );
        }

        void lock_shared( )
        {
            g_rw_lock_reader_lock( &impl_ );
        }
        bool try_lock_shared( )
        {
            return g_rw_lock_reader_trylock( &impl_ ) != 0;
        }
        void unlock_shared( )
        {
            g_rw_lock_reader_unlock( &impl_ );
        }
    };

    class Cond
    {
        GCond impl_;
    public:
        Cond( )
            : impl_{}
        {
            g_cond_init( &impl_ );
        }

        Cond( const Cond& other ) = delete;
        Cond( Cond&& other ) = delete;

        ~Cond( )
        {
            g_cond_clear( &impl_ );
        }

        Cond& operator = ( const Cond& other ) = delete;
        Cond& operator = ( Cond&& other ) = delete;

        void Wait( GMutex* mutex )
        {
            g_cond_wait( &impl_, mutex );
        }

        void Wait( Mutex& mutex )
        {
            g_cond_wait( &impl_, &mutex.impl_ );
        }

        void wait( GMutex* mutex )
        {
            g_cond_wait( &impl_, mutex );
        }

        void wait( Mutex& mutex )
        {
            g_cond_wait( &impl_, &mutex.impl_ );
        }

        bool Wait( GMutex* mutex, Int64 endTime )
        {
            return g_cond_wait_until( &impl_, mutex, endTime ) != 0;
        }

        bool Wait( Mutex& mutex, Int64 endTime )
        {
            return g_cond_wait_until( &impl_, &mutex.impl_, endTime ) != 0;
        }

        void Signal( )
        {
            g_cond_signal( &impl_ );
        }

        void notify_one( ) noexcept
        {
            g_cond_signal( &impl_ );
        }
        void Broadcast( )
        {
            g_cond_broadcast( &impl_ );
        }
        void notify_all( ) noexcept
        {
            g_cond_broadcast( &impl_ );
        }
    };



}

#endif
