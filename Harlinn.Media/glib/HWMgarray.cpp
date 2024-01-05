/*
   Copyright 2024 Espen Harlinn

   Licensed under the Apache License, Version 2.0 (the "License")
   you may not use this file except in compliance with the License.
   You may obtain a copy of the License at

       http://www.apache.org/licenses/LICENSE-2.0

   Unless required by applicable law or agreed to in writing, software
   distributed under the License is distributed on an "AS IS" BASIS,
   WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
   See the License for the specific language governing permissions and
   limitations under the License.
*/
#include "pch.h"
#include "HWMgarray.h"
#include <gst/gst.h>
namespace Harlinn::Media::GLib
{
	static_assert( sizeof( Array ) == sizeof( GArray ) );
	static_assert( sizeof( PtrArray ) == sizeof( GPtrArray ) );
	static_assert( sizeof( ByteArray ) == sizeof( GByteArray ) );

	HWM_EXPORT Array* ArrayNew( Bool32 zeroTerminated, Bool32 clear, UInt32 elementSize )
	{
		return reinterpret_cast< Array* >( g_array_new( zeroTerminated, clear, elementSize ) );
	}
	HWM_EXPORT Pointer ArraySteal( Array* array, size_t* len )
	{
		return g_array_steal( reinterpret_cast< GArray* >( array ), len );
	}
	HWM_EXPORT Array* ArraySizedNew( Bool32 zeroTerminated, Bool32 clear, UInt32 elementSize, UInt32 reservedSize )
	{
		return reinterpret_cast< Array* >( g_array_sized_new( zeroTerminated, clear, elementSize, reservedSize ) );
	}
	HWM_EXPORT Array* ArrayCopy( Array* array )
	{
		return reinterpret_cast< Array* >( g_array_copy( reinterpret_cast< GArray* >( array ) ) );
	}
	HWM_EXPORT char* ArrayFree( Array* array, Bool32 freeSegment )
	{
		return g_array_free( reinterpret_cast< GArray* >( array ), freeSegment );
	}
	HWM_EXPORT Array* ArrayRef( Array* array )
	{
		return reinterpret_cast< Array* >( g_array_ref( reinterpret_cast< GArray* >( array ) ) );
	}
	HWM_EXPORT void ArrayUnref( Array* array )
	{
		g_array_unref( reinterpret_cast< GArray* >( array ) );
	}
	HWM_EXPORT UInt32 ArrayGetElementSize( Array* array )
	{
		return g_array_get_element_size( reinterpret_cast< GArray* >( array ) );
	}
	HWM_EXPORT Array* ArrayAppendVals( Array* array, ConstPointer data, UInt32 len )
	{
		return reinterpret_cast< Array* >( g_array_append_vals( reinterpret_cast< GArray* >( array ), data, len ) );
	}
	HWM_EXPORT Array* ArrayPrependVals( Array* array, ConstPointer data, UInt32 len )
	{
		return reinterpret_cast< Array* >( g_array_prepend_vals( reinterpret_cast< GArray* >( array ), data, len ) );
	}
	HWM_EXPORT Array* ArrayInsertVals( Array* array, UInt32 index, ConstPointer data, UInt32 len )
	{
		return reinterpret_cast< Array* >( g_array_insert_vals( reinterpret_cast< GArray* >( array ), index, data, len ) );
	}
	HWM_EXPORT Array* ArraySetSize( Array* array, UInt32 length )
	{
		return reinterpret_cast< Array* >( g_array_set_size( reinterpret_cast< GArray* >( array ), length ) );
	}
	HWM_EXPORT Array* ArrayRemoveIndex( Array* array, UInt32 index )
	{
		return reinterpret_cast< Array* >( g_array_remove_index( reinterpret_cast< GArray* >( array ), index ) );
	}
	HWM_EXPORT Array* ArrayRemoveIndexFast( Array* array, UInt32 index )
	{
		return reinterpret_cast< Array* >( g_array_remove_index_fast( reinterpret_cast< GArray* >( array ), index ) );
	}
	HWM_EXPORT Array* ArrayRemoveRange( Array* array, UInt32 index, UInt32 length )
	{
		return reinterpret_cast< Array* >( g_array_remove_range( reinterpret_cast< GArray* >( array ), index, length ) );
	}
	HWM_EXPORT void ArraySort( Array* array, CompareFunc compareFunc )
	{
		g_array_sort( reinterpret_cast< GArray* >( array ), compareFunc );
	}
	HWM_EXPORT void ArraySortWithData( Array* array, CompareDataFunc compareFunc, Pointer userData )
	{
		g_array_sort_with_data( reinterpret_cast< GArray* >( array ), compareFunc, userData );
	}
	HWM_EXPORT Bool32 ArrayBinarySearch( Array* array, ConstPointer target, CompareFunc compareFunc, UInt32* resultMatchIndex )
	{
		return g_array_binary_search( reinterpret_cast< GArray* >( array ), target, compareFunc, resultMatchIndex );
	}
	HWM_EXPORT void ArraySetClearFunc( Array* array, DestroyNotify clearFunc )
	{
		g_array_set_clear_func( reinterpret_cast< GArray* >( array ), clearFunc );
	}

