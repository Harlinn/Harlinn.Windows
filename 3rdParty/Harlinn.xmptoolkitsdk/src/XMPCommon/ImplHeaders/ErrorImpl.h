#pragma once
#ifndef ErrorImpl_h__
#define ErrorImpl_h__ 1

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

#include "XMPCommon/Interfaces/IError_I.h"
#include "XMPCommon/BaseClasses/MemoryManagedObject.h"
#include "XMPCommon/ImplHeaders/SharedObjectImpl.h"
#include "XMPCommon/Interfaces/IUTF8String_I.h"

#if XMP_WinBuild
	#pragma warning( push )
	#pragma warning( disable : 4250 )
#endif

namespace XMP_COMPONENT_INT_NAMESPACE {

	class ErrorImpl
		: public virtual IError_I
		, public virtual SharedObjectImpl
		, public virtual MemoryManagedObject
	{
	public:
		ErrorImpl( eErrorDomain domain, eErrorCode code, eErrorSeverity severity );
		virtual ~ErrorImpl() __NOTHROW__ ;

		virtual eErrorCode GetCode() const;
		virtual eErrorDomain GetDomain() const;
		virtual eErrorSeverity GetSeverity() const;
		virtual spcIUTF8String GetMessage() const;
		virtual spcIUTF8String GetLocation() const;
		virtual spcIUTF8String GetParameter( sizet index ) const;
		virtual sizet GetParametersCount() const __NOTHROW__;
		virtual spIError GetNextError();
		virtual spIError SetNextError( const spIError & error );
		virtual void SetMessage( const char * message, sizet len = npos ) __NOTHROW__;
		virtual void SetLocation( const char * fileName, sizet lineNumber ) __NOTHROW__;
		virtual void AppendParameter( const char * parameter, sizet len = npos ) __NOTHROW__;
		virtual void AppendParameter( void * addressParameter ) __NOTHROW__;
		virtual void AppendParameter( const uint32 & integerValue ) __NOTHROW__;
		virtual void AppendParameter( const uint64 & integerValue ) __NOTHROW__;
		virtual void AppendParameter( const int32 & integerValue ) __NOTHROW__;
		virtual void AppendParameter( const int64 & integerValue ) __NOTHROW__;
		virtual void AppendParameter( const float & floatValue ) __NOTHROW__;
		virtual void AppendParameter( const double & doubleValue ) __NOTHROW__;
		virtual void AppendParameter( bool booleanValue ) __NOTHROW__;

	protected:
		eErrorCode				mErrorCode;
		eErrorDomain			mErrorDomain;
		eErrorSeverity			mErrorSeverity;
		spIUTF8String			mLocation;
		spIUTF8String			mMessage;
		mmcIUTF8StringList		mParameters;
		spIError				mNextError;

	#ifdef FRIEND_CLASS_DECLARATION
		FRIEND_CLASS_DECLARATION();
	#endif
		REQ_FRIEND_CLASS_DECLARATION();
	};
}

#if XMP_WinBuild
	#pragma warning( pop )
#endif

#endif  // ErrorImpl_h__
