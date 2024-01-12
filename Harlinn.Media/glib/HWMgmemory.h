#pragma once
#ifndef HARLINN_MEDIA_GLIB_HWMGMEMORY_H_
#define HARLINN_MEDIA_GLIB_HWMGMEMORY_H_

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


#include "HWMgtraits.h"

namespace Harlinn::Media::GLib
{


    // The purpose of the FreeMemoryDeleter is to
    // call FreeMemory - it will *not* run any destructor code
    // and should only be used to release memory allocated
    // by GStreamer and related dll's for objects that
    // do not have their own g_xxx_free/g_xxx_unref or similar
    // functionality implemented for them by those dlls.  
    template<typename T>
    struct FreeMemoryDeleter 
    {
        FreeMemoryDeleter( ) = default;
        template <typename T2, std::enable_if_t<std::is_convertible_v<T2*, T*>, int> = 0>
        FreeMemoryDeleter( const FreeMemoryDeleter<T2>& ) noexcept
        {}

        void operator()( T* ptr ) const noexcept 
        { 
            if ( ptr )
            {
                g_free( ptr );
            }
        }
    };
    template<typename T>
    struct FreeMemoryDeleter<T[]>
    {
        FreeMemoryDeleter( ) = default;
        
        template <typename T2, std::enable_if_t<std::is_convertible_v<T2( * )[ ], T( * )[ ]>, int> = 0>
        FreeMemoryDeleter( const FreeMemoryDeleter<T2[ ]>& ) noexcept
        {
        }

        template <typename T2, std::enable_if_t<std::is_convertible_v<T2( * )[ ], T( * )[ ]>, int> = 0>
        void operator()( T2* ptr ) const noexcept
        { 
            if ( ptr )
            {
                g_free( ptr );
            }
        }
    };

    template<typename T>
    using FreeMemoryPtr = std::unique_ptr<T, FreeMemoryDeleter<T>>;

    

    enum class ReferenceType
    {
        None,
        Ref,
        RefSink,
        TakeRef
    };


    template<typename DerivedT, typename WrappedT, typename WrappedTraitsT = ObjectTraits<WrappedT> >
    class ReferenceBase
    {
    public:
        using DerivedType = DerivedT;
        using WrappedType = WrappedT;
        using WrappedTraits = WrappedTraitsT;
    private:
        WrappedType* wrapped_ = nullptr;
    public:
        ReferenceBase( ) = default;
        ReferenceBase( WrappedType* wrapped, ReferenceType referenceType = ReferenceType::None )
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
        ReferenceBase( const ReferenceBase& other ) = delete;
        ReferenceBase( ReferenceBase&& other ) noexcept
            : wrapped_( other.wrapped_ )
        {
            other.wrapped_ = nullptr;
        }

        ~ReferenceBase( )
        {
            if ( wrapped_ )
            {
                WrappedTraits::Unref( wrapped_ );
            }
        }

        ReferenceBase& operator = ( const ReferenceBase& other ) = delete;

        ReferenceBase& operator = ( ReferenceBase&& other ) noexcept
        {
            std::swap( wrapped_, other.wrapped_ );
            return *this;
        }

        void Assign( WrappedType* wrapped, ReferenceType referenceType = ReferenceType::None )
        {
            if ( wrapped_ != wrapped )
            {
                if ( wrapped_ )
                {
                    WrappedTraits::Unref( wrapped_ );
                }
                wrapped_ = wrapped;
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
        }

        ReferenceBase& operator = ( WrappedType* wrapped ) noexcept
        {
            Assign( wrapped );
            return *this;
        }

        [[nodiscard]]
        WrappedType* get( ) const
        {
            return wrapped_;
        }

        [[nodiscard]]
        explicit operator bool( ) const noexcept
        {
            return wrapped_ != nullptr;
        }

        [[nodiscard]]
        WrappedType* Detach( )
        {
            WrappedType* tmp = wrapped_;
            wrapped_ = nullptr;
            return tmp;
        }

        [[nodiscard]]
        operator WrappedType* ( ) const
        {
            return wrapped_;
        }
    };

    template<typename T>
    class Attached : public T
    {
    public:
        using Base = T;
        using WrappedType = typename T::WrappedType;
        using WrappedTraits = typename T::WrappedTraits;

        template<typename ... Args>
            requires std::is_constructible_v<T, Args...>
        Attached( Args&& ... args )
            : Base( std::forward<Args>( args ) ... )
        { }


        ~Attached( )
        {
            (void)Base::Detach( );
        }

    };

}

#endif
