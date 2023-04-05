#pragma once
// =================================================================================================
// Copyright Adobe
// Copyright 2015 Adobe
// All Rights Reserved
//
// NOTICE:  Adobe permits you to use, modify, and distribute this file in accordance with the terms
// of the Adobe license agreement accompanying it. 
// =================================================================================================
#ifndef HARLINN_XMP_INODE_INL_
#define HARLINN_XMP_INODE_INL_

#include <assert.h>

namespace AdobeXMPCore {

	HXMP_INLINE INodeProxy::INodeProxy( pINode ptr ) : mRawPtr( ptr ) {
		mRawPtr->Acquire();
	}

	HXMP_INLINE INodeProxy::~INodeProxy() __NOTHROW__ {
		mRawPtr->Release();
	}

	HXMP_INLINE pINode INodeProxy::GetActualINode() __NOTHROW__ {
		return mRawPtr;
	}

	HXMP_INLINE void INodeProxy::Acquire() const __NOTHROW__ {
		assert( false );
	}

	HXMP_INLINE void INodeProxy::Release() const __NOTHROW__ {
		assert( false );
	}

	HXMP_INLINE AdobeXMPCommon_Int::pISharedObject_I INodeProxy::GetISharedObject_I() __NOTHROW__ {
		return mRawPtr->GetISharedObject_I();
	}

	HXMP_INLINE AdobeXMPCore_Int::pINode_I INodeProxy::GetINode_I() __NOTHROW__ {
		return mRawPtr->GetINode_I();
	}

	HXMP_INLINE pvoid INodeProxy::getInterfacePointer( uint64 interfaceID, uint32 interfaceVersion, pcIError_base & error ) __NOTHROW__ {
		assert( false );
		return mRawPtr->getInterfacePointer( interfaceID, interfaceVersion, error );
	}

	HXMP_INLINE spINode INodeProxy::GetParent() {
		return CallSafeFunctionReturningPointer< INode_v1, pINode_base, INode >(
			mRawPtr, &INode_v1::getParent );
	}

	HXMP_INLINE void INodeProxy::SetName( const char * name, sizet nameLength ) {
		return CallSafeFunctionReturningVoid< INode_v1, const char *, sizet >(
			mRawPtr, &INode_v1::setName, name, nameLength );
	}

	HXMP_INLINE spcIUTF8String INodeProxy::GetName() const {
		return CallConstSafeFunctionReturningPointer< INode_v1, pcIUTF8String_base, const IUTF8String >(
			mRawPtr, &INode_v1::getName );
	}

	HXMP_INLINE void INodeProxy::SetNameSpace( const char * nameSpace, sizet nameSpaceLength ) {
		return CallSafeFunctionReturningVoid< INode_v1, const char *, sizet >(
			mRawPtr, &INode_v1::setNameSpace, nameSpace, nameSpaceLength );

	}

	HXMP_INLINE spcIUTF8String INodeProxy::GetNameSpace() const {
		return CallConstSafeFunctionReturningPointer< INode_v1, pcIUTF8String_base, const IUTF8String >(
			mRawPtr, &INode_v1::getNameSpace );
	}

	HXMP_INLINE spIPath INodeProxy::GetPath() const {
		return CallConstSafeFunctionReturningPointer< INode_v1, pIPath_base, IPath >(
			mRawPtr, &INode_v1::getPath );
	}

	HXMP_INLINE sizet INodeProxy::QualifiersCount() const __NOTHROW__ {
		return mRawPtr->QualifiersCount();
	}

	HXMP_INLINE spINodeIterator INodeProxy::QualifiersIterator() {
		return CallSafeFunctionReturningPointer< INode_v1, pINodeIterator_base, INodeIterator >(
			mRawPtr, &INode_v1::qualifiersIterator );
	}

	HXMP_INLINE spINode INodeProxy::GetQualifier( const char * nameSpace, sizet nameSpaceLength, const char * name, sizet nameLength ) {
		return CallSafeFunctionReturningPointer< INode_v1, pINode_base, INode, const char *, sizet, const char *, sizet >(
			mRawPtr, &INode_v1::getQualifier, nameSpace, nameSpaceLength, name, nameLength );
	}

