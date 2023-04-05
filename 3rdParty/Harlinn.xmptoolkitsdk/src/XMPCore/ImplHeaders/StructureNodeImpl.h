#pragma once
#ifndef StructureNodeImpl_h__
#define StructureNodeImpl_h__ 1

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

#include "XMPCore/Interfaces/IStructureNode_I.h"
#include "XMPCore/ImplHeaders/CompositeNodeImpl.h"
#include "XMPCommon/Utilities/TAllocator.h"

#include <map>

#if XMP_WinBuild
	#pragma warning( push )
	#pragma warning( disable : 4250 )
#endif

namespace AdobeXMPCore_Int {

	class StructureNodeImpl
		: public virtual IStructureNode_I
		, public virtual CompositeNodeImpl
	{
	public:

		struct QualifiedName {
			QualifiedName( const spcIUTF8String & nameSpace, const spcIUTF8String & name )
				: mNameSpace( nameSpace )
				, mName( name ) {}
			spcIUTF8String mNameSpace;
			spcIUTF8String mName;
		};

		struct CompareQualifiedName {
			bool operator()( const QualifiedName & key1, const QualifiedName & key2 ) const;
		};

		typedef std::map< QualifiedName, spINode, CompareQualifiedName, TAllocator< std::pair<const QualifiedName, spINode > > > QualifiedNameNodeMap;
		
		StructureNodeImpl( const char * nameSpace, sizet nameSpaceLength, const char * name, sizet nameLength );
		using IStructureNode_I::GetNode;
		virtual spINode GetNode( const spcIUTF8String & nameSpace, const spcIUTF8String & name );
		virtual spINode GetNode( const char * nameSpace, sizet nameSpaceLength, const char * name, sizet nameLength );
		virtual spINode RemoveNode( const spcIUTF8String & nameSpace, const spcIUTF8String & name );
		virtual spINode RemoveNode( const char * nameSpace, sizet nameSpaceLength, const char * name, sizet nameLength );
		virtual eNodeType GetChildNodeType( const char * nameSpace, sizet nameSpaceLength, const char * name, sizet nameLength ) const;
		virtual eNodeType GetNodeType() const;
		virtual void InsertNode( const spINode & node );
		virtual spINode ReplaceNode( const spINode & node );
		virtual void AppendNode( const spINode & node );
		virtual spINodeIterator Iterator();
		virtual sizet ChildCount() const __NOTHROW__;
		virtual spIStructureNode ConvertToStructureNode();
		virtual bool HasContent() const;
		virtual bool ValidateNameOrNameSpaceChangeForAChild( const spcIUTF8String & currentNameSpace, const spcIUTF8String & currentName, const spcIUTF8String & newNameSpace, const spcIUTF8String & newName );
		virtual void ClearContents();
		virtual spINode CloneContents( bool ignoreEmptyNodes, bool ignoreNodesWithOnlyQualifiers, sizet qualifiersCount ) const;

	protected:
		virtual ~StructureNodeImpl() __NOTHROW__ {}
		virtual void resetChangesForChildren() const;

		QualifiedNameNodeMap			mChildrenMap;

	#ifdef FRIEND_CLASS_DECLARATION
		FRIEND_CLASS_DECLARATION();
	#endif
		REQ_FRIEND_CLASS_DECLARATION();
	};
}

#if XMP_WinBuild
	#pragma warning( pop )
#endif

#endif // StructureNodeImpl_h__
