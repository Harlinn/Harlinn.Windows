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


#include <HWMDef.h>
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


    namespace Internal
    {
        template<typename DerivedT, typename InnerT>
        class Base
        {
        public:
            using DerivedType = DerivedT;
            using InnerType = InnerT;
        private:
            InnerType* impl_ = nullptr;
        public:
            Base( ) = default;
            Base( InnerType* impl )
                : impl_( impl )
            { }
            Base( const Base& other ) = delete;
            Base( Base&& other ) noexcept
                : impl_( other.impl_ )
            {
                other.impl_ = nullptr;
            }

            ~Base( )
            {
                if ( impl_ )
                {
                    DerivedType::ReleaseInner( impl_ );
                }
            }

            Base& operator = ( const Base& other ) = delete;

            Base& operator = ( Base&& other ) noexcept
            {
                std::swap( impl_, other.impl_ );
                return *this;
            }

            Base& operator = ( InnerType* impl ) noexcept
            {
                if ( impl_ != impl )
                {
                    if ( impl_ )
                    {
                        DerivedType::ReleaseInner( impl_ );
                    }
                    impl_ = impl;
                }
                return *this;
            }

            InnerType* get( ) const
            {
                return impl_;
            }

            explicit operator bool( ) const noexcept
            {
                return impl_ != nullptr;
            }

            InnerType* Detach( )
            {
                InnerType* tmp = impl_;
                impl_ = nullptr;
                return tmp;
            }

            operator InnerType* ( ) const
            {
                return impl_;
            }
        };

        


    }


}

#endif
