#pragma once
// =================================================================================================
// Copyright Adobe
// Copyright 2015 Adobe
// All Rights Reserved
//
// NOTICE:  Adobe permits you to use, modify, and distribute this file in accordance with the terms
// of the Adobe license agreement accompanying it. 
// =================================================================================================
#ifndef HARLINN_XMP_ISTRUCTURENODE_INL_
#define HARLINN_XMP_ISTRUCTURENODE_INL_
#include <assert.h>

namespace AdobeXMPCore {


	HXMP_INLINE IStructureNodeProxy::IStructureNodeProxy( pIStructureNode ptr ) : mRawPtr( ptr )
		, ICompositeNodeProxy( ptr )
		, INodeProxy( ptr ) { }

	HXMP_INLINE IStructureNodeProxy::~IStructureNodeProxy() __NOTHROW__ { }

	HXMP_INLINE AdobeXMPCore_Int::pIStructureNode_I IStructureNodeProxy::GetIStructureNode_I() __NOTHROW__ {
		return mRawPtr->GetIStructureNode_I();
	}

	HXMP_INLINE INode_v1::eNodeType IStructureNodeProxy::GetChildNodeType( const char * nameSpace, sizet nameSpaceLength, const char * name, sizet nameLength ) const {
		return CallConstSafeFunction< IStructureNode_v1, eNodeType, uint32, const char *, sizet, const char *, sizet >(
			mRawPtr, &IStructureNode_v1::getChildNodeType, nameSpace, nameSpaceLength, name, nameLength );
	}

	HXMP_INLINE spINode IStructureNodeProxy::GetNode( const char * nameSpace, sizet nameSpaceLength, const char * name, sizet nameLength ) {
		return CallSafeFunctionReturningPointer< IStructureNode_v1, pINode_base, INode, const char *, sizet, const char *, sizet >(
			mRawPtr, &IStructureNode_v1::getNode, nameSpace, nameSpaceLength, name, nameLength );
	}

	HXMP_INLINE void IStructureNodeProxy::InsertNode( const spINode & node ) {
		return CallSafeFunctionReturningVoid< IStructureNode_v1, pINode_base >(
			mRawPtr, &IStructureNode_v1::insertNode, node ? node->GetActualINode() : NULL );
	}

	HXMP_INLINE spINode IStructureNodeProxy::ReplaceNode( const spINode & node ) {
		return CallSafeFunctionReturningPointer< IStructureNode_v1, pINode_base, INode, pINode_base >(
			mRawPtr, &IStructureNode_v1::replaceNode, node ? node->GetActualINode() : NULL );
	}

	HXMP_INLINE spINode IStructureNodeProxy::RemoveNode( const char * nameSpace, sizet nameSpaceLength, const char * name, sizet nameLength ) {
		return CallSafeFunctionReturningPointer< IStructureNode_v1, pINode_base, INode, const char *, sizet, const char *, sizet >(
			mRawPtr, &IStructureNode_v1::removeNode, nameSpace, nameSpaceLength, name, nameLength );
	}

	HXMP_INLINE uint32 IStructureNodeProxy::getChildNodeType( const char * nameSpace, sizet nameSpaceLength, const char * name, sizet nameLength, pcIError_base & error ) const __NOTHROW__ {
		assert( false );
		return mRawPtr->getChildNodeType( nameSpace, nameSpaceLength, name, nameLength, error );
	}

	HXMP_INLINE pINode_base IStructureNodeProxy::getNode( const char * nameSpace, sizet nameSpaceLength, const char * name, sizet nameLength, pcIError_base & error ) __NOTHROW__ {
		assert( false );
		return mRawPtr->getNode( nameSpace, nameSpaceLength, name, nameLength, error );
	}

	HXMP_INLINE void IStructureNodeProxy::insertNode( pINode_base node, pcIError_base & error ) __NOTHROW__ {
		assert( false );
		return mRawPtr->insertNode( node, error );
	}

	HXMP_INLINE pINode_base IStructureNodeProxy::replaceNode( pINode_base node, pcIError_base & error ) __NOTHROW__ {
		assert( false );
		return mRawPtr->replaceNode( node, error );
	}

	HXMP_INLINE pINode_base IStructureNodeProxy::removeNode( const char * nameSpace, sizet nameSpaceLength, const char * name, sizet nameLength, pcIError_base & error ) __NOTHROW__ {
		assert( false );
		return mRawPtr->removeNode( nameSpace, nameSpaceLength, name, nameLength, error );
	}

	HXMP_INLINE pIStructureNode IStructureNodeProxy::GetActualIStructureNode() __NOTHROW__ {
		return mRawPtr;
	}


}


#endif  

