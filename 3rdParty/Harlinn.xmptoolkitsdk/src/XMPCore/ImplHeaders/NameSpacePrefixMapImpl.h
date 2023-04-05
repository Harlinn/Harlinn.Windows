#pragma once
#ifndef NameSpacePrefixMapImpl_h__
#define NameSpacePrefixMapImpl_h__ 1

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

#include "XMPCore/Interfaces/INameSpacePrefixMap_I.h"
#include "XMPCommon/BaseClasses/MemoryManagedObject.h"
#include "XMPCommon/ImplHeaders/SharedObjectImpl.h"
#include "XMPCommon/ImplHeaders/ThreadSafeImpl.h"
#include "XMPCommon/Utilities/TAllocator.h"
#include "XMPCommon/Utilities/IUTF8StringComparator.h"


#include <map>

#if XMP_WinBuild
	#pragma warning( push )
	#pragma warning( disable : 4250 )
#endif

namespace AdobeXMPCore_Int {

	class NameSpacePrefixMapImpl
		: public virtual INameSpacePrefixMap_I
		, public virtual SharedObjectImpl
		, public virtual MemoryManagedObject
		, public virtual ThreadSafeImpl
	{
	public:
		typedef std::pair< spcIUTF8String, spcIUTF8String > NameSpacePrefixPair;
		typedef std::map< spcIUTF8String, spcIUTF8String, IUTF8StringComparator, TAllocator< std::pair< const spcIUTF8String, spcIUTF8String > > > NameSpacePrefixMap;

		NameSpacePrefixMapImpl();


	protected:
		virtual ~NameSpacePrefixMapImpl() __NOTHROW__ {}

		virtual bool Insert( const char * prefix, sizet prefixLength, const char * nameSpace, sizet nameSpaceLength );
		virtual bool RemovePrefix( const char * prefix, sizet prefixLength );
		virtual bool RemoveNameSpace( const char * nameSpace, sizet nameSpaceLength );
		virtual bool IsPrefixPresent( const char * prefix, sizet prefixLength ) const;
		virtual bool IsNameSpacePresent( const char * nameSpace, sizet nameSpaceLength ) const;
		virtual spcIUTF8String GetNameSpace( const char * prefix, sizet prefixLength ) const;
		virtual spcIUTF8String GetNameSpace( const spcIUTF8String & prefix ) const;
		virtual spcIUTF8String GetPrefix( const char * nameSpace, sizet nameSpaceLength ) const;
		virtual spcIUTF8String GetPrefix( const spcIUTF8String & nameSpace ) const;
		virtual void Merge( const spcINameSpacePrefixMap & otherMap );
		virtual sizet Size() const __NOTHROW__;
		virtual void Clear() __NOTHROW__;
		virtual spINameSpacePrefixMap Clone() const;

		NameSpacePrefixMap				mNameSpaceToPrefixMap;
		NameSpacePrefixMap				mPrefixToNameSpaceMap;

	#ifdef FRIEND_CLASS_DECLARATION
		FRIEND_CLASS_DECLARATION();
	#endif
		REQ_FRIEND_CLASS_DECLARATION();
	};
}

#if XMP_WinBuild
	#pragma warning( pop )
#endif

#endif // NameSpacePrefixMapImpl_h__
