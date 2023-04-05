#pragma once
// =================================================================================================
// Copyright Adobe
// Copyright 2015 Adobe
// All Rights Reserved
//
// NOTICE:  Adobe permits you to use, modify, and distribute this file in accordance with the terms
// of the Adobe license agreement accompanying it. 
// =================================================================================================
#ifndef HARLINN_XMP_IPATH_INL_
#define HARLINN_XMP_IPATH_INL_

#include <assert.h>

namespace AdobeXMPCore {

	HXMP_INLINE IPathProxy::IPathProxy( pIPath ptr )
		: mRawPtr( ptr )
	{
		mRawPtr->Acquire();
	}

	HXMP_INLINE IPathProxy::~IPathProxy() __NOTHROW__ { mRawPtr->Release(); }

	HXMP_INLINE void IPathProxy::Acquire() const __NOTHROW__ { assert( false ); }

	HXMP_INLINE void IPathProxy::Release() const __NOTHROW__ { assert( false ); }

	HXMP_INLINE AdobeXMPCommon_Int::pISharedObject_I IPathProxy::GetISharedObject_I() __NOTHROW__ {
		return mRawPtr->GetISharedObject_I();
	}

	HXMP_INLINE AdobeXMPCore_Int::pIPath_I IPathProxy::GetIPath_I() __NOTHROW__ {
		return mRawPtr->GetIPath_I();
	}

	HXMP_INLINE pvoid IPathProxy::GetInterfacePointer( uint64 interfaceID, uint32 interfaceVersion ) {
		return CallSafeFunction< IVersionable, pvoid, pvoid, uint64, uint32 >(
			mRawPtr, &IVersionable::getInterfacePointer, interfaceID, interfaceVersion );
	}

	HXMP_INLINE pvoid IPathProxy::getInterfacePointer( uint64 interfaceID, uint32 interfaceVersion, pcIError_base & error ) __NOTHROW__ {
		assert( false );
		return mRawPtr->getInterfacePointer( interfaceID, interfaceVersion, error );
	}

	HXMP_INLINE spcINameSpacePrefixMap IPathProxy::RegisterNameSpacePrefixMap( const spcINameSpacePrefixMap & map ) {
		return CallSafeFunctionReturningPointer< IPath_v1, pcINameSpacePrefixMap_base, const INameSpacePrefixMap, pcINameSpacePrefixMap_base >(
			mRawPtr, &IPath_v1::registerNameSpacePrefixMap, map ? map->GetActualINameSpacePrefixMap() : NULL );
	}

	HXMP_INLINE pcINameSpacePrefixMap_base IPathProxy::registerNameSpacePrefixMap( pcINameSpacePrefixMap_base map, pcIError_base & error ) __NOTHROW__ {
		assert( false );
		return mRawPtr->registerNameSpacePrefixMap( map, error );
	}

	HXMP_INLINE spIUTF8String IPathProxy::Serialize( const spcINameSpacePrefixMap & map ) const {
		return CallConstSafeFunctionReturningPointer< IPath_v1, pIUTF8String_base, IUTF8String, pcINameSpacePrefixMap_base >(
			mRawPtr, &IPath_v1::serialize, map ? map->GetActualINameSpacePrefixMap() : NULL );
	}

	HXMP_INLINE pIUTF8String_base IPathProxy::serialize( pcINameSpacePrefixMap_base map, pcIError_base & error ) const __NOTHROW__ {
		assert( false );
		return mRawPtr->serialize( map, error );
	}

	HXMP_INLINE void IPathProxy::AppendPathSegment( const spcIPathSegment & segment ) {
		return CallSafeFunctionReturningVoid< IPath_v1, pcIPathSegment_base >(
			mRawPtr, &IPath_v1::appendPathSegment, segment ? segment->GetActualIPathSegment() : NULL );
	}

	HXMP_INLINE void IPathProxy::appendPathSegment( pcIPathSegment_base segment, pcIError_base & error ) __NOTHROW__ {
		assert( false );
		return mRawPtr->appendPathSegment( segment, error );
	}

	HXMP_INLINE spcIPathSegment IPathProxy::RemovePathSegment( sizet index ) {
		return CallSafeFunctionReturningPointer< IPath_v1, pcIPathSegment_base, const IPathSegment, sizet >(
			mRawPtr, &IPath_v1::removePathSegment, index );
	}

	HXMP_INLINE pcIPathSegment_base IPathProxy::removePathSegment( sizet index, pcIError_base & error ) __NOTHROW__ {
		assert( false );
		return mRawPtr->removePathSegment( index, error );
	}

	HXMP_INLINE spcIPathSegment IPathProxy::GetPathSegment( sizet index ) const {
		return CallConstSafeFunctionReturningPointer< IPath_v1, pcIPathSegment_base, const IPathSegment, sizet >(
			mRawPtr, &IPath_v1::getPathSegment, index );
	}

	HXMP_INLINE pcIPathSegment_base IPathProxy::getPathSegment( sizet index, pcIError_base & error ) const __NOTHROW__ {
		assert( false );
		return mRawPtr->getPathSegment( index, error );
	}

	HXMP_INLINE sizet IPathProxy::Size() const __NOTHROW__ {
		return mRawPtr->Size(  );
	}

	HXMP_INLINE void IPathProxy::Clear() __NOTHROW__ {
		return mRawPtr->Clear(  );
	}

	HXMP_INLINE spIPath IPathProxy::Clone( sizet startingIndex, sizet countOfSegments ) const {
		return CallConstSafeFunctionReturningPointer< IPath_v1, pIPath_base, IPath, sizet, sizet >(
			mRawPtr, &IPath_v1::clone, startingIndex, countOfSegments );
	}

	HXMP_INLINE pIPath_base IPathProxy::clone( sizet startingIndex, sizet countOfSegemetns, pcIError_base & error ) const __NOTHROW__ {
		assert( false );
		return mRawPtr->clone( startingIndex, countOfSegemetns, error );
	}

}

#endif


