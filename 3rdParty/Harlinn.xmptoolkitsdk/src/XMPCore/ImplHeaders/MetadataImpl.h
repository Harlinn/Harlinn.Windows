#pragma once
#ifndef MetadataImpl_h__
#define MetadataImpl_h__ 1

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

#include "XMPCore/Interfaces/IMetadata_I.h"
#include "XMPCore/ImplHeaders/StructureNodeImpl.h"
#if XMP_WinBuild
	#pragma warning( push )
	#pragma warning( disable : 4250 )
#endif

namespace AdobeXMPCore_Int {

	class MetadataImpl
		: public virtual IMetadata_I
		, public virtual StructureNodeImpl
	{
	public:
		MetadataImpl();


	protected:
		virtual ~MetadataImpl() __NOTHROW__ {}

		virtual spcIUTF8String GetAboutURI() const;
		virtual void SetAboutURI( const char * uri, sizet uriLength ) __NOTHROW__;

		virtual spcIUTF8String GetName() const;
		virtual spcIUTF8String GetNameSpace() const;

		virtual spINode GetParent();
		virtual eNodeType GetParentNodeType() const;

		virtual void SetName( const char * name, sizet nameLength );
		virtual void SetNameSpace( const char * nameSpace, sizet nameSpaceLength );

		virtual void ClearContents();
		virtual spINode CloneContents( bool ignoreEmptyNodes, bool ignoreNodesWithOnlyQualifiers, sizet qualifiersCount ) const;

		virtual spIMetadata ConvertToMetadata();
		virtual void EnableFeature( const char * key, sizet keyLength ) const __NOTHROW__;
		virtual void DisableFeature( const char * key, sizet keyLength ) const __NOTHROW__;
        using IMetadata_I::GetNode;
        using IMetadata_I::RemoveNode;
		virtual spINode GetNode( const spcIUTF8String & nameSpace, const spcIUTF8String & name );
		virtual spINode RemoveNode( const spcIUTF8String & nameSpace, const spcIUTF8String & name );
		virtual void InsertNode( const spINode & node );
		virtual spINode ReplaceNode( const spINode & node );

		spIUTF8String			mAboutURI;
		mutable bool			mSupportAliases;

	#ifdef FRIEND_CLASS_DECLARATION
		FRIEND_CLASS_DECLARATION();
	#endif
		REQ_FRIEND_CLASS_DECLARATION();
	};
}

#if XMP_WinBuild
	#pragma warning( pop )
#endif

#if !(IMPLEMENTATION_HEADERS_CAN_BE_INCLUDED)
	#error "Not adhering to design constraints"
	// this file should only be included from its own cpp file
#endif

#endif // MetadataImpl_h__

