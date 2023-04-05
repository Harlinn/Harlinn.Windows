#pragma once
// =================================================================================================
// Copyright Adobe
// Copyright 2015 Adobe
// All Rights Reserved
//
// NOTICE:  Adobe permits you to use, modify, and distribute this file in accordance with the terms
// of the Adobe license agreement accompanying it. 
// =================================================================================================
#ifndef HARLINN_XMP_ICOMPOSITENODE_INL
#define HARLINN_XMP_ICOMPOSITENODE_INL

#include <assert.h>

namespace AdobeXMPCore {
	HXMP_INLINE ICompositeNodeProxy::ICompositeNodeProxy( pICompositeNode ptr )
		: mRawPtr( ptr )
		, INodeProxy( ptr ) {}

	HXMP_INLINE ICompositeNodeProxy::~ICompositeNodeProxy() __NOTHROW__ {}

	HXMP_INLINE pICompositeNode ICompositeNodeProxy::GetActualICompositeNode() __NOTHROW__ { return mRawPtr; }

	HXMP_INLINE AdobeXMPCore_Int::pICompositeNode_I ICompositeNodeProxy::GetICompositeNode_I() __NOTHROW__ {
		return mRawPtr->GetICompositeNode_I();
	}

	HXMP_INLINE INode_v1::eNodeType ICompositeNodeProxy::GetNodeTypeAtPath( const spcIPath & path ) const {
		return CallConstSafeFunction< ICompositeNode_v1, eNodeType, uint32, pcIPath_base >(
			mRawPtr, &ICompositeNode_v1::getNodeTypeAtPath, path ? path->GetActualIPath() : NULL );
	}

	HXMP_INLINE spINode ICompositeNodeProxy::GetNodeAtPath( const spcIPath & path ) {
		return CallSafeFunctionReturningPointer< ICompositeNode_v1, pINode_base, INode, pcIPath_base >(
			mRawPtr, &ICompositeNode_v1::getNodeAtPath, path ? path->GetActualIPath() : NULL );
	}

	HXMP_INLINE void ICompositeNodeProxy::AppendNode( const spINode & node ) {
		return CallSafeFunctionReturningVoid< ICompositeNode_v1, pINode_base >(
			mRawPtr, &ICompositeNode_v1::appendNode, node ? node->GetActualINode() : NULL );
	}

	HXMP_INLINE void ICompositeNodeProxy::InsertNodeAtPath( const spINode & node, const spcIPath & path ) {
		return CallSafeFunctionReturningVoid< ICompositeNode_v1, pINode_base, pcIPath_base >(
			mRawPtr, &ICompositeNode_v1::insertNodeAtPath, node ? node->GetActualINode() : NULL, path ? path->GetActualIPath() : NULL );
	}

	HXMP_INLINE spINode ICompositeNodeProxy::ReplaceNodeAtPath( const spINode & node, const spcIPath & path ) {
		return CallSafeFunctionReturningPointer< ICompositeNode_v1, pINode_base, INode, pINode_base, pcIPath_base >(
			mRawPtr, &ICompositeNode_v1::replaceNodeAtPath, node ? node->GetActualINode() : NULL, path ? path->GetActualIPath() : NULL );
	}

	HXMP_INLINE spINode ICompositeNodeProxy::RemoveNodeAtPath( const spcIPath & path ) {
		return CallSafeFunctionReturningPointer< ICompositeNode_v1, pINode_base, INode, pcIPath_base >(
			mRawPtr, &ICompositeNode_v1::removeNodeAtPath, path ? path->GetActualIPath() : NULL );
	}

	HXMP_INLINE spINodeIterator ICompositeNodeProxy::Iterator() {
		return CallSafeFunctionReturningPointer< ICompositeNode_v1, pINodeIterator_base, INodeIterator >(
			mRawPtr, &ICompositeNode_v1::iterator );
	}

	HXMP_INLINE sizet ICompositeNodeProxy::ChildCount() const __NOTHROW__ {
		return mRawPtr->ChildCount();
	}

	HXMP_INLINE uint32 ICompositeNodeProxy::getNodeTypeAtPath( pcIPath_base path, pcIError_base & error ) const  __NOTHROW__ {
		assert( false );
		return mRawPtr->getNodeTypeAtPath( path, error );
	}

	HXMP_INLINE pINode_base ICompositeNodeProxy::getNodeAtPath( pcIPath_base path, pcIError_base & error )  __NOTHROW__ {
		assert( false );
		return mRawPtr->getNodeAtPath( path, error );
	}

	HXMP_INLINE void ICompositeNodeProxy::appendNode( pINode_base node, pcIError_base & error )  __NOTHROW__ {
		assert( false );
		return mRawPtr->appendNode( node, error );
	}

	HXMP_INLINE void ICompositeNodeProxy::insertNodeAtPath( pINode_base node, pcIPath_base path, pcIError_base & error )  __NOTHROW__ {
		assert( false );
		return mRawPtr->insertNodeAtPath( node, path, error );
	}

	HXMP_INLINE pINode_base ICompositeNodeProxy::replaceNodeAtPath( pINode_base node, pcIPath_base path, pcIError_base & error )  __NOTHROW__ {
		assert( false );
		return mRawPtr->replaceNodeAtPath( node, path, error );
	}

	HXMP_INLINE pINode_base ICompositeNodeProxy::removeNodeAtPath( pcIPath_base path, pcIError_base & error )  __NOTHROW__ {
		assert( false );
		return mRawPtr->removeNodeAtPath( path, error );
	}

	HXMP_INLINE pINodeIterator_base ICompositeNodeProxy::iterator( pcIError_base & error )  __NOTHROW__ {
		assert( false );
		return mRawPtr->iterator( error );
	}

	
}

#endif