	HWM_EXPORT PtrArray* PtrArrayNew( )
	{
		return reinterpret_cast< PtrArray* >( g_ptr_array_new( ) );
	}
	HWM_EXPORT PtrArray* PtrArrayNewWithFreeFunc( DestroyNotify elementFreeFunc )
	{
		return reinterpret_cast< PtrArray* >( g_ptr_array_new_with_free_func( elementFreeFunc ) );
	}
	HWM_EXPORT Pointer* PtrArraySteal( PtrArray* array, size_t* len )
	{
		return g_ptr_array_steal( reinterpret_cast< GPtrArray* >( array ), len );
	}
	HWM_EXPORT PtrArray* PtrArrayCopy( PtrArray* array, CopyFunc func, Pointer userData )
	{
		return reinterpret_cast< PtrArray* >( g_ptr_array_copy( reinterpret_cast< GPtrArray* >( array ), func, userData ));
	}
	HWM_EXPORT PtrArray* PtrArraySizedNew( UInt32 reservedSize )
	{
		return reinterpret_cast< PtrArray* >( g_ptr_array_sized_new( reservedSize ) );
	}
	HWM_EXPORT PtrArray* PtrArrayNewFull( UInt32 reservedSize, DestroyNotify elementFreeFunc )
	{
		return reinterpret_cast< PtrArray* >( g_ptr_array_new_full( reservedSize, elementFreeFunc ) );
	}
	HWM_EXPORT PtrArray* PtrArrayNewNullTerminated( UInt32 reservedSize, DestroyNotify elementFreeFunc, Bool32 nullTerminated )
	{
		return reinterpret_cast< PtrArray* >( g_ptr_array_new_null_terminated( reservedSize, elementFreeFunc, nullTerminated ) );
	}
	HWM_EXPORT Pointer* PtrArrayFree( PtrArray* array, Bool32 freeSegment )
	{
		return g_ptr_array_free( reinterpret_cast< GPtrArray* >( array ), freeSegment );
	}
	HWM_EXPORT PtrArray* PtrArrayRef( PtrArray* array )
	{
		return reinterpret_cast< PtrArray* >( g_ptr_array_ref( reinterpret_cast< GPtrArray* >( array ) ) );
	}
	HWM_EXPORT void PtrArrayUnref( PtrArray* array )
	{
		g_ptr_array_unref( reinterpret_cast< GPtrArray* >( array ) );
	}
	HWM_EXPORT void PtrArraySetFreeFunc( PtrArray* array, DestroyNotify elementFreeFunc )
	{
		g_ptr_array_set_free_func( reinterpret_cast< GPtrArray* >( array ), elementFreeFunc );
	}
	HWM_EXPORT void PtrArraySetSize( PtrArray* array, Int32 length )
	{
		g_ptr_array_set_size( reinterpret_cast< GPtrArray* >( array ), length );
	}
	HWM_EXPORT Pointer PtrArrayRemoveIndex( PtrArray* array, UInt32 index )
	{
		return g_ptr_array_remove_index( reinterpret_cast< GPtrArray* >( array ), index );
	}
	HWM_EXPORT Pointer PtrArrayRemoveIndexFast( PtrArray* array, UInt32 index )
	{
		return g_ptr_array_remove_index_fast( reinterpret_cast< GPtrArray* >( array ), index );
	}
	HWM_EXPORT Pointer PtrArrayStealIndex( PtrArray* array, UInt32 index )
	{
		return g_ptr_array_steal_index( reinterpret_cast< GPtrArray* >( array ), index );
	}
	HWM_EXPORT Pointer PtrArrayStealIndexFast( PtrArray* array, UInt32 index )
	{
		return g_ptr_array_steal_index_fast( reinterpret_cast< GPtrArray* >( array ), index );
	}
	HWM_EXPORT Bool32 PtrArrayRemove( PtrArray* array, Pointer data )
	{
		return g_ptr_array_remove( reinterpret_cast< GPtrArray* >( array ), data );
	}
	HWM_EXPORT Bool32 PtrArrayRemoveFast( PtrArray* array, Pointer data )
	{
		return g_ptr_array_remove_fast( reinterpret_cast< GPtrArray* >( array ), data );
	}
	HWM_EXPORT PtrArray* PtrArrayRemoveRange( PtrArray* array, UInt32 index, UInt32 length )
	{
		return reinterpret_cast< PtrArray* >( g_ptr_array_remove_range( reinterpret_cast< GPtrArray* >( array ), index, length ) );
	}
	HWM_EXPORT void PtrArrayAdd( PtrArray* array, Pointer data )
	{
		g_ptr_array_add( reinterpret_cast< GPtrArray* >( array ), data );
	}
	HWM_EXPORT void PtrArrayExtend( PtrArray* arrayToExtend, PtrArray* array, CopyFunc func, Pointer userData )
	{
		g_ptr_array_extend( reinterpret_cast< GPtrArray* >( arrayToExtend ), reinterpret_cast< GPtrArray* >( array ), func, userData );
	}
	HWM_EXPORT void PtrArrayExtendAndSteal( PtrArray* arrayToExtend, PtrArray* array )
	{
		g_ptr_array_extend_and_steal( reinterpret_cast< GPtrArray* >( arrayToExtend ), reinterpret_cast< GPtrArray* >( array ) );
	}
	HWM_EXPORT void PtrArrayInsert( PtrArray* array, Int32 index, Pointer data )
	{
		g_ptr_array_insert( reinterpret_cast< GPtrArray* >( array ), index, data );
	}
	HWM_EXPORT void PtrArraySort( PtrArray* array, CompareFunc compareFunc )
	{
		g_ptr_array_sort( reinterpret_cast< GPtrArray* >( array ), compareFunc );
	}
	HWM_EXPORT void PtrArraySortWithData( PtrArray* array, CompareDataFunc compareFunc, Pointer userData )
	{
		g_ptr_array_sort_with_data( reinterpret_cast< GPtrArray* >( array ), compareFunc, userData );
	}
	HWM_EXPORT void PtrArrayForeach( PtrArray* array, Func func, Pointer userData )
	{
		g_ptr_array_foreach( reinterpret_cast< GPtrArray* >( array ), func, userData );
	}
	HWM_EXPORT Bool32 PtrArrayFind( PtrArray* haystack, ConstPointer needle, UInt32* index )
	{
		return g_ptr_array_find( reinterpret_cast< GPtrArray* >( haystack ), needle, index );
	}
	HWM_EXPORT Bool32 PtrArrayFindWithEqualFunc( PtrArray* haystack, ConstPointer  needle, EqualFunc equalFunc, UInt32* index )
	{
		return g_ptr_array_find_with_equal_func( reinterpret_cast< GPtrArray* >( haystack ), needle, equalFunc, index );
	}
	HWM_EXPORT Bool32 PtrArrayIsNullTerminated( PtrArray* array )
	{
		return g_ptr_array_is_null_terminated( reinterpret_cast< GPtrArray* >( array ) );
	}


