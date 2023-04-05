#pragma once
#ifndef ArrayNodeImpl_h__
#define ArrayNodeImpl_h__ 1

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

#include "XMPCore/Interfaces/IArrayNode_I.h"
#include "XMPCore/ImplHeaders/CompositeNodeImpl.h"
#include "XMPCommon/Utilities/TAllocator.h"

#include <vector>

#if XMP_WinBuild
	#pragma warning( push )
	#pragma warning( disable : 4250 )
#endif

namespace AdobeXMPCore_Int {

	class ArrayNodeImpl
		: public virtual IArrayNode_I
		, public virtual CompositeNodeImpl
	{
	public:
		typedef std::vector< spINode, TAllocator< spINode > > NodeVector;

		ArrayNodeImpl( const char * nameSpace, sizet nameSpaceLength, const char * name, sizet nameLength, eArrayForm arrarForm );

		virtual eArrayForm GetArrayForm() const;
		virtual eNodeType GetChildNodeType() const;
		virtual spINode GetNodeAtIndex( sizet index );
		virtual void InsertNodeAtIndex( const spINode & node, sizet index );
		virtual spINode RemoveNodeAtIndex( sizet index );
		virtual spINode ReplaceNodeAtIndex( const spINode & node, sizet index );
		virtual void AppendNode( const spINode & node );
		virtual spINodeIterator Iterator();
		virtual sizet ChildCount() const __NOTHROW__;
		virtual spIArrayNode ConvertToArrayNode();
		virtual eNodeType GetNodeType() const;
		virtual bool HasContent() const;
		virtual void ClearContents();
		virtual spINode CloneContents( bool ignoreEmptyNodes, bool ignoreNodesWithOnlyQualifiers, sizet qualifiersCount ) const;
		virtual bool CheckSuitabilityToBeUsedAsChildNode( const spcINode & node ) const;

	protected:
		virtual ~ArrayNodeImpl() __NOTHROW__ {}
		virtual void resetChangesForChildren() const;


		eArrayForm						mArrayForm;
		NodeVector						mChildren;

	#ifdef FRIEND_CLASS_DECLARATION
		FRIEND_CLASS_DECLARATION();
	#endif
		REQ_FRIEND_CLASS_DECLARATION();
	};
}

#endif // ArrayNodeImpl_h__
