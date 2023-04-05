#pragma once
// =================================================================================================
// Copyright Adobe
// Copyright 2015 Adobe
// All Rights Reserved
//
// NOTICE:  Adobe permits you to use, modify, and distribute this file in accordance with the terms
// of the Adobe license agreement accompanying it. 
// =================================================================================================
#ifndef HARLINN_XMP_ICONFIGURATIONMANAGER_INL_
#define HARLINN_XMP_ICONFIGURATIONMANAGER_INL_

#include <assert.h>

namespace AdobeXMPCommon {

	HXMP_INLINE void IConfigurationManagerProxy::Acquire() const __NOTHROW__ {
		assert( false );
	}

	HXMP_INLINE void IConfigurationManagerProxy::Release() const __NOTHROW__ {
		assert( false );
	}

	HXMP_INLINE pvoid IConfigurationManagerProxy::getInterfacePointer( uint64 interfaceID, uint32 interfaceVersion, pcIError_base & error ) __NOTHROW__ {
		assert( false );
		return mRawPtr->getInterfacePointer( interfaceID, interfaceVersion, error );
	}

	HXMP_INLINE pvoid IConfigurationManagerProxy::GetInterfacePointer( uint64 interfaceID, uint32 interfaceVersion ) {
		return AdobeXMPCommon::CallSafeFunction<
			IVersionable, pvoid, pvoid, uint64, uint32
		>( mRawPtr, &IVersionable::getInterfacePointer, interfaceID, interfaceVersion );
	}

	HXMP_INLINE uint32 IConfigurationManagerProxy::registerMemoryAllocator( pIMemoryAllocator_base memoryAllocator, pcIError_base & error ) __NOTHROW__ {
		assert( false );
		return mRawPtr->registerMemoryAllocator( memoryAllocator, error );
	}

	HXMP_INLINE bool IConfigurationManagerProxy::RegisterMemoryAllocator( pIMemoryAllocator memoryAllocator ) {
		return CallSafeFunction< IConfigurationManager, bool, uint32, pIMemoryAllocator_base >(
			mRawPtr, &IConfigurationManager::registerMemoryAllocator, memoryAllocator );
	}

	HXMP_INLINE uint32 IConfigurationManagerProxy::registerErrorNotifier( pIErrorNotifier_base clientErrorNotifier, pcIError_base & error ) __NOTHROW__ {
		assert( false );
		return mRawPtr->registerErrorNotifier( clientErrorNotifier, error );
	}

	HXMP_INLINE bool IConfigurationManagerProxy::RegisterErrorNotifier( pIErrorNotifier_base clientErrorNotifier ) {
		return CallSafeFunction< IConfigurationManager, bool, uint32, pIErrorNotifier_base >(
			mRawPtr, &IConfigurationManager::registerErrorNotifier, clientErrorNotifier );
	}

	HXMP_INLINE uint32 IConfigurationManagerProxy::disableMultiThreading( pcIError_base & error ) __NOTHROW__ {
		assert( false );
		return mRawPtr->disableMultiThreading( error );
	}

	HXMP_INLINE bool IConfigurationManagerProxy::DisableMultiThreading() {
		return CallSafeFunction< IConfigurationManager, bool, uint32 >(
			mRawPtr, &IConfigurationManager::disableMultiThreading );
	}

	HXMP_INLINE uint32 IConfigurationManagerProxy::isMultiThreaded( pcIError_base & error ) const __NOTHROW__ {
		assert( false );
		return mRawPtr->isMultiThreaded( error );
	}

	HXMP_INLINE bool IConfigurationManagerProxy::IsMultiThreaded() const {
		return CallConstSafeFunction< IConfigurationManager, bool, uint32 >(
			mRawPtr, &IConfigurationManager::isMultiThreaded );
	}


}

#endif
