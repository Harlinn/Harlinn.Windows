#pragma once
// =================================================================================================
// Copyright Adobe
// Copyright 2015 Adobe
// All Rights Reserved
//
// NOTICE:  Adobe permits you to use, modify, and distribute this file in accordance with the terms
// of the Adobe license agreement accompanying it. 
// =================================================================================================
#ifndef HARLINN_XMP_IPATHSEGMENT_INL
#define HARLINN_XMP_IPATHSEGMENT_INL


#include <assert.h>

namespace AdobeXMPCore {

	HXMP_INLINE IPathSegmentProxy::IPathSegmentProxy( pIPathSegment ptr )
		: mRawPtr( ptr )
	{
		mRawPtr->Acquire();
	}

	HXMP_INLINE IPathSegmentProxy::~IPathSegmentProxy() __NOTHROW__ { mRawPtr->Release(); }

	HXMP_INLINE void IPathSegmentProxy::Acquire() const __NOTHROW__ { assert( false ); }

	HXMP_INLINE void IPathSegmentProxy::Release() const __NOTHROW__ { assert( false ); }

	HXMP_INLINE AdobeXMPCommon_Int::pISharedObject_I IPathSegmentProxy::GetISharedObject_I() __NOTHROW__ {
		return mRawPtr->GetISharedObject_I();
	}

	HXMP_INLINE AdobeXMPCore_Int::pIPathSegment_I IPathSegmentProxy::GetIPathSegment_I() __NOTHROW__ {
		return mRawPtr->GetIPathSegment_I();
	}

	HXMP_INLINE pvoid IPathSegmentProxy::GetInterfacePointer( uint64 interfaceID, uint32 interfaceVersion ) {
		return CallSafeFunction< IVersionable, pvoid, pvoid, uint64, uint32 >(
			mRawPtr, &IVersionable::getInterfacePointer, interfaceID, interfaceVersion );
	}

	HXMP_INLINE pvoid IPathSegmentProxy::getInterfacePointer( uint64 interfaceID, uint32 interfaceVersion, pcIError_base & error ) __NOTHROW__ {
		assert( false );
		return mRawPtr->getInterfacePointer( interfaceID, interfaceVersion, error );
	}

	HXMP_INLINE spcIUTF8String IPathSegmentProxy::GetNameSpace() const {
		return CallConstSafeFunctionReturningPointer< IPathSegment_v1, pcIUTF8String_base, const IUTF8String >(
			mRawPtr, &IPathSegment_v1::getNameSpace );
	}

	HXMP_INLINE pcIUTF8String_base IPathSegmentProxy::getNameSpace( pcIError_base & error ) const __NOTHROW__ {
		assert( false );
		return mRawPtr->getNameSpace( error );
	}

	HXMP_INLINE spcIUTF8String IPathSegmentProxy::GetName() const {
		return CallConstSafeFunctionReturningPointer< IPathSegment_v1, pcIUTF8String_base, const IUTF8String >(
			mRawPtr, &IPathSegment_v1::getName );
	}

	HXMP_INLINE pcIUTF8String_base IPathSegmentProxy::getName( pcIError_base & error ) const __NOTHROW__ {
		assert( false );
		return mRawPtr->getName( error );
	}

	HXMP_INLINE IPathSegment::ePathSegmentType IPathSegmentProxy::GetType() const {
		return CallConstSafeFunction< IPathSegment_v1, ePathSegmentType, uint32 >(
			mRawPtr, &IPathSegment_v1::getType );
	}

	HXMP_INLINE uint32 IPathSegmentProxy::getType( pcIError_base & error ) const __NOTHROW__ {
		assert( false );
		return mRawPtr->getType( error );
	}

	HXMP_INLINE sizet IPathSegmentProxy::GetIndex() const __NOTHROW__ {
		return mRawPtr->GetIndex();
	}

	HXMP_INLINE spcIUTF8String IPathSegmentProxy::GetValue() const {
		return CallConstSafeFunctionReturningPointer< IPathSegment_v1, pcIUTF8String_base, const IUTF8String >(
			mRawPtr, &IPathSegment_v1::getValue );
	}

	HXMP_INLINE pcIUTF8String_base IPathSegmentProxy::getValue( pcIError_base & error ) const __NOTHROW__ {
		assert( false );
		return mRawPtr->getValue( error );
	}
}

#endif



