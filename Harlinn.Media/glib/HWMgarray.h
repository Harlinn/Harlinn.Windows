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
    template<typename T>
    struct ArrayT
    {
        T* data;
        UInt32 len;
    };
    using Array = ArrayT<char>;
    using ByteArray = ArrayT<Byte>;
    using PtrArray = ArrayT<Pointer>;
	struct Bytes;

	HWM_EXPORT Array* ArrayNew( Bool32 zeroTerminated, Bool32 clear, UInt32 elementSize );
	HWM_EXPORT Pointer ArraySteal( Array* array, size_t* len );
	HWM_EXPORT Array* ArraySizedNew( Bool32 zeroTerminated, Bool32 clear, UInt32 elementSize, UInt32 reservedSize );
	HWM_EXPORT Array* ArrayCopy( Array* array );
	HWM_EXPORT char* ArrayFree( Array* array, Bool32 freeSegment );
	HWM_EXPORT Array* ArrayRef( Array* array );
	HWM_EXPORT void ArrayUnref( Array* array );
	HWM_EXPORT UInt32 ArrayGetElementSize( Array* array );
	HWM_EXPORT Array* ArrayAppendVals( Array* array, ConstPointer data, UInt32 len );
	HWM_EXPORT Array* ArrayPrependVals( Array* array, ConstPointer data, UInt32 len );
	HWM_EXPORT Array* ArrayInsertVals( Array* array, UInt32 index, ConstPointer data, UInt32 len );
	HWM_EXPORT Array* ArraySetSize( Array* array, UInt32 length );
	HWM_EXPORT Array* ArrayRemoveIndex( Array* array, UInt32 index );
	HWM_EXPORT Array* ArrayRemoveIndexFast( Array* array, UInt32 index );
	HWM_EXPORT Array* ArrayRemoveRange( Array* array, UInt32 index, UInt32 length );
	HWM_EXPORT void ArraySort( Array* array, CompareFunc compareFunc );
	HWM_EXPORT void ArraySortWithData( Array* array, CompareDataFunc compareFunc, Pointer userData );
	HWM_EXPORT Bool32 ArrayBinarySearch( Array* array, ConstPointer target, CompareFunc compareFunc, UInt32* resultMatchIndex );
	HWM_EXPORT void ArraySetClearFunc( Array* array, DestroyNotify clearFunc );

	template<typename T>
	inline Array* ArrayAppendVal( Array* array, const T& v )
	{
		return ArrayAppendVals( array, &v, 1 );
	}

	template<typename T>
	inline Array* ArrayPrependVal( Array* array, const T& v )
	{
		return ArrayPrependVals( array, &v, 1 );
	}

	template<typename T>
	inline Array* ArrayInsertVal( Array* array, size_t index, const T& v )
	{
		return ArrayInsertVals( array, index, &v, 1 );
	}

	template<typename T>
	T& ArrayIndex( Array* array, size_t index )
	{
		reinterpret_cast< T* >( array->data )[ index ];
	}
	template<typename T>
	const T& ArrayIndex( const Array* array, size_t index )
	{
		reinterpret_cast< const T* >( array->data )[ index ];
	}

	/* Resizable pointer array.  This interface is much less complicated
	 * than the above.  Add appends a pointer.  Remove fills any cleared
	 * spot and shortens the array. remove_fast will again distort order.
	 */

	inline Pointer PtrArrayIndex( PtrArray* array, size_t index )
	{
		return array->data[ index ];
	}
	inline ConstPointer PtrArrayIndex( const PtrArray* array, size_t index )
	{
		return array->data[ index ];
	}

	template<typename T>
	inline T* PtrArrayIndex( PtrArray* array, size_t index )
	{
		return reinterpret_cast<T*>( array->data[ index ]);
	}
	template<typename T>
	inline const T* PtrArrayIndex( const PtrArray* array, size_t index )
	{
		return reinterpret_cast< const T* >( array->data[ index ] );
	}


	HWM_EXPORT PtrArray* PtrArrayNew( );
	HWM_EXPORT PtrArray* PtrArrayNewWithFreeFunc( DestroyNotify elementFreeFunc );
	HWM_EXPORT Pointer* PtrArraySteal( PtrArray* array, size_t* len );
	HWM_EXPORT PtrArray* PtrArrayCopy( PtrArray* array, CopyFunc func, Pointer userData );
	HWM_EXPORT PtrArray* PtrArraySizedNew( UInt32 reservedSize );
	HWM_EXPORT PtrArray* PtrArrayNewFull( UInt32 reservedSize, DestroyNotify elementFreeFunc );
	HWM_EXPORT PtrArray* PtrArrayNewNullTerminated( UInt32 reservedSize, DestroyNotify elementFreeFunc, Bool32 nullTerminated );
	HWM_EXPORT Pointer* PtrArrayFree( PtrArray* array, Bool32 freeSegment );
	HWM_EXPORT PtrArray* PtrArrayRef( PtrArray* array );
	HWM_EXPORT void PtrArrayUnref( PtrArray* array );
	HWM_EXPORT void PtrArraySetFreeFunc( PtrArray* array, DestroyNotify elementFreeFunc );
	HWM_EXPORT void PtrArraySetSize( PtrArray* array, Int32 length );
	HWM_EXPORT Pointer PtrArrayRemoveIndex( PtrArray* array, UInt32 index );
	HWM_EXPORT Pointer PtrArrayRemoveIndexFast( PtrArray* array, UInt32 index );
	HWM_EXPORT Pointer PtrArrayStealIndex( PtrArray* array, UInt32 index );
	HWM_EXPORT Pointer PtrArrayStealIndexFast( PtrArray* array, UInt32 index );
	HWM_EXPORT Bool32 PtrArrayRemove( PtrArray* array, Pointer data );
	HWM_EXPORT Bool32 PtrArrayRemoveFast( PtrArray* array, Pointer data );
	HWM_EXPORT PtrArray* PtrArrayRemoveRange( PtrArray* array, UInt32 index, UInt32 length );
	HWM_EXPORT void PtrArrayAdd( PtrArray* array, Pointer data );
	HWM_EXPORT void PtrArrayExtend( PtrArray* arrayToExtend, PtrArray* array, CopyFunc func, Pointer userData );
	HWM_EXPORT void PtrArrayExtendAndSteal( PtrArray* arrayToExtend, PtrArray* array );
	HWM_EXPORT void PtrArrayInsert( PtrArray* array, Int32 index, Pointer data );
	HWM_EXPORT void PtrArraySort( PtrArray* array, CompareFunc compareFunc );
	HWM_EXPORT void PtrArraySortWithData( PtrArray* array, CompareDataFunc compareFunc, Pointer userData );
	HWM_EXPORT void PtrArrayForeach( PtrArray* array, Func func, Pointer userData );
	HWM_EXPORT Bool32 PtrArrayFind( PtrArray* haystack, ConstPointer needle, UInt32* index );
	HWM_EXPORT Bool32 PtrArrayFindWithEqualFunc( PtrArray* haystack, ConstPointer  needle, EqualFunc equalFunc, UInt32* index );
	HWM_EXPORT Bool32 PtrArrayIsNullTerminated( PtrArray* array );

	
	// Byte arrays, an array of Byte. Implemented as a Array, but type-safe.
	HWM_EXPORT ByteArray* ByteArrayNew( void );
	HWM_EXPORT ByteArray* ByteArrayNewTake( Byte* data, size_t len );
	HWM_EXPORT Byte* ByteArraySteal( ByteArray* array, size_t* len );
	HWM_EXPORT ByteArray* ByteArraySizedNew( UInt32 reservedSize );
	HWM_EXPORT Byte* ByteArrayFree( ByteArray* array, Bool32 freeSegment );
	HWM_EXPORT Bytes* ByteArrayFreeToBytes( ByteArray* array );
	HWM_EXPORT ByteArray* ByteArrayRef( ByteArray* array );
	HWM_EXPORT void ByteArrayUnref( ByteArray* array );
	HWM_EXPORT ByteArray* ByteArrayAppend( ByteArray* array, const Byte* data, UInt32 len );
	HWM_EXPORT ByteArray* ByteArrayPrepend( ByteArray* array, const Byte* data, UInt32 len );
	HWM_EXPORT ByteArray* ByteArraySetSize( ByteArray* array, UInt32 length );
	HWM_EXPORT ByteArray* ByteArrayRemoveIndex( ByteArray* array, UInt32 index );
	HWM_EXPORT ByteArray* ByteArrayRemoveIndexFast( ByteArray* array, UInt32 index );
	HWM_EXPORT ByteArray* ByteArrayRemoveRange( ByteArray* array, UInt32 index, UInt32 length );
	HWM_EXPORT void ByteArraySort( ByteArray* array, CompareFunc compareFunc );
	HWM_EXPORT void ByteArraySortWithData( ByteArray* array, CompareDataFunc compareFunc, Pointer userData );


}

#endif
