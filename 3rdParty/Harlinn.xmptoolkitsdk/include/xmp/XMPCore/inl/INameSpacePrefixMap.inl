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



	HXMP_INLINE INameSpacePrefixMapProxy::INameSpacePrefixMapProxy( pINameSpacePrefixMap ptr )
		: mRawPtr( ptr )
	{
		mRawPtr->Acquire();
	}

	HXMP_INLINE INameSpacePrefixMapProxy::~INameSpacePrefixMapProxy() __NOTHROW__ { mRawPtr->Release(); }


	HXMP_INLINE void INameSpacePrefixMapProxy::Acquire() const __NOTHROW__ { assert( false ); }

	HXMP_INLINE void INameSpacePrefixMapProxy::Release() const __NOTHROW__ { assert( false ); }

	HXMP_INLINE AdobeXMPCommon_Int::pISharedObject_I INameSpacePrefixMapProxy::GetISharedObject_I() __NOTHROW__ {
		return mRawPtr->GetISharedObject_I();
	}

	HXMP_INLINE AdobeXMPCore_Int::pINameSpacePrefixMap_I INameSpacePrefixMapProxy::GetINameSpacePrefixMap_I() __NOTHROW__ {
		return mRawPtr->GetINameSpacePrefixMap_I();
	}

	HXMP_INLINE pvoid INameSpacePrefixMapProxy::GetInterfacePointer( uint64 interfaceID, uint32 interfaceVersion ) {
		return CallSafeFunction< IVersionable, pvoid, pvoid, uint64, uint32 >(
			mRawPtr, &IVersionable::getInterfacePointer, interfaceID, interfaceVersion );
	}

	HXMP_INLINE pvoid INameSpacePrefixMapProxy::getInterfacePointer( uint64 interfaceID, uint32 interfaceVersion, pcIError_base & error ) __NOTHROW__ {
		assert( false );
		return mRawPtr->getInterfacePointer( interfaceID, interfaceVersion, error );
	}

	HXMP_INLINE bool INameSpacePrefixMapProxy::INameSpacePrefixMapProxy::Insert( const char * prefix, sizet prefixLength, const char * nameSpace, sizet nameSpaceLength ) {
		return CallSafeFunction< INameSpacePrefixMap_v1, bool, uint32, const char *, sizet, const char *, sizet >(
			mRawPtr, &INameSpacePrefixMap_v1::insert, prefix, prefixLength, nameSpace, nameSpaceLength );
	}

	HXMP_INLINE uint32 INameSpacePrefixMapProxy::insert( const char * prefix, sizet prefixLength, const char * nameSpace, sizet nameSpaceLength, pcIError_base & error ) __NOTHROW__ {
		assert( false );
		return mRawPtr->insert( prefix, prefixLength, nameSpace, nameSpaceLength, error );
	}

	HXMP_INLINE bool INameSpacePrefixMapProxy::RemovePrefix( const char * prefix, sizet prefixLength ) {
		return CallSafeFunction< INameSpacePrefixMap_v1, bool, uint32, uint32, const char *, sizet >(
			mRawPtr, &INameSpacePrefixMap_v1::remove, kPrefixIsParameter, prefix, prefixLength );
	}

	HXMP_INLINE bool INameSpacePrefixMapProxy::RemoveNameSpace( const char * nameSpace, sizet nameSpaceLength ) {
		return CallSafeFunction< INameSpacePrefixMap_v1, bool, uint32, uint32, const char *, sizet >(
			mRawPtr, &INameSpacePrefixMap_v1::remove, kNameSpaceIsParameter, nameSpace, nameSpaceLength );
	}

	HXMP_INLINE bool INameSpacePrefixMapProxy::IsPrefixPresent( const char * prefix, sizet prefixLength ) const {
		return CallConstSafeFunction< INameSpacePrefixMap_v1, bool, uint32, uint32, const char *, sizet >(
			mRawPtr, &INameSpacePrefixMap_v1::isPresent, kPrefixIsParameter, prefix, prefixLength );
	}

	HXMP_INLINE bool INameSpacePrefixMapProxy::IsNameSpacePresent( const char * nameSpace, sizet nameSpaceLength ) const {
		return CallConstSafeFunction< INameSpacePrefixMap_v1, bool, uint32, uint32, const char *, sizet >(
			mRawPtr, &INameSpacePrefixMap_v1::isPresent, kNameSpaceIsParameter, nameSpace, nameSpaceLength );
	}

	HXMP_INLINE spcIUTF8String INameSpacePrefixMapProxy::GetNameSpace( const char * prefix, sizet prefixLength ) const {
		return CallConstSafeFunctionReturningPointer< INameSpacePrefixMap_v1, pcIUTF8String_base, const IUTF8String, uint32, const char *, sizet >(
			mRawPtr, &INameSpacePrefixMap_v1::get, kPrefixIsParameter, prefix, prefixLength );
	}

	HXMP_INLINE spcIUTF8String INameSpacePrefixMapProxy::GetPrefix( const char * nameSpace, sizet nameSpaceLength ) const {
		return CallConstSafeFunctionReturningPointer< INameSpacePrefixMap_v1, pcIUTF8String_base, const IUTF8String, uint32, const char *, sizet >(
			mRawPtr, &INameSpacePrefixMap_v1::get, kNameSpaceIsParameter, nameSpace, nameSpaceLength );
	}

	HXMP_INLINE sizet INameSpacePrefixMapProxy::Size() const __NOTHROW__ {
		return mRawPtr->Size();
	}

	HXMP_INLINE void INameSpacePrefixMapProxy::Clear() __NOTHROW__ {
		return mRawPtr->Clear();
	}

	HXMP_INLINE spINameSpacePrefixMap INameSpacePrefixMapProxy::Clone() const {
		return CallConstSafeFunctionReturningPointer< INameSpacePrefixMap_v1, pINameSpacePrefixMap_base, INameSpacePrefixMap >(
			mRawPtr, &INameSpacePrefixMap_v1::clone );
	}

	HXMP_INLINE pINameSpacePrefixMap_base INameSpacePrefixMapProxy::clone( pcIError_base & error ) const __NOTHROW__ {
		assert( false );
		return mRawPtr->clone( error );
	}

	HXMP_INLINE uint32 INameSpacePrefixMapProxy::remove( uint32 keyType, const char * key, sizet keyLength, pcIError_base & error ) __NOTHROW__ {
		assert( false );
		return mRawPtr->remove( keyType, key, keyLength, error );
	}

	HXMP_INLINE uint32 INameSpacePrefixMapProxy::isPresent( uint32 keyType, const char * key, sizet keyLength, pcIError_base & error ) const __NOTHROW__ {
		assert( false );
		return mRawPtr->isPresent( keyType, key, keyLength, error );
	}

	HXMP_INLINE pcIUTF8String_base INameSpacePrefixMapProxy::get( uint32 keyType, const char * key, sizet keyLength, pcIError_base & error ) const __NOTHROW__ {
		assert( false );
		return mRawPtr->get( keyType, key, keyLength, error );
	}

	HXMP_INLINE void INameSpacePrefixMapProxy::EnableThreadSafety() const __NOTHROW__  {
		return mRawPtr->EnableThreadSafety();
	}

	HXMP_INLINE void INameSpacePrefixMapProxy::DisableThreadSafety() const __NOTHROW__  {
		return mRawPtr->DisableThreadSafety();
	}

	HXMP_INLINE bool INameSpacePrefixMapProxy::IsThreadSafe() const {
		return mRawPtr->isThreadSafe() != 0;
	}

	HXMP_INLINE uint32 INameSpacePrefixMapProxy::isThreadSafe( ) const __NOTHROW__ {
		assert( false );
		return mRawPtr->isThreadSafe();
	}

	HXMP_INLINE AdobeXMPCommon_Int::pIThreadSafe_I INameSpacePrefixMapProxy::GetIThreadSafe_I() __NOTHROW__ {
		return mRawPtr->GetIThreadSafe_I();
	}


}




