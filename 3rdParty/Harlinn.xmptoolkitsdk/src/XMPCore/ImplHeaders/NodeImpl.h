#pragma once
#ifndef __NodeImpl_h__
#define __NodeImpl_h__ 1

// =================================================================================================
// Copyright Adobe
// Copyright 2014 Adobe
// All Rights Reserved
//
// NOTICE:  Adobe permits you to use, modify, and distribute this file in accordance with the terms
// of the Adobe license agreement accompanying it. 
// =================================================================================================

#if !(IMPLEMENTATION_HEADERS_CAN_BE_INCLUDED)
	#error "Not adhering to design constraints"
	// this file should only be included from its own cpp file
#endif

#include "XMPCore/Interfaces/INode_I.h"
#include "XMPCommon/BaseClasses/MemoryManagedObject.h"
#include "XMPCommon/ImplHeaders/SharedObjectImpl.h"
#include "XMPCommon/ImplHeaders/ThreadSafeImpl.h"
#include "XMPCommon/Utilities/TAtomicTypes.h"

#include <map>

#if XMP_WinBuild
	#pragma warning( push )
	#pragma warning( disable : 4250 )
#endif

namespace AdobeXMPCore_Int {

	class NodeImpl
		: public virtual INode_I
		, public virtual SharedObjectImpl
		, public virtual MemoryManagedObject
		, public virtual ThreadSafeImpl
	{
	public:
		NodeImpl() {}
		NodeImpl( const char * nameSpace, sizet nameSpaceLength, const char * name, sizet nameLength );

		virtual void ChangeParent( pINode parent );
		virtual pINode GetRawParentPointer();
		virtual spINode GetParent();
		virtual void SetName( const char * name, sizet nameLength );
		virtual spcIUTF8String GetName() const;
		virtual void SetNameSpace( const char * nameSpace, sizet nameSpaceLength );
		virtual spcIUTF8String GetNameSpace() const;
		virtual spIPath GetPath() const;
		virtual sizet QualifiersCount() const __NOTHROW__;
		virtual spINodeIterator QualifiersIterator();
		virtual spINode GetQualifier( const char * nameSpace, sizet nameSpaceLength, const char * name, sizet nameLength );
		virtual spINode GetQualifier( const spcIUTF8String & nameSpace, const spcIUTF8String & name );
		virtual void InsertQualifier( const spINode & node );
		virtual spINode ReplaceQualifier( const spINode & node );
		virtual spINode RemoveQualifier( const char * nameSpace, sizet nameSpaceLength, const char * name, sizet nameLength );
		virtual spINode RemoveQualifier( const spcIUTF8String & nameSpace, const spcIUTF8String & name );
		virtual bool IsArrayItem() const;
		virtual bool HasQualifiers() const;
		virtual bool IsEmpty() const;
		virtual bool HasChanged() const;
		virtual void AcknowledgeChanges() const __NOTHROW__;
		virtual void Clear( bool contents = true, bool qualifiers = true );
		virtual spINode Clone( bool ignoreEmptyNodes = false, bool ignoreNodesWithOnlyQualifiers = false ) const;
		virtual void SetIndex( sizet currentIndex );
		virtual void SetIsQualifierNode( bool isQualifierNode );
		virtual bool IsQualifierNode() const;
		virtual sizet GetIndex() const;
		virtual void RegisterChange();
		virtual eNodeType GetParentNodeType() const;
		virtual eNodeType GetQualifierNodeType( const char * nameSpace, sizet nameSpaceLength, const char * name, sizet nameLength ) const;
		virtual spISimpleNode ConvertToSimpleNode();
		virtual spIStructureNode ConvertToStructureNode();
		virtual spIArrayNode ConvertToArrayNode();
		virtual spIMetadata ConvertToMetadata();
		virtual void UnRegisterChange();
		virtual bool ValidateNameOrNameSpaceChangeForAChild( const spcIUTF8String & currentNameSpace, const spcIUTF8String & currentName, const spcIUTF8String & newNameSpace, const spcIUTF8String & newName );

		virtual void Acquire() const __NOTHROW__;
		virtual void Release() const __NOTHROW__;
		virtual void AcquireInternal() const __NOTHROW__;

		// functions base classes need to implement.
		virtual void ClearContents() = 0;
		virtual spINode CloneContents( bool ignoreEmptyNodes, bool ignoreNodesWithOnlyQualifiers, sizet qualifiersCount ) const = 0;
		virtual void SetQualifiers( const spIStructureNode & node );

	protected:
		void updateParentSharedPointer( bool calledFromRelease = false );
		virtual void resetChangesForChildren() const = 0;
		void CreateQualifierNode();
		virtual ~NodeImpl() __NOTHROW__ {}

		spIUTF8String						mNameSpace;
		spIUTF8String						mName;
		sizet								mIndex;
		pINode								mpParent;
		spINode								mspParent;
		spIStructureNode					mQualifiers;
		mutable atomic_sizet				mChangeCount;
		bool								mIsQualifierNode;

	#ifdef FRIEND_CLASS_DECLARATION
		FRIEND_CLASS_DECLARATION();
	#endif
		REQ_FRIEND_CLASS_DECLARATION();
	};
}

#endif  // __NodeImpl_h__
