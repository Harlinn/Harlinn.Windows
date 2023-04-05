#pragma once
// =================================================================================================
// Copyright Adobe
// Copyright 2015 Adobe
// All Rights Reserved
//
// NOTICE:  Adobe permits you to use, modify, and distribute this file in accordance with the terms
// of the Adobe license agreement accompanying it. 
// =================================================================================================



#include <assert.h>

namespace AdobeXMPCore {

#if XMP_WinBuild
	#pragma warning( push )
	#pragma warning( disable : 4250 )
#endif

	HXMP_INLINE ISimpleNodeProxy::ISimpleNodeProxy( pISimpleNode ptr )
		: mRawPtr( ptr )
		, INodeProxy( ptr ) {}

	HXMP_INLINE ISimpleNodeProxy::~ISimpleNodeProxy() __NOTHROW__ {}


	HXMP_INLINE AdobeXMPCore_Int::pISimpleNode_I ISimpleNodeProxy::GetISimpleNode_I() __NOTHROW__ {
		return mRawPtr->GetISimpleNode_I();
	}

	HXMP_INLINE spcIUTF8String ISimpleNodeProxy::GetValue() const {
		return CallConstSafeFunctionReturningPointer< ISimpleNode_v1, pcIUTF8String_base, const IUTF8String >(
			mRawPtr, &ISimpleNode_v1::getValue );
	}

	HXMP_INLINE void ISimpleNodeProxy::SetValue( const char * value, sizet valueLength ) {
		return CallSafeFunctionReturningVoid< ISimpleNode_v1, const char *, sizet >(
			mRawPtr, &ISimpleNode_v1::setValue, value, valueLength );
	}

	HXMP_INLINE bool ISimpleNodeProxy::IsURIType() const {
		return CallConstSafeFunction< ISimpleNode_v1, bool, uint32 >(
			mRawPtr, &ISimpleNode_v1::isURIType );
	}

	HXMP_INLINE void ISimpleNodeProxy::SetURIType( bool isURI ) {
		return CallSafeFunctionReturningVoid< ISimpleNode_v1, uint32 >(
			mRawPtr, &ISimpleNode_v1::setURIType, isURI ? 1 : 0 );
	}

	HXMP_INLINE pcIUTF8String_base ISimpleNodeProxy::getValue( pcIError_base & error ) const __NOTHROW__ {
		assert( false );
		return mRawPtr->getValue( error );
	}

	HXMP_INLINE void ISimpleNodeProxy::setValue( const char * value, sizet valueLength, pcIError_base & error ) __NOTHROW__ {
		assert( false );
		return mRawPtr->setValue( value, valueLength, error );
	}

	HXMP_INLINE uint32 ISimpleNodeProxy::isURIType( pcIError_base & error ) const __NOTHROW__ {
		assert( false );
		return mRawPtr->isURIType( error );
	}

	HXMP_INLINE void ISimpleNodeProxy::setURIType( uint32 isURI, pcIError_base & error ) __NOTHROW__ {
		assert( false );
		return mRawPtr->setURIType( isURI, error );
	}


#if XMP_WinBuild
	#pragma warning( pop )
#endif
}




