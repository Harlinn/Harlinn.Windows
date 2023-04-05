#pragma once
// =================================================================================================
// Copyright Adobe
// Copyright 2015 Adobe
// All Rights Reserved
//
// NOTICE:  Adobe permits you to use, modify, and distribute this file in accordance with the terms
// of the Adobe license agreement accompanying it. 
// =================================================================================================
#ifndef HARLINN_XMP_IMETADATA_INL_
#define HARLINN_XMP_IMETADATA_INL_

#include <assert.h>

namespace AdobeXMPCore {

#if XMP_WinBuild
	#pragma warning( push )
	#pragma warning( disable : 4250 )
#endif

	HXMP_INLINE IMetadataProxy::IMetadataProxy( pIMetadata ptr )
		: mRawPtr( ptr )
		, IStructureNodeProxy( ptr )
		, ICompositeNodeProxy( ptr )
		, INodeProxy( ptr ) {}

	HXMP_INLINE IMetadataProxy::~IMetadataProxy() __NOTHROW__ {}

	

	HXMP_INLINE void IMetadataProxy::Acquire() const __NOTHROW__ { assert( false ); }

	HXMP_INLINE void IMetadataProxy::Release() const __NOTHROW__ { assert( false ); }

	HXMP_INLINE AdobeXMPCommon_Int::pISharedObject_I IMetadataProxy::GetISharedObject_I() __NOTHROW__ {
		return mRawPtr->GetISharedObject_I();
	}

	HXMP_INLINE AdobeXMPCore_Int::pIMetadata_I IMetadataProxy::GetIMetadata_I() __NOTHROW__ {
		return mRawPtr->GetIMetadata_I();
	}

	HXMP_INLINE pvoid IMetadataProxy::GetInterfacePointer( uint64 interfaceID, uint32 interfaceVersion ) {
		return CallSafeFunction< IVersionable, pvoid, pvoid, uint64, uint32 >(
			mRawPtr, &IVersionable::getInterfacePointer, interfaceID, interfaceVersion );
	}

	HXMP_INLINE pvoid IMetadataProxy::getInterfacePointer( uint64 interfaceID, uint32 interfaceVersion, pcIError_base & error ) __NOTHROW__ {
		assert( false );
		return mRawPtr->getInterfacePointer( interfaceID, interfaceVersion, error );
	}

	HXMP_INLINE spcIUTF8String IMetadataProxy::GetAboutURI() const {
		return CallConstSafeFunctionReturningPointer< IMetadata_v1, pcIUTF8String_base, const IUTF8String >(
			mRawPtr, &IMetadata_v1::getAboutURI );
	}

	HXMP_INLINE void IMetadataProxy::SetAboutURI( const char * uri, sizet uriLength ) __NOTHROW__ {
		mRawPtr->SetAboutURI( uri, uriLength );
	}

	HXMP_INLINE pcIUTF8String_base IMetadataProxy::getAboutURI( pcIError_base & error ) const __NOTHROW__ {
		assert( false );
		return mRawPtr->getAboutURI( error );
	}

	HXMP_INLINE void IMetadataProxy::EnableFeature( const char * key, sizet keyLength ) const __NOTHROW__ {
		return mRawPtr->EnableFeature( key, keyLength );
	}

	HXMP_INLINE void IMetadataProxy::DisableFeature( const char * key, sizet keyLength ) const __NOTHROW__ {
		return mRawPtr->DisableFeature( key, keyLength );
	}

#if XMP_WinBuild
	#pragma warning( pop )
#endif


}

#endif