	// Byte arrays, an array of Byte. Implemented as a Array, but type-safe.
	HWM_EXPORT ByteArray* ByteArrayNew( void )
	{
		return reinterpret_cast< ByteArray* >( g_byte_array_new( ) );
	}
	HWM_EXPORT ByteArray* ByteArrayNewTake( Byte* data, size_t len )
	{
		return reinterpret_cast< ByteArray* >( g_byte_array_new_take( data, len ) );
	}
	HWM_EXPORT Byte* ByteArraySteal( ByteArray* array, size_t* len )
	{
		return g_byte_array_steal( reinterpret_cast< GByteArray* >( array ), len );
	}
	HWM_EXPORT ByteArray* ByteArraySizedNew( UInt32 reservedSize )
	{
		return reinterpret_cast< ByteArray* >( g_byte_array_sized_new( reservedSize ) );
	}
	HWM_EXPORT Byte* ByteArrayFree( ByteArray* array, Bool32 freeSegment )
	{
		return g_byte_array_free( reinterpret_cast< GByteArray* >( array ), freeSegment );
	}
	HWM_EXPORT Bytes* ByteArrayFreeToBytes( ByteArray* array )
	{
		return reinterpret_cast< Bytes* >( g_byte_array_free_to_bytes( reinterpret_cast< GByteArray* >( array ) ) );
	}
	HWM_EXPORT ByteArray* ByteArrayRef( ByteArray* array )
	{
		return reinterpret_cast< ByteArray* >( g_byte_array_ref( reinterpret_cast< GByteArray* >( array ) ) );
	}
	HWM_EXPORT void ByteArrayUnref( ByteArray* array )
	{
		g_byte_array_unref( reinterpret_cast< GByteArray* >( array ) );
	}
	HWM_EXPORT ByteArray* ByteArrayAppend( ByteArray* array, const Byte* data, UInt32 len )
	{
		return reinterpret_cast< ByteArray* >( g_byte_array_append( reinterpret_cast< GByteArray* >( array ), data, len ) );
	}
	HWM_EXPORT ByteArray* ByteArrayPrepend( ByteArray* array, const Byte* data, UInt32 len )
	{
		return reinterpret_cast< ByteArray* >( g_byte_array_prepend( reinterpret_cast< GByteArray* >( array ), data, len ) );
	}
	HWM_EXPORT ByteArray* ByteArraySetSize( ByteArray* array, UInt32 length )
	{
		return reinterpret_cast< ByteArray* >( g_byte_array_set_size( reinterpret_cast< GByteArray* >( array ), length ) );
	}
	HWM_EXPORT ByteArray* ByteArrayRemoveIndex( ByteArray* array, UInt32 index )
	{
		return reinterpret_cast< ByteArray* >( g_byte_array_remove_index( reinterpret_cast< GByteArray* >( array ), index ) );
	}
	HWM_EXPORT ByteArray* ByteArrayRemoveIndexFast( ByteArray* array, UInt32 index )
	{
		return reinterpret_cast< ByteArray* >( g_byte_array_remove_index( reinterpret_cast< GByteArray* >( array ), index ) );
	}
	HWM_EXPORT ByteArray* ByteArrayRemoveRange( ByteArray* array, UInt32 index, UInt32 length )
	{
		return reinterpret_cast< ByteArray* >( g_byte_array_remove_range( reinterpret_cast< GByteArray* >( array ), index, length ) );
	}
	HWM_EXPORT void ByteArraySort( ByteArray* array, CompareFunc compareFunc )
	{
		g_byte_array_sort( reinterpret_cast< GByteArray* >( array ), compareFunc );
	}
	HWM_EXPORT void ByteArraySortWithData( ByteArray* array, CompareDataFunc compareFunc, Pointer userData )
	{
		g_byte_array_sort_with_data( reinterpret_cast< GByteArray* >( array ), compareFunc, userData );
	}
}