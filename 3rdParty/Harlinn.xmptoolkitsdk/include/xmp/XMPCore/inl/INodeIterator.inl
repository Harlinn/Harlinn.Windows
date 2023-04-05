#pragma once
// =================================================================================================
// Copyright Adobe
// Copyright 2015 Adobe
// All Rights Reserved
//
// NOTICE:  Adobe permits you to use, modify, and distribute this file in accordance with the terms
// of the Adobe license agreement accompanying it. 
// =================================================================================================
#ifndef HARLINN_XMP_INODEITERATOR_INL_
#define HARLINN_XMP_INODEITERATOR_INL_

#include <assert.h>

namespace AdobeXMPCore {

	HXMP_INLINE INodeIteratorProxy::INodeIteratorProxy( pINodeIterator ptr )
		: mRawPtr( ptr )
	{
		mRawPtr->Acquire();
	}

	HXMP_INLINE INodeIteratorProxy::~INodeIteratorProxy() __NOTHROW__ { mRawPtr->Release(); }


	HXMP_INLINE void INodeIteratorProxy::Acquire() const __NOTHROW__ { assert( false ); }

	HXMP_INLINE void INodeIteratorProxy::Release() const __NOTHROW__ { assert( false ); }

	HXMP_INLINE AdobeXMPCommon_Int::pISharedObject_I INodeIteratorProxy::GetISharedObject_I() __NOTHROW__ {
		return mRawPtr->GetISharedObject_I();
	}

	HXMP_INLINE AdobeXMPCore_Int::pINodeIterator_I INodeIteratorProxy::GetINodeIterator_I() __NOTHROW__ {
		return mRawPtr->GetINodeIterator_I();
	}

	HXMP_INLINE pvoid INodeIteratorProxy::getInterfacePointer( uint64 interfaceID, uint32 interfaceVersion, pcIError_base & error ) __NOTHROW__ {
		assert( false );
		return mRawPtr->getInterfacePointer( interfaceID, interfaceVersion, error );
	}

	HXMP_INLINE spINode INodeIteratorProxy::GetNode() {
		return CallSafeFunctionReturningPointer< INodeIterator_v1, pINode_base, INode >(
			mRawPtr, &INodeIterator_v1::getNode );
	}

	HXMP_INLINE INode_v1::eNodeType INodeIteratorProxy::GetNodeType() const {
		return CallConstSafeFunction< INodeIterator_v1, INode_v1::eNodeType, uint32 >(
			mRawPtr, &INodeIterator_v1::getNodeType );
	}

	HXMP_INLINE spINodeIterator INodeIteratorProxy::Next() {
		return CallSafeFunctionReturningPointer< INodeIterator_v1, pINodeIterator, INodeIterator >(
			mRawPtr, &INodeIterator_v1::next );
	}

	HXMP_INLINE uint32 INodeIteratorProxy::getNodeType( pcIError_base & error ) const __NOTHROW__ {
		assert( false );
		return mRawPtr->getNodeType( error );
	}

	HXMP_INLINE pINode_base INodeIteratorProxy::getNode( pcIError_base & error ) __NOTHROW__ {
		assert( false );
		return mRawPtr->getNode( error );
	}

	HXMP_INLINE pINodeIterator_base INodeIteratorProxy::next( pcIError_base & error ) __NOTHROW__ {
		assert( false );
		return mRawPtr->next( error );
	}

	HXMP_INLINE pvoid INodeIteratorProxy::GetInterfacePointer( uint64 interfaceID, uint32 interfaceVersion ) {
	return CallSafeFunction< IVersionable, pvoid, pvoid, uint64, uint32 >(
		mRawPtr, &IVersionable::getInterfacePointer, interfaceID, interfaceVersion );
	}

	


}

#endif


