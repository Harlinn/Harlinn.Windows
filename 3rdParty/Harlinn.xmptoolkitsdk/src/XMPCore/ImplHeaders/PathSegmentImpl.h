#pragma once
#ifndef PathSegmentImpl_h__
#define PathSegmentImpl_h__ 1

// =================================================================================================
// Copyright Adobe
// Copyright 2014 Adobe
// All Rights Reserved
//
// NOTICE: Adobe permits you to use, modify, and distribute this file in accordance with the terms
// of the Adobe license agreement accompanying it. 
// =================================================================================================

#if !(IMPLEMENTATION_HEADERS_CAN_BE_INCLUDED)
	#error "Not adhering to design constraints"
	// this file should only be included from its own cpp file
#endif

#include "XMPCore/Interfaces/IPathSegment_I.h"
#include "XMPCommon/BaseClasses/MemoryManagedObject.h"
#include "XMPCommon/ImplHeaders/SharedObjectImpl.h"

#if XMP_WinBuild
	#pragma warning( push )
	#pragma warning( disable : 4250 )
#endif

namespace AdobeXMPCore_Int {

	class PathSegmentImpl
		: public virtual IPathSegment_I
		, public virtual SharedObjectImpl
		, public virtual MemoryManagedObject
	{
	public:
		PathSegmentImpl( const char * nameSpace, sizet nameSpaceLength, const char * name, sizet nameLength,
			const char * value, sizet valueLength, ePathSegmentType type, sizet index );

		virtual spcIUTF8String GetNameSpace() const;
		virtual spcIUTF8String GetName() const;
		virtual ePathSegmentType GetType() const;
		virtual sizet GetIndex() const __NOTHROW__;
		virtual spcIUTF8String GetValue() const;
		virtual spcIPathSegment Clone() const;


	protected:
		virtual ~PathSegmentImpl() __NOTHROW__ {}

		spIUTF8String			mNameSpace;
		spIUTF8String			mName;
		spIUTF8String			mValue;
		ePathSegmentType		mType;
		sizet					mIndex;

	#ifdef FRIEND_CLASS_DECLARATION
		FRIEND_CLASS_DECLARATION();
	#endif
		REQ_FRIEND_CLASS_DECLARATION();
	};
}

#if XMP_WinBuild
	#pragma warning( pop )
#endif

#endif // PathSegmentImpl_h__
