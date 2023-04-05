#pragma once
#ifndef MemoryAllocatorWrapperImpl_h__
#define MemoryAllocatorWrapperImpl_h__ 1

// =================================================================================================
// Copyright Adobe
// Copyright 2015 Adobe
// All Rights Reserved
//
// NOTICE:  Adobe permits you to use, modify, and distribute this file in accordance with the terms
// of the Adobe license agreement accompanying it. 
// =================================================================================================

#include <xmp/XMPCommon/Interfaces/IMemoryAllocator.h>
#include <cstdlib>

namespace XMP_COMPONENT_INT_NAMESPACE {
	using namespace AdobeXMPCommon;

	class MemoryAllocatorWrapperImpl
		: public virtual IMemoryAllocator
	{
	public:
		MemoryAllocatorWrapperImpl();
		pIMemoryAllocator_base SetMemoryAllocator( pIMemoryAllocator_base memoryAllocator );

		virtual void * allocate( sizet size ) __NOTHROW__;
		virtual void deallocate( void * ptr ) __NOTHROW__;
		virtual void * reallocate( void * ptr, sizet size ) __NOTHROW__;

	protected:
		pIMemoryAllocator_base				mpMemoryAllocator;
	};


}

#endif  // MemoryAllocatorWrapperImpl_h__