	HXMP_INLINE void INodeProxy::InsertQualifier( const spINode & node ) {
		return CallSafeFunctionReturningVoid< INode_v1, pINode_base >(
			mRawPtr, &INode_v1::insertQualifier, node ? node->GetActualINode() : NULL );
	}

	HXMP_INLINE spINode INodeProxy::ReplaceQualifier( const spINode & node ) {
		return CallSafeFunctionReturningPointer< INode_v1, pINode_base, INode, pINode_base >(
			mRawPtr, &INode_v1::replaceQualifier, node ? node->GetActualINode() : NULL );
	}

	HXMP_INLINE spINode INodeProxy::RemoveQualifier( const char * nameSpace, sizet nameSpaceLength, const char * name, sizet nameLength ) {
		return CallSafeFunctionReturningPointer< INode_v1, pINode_base, INode, const char *, sizet, const char *, sizet >(
			mRawPtr, &INode_v1::removeQualifier, nameSpace, nameSpaceLength, name, nameLength );
	}

	HXMP_INLINE INode_v1::eNodeType INodeProxy::GetNodeType() const {
		return CallConstSafeFunction< INode_v1, eNodeType, uint32 >(
			mRawPtr, &INode_v1::getNodeType );
	}

	HXMP_INLINE bool INodeProxy::IsArrayItem() const {
		return CallConstSafeFunction< INode_v1, bool, uint32 >(
			mRawPtr, &INode_v1::isArrayItem );
	}

	HXMP_INLINE bool INodeProxy::IsQualifierNode() const {
		return CallConstSafeFunction< INode_v1, bool, uint32 >(
			mRawPtr, &INode_v1::isQualifierNode );
	}

	HXMP_INLINE sizet INodeProxy::GetIndex() const {
		return CallConstSafeFunction< INode_v1, sizet, sizet >(
			mRawPtr, &INode_v1::getIndex );
	}

	HXMP_INLINE bool INodeProxy::HasQualifiers() const {
		return CallConstSafeFunction< INode_v1, bool, uint32 >(
			mRawPtr, &INode_v1::hasQualifiers );
	}

	HXMP_INLINE bool INodeProxy::HasContent() const {
		return CallConstSafeFunction< INode_v1, bool, uint32 >(
			mRawPtr, &INode_v1::hasContent );
	}

	HXMP_INLINE bool INodeProxy::IsEmpty() const {
		return CallConstSafeFunction< INode_v1, bool, uint32 >(
			mRawPtr, &INode_v1::isEmpty );
	}

	HXMP_INLINE bool INodeProxy::HasChanged() const {
		return CallConstSafeFunction< INode_v1, bool, uint32 >(
			mRawPtr, &INode_v1::hasChanged );
	}

	HXMP_INLINE void INodeProxy::AcknowledgeChanges() const __NOTHROW__ {
		return mRawPtr->AcknowledgeChanges(  );
	}

	HXMP_INLINE void INodeProxy::Clear( bool contents, bool qualifiers ) {
		return CallSafeFunctionReturningVoid< INode_v1, uint32, uint32 >(
			mRawPtr, &INode_v1::clear, static_cast< uint32 >( contents ), static_cast< uint32 >( qualifiers ) );
	}

	HXMP_INLINE spINode INodeProxy::Clone( bool ignoreEmptyNodes, bool ignoreNodesWithOnlyQualifiers ) const {
		return CallConstSafeFunctionReturningPointer< INode_v1, pINode_base, INode, uint32, uint32 >(
			mRawPtr, &INode_v1::clone, static_cast< uint32 >( ignoreEmptyNodes ), static_cast< uint32 >( ignoreNodesWithOnlyQualifiers ) );
	}

	HXMP_INLINE pINode_base INodeProxy::getParent( pcIError_base & error ) __NOTHROW__ {
		assert( false );
		return mRawPtr->getParent( error );
	}

	HXMP_INLINE void INodeProxy::setName( const char * name, sizet nameLength, pcIError_base & error ) __NOTHROW__ {
		assert( false );
		return mRawPtr->setName( name, nameLength, error );
	}

	HXMP_INLINE AdobeXMPCommon::pcIUTF8String_base INodeProxy::getName( pcIError_base & error ) const __NOTHROW__ {
		assert( false );
		return mRawPtr->getName( error );
	}

