// =================================================================================================
// Copyright Adobe
// Copyright 2014 Adobe
// All Rights Reserved
//
// NOTICE: Adobe permits you to use, modify, and distribute this file in accordance with the terms
// of the Adobe license agreement accompanying it. 
// =================================================================================================

#define IMPLEMENTATION_HEADERS_CAN_BE_INCLUDED 1
	#include "XMPCommon/ImplHeaders/SharedObjectImpl.h"
#undef IMPLEMENTATION_HEADERS_CAN_BE_INCLUDED
#include <assert.h>

namespace XMP_COMPONENT_INT_NAMESPACE {

	void SharedObjectImpl::Acquire() const __NOTHROW__ {
		if ( mCountInternal != 0 ) {
			--mCountInternal;
		} else {
			++mRefCount;
		}
	}

	void SharedObjectImpl::Release() const __NOTHROW__ {
		if ( mRefCount.load( ) == 0 || --mRefCount == 0 ) {
			delete this;
		}
	}

	SharedObjectImpl::~SharedObjectImpl() __NOTHROW__ {
		assert( mRefCount == 0 );
	}

	void SharedObjectImpl::AcquireInternal() const __NOTHROW__ {
		++mCountInternal;
		++mRefCount;
	}

}
