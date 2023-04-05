#pragma once
// =================================================================================================
// Copyright Adobe
// Copyright 2015 Adobe
// All Rights Reserved
//
// NOTICE:  Adobe permits you to use, modify, and distribute this file in accordance with the terms
// of the Adobe license agreement accompanying it. 
// =================================================================================================
#ifndef HARLINN_XMP_ICORECONFIGURATIONMANAGER_INL_
#define HARLINN_XMP_ICORECONFIGURATIONMANAGER_INL_

#include <assert.h>

namespace AdobeXMPCore {

#if XMP_WinBuild
	#pragma warning( push )
	#pragma warning( disable : 4250 )
#endif

	HXMP_INLINE ICoreConfigurationManagerProxy::ICoreConfigurationManagerProxy( pICoreConfigurationManager ptr )
		: IConfigurationManagerProxy( ptr )
		, mRawPtr( ptr ) {}

	HXMP_INLINE ICoreConfigurationManagerProxy::~ICoreConfigurationManagerProxy() __NOTHROW__ {}

	HXMP_INLINE void ICoreConfigurationManagerProxy::Acquire() const __NOTHROW__ { assert( false ); }

	HXMP_INLINE void ICoreConfigurationManagerProxy::Release() const __NOTHROW__ { assert( false ); }

	HXMP_INLINE AdobeXMPCommon_Int::pISharedObject_I ICoreConfigurationManagerProxy::GetISharedObject_I() __NOTHROW__ {
		return mRawPtr->GetISharedObject_I();
	}

	HXMP_INLINE AdobeXMPCore_Int::pICoreConfigurationManager_I ICoreConfigurationManagerProxy::GetICoreConfigurationManager_I() __NOTHROW__ {
		return mRawPtr->GetICoreConfigurationManager_I();
	}

	HXMP_INLINE pvoid ICoreConfigurationManagerProxy::GetInterfacePointer( uint64 interfaceID, uint32 interfaceVersion ) {
		return CallSafeFunction< IVersionable, pvoid, pvoid, uint64, uint32 >(
			mRawPtr, &IVersionable::getInterfacePointer, interfaceID, interfaceVersion );
	}

	HXMP_INLINE pvoid ICoreConfigurationManagerProxy::getInterfacePointer( uint64 interfaceID, uint32 interfaceVersion, pcIError_base & error ) __NOTHROW__ {
		assert( false );
		return mRawPtr->getInterfacePointer( interfaceID, interfaceVersion, error );
	}

#if XMP_WinBuild
	#pragma warning( pop )
#endif

}

#endif


