#pragma once
// =================================================================================================
// Copyright Adobe
// Copyright 2015 Adobe
// All Rights Reserved
//
// NOTICE:  Adobe permits you to use, modify, and distribute this file in accordance with the terms
// of the Adobe license agreement accompanying it. 
// =================================================================================================
#ifndef HARLINN_XMP_IARRAYNODE_INL_
#define HARLINN_XMP_IARRAYNODE_INL_

namespace AdobeXMPCore {
	class IArrayNodeProxy;
}

#define FRIEND_CLASS_DECLARATION() friend class AdobeXMPCore::IArrayNodeProxy;

#ifndef BUILDING_HARLINN_XMPTOOLKITSDK
#include <xmp/XMPCore/Interfaces/IArrayNode.h>
#endif




#include <xmp/XMPCommon/Utilities/TWrapperFunctions.h>
#include <xmp/XMPCore/Interfaces/ICoreObjectFactory.h>

#include <assert.h>

namespace AdobeXMPCore {

#if XMP_WinBuild
	#pragma warning( push )
	#pragma warning( disable : 4250 )
#endif

	HXMP_INLINE IArrayNodeProxy::IArrayNodeProxy( pIArrayNode ptr )
		: mRawPtr( ptr )
		, ICompositeNodeProxy( ptr )
		, INodeProxy( ptr ) {}

	HXMP_INLINE void IArrayNodeProxy::Acquire() const __NOTHROW__ { assert( false ); }

	HXMP_INLINE void IArrayNodeProxy::Release() const __NOTHROW__ { assert( false ); }

	HXMP_INLINE AdobeXMPCommon_Int::pISharedObject_I IArrayNodeProxy::GetISharedObject_I() __NOTHROW__ {
		return mRawPtr->GetISharedObject_I();
	}

	HXMP_INLINE AdobeXMPCore_Int::pIArrayNode_I IArrayNodeProxy::GetIArrayNode_I() __NOTHROW__ {
		return mRawPtr->GetIArrayNode_I();
	}

	HXMP_INLINE pvoid IArrayNodeProxy::GetInterfacePointer( uint64 interfaceID, uint32 interfaceVersion ) {
		return CallSafeFunction< IVersionable, pvoid, pvoid, uint64, uint32 >(
			mRawPtr, &IVersionable::getInterfacePointer, interfaceID, interfaceVersion );
	}

	HXMP_INLINE pvoid IArrayNodeProxy::getInterfacePointer( uint64 interfaceID, uint32 interfaceVersion, pcIError_base & error ) __NOTHROW__ {
		assert( false );
		return mRawPtr->getInterfacePointer( interfaceID, interfaceVersion, error );
	}

	HXMP_INLINE IArrayNode::eArrayForm IArrayNodeProxy::GetArrayForm() const {
		return CallConstSafeFunction< IArrayNode_v1, eArrayForm, uint32 >(
			mRawPtr, &IArrayNode_v1::getArrayForm );
	}

	HXMP_INLINE IArrayNode::eNodeType IArrayNodeProxy::GetChildNodeType() const {
		return CallConstSafeFunction< IArrayNode_v1, eNodeType, uint32 >(
			mRawPtr, &IArrayNode_v1::getChildNodeType );
	}

	HXMP_INLINE spINode IArrayNodeProxy::GetNodeAtIndex( sizet index ) {
		return CallSafeFunctionReturningPointer< IArrayNode_v1, pINode_base, INode, sizet >(
			mRawPtr, &IArrayNode_v1::getNodeAtIndex, index );
	}

	HXMP_INLINE void IArrayNodeProxy::InsertNodeAtIndex( const spINode & node, sizet index ) {
		return CallSafeFunctionReturningVoid< IArrayNode_v1, pINode_base, sizet >(
			mRawPtr, &IArrayNode_v1::insertNodeAtIndex, node ? node->GetActualINode() : NULL, index );
	}

	HXMP_INLINE spINode IArrayNodeProxy::RemoveNodeAtIndex( sizet index ) {
		return CallSafeFunctionReturningPointer< IArrayNode_v1, pINode_base, INode, sizet >(
			mRawPtr, &IArrayNode_v1::removeNodeAtIndex, index );
	}

	HXMP_INLINE spINode IArrayNodeProxy::ReplaceNodeAtIndex( const spINode & node, sizet index ) {
		return CallSafeFunctionReturningPointer< IArrayNode_v1, pINode_base, INode, pINode_base, sizet >(
			mRawPtr, &IArrayNode_v1::replaceNodeAtIndex, node ? node->GetActualINode() :NULL, index );
	}

	HXMP_INLINE uint32 IArrayNodeProxy::getArrayForm( pcIError_base & error ) const __NOTHROW__ {
		assert( false );
		return mRawPtr->getArrayForm( error );
	}

	HXMP_INLINE pINode_base IArrayNodeProxy::getNodeAtIndex( sizet index, pcIError_base & error ) __NOTHROW__ {
		assert( false );
		return mRawPtr->getNodeAtIndex( index, error );
	}

	HXMP_INLINE void IArrayNodeProxy::insertNodeAtIndex( pINode_base node, sizet index, pcIError_base & error ) __NOTHROW__ {
		assert( false );
		return mRawPtr->insertNodeAtIndex( node, index, error );
	}

	HXMP_INLINE pINode_base IArrayNodeProxy::removeNodeAtIndex( sizet index, pcIError_base & error ) __NOTHROW__ {
		assert( false );
		return mRawPtr->removeNodeAtIndex( index, error );
	}

	HXMP_INLINE pINode_base IArrayNodeProxy::replaceNodeAtIndex( pINode_base node, sizet index, pcIError_base & error ) __NOTHROW__ {
		assert( false );
		return mRawPtr->replaceNodeAtIndex( node, index, error );
	}

	HXMP_INLINE uint32 IArrayNodeProxy::getChildNodeType( pcIError_base & error ) const __NOTHROW__ {
		assert( false );
		return mRawPtr->getChildNodeType( error );
	}

	

#if XMP_WinBuild
	#pragma warning( pop )
#endif

	

}

#endif


