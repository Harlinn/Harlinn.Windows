#pragma once
// =================================================================================================
// Copyright Adobe
// Copyright 2015 Adobe
// All Rights Reserved
//
// NOTICE:  Adobe permits you to use, modify, and distribute this file in accordance with the terms
// of the Adobe license agreement accompanying it. 
// =================================================================================================
#ifndef HARLINN_XMP_IDOMIMPLEMENTATIONREGISTRY_INL_
#define HARLINN_XMP_IDOMIMPLEMENTATIONREGISTRY_INL_

#include <assert.h>

namespace AdobeXMPCore {

	HXMP_INLINE IDOMImplementationRegistryProxy::IDOMImplementationRegistryProxy( pIDOMImplementationRegistry ptr )
		: mRawPtr( ptr )
	{
		mRawPtr->Acquire();
	}

	HXMP_INLINE IDOMImplementationRegistryProxy::~IDOMImplementationRegistryProxy() __NOTHROW__ { mRawPtr->Release(); }

	HXMP_INLINE void IDOMImplementationRegistryProxy::Acquire() const __NOTHROW__ { assert( false ); }

	HXMP_INLINE void IDOMImplementationRegistryProxy::Release() const __NOTHROW__ { assert( false ); }

	HXMP_INLINE AdobeXMPCommon_Int::pISharedObject_I IDOMImplementationRegistryProxy::GetISharedObject_I() __NOTHROW__ {
		return mRawPtr->GetISharedObject_I();
	}

	HXMP_INLINE AdobeXMPCore_Int::pIDOMImplementationRegistry_I IDOMImplementationRegistryProxy::GetIDOMImplementationRegistry_I() __NOTHROW__ {
		return mRawPtr->GetIDOMImplementationRegistry_I();
	}

	HXMP_INLINE pvoid IDOMImplementationRegistryProxy::GetInterfacePointer( uint64 interfaceID, uint32 interfaceVersion ) {
		return CallSafeFunction< IVersionable, pvoid, pvoid, uint64, uint32 >(
			mRawPtr, &IVersionable::getInterfacePointer, interfaceID, interfaceVersion );
	}

	HXMP_INLINE pvoid IDOMImplementationRegistryProxy::getInterfacePointer( uint64 interfaceID, uint32 interfaceVersion, pcIError_base & error ) __NOTHROW__ {
		assert( false );
		return mRawPtr->getInterfacePointer( interfaceID, interfaceVersion, error );
	}

	HXMP_INLINE spIDOMParser IDOMImplementationRegistryProxy::GetParser( const char * key ) const {
		return CallConstSafeFunctionReturningPointer< IDOMImplementationRegistry, pIDOMParser_base, IDOMParser, const char * >(
			mRawPtr, &IDOMImplementationRegistry::getParser, key );
	}

	HXMP_INLINE spIDOMSerializer IDOMImplementationRegistryProxy::GetSerializer( const char * key ) const {
		return CallConstSafeFunctionReturningPointer< IDOMImplementationRegistry, pIDOMSerializer_base, IDOMSerializer, const char * >(
			mRawPtr, &IDOMImplementationRegistry::getSerializer, key );
	}

	HXMP_INLINE bool IDOMImplementationRegistryProxy::RegisterParser( const char * key, pIClientDOMParser_base parser ) {
		return CallSafeFunction< IDOMImplementationRegistry, bool, uint32, const char *, pIClientDOMParser_base >(
			mRawPtr, &IDOMImplementationRegistry::registerParser, key, parser );
	}

	HXMP_INLINE bool IDOMImplementationRegistryProxy::RegisterSerializer( const char * key, pIClientDOMSerializer_base serializer ) {
		return CallSafeFunction< IDOMImplementationRegistry, bool, uint32, const char *, pIClientDOMSerializer_base >(
			mRawPtr, &IDOMImplementationRegistry::registerSerializer, key, serializer );
	}

	HXMP_INLINE pIDOMParser_base IDOMImplementationRegistryProxy::getParser( const char * key, pcIError_base & error ) const __NOTHROW__ {
		assert( false );
		return mRawPtr->getParser( key, error );
	}

	HXMP_INLINE pIDOMSerializer_base IDOMImplementationRegistryProxy::getSerializer( const char * key, pcIError_base & error ) const __NOTHROW__ {
		assert( false );
		return mRawPtr->getSerializer( key, error );
	}

	HXMP_INLINE uint32 IDOMImplementationRegistryProxy::registerParser( const char * key, pIClientDOMParser_base parser, pcIError_base & error ) __NOTHROW__ {
		assert( false );
		return mRawPtr->registerParser( key, parser, error );
	}

	HXMP_INLINE uint32 IDOMImplementationRegistryProxy::registerSerializer( const char * key, pIClientDOMSerializer_base serializer, pcIError_base & error ) __NOTHROW__ {
		assert( false );
		return mRawPtr->registerSerializer( key, serializer, error );
	}



}

#endif


