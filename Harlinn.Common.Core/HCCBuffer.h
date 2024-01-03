#pragma once
#ifndef __HCCBUFFER_H__
#define __HCCBUFFER_H__
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

#include <HCCDef.h>

namespace Harlinn::Common::Core
{
    class Buffer
    {
    public:
        struct Data
        { 
            size_t size_;
#pragma warning(push)
#pragma warning(disable:4200)
            Byte data_[0];
#pragma warning(pop)
        };
    private:
        Data* data_;

        static Data* Allocate( size_t bufferSize )
        {
            auto* result = (Data*)std::malloc( bufferSize + sizeof( size_t ) );
            if ( result ) [[likely]]
            {
                result->size_ = bufferSize;
            }
            else
            {
                throw std::bad_alloc( );
            }
            return result;
        }

        static Data* ReAllocate( Data* current, size_t newBufferSize )
        {
            auto* result = (Data*)std::realloc( current, newBufferSize + sizeof( size_t ) );
            if ( result ) [[likely]]
            {
                result->size_ = newBufferSize;
            }
            else
            {
                throw std::bad_alloc( );
            }
            return result;
        }

        static void Free( Data* current )
        {
            if ( current )
            {
                std::free( current );
            }
        }

    public:
        constexpr Buffer() noexcept
            : data_(nullptr)
        { }

        explicit Buffer( size_t bufferSize ) noexcept
            : data_( Allocate( bufferSize ) )
        {
            
        }

        Buffer( const Buffer& other ) = delete;
        constexpr Buffer( Buffer&& other ) noexcept
            : data_(other.data_)
        {
            other.data_ = nullptr;
        }

        ~Buffer()
        { 
            if ( data_ )
            {
                Free( data_ );
            }
        }


        Buffer& operator = ( const Buffer& other ) = delete;
        constexpr Buffer& operator = ( Buffer&& other ) noexcept
        {
            std::swap( data_, other.data_ );
            return *this;
        }

        void resize( size_t bufferSize )
        {
            data_ = ReAllocate( data_, bufferSize );
        }

        const size_t size( ) const
        {
            return data_ ? data_->size_ : 0;
        }

        Byte* data( )
        {
            return data_ ? data_->data_:nullptr;
        }
        const Byte* data( ) const
        {
            return data_ ? data_->data_ : nullptr;
        }



    };
}

#endif
