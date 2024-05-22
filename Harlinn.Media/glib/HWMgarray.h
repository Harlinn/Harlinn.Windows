#pragma once
#ifndef HARLINN_MEDIA_GLIB_HWMGARRAY_H_
#define HARLINN_MEDIA_GLIB_HWMGARRAY_H_
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
    class ArrayBase
    {
        GArray* _array = nullptr;
    public:
        ArrayBase( ) = default;

        explicit ArrayBase( bool zeroTerminated, bool clear, UInt32 elementSize )
            : _array( g_array_new( zeroTerminated, clear, elementSize ) )
        {
        }

        explicit ArrayBase( bool zeroTerminated, bool clear, UInt32 elementSize, UInt32 reservedSize )
            : _array( g_array_sized_new( zeroTerminated, clear, elementSize, reservedSize ) )
        {
        }



        explicit ArrayBase( GArray* array, bool addRef = true )
            : _array( array )
        {
            if ( array && addRef )
            {
                g_array_ref( array );
            }
        }

        explicit ArrayBase( const ArrayBase& other )
            : _array( other._array )
        {
            if ( other._array )
            {
                g_array_ref( _array );
            }
        }

        explicit ArrayBase( ArrayBase&& other ) noexcept
            : _array( other._array )
        {
            other._array = nullptr;
        }


        ~ArrayBase( )
        {
            if ( _array )
            {
                g_array_unref( _array );
            }
        }

        ArrayBase& operator = ( const ArrayBase& other )
        {
            if ( _array != other._array )
            {
                if ( _array )
                {
                    g_array_unref( _array );
                }
                _array = other._array;
                if ( _array )
                {
                    g_array_ref( _array );
                }
            }
            return *this;
        }

        ArrayBase& operator = ( ArrayBase&& other ) noexcept
        {
            std::swap( _array, other._array );
            return *this;
        }

        template<typename T>
        T* At( size_t index ) const
        {
            return g_array_index( _array, T, index );
        }


        ArrayBase Copy( ) const
        {
            return ArrayBase( reinterpret_cast< GArray* >( g_array_copy( _array ) ), false );
        }

        void Append( gconstpointer data, UInt32 length )
        {
            g_array_append_vals( _array, data, length );
        }

        void Prepend( gconstpointer data, UInt32 length )
        {
            g_array_prepend_vals( _array, data, length );
        }

        bool BinarySearch( gconstpointer target, GCompareFunc compareFunc, UInt32* outMatchIndex ) const
        {
            return g_array_binary_search( _array, target, compareFunc, outMatchIndex );
        }

        UInt32 ElementSize( ) const
        {
            return g_array_get_element_size( _array );
        }

        void Insert( UInt32 index, gconstpointer data, UInt32 length )
        {
            g_array_insert_vals( _array, index, data, length );
        }

        void SetSize( UInt32 newSize )
        {
            g_array_set_size( _array, newSize );
        }

        void Remove( UInt32 index )
        {
            g_array_remove_index( _array, index );
        }

        void RemoveFast( UInt32 index )
        {
            g_array_remove_index_fast( _array, index );
        }

        void Remove( UInt32 index, UInt32 length )
        {
            g_array_remove_range( _array, index, length );
        }

        void Sort( GCompareFunc compareFunc )
        {
            g_array_sort( _array, compareFunc );
        }

        void Sort( GCompareDataFunc compareFunc, gpointer userData )
        {
            g_array_sort_with_data( _array, compareFunc, userData );
        }

        void SetClearFunc( GDestroyNotify clearFunc )
        {
            g_array_set_clear_func( _array, clearFunc );
        }
    };


    template<typename T>
    class Array : public ArrayBase
    {
    public:
        using element_type = T;
    };




    class PtrArray
    {
        GPtrArray* _array = nullptr;
    public:
        PtrArray( ) = default;

        explicit PtrArray( UInt32 reserveSize )
            : _array( g_ptr_array_sized_new( reserveSize ) )
        {
        }

        explicit PtrArray( GDestroyNotify elementFreeFunc )
            : _array( g_ptr_array_new_with_free_func( elementFreeFunc ) )
        {
        }

        explicit PtrArray( UInt32 reserveSize, GDestroyNotify elementFreeFunc )
            : _array( g_ptr_array_new_full( reserveSize, elementFreeFunc ) )
        {
        }

        explicit PtrArray( UInt32 reserveSize, GDestroyNotify elementFreeFunc, bool nullTerminated )
            : _array( g_ptr_array_new_null_terminated( reserveSize, elementFreeFunc, nullTerminated ) )
        {
        }


        explicit PtrArray( GPtrArray* array, bool addRef = true )
            : _array( array )
        {
            if ( array && addRef )
            {
                g_ptr_array_ref( array );
            }
        }

        static PtrArray Create( )
        {
            return PtrArray( g_ptr_array_new( ), false );
        }


        explicit PtrArray( const PtrArray& other )
            : _array( other._array )
        {
            if ( other._array )
            {
                g_ptr_array_ref( _array );
            }
        }

        explicit PtrArray( PtrArray&& other ) noexcept
            : _array( other._array )
        {
            other._array = nullptr;
        }


        ~PtrArray( )
        {
            if ( _array )
            {
                g_ptr_array_unref( _array );
            }
        }

        PtrArray& operator = ( const PtrArray& other )
        {
            if ( _array != other._array )
            {
                if ( _array )
                {
                    g_ptr_array_unref( _array );
                }
                _array = other._array;
                if ( _array )
                {
                    g_ptr_array_ref( _array );
                }
            }
            return *this;
        }

        PtrArray& operator = ( PtrArray&& other ) noexcept
        {
            std::swap( _array, other._array );
            return *this;
        }


        void* At( size_t index )
        {
            return g_ptr_array_index(_array, index );
        }

        void* operator[]( size_t index )
        {
            return g_ptr_array_index( _array, index );
        }


        PtrArray Copy( GCopyFunc func, gpointer userData ) const
        {
            return PtrArray( g_ptr_array_copy( _array, func, userData ), false );
        }

        void SetFreeFunc( GDestroyNotify elementFreeFunc )
        {
            g_ptr_array_set_free_func( _array, elementFreeFunc );
        }

        void SetSize( Int32 newSize )
        {
            g_ptr_array_set_size( _array, newSize );
        }



    };



}

#endif
