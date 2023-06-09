#pragma once
#ifndef __UTF8String_Impl_h__
#define __UTF8String_Impl_h__ 1

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

#include "XMPCommon/Interfaces/IUTF8String_I.h"
#include "XMPCommon/BaseClasses/MemoryManagedObject.h"
#include "XMPCommon/ImplHeaders/SharedObjectImpl.h"

#include "XMPCommon/Utilities/UTF8String.h"

#if XMP_WinBuild
	#pragma warning( push )
	#pragma warning( disable : 4250 )
#endif

namespace XMP_COMPONENT_INT_NAMESPACE {

	class UTF8StringImpl
		: public virtual IUTF8String_I
		, public virtual SharedObjectImpl
		, public virtual MemoryManagedObject
		, public enable_shared_from_this< UTF8StringImpl >
	{
	public:
		UTF8StringImpl() {}
        using IUTF8String_I::append;
        using IUTF8String_I::assign;
        using IUTF8String_I::insert;
        using IUTF8String_I::erase;
        using IUTF8String_I::resize;
        using IUTF8String_I::replace;
        using IUTF8String_I::copy;
        using IUTF8String_I::find;
        using IUTF8String_I::rfind;
        using IUTF8String_I::compare;
        using IUTF8String_I::substr;
        using IUTF8String_I::empty;
        
		virtual spIUTF8String append( const char * buf, sizet count );
		virtual spIUTF8String append( const spcIUTF8String & src, sizet srcPos, sizet count );
		virtual spIUTF8String assign( const char * buf, sizet count );
		virtual spIUTF8String assign( const spcIUTF8String & src, sizet srcPos, sizet count );
		virtual spIUTF8String insert( sizet pos, const char * buf, sizet count );
		virtual spIUTF8String insert( sizet pos, const spcIUTF8String & src, sizet srcPos, sizet count );
		virtual spIUTF8String erase( sizet pos, sizet count );
		virtual void resize( sizet n );
		virtual spIUTF8String replace( sizet pos, sizet count, const char * buf, sizet srcCount );
		virtual spIUTF8String replace( sizet pos, sizet count, const spcIUTF8String & src, sizet srcPos, sizet srcCount );
		virtual sizet copy( char * buf, sizet len, sizet pos ) const;
		virtual sizet find( const char * buf, sizet pos, sizet count ) const;
		virtual sizet find( const spcIUTF8String & src, sizet pos, sizet count ) const;
		virtual sizet rfind( const char * buf, sizet pos, sizet count ) const;
		virtual sizet rfind( const spcIUTF8String & src, sizet pos, sizet count ) const;
		virtual int32 compare( sizet pos, sizet len, const char * buf, sizet count ) const;
		virtual int32 compare( sizet pos, sizet len, const spcIUTF8String & str, sizet strPos, sizet strLen ) const;
		virtual spIUTF8String substr( sizet pos, sizet count ) const;

		virtual bool empty() const;
		virtual const char * c_str() const __NOTHROW__;
		virtual void clear() __NOTHROW__;
		virtual sizet size() const __NOTHROW__;

	protected:
		spIUTF8String returnSelfSharedPointer();
		sizet ValidatePosParameter( const sizet & pos ) const;

		UTF8String				mString;
        
        virtual ~UTF8StringImpl() __NOTHROW__ {}

	#ifdef FRIEND_CLASS_DECLARATION
		FRIEND_CLASS_DECLARATION();
	#endif
		REQ_FRIEND_CLASS_DECLARATION();
	};
}

#if XMP_WinBuild
	#pragma warning( pop )
#endif

#endif  // __UTF8String_Impl_h__
