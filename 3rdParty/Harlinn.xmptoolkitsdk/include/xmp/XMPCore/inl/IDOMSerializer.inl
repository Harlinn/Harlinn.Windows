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

	HXMP_INLINE IDOMSerializerProxy::IDOMSerializerProxy( pIDOMSerializer ptr )
		: IConfigurableProxy( ptr )
		, mRawPtr( ptr )
	{
		mRawPtr->Acquire();
	}

	HXMP_INLINE IDOMSerializerProxy::~IDOMSerializerProxy() __NOTHROW__ { mRawPtr->Release();  }


	HXMP_INLINE void IDOMSerializerProxy::Acquire() const __NOTHROW__ { assert( false ); }

	HXMP_INLINE void IDOMSerializerProxy::Release() const __NOTHROW__ { assert( false ); }

	HXMP_INLINE AdobeXMPCommon_Int::pISharedObject_I IDOMSerializerProxy::GetISharedObject_I() __NOTHROW__ {
		return mRawPtr->GetISharedObject_I();
	}

	HXMP_INLINE AdobeXMPCore_Int::pIDOMSerializer_I IDOMSerializerProxy::GetIDOMSerializer_I() __NOTHROW__ {
		return mRawPtr->GetIDOMSerializer_I();
	}

	HXMP_INLINE pvoid IDOMSerializerProxy::GetInterfacePointer( uint64 interfaceID, uint32 interfaceVersion ) {
		return CallSafeFunction< IVersionable, pvoid, pvoid, uint64, uint32 >(
			mRawPtr, &IVersionable::getInterfacePointer, interfaceID, interfaceVersion );
	}

	HXMP_INLINE pvoid IDOMSerializerProxy::getInterfacePointer( uint64 interfaceID, uint32 interfaceVersion, pcIError_base & error ) __NOTHROW__ {
		assert( false );
		return mRawPtr->getInterfacePointer( interfaceID, interfaceVersion, error );
	}

	HXMP_INLINE spIDOMSerializer IDOMSerializerProxy::Clone() const {
		return CallConstSafeFunctionReturningPointer< IDOMSerializer, pIDOMSerializer_base, IDOMSerializer >(
			mRawPtr, &IDOMSerializer_v1::clone );
	}

	HXMP_INLINE spIUTF8String IDOMSerializerProxy::Serialize( const spINode & node, const spcINameSpacePrefixMap & map ) {
		return CallSafeFunctionReturningPointer< IDOMSerializer, pIUTF8String_base, IUTF8String, pINode_base, pcINameSpacePrefixMap_base >(
			mRawPtr, &IDOMSerializer_v1::serialize, node ? node->GetActualINode() : NULL , map ? map->GetActualINameSpacePrefixMap() : NULL );
	}

	HXMP_INLINE pIDOMSerializer_base IDOMSerializerProxy::clone( pcIError_base & error ) const __NOTHROW__ {
		assert( false );
		return mRawPtr->clone( error );
	}

	HXMP_INLINE pIUTF8String_base IDOMSerializerProxy::serialize( pINode_base node, pcINameSpacePrefixMap_base map, pcIError_base & error ) __NOTHROW__ {
		assert( false );
		return mRawPtr->serialize( node, map, error );
	}


#if XMP_WinBuild
	#pragma warning( pop )
#endif


}


