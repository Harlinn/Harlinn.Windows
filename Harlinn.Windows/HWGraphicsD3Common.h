#pragma once
#ifndef HARLINN_WINDOWS_HWGRAPHICSD3COMMON_H_
#define HARLINN_WINDOWS_HWGRAPHICSD3COMMON_H_
/*
   Copyright 2024-2025 Espen Harlinn

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

#include <HWDef.h>
#include <HCCCOM.h>
#include <HCCException.h>
#include <HWCommon.h>
#include <HWControl.h>
#include <HCCIterator.h>

namespace Harlinn::Windows::Graphics
{
    using namespace Harlinn::Common::Core;

    /// <summary>
    /// Used to return arbitrary-length data.
    /// </summary>
    class D3D10Blob : public Unknown
    {
    public:
        using Base = Unknown;

        HCC_COM_STANDARD_METHODS_IMPL( D3D10Blob, Unknown, ID3D10Blob, IUnknown )
    public:
        using value_type = Byte;
        using size_type = size_t;
        using difference_type = SSizeT;
        using pointer = value_type*;
        using reference = value_type&;
        using const_pointer = const value_type*;
        using const_reference = const value_type&;

        using iterator = Harlinn::Common::Core::Internal::PointerIterator<D3D10Blob>;
        using const_iterator = Harlinn::Common::Core::Internal::ConstPointerIterator<D3D10Blob>;

        using reverse_iterator = std::reverse_iterator<iterator>;
        using const_reverse_iterator = std::reverse_iterator<const_iterator>;

        using span_type = std::span<value_type>;
        using const_span_type = std::span<const value_type>;


        /// <summary>
        /// Gets a pointer to the data.
        /// </summary>
        [[nodiscard]] LPVOID GetBufferPointer( ) const
        {
            InterfaceType* pInterface = GetInterface( );
            return pInterface->GetBufferPointer( );
        }

        /// <summary>
        /// Gets the size.
        /// </summary>
        /// <returns>
        /// The size of the data, in bytes.
        /// </returns>
        [[nodiscard]] SIZE_T GetBufferSize( ) const
        {
            InterfaceType* pInterface = GetInterface( );
            return pInterface->GetBufferSize( );
        }

        [[nodiscard]] span_type ToSpan( )
        {
            return span_type( data( ), size( ) );
        }

        [[nodiscard]] const_span_type ToSpan( ) const
        {
            return const_span_type( data( ), size( ) );
        }


        [[nodiscard]] size_t size( ) const
        {
            return GetBufferSize( );
        }
        [[nodiscard]] pointer data( )
        {
            return reinterpret_cast< value_type* >( GetBufferPointer( ) );
        }
        [[nodiscard]] const_pointer data( ) const
        {
            return reinterpret_cast< const value_type* >( GetBufferPointer( ) );
        }


        [[nodiscard]] iterator begin( )
        {
            return iterator( data( ) );
        }

        [[nodiscard]] const_iterator begin( ) const
        {
            return const_iterator( data( ) );
        }

        [[nodiscard]] const_iterator cbegin( ) const 
        {
            return const_iterator( data( ) );
        }

        [[nodiscard]] iterator end( )
        {
            return iterator( data( ) + size( ) );
        }
        [[nodiscard]] const_iterator end( ) const
        {
            return const_iterator( data( ) + size( ) );
        }
        [[nodiscard]] const_iterator cend( ) const
        {
            return const_iterator( data( ) + size( ) );
        }


        [[nodiscard]] reverse_iterator rbegin( )
        {
            return reverse_iterator( end( ) );
        }

        [[nodiscard]] const_reverse_iterator rbegin( ) const
        {
            return const_reverse_iterator( end( ) );
        }

        [[nodiscard]] reverse_iterator rend( )
        {
            return reverse_iterator( begin( ) );
        }

        [[nodiscard]] const_reverse_iterator rend( ) const
        {
            return const_reverse_iterator( begin( ) );
        }

        [[nodiscard]] const_reverse_iterator crbegin( ) const
        {
            return rbegin( );
        }

        [[nodiscard]] const_reverse_iterator crend( ) const
        {
            return rend( );
        }

        [[nodiscard]] reference front( )
        {
            return *data();
        }
        [[nodiscard]] const_reference front( ) const
        {
            return *data( );
        }
        [[nodiscard]] reference back( )
        {
            return *( data( ) + ( size( ) - 1 ) );
        }
        [[nodiscard]] const_reference back( ) const
        {
            return *( data( ) + ( size( ) - 1 ) );
        }

        [[nodiscard]] reference operator[]( size_type i )
        {
            return data( )[ i ];
        }
        [[nodiscard]] const_reference operator[]( size_type i ) const
        {
            return data( )[ i ];
        }

    };

    using D3DBlob = D3D10Blob;

    namespace D3D10
    {
        class Multithread : public Unknown
        {
        public:
            HCC_COM_STANDARD_METHODS_IMPL( Multithread, Unknown, ID3D10Multithread, IUnknown )
        public:
            void Enter( ) const
            {
                InterfaceType* pInterface = GetInterface( );
                return pInterface->Enter( );
            }

            void Leave( ) const
            {
                InterfaceType* pInterface = GetInterface( );
                return pInterface->Leave( );
            }

            bool SetMultithreadProtected( _In_  BOOL bMTProtect ) const
            {
                InterfaceType* pInterface = GetInterface( );
                return pInterface->SetMultithreadProtected( bMTProtect ) != FALSE;
            }

            bool GetMultithreadProtected( ) const
            {
                InterfaceType* pInterface = GetInterface( );
                return pInterface->GetMultithreadProtected( ) != FALSE;
            }
        };
    }

}

#endif