	HXMP_INLINE void INodeProxy::setNameSpace( const char * nameSpace, sizet nameSpaceLength, pcIError_base & error ) __NOTHROW__ {
		assert( false );
		return mRawPtr->setNameSpace( nameSpace, nameSpaceLength, error );
	}

	HXMP_INLINE pcIUTF8String_base INodeProxy::getNameSpace( pcIError_base & error ) const __NOTHROW__ {
		assert( false );
		return mRawPtr->getNameSpace( error );
	}

	HXMP_INLINE pIPath_base INodeProxy::getPath( pcIError_base & error ) const __NOTHROW__ {
		assert( false );
		return mRawPtr->getPath( error );
	}

	HXMP_INLINE pINodeIterator_base INodeProxy::qualifiersIterator( pcIError_base & error ) __NOTHROW__ {
		assert( false );
		return mRawPtr->qualifiersIterator( error );
	}

	HXMP_INLINE pINode_base INodeProxy::getQualifier( const char * nameSpace, sizet nameSpaceLength, const char * name, sizet nameLength, pcIError_base & error ) __NOTHROW__ {
		assert( false );
		return mRawPtr->getQualifier( nameSpace, nameSpaceLength, name, nameLength, error );
	}

	HXMP_INLINE void INodeProxy::insertQualifier( pINode_base base, pcIError_base & error ) __NOTHROW__ {
		assert( false );
		return mRawPtr->insertQualifier( base, error );
	}

	HXMP_INLINE pINode_base INodeProxy::replaceQualifier( pINode_base node, pcIError_base & error ) __NOTHROW__ {
		assert( false );
		return mRawPtr->replaceQualifier( node, error );
	}

	HXMP_INLINE pINode_base INodeProxy::removeQualifier( const char * nameSpace, sizet nameSpaceLength, const char * name, sizet nameLength, pcIError_base & error ) __NOTHROW__ {
		assert( false );
		return mRawPtr->removeQualifier( nameSpace, nameSpaceLength, name, nameLength, error );
	}

	HXMP_INLINE uint32 INodeProxy::getNodeType( pcIError_base & error ) const __NOTHROW__ {
		assert( false );
		return mRawPtr->getNodeType( error );
	}

	HXMP_INLINE uint32 INodeProxy::isArrayItem( pcIError_base & error ) const __NOTHROW__ {
		assert( false );
		return mRawPtr->isArrayItem( error );
	}

	HXMP_INLINE uint32 INodeProxy::isQualifierNode( pcIError_base & error ) const __NOTHROW__ {
		assert( false );
		return mRawPtr->isQualifierNode( error );
	}

	HXMP_INLINE sizet INodeProxy::getIndex( pcIError_base & error ) const __NOTHROW__ {
		assert( false );
		return mRawPtr->getIndex( error );
	}

	HXMP_INLINE uint32 INodeProxy::hasQualifiers( pcIError_base & error ) const __NOTHROW__ {
		assert( false );
		return mRawPtr->hasQualifiers( error );
	}

	HXMP_INLINE uint32 INodeProxy::hasContent( pcIError_base & error ) const __NOTHROW__ {
		assert( false );
		return mRawPtr->hasContent( error );
	}

	HXMP_INLINE uint32 INodeProxy::isEmpty( pcIError_base & error ) const __NOTHROW__ {
		assert( false );
		return mRawPtr->isEmpty( error );
	}

	HXMP_INLINE uint32 INodeProxy::hasChanged( pcIError_base & error ) const __NOTHROW__ {
		assert( false );
		return mRawPtr->hasChanged( error );
	}

	HXMP_INLINE void INodeProxy::clear( uint32 contents, uint32 qualifiers, pcIError_base & error ) __NOTHROW__ {
		assert( false );
		return mRawPtr->clear( contents, qualifiers, error );
	}

	HXMP_INLINE pINode_base INodeProxy::clone( uint32 igoreEmptyNodes, uint32 ignoreNodesWithOnlyQualifiers, pcIError_base & error ) const __NOTHROW__ {
		assert( false );
		return mRawPtr->clone( igoreEmptyNodes, ignoreNodesWithOnlyQualifiers, error );
	}

	HXMP_INLINE void INodeProxy::EnableThreadSafety() const __NOTHROW__ {
		return mRawPtr->EnableThreadSafety(  );
	}

