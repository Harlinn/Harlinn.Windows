#pragma once
// =================================================================================================
// Copyright Adobe
// Copyright 2015 Adobe
// All Rights Reserved
//
// NOTICE:  Adobe permits you to use, modify, and distribute this file in accordance with the terms
// of the Adobe license agreement accompanying it. 
// =================================================================================================
#ifndef HARLINN_XMP_IERROR_INL_
#define HARLINN_XMP_IERROR_INL_


#include <assert.h>

namespace AdobeXMPCommon {

	HXMP_INLINE void IErrorProxy::Acquire() const __NOTHROW__ { assert( false ); }

	HXMP_INLINE void IErrorProxy::Release() const __NOTHROW__ { assert( false ); }

	HXMP_INLINE pvoid IErrorProxy::GetInterfacePointer( uint64 interfaceID, uint32 interfaceVersion ) 
	{
		return CallSafeFunction<IVersionable, pvoid, pvoid, uint64, uint32>( mRawPtr, &IVersionable::getInterfacePointer, interfaceID, interfaceVersion );
	}

	HXMP_INLINE pvoid IErrorProxy::getInterfacePointer( uint64 interfaceID, uint32 interfaceVersion, pcIError_base & error ) __NOTHROW__ 
	{
		assert( false );
		return mRawPtr->getInterfacePointer( interfaceID, interfaceVersion, error );
	}

	HXMP_INLINE IError_v1::eErrorCode IErrorProxy::GetCode() const
	{
		return CallConstSafeFunction< IError, eErrorCode, uint32 >(mRawPtr, &IError::getCode );
	}

	HXMP_INLINE uint32 IErrorProxy::getCode( pcIError_base & error ) const __NOTHROW__ 
	{
		assert( false );
		return mRawPtr->getCode( error );
	}

	HXMP_INLINE IError_v1::eErrorDomain IErrorProxy::GetDomain() const
	{
		return CallConstSafeFunction< IError, eErrorDomain, uint32 >( mRawPtr, &IError::getDomain );
	}

	HXMP_INLINE uint32 IErrorProxy::getDomain( pcIError_base & error ) const __NOTHROW__
	{
		assert( false );
		return mRawPtr->getDomain( error );
	}

	HXMP_INLINE IError_v1::eErrorSeverity IErrorProxy::GetSeverity() const
	{
		return CallConstSafeFunction< IError, eErrorSeverity, uint32 >(
			mRawPtr, &IError::getSeverity );
	}

	HXMP_INLINE uint32 IErrorProxy::getSeverity( pcIError_base & error ) const __NOTHROW__
	{
		assert( false );
		return mRawPtr->getSeverity( error );
	}

	HXMP_INLINE spcIUTF8String IErrorProxy::GetMessage() const {
		return CallConstSafeFunctionReturningPointer< IError, pcIUTF8String_base, const IUTF8String >(
			mRawPtr, &IError::getMessage );
	}

	HXMP_INLINE pcIUTF8String_base IErrorProxy::getMessage( pcIError_base & error ) const __NOTHROW__ {
		assert( false );
		return mRawPtr->getMessage( error );
	}

	HXMP_INLINE spcIUTF8String IErrorProxy::GetLocation() const {
		return CallConstSafeFunctionReturningPointer< IError, pcIUTF8String_base, const IUTF8String >(
			mRawPtr, &IError::getLocation );
	}

	HXMP_INLINE pcIUTF8String_base IErrorProxy::getLocation( pcIError_base & error ) const __NOTHROW__ {
		assert( false );
		return mRawPtr->getLocation( error );
	}

	HXMP_INLINE spcIUTF8String IErrorProxy::GetParameter( sizet index ) const {
		return CallConstSafeFunctionReturningPointer< IError, pcIUTF8String_base, const IUTF8String, sizet >(
			mRawPtr, &IError::getParameter, index );
	}

	HXMP_INLINE pcIUTF8String_base IErrorProxy::getParameter( sizet index, pcIError_base & error ) const __NOTHROW__ {
		assert( false );
		return mRawPtr->getParameter( index, error );
	}

	HXMP_INLINE sizet IErrorProxy::GetParametersCount() const __NOTHROW__ {
		return mRawPtr->GetParametersCount();
	}

	HXMP_INLINE spIError IErrorProxy::GetNextError() {
		pcIError_base error( NULL );
		pIError_base ptr = mRawPtr->getNextError( error );
		if ( error ) throw MakeShared( error );
		return MakeShared( ptr );
	}

	HXMP_INLINE pIError_base IErrorProxy::getNextError( pcIError_base & error ) __NOTHROW__ {
		assert( false );
		return mRawPtr->getNextError( error );
	}

	HXMP_INLINE spIError IErrorProxy::SetNextError( const spIError & nextError ) {
		pcIError_base error( NULL );
		pIError_base ptr = mRawPtr->setNextError( nextError ? nextError->GetActualIError() : NULL, error );
		if ( error ) throw MakeShared( error );
		return MakeShared( ptr );
	}

	HXMP_INLINE pIError_base IErrorProxy::setNextError( pIError_base nextError, pcIError_base & error ) __NOTHROW__ {
		assert( false );
		return mRawPtr->setNextError( nextError, error );
	}

	HXMP_INLINE void IErrorProxy::SetMessage( const char * message, sizet len ) __NOTHROW__ {
		mRawPtr->SetMessage( message, len );
	}

	HXMP_INLINE void IErrorProxy::SetLocation( const char * fileName, sizet lineNumber ) __NOTHROW__ {
		mRawPtr->SetLocation( fileName, lineNumber );
	}

	HXMP_INLINE void IErrorProxy::AppendParameter( const char * parameter, sizet len ) __NOTHROW__ {
		mRawPtr->AppendParameter( parameter, len );
	}

	HXMP_INLINE void IErrorProxy::AppendParameter( void * addressParameter ) __NOTHROW__ {
		return mRawPtr->AppendParameter( addressParameter );
	}

	HXMP_INLINE void IErrorProxy::AppendParameter( const uint32 & integerValue ) __NOTHROW__ {
		return mRawPtr->AppendParameter( integerValue );
	}

	HXMP_INLINE void IErrorProxy::AppendParameter( const uint64 & integerValue ) __NOTHROW__ {
		return mRawPtr->AppendParameter( integerValue );
	}

	HXMP_INLINE void IErrorProxy::AppendParameter( const int32 & integerValue ) __NOTHROW__ {
		return mRawPtr->AppendParameter( integerValue );
	}

	HXMP_INLINE void IErrorProxy::AppendParameter( const int64 & integerValue ) __NOTHROW__ {
		return mRawPtr->AppendParameter( integerValue );
	}

	HXMP_INLINE void IErrorProxy::AppendParameter( const float & floatValue ) __NOTHROW__ {
		return mRawPtr->AppendParameter( floatValue );
	}

	HXMP_INLINE void IErrorProxy::AppendParameter( const double & doubleValue ) __NOTHROW__ {
		return mRawPtr->AppendParameter( doubleValue );
	}

	HXMP_INLINE void IErrorProxy::AppendParameter( bool booleanValue ) __NOTHROW__ {
		return mRawPtr->AppendParameter( booleanValue );
	}

	HXMP_INLINE AdobeXMPCommon_Int::pISharedObject_I IErrorProxy::GetISharedObject_I() __NOTHROW__ {
		return mRawPtr->GetISharedObject_I();
	}

	

}


#endif