	HXMP_INLINE void INodeProxy::DisableThreadSafety() const __NOTHROW__ {
		return mRawPtr->DisableThreadSafety(  );
	}

	HXMP_INLINE bool INodeProxy::IsThreadSafe() const {
		return mRawPtr->isThreadSafe() != 0;
	}

	HXMP_INLINE uint32 INodeProxy::isThreadSafe() const __NOTHROW__ {
		assert( false );
		return mRawPtr->isThreadSafe();
	}

	HXMP_INLINE spISimpleNode INodeProxy::ConvertToSimpleNode() {
		return CallSafeFunctionReturningPointer< INode_v1, pISimpleNode_base, ISimpleNode >(
			mRawPtr, &INode_v1::convertToSimpleNode );
	}

	HXMP_INLINE spIStructureNode INodeProxy::ConvertToStructureNode() {
		return CallSafeFunctionReturningPointer< INode_v1, pIStructureNode_base, IStructureNode >(
			mRawPtr, &INode_v1::convertToStructureNode );
	}

	HXMP_INLINE spIArrayNode INodeProxy::ConvertToArrayNode() {
		return CallSafeFunctionReturningPointer< INode_v1, pIArrayNode_base, IArrayNode >(
			mRawPtr, &INode_v1::convertToArrayNode );
	}

	HXMP_INLINE spIMetadata INodeProxy::ConvertToMetadata() {
		return CallSafeFunctionReturningPointer< INode_v1, pIMetadata_base, IMetadata >(
			mRawPtr, &INode_v1::convertToMetadata );
	}

	HXMP_INLINE pISimpleNode_base INodeProxy::convertToSimpleNode( pcIError_base & error ) __NOTHROW__ {
		assert( false );
		return mRawPtr->convertToSimpleNode( error );
	}

	HXMP_INLINE pIStructureNode_base INodeProxy::convertToStructureNode( pcIError_base & error ) __NOTHROW__ {
		assert( false );
		return mRawPtr->convertToStructureNode( error );	}

	HXMP_INLINE pIArrayNode_base INodeProxy::convertToArrayNode( pcIError_base & error ) __NOTHROW__ {
		assert( false );
		return mRawPtr->convertToArrayNode( error );
	}

	HXMP_INLINE pIMetadata_base INodeProxy::convertToMetadata( pcIError_base & error ) __NOTHROW__ {
		assert( false );
		return mRawPtr->convertToMetadata( error );
	}

	HXMP_INLINE uint32 INodeProxy::getParentNodeType( pcIError_base & error ) const __NOTHROW__ {
		assert( false );
		return mRawPtr->getParentNodeType( error );
	}

	HXMP_INLINE uint32 INodeProxy::getQualifierNodeType( const char * nameSpace, sizet nameSpaceLength, const char * name, sizet nameLength, pcIError_base & error ) const __NOTHROW__ {
		assert( false );
		return mRawPtr->getQualifierNodeType( nameSpace, nameSpaceLength, name, nameLength, error );
	}

	HXMP_INLINE INode_v1::eNodeType INodeProxy::GetParentNodeType() const {
		return CallConstSafeFunction< INode_v1, eNodeType, uint32 >(
			mRawPtr, &INode_v1::getParentNodeType );
	}

	HXMP_INLINE INode_v1::eNodeType INodeProxy::GetQualifierNodeType( const char * nameSpace, sizet nameSpaceLength, const char * name, sizet nameLength ) const {
		return CallConstSafeFunction< INode_v1, eNodeType, uint32, const char *, sizet, const char *, sizet >(
			mRawPtr, &INode_v1::getQualifierNodeType, nameSpace, nameSpaceLength, name, nameLength );
	}

	HXMP_INLINE AdobeXMPCommon_Int::pIThreadSafe_I INodeProxy::GetIThreadSafe_I() __NOTHROW__ {
		return mRawPtr->GetIThreadSafe_I(  );
	}

	HXMP_INLINE pvoid INodeProxy::GetInterfacePointer( uint64 interfaceID, uint32 interfaceVersion ) {
		return CallSafeFunction< IVersionable, pvoid, pvoid, uint64, uint32 >(
			mRawPtr, &IVersionable::getInterfacePointer, interfaceID, interfaceVersion );
	}


}
#endif



