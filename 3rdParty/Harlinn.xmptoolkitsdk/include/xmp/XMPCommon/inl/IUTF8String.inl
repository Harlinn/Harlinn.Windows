#pragma once
// =================================================================================================
// Copyright Adobe
// Copyright 2015 Adobe
// All Rights Reserved
//
// NOTICE:  Adobe permits you to use, modify, and distribute this file in accordance with the terms
// of the Adobe license agreement accompanying it. 
// =================================================================================================

#ifndef HARLINN_XMP_IUTF8STRING_INL_
#define HARLINN_XMP_IUTF8STRING_INL_


#include <xmp/XMPCommon/Interfaces/IObjectFactory.h>

#include <assert.h>

namespace AdobeXMPCommon {

	HXMP_INLINE IUTF8StringProxy::IUTF8StringProxy( pIUTF8String ptr )
		: mRawPtr( ptr )
	{
		mRawPtr->Acquire();
	}

	HXMP_INLINE IUTF8StringProxy::~IUTF8StringProxy() __NOTHROW__ { mRawPtr->Release(); }

	

	HXMP_INLINE void IUTF8StringProxy::Acquire() const __NOTHROW__ { assert( false ); }

	HXMP_INLINE void IUTF8StringProxy::Release() const __NOTHROW__ { assert( false ); }

	HXMP_INLINE spIUTF8String IUTF8StringProxy::append( const char * buf, sizet count ) {
		CallSafeFunction< IUTF8String, pIUTF8String_base, pIUTF8String_base, const char *, sizet >(
			mRawPtr, &IUTF8String::append, buf, count )->Release();
		return shared_from_this();
	}

	HXMP_INLINE spIUTF8String IUTF8StringProxy::append( const spcIUTF8String & src, sizet srcPos, sizet count ) {
		CallSafeFunction< IUTF8String, pIUTF8String_base, pIUTF8String_base, pcIUTF8String_base, sizet, sizet >(
			mRawPtr, &IUTF8String::append, src ? src->GetActualIUTF8String() : NULL, srcPos, count )->Release();
		return shared_from_this();
	}

	HXMP_INLINE pIUTF8String_base IUTF8StringProxy::append( const char * buffer, sizet count, pcIError_base & error ) __NOTHROW__ {
		assert( false );
		mRawPtr->append( buffer, count, error );
		return this;
	}

	HXMP_INLINE pIUTF8String_base IUTF8StringProxy::append( pcIUTF8String_base str, sizet srcPos, sizet count, pcIError_base & error ) __NOTHROW__ {
		assert( false );
		mRawPtr->append( str, srcPos, count, error );
		return this;
	}

	HXMP_INLINE spIUTF8String IUTF8StringProxy::assign( const char * buf, sizet count ) {
		CallSafeFunction< IUTF8String, pIUTF8String_base, pIUTF8String_base, const char *, sizet >(
			mRawPtr, &IUTF8String::assign, buf, count )->Release();
		return shared_from_this();
	}

	HXMP_INLINE spIUTF8String IUTF8StringProxy::assign( const spcIUTF8String & src, sizet srcPos, sizet count ) {
		CallSafeFunction< IUTF8String, pIUTF8String_base, pIUTF8String_base, pcIUTF8String_base, sizet, sizet >(
			mRawPtr, &IUTF8String::assign, src ? src->GetActualIUTF8String() : NULL, srcPos, count )->Release();
		return shared_from_this();
	}

	HXMP_INLINE pIUTF8String_base IUTF8StringProxy::assign( const char * buffer, sizet count, pcIError_base & error ) __NOTHROW__ {
		assert( false );
		mRawPtr->assign( buffer, count, error );
		return this;
	}

	HXMP_INLINE pIUTF8String_base IUTF8StringProxy::assign( pcIUTF8String_base str, sizet srcPos, sizet count, pcIError_base & error ) __NOTHROW__ {
		assert( false );
		mRawPtr->assign( str, srcPos, count, error );
		return this;
	}

	HXMP_INLINE spIUTF8String IUTF8StringProxy::insert( sizet pos, const char * buf, sizet count ) {
		CallSafeFunction< IUTF8String, pIUTF8String_base, pIUTF8String_base, sizet, const char *, sizet >(
			mRawPtr, &IUTF8String::insert, pos, buf, count )->Release();
		return shared_from_this();
	}

	HXMP_INLINE spIUTF8String IUTF8StringProxy::insert( sizet pos, const spcIUTF8String & src, sizet srcPos, sizet count ) {
		CallSafeFunction< IUTF8String, pIUTF8String_base, pIUTF8String_base, sizet, pcIUTF8String_base, sizet, sizet >(
			mRawPtr, &IUTF8String::insert, pos, src ? src->GetActualIUTF8String() : NULL, srcPos, count )->Release();
		return shared_from_this();
	}

	HXMP_INLINE pIUTF8String_base IUTF8StringProxy::insert( sizet pos, const char * buf, sizet count, pcIError_base & error ) __NOTHROW__ {
		assert( false );
		mRawPtr->insert( pos, buf, count, error );
		return this;
	}

	HXMP_INLINE pIUTF8String_base IUTF8StringProxy::insert( sizet pos, pcIUTF8String_base src, sizet srcPos, sizet count, pcIError_base & error ) __NOTHROW__ {
		assert( false );
		mRawPtr->insert( pos, src, srcPos, count, error );
		return this;
	}

	HXMP_INLINE spIUTF8String IUTF8StringProxy::erase( sizet pos, sizet count ) {
		CallSafeFunction< IUTF8String, pIUTF8String_base, pIUTF8String_base, sizet, sizet >(
			mRawPtr, &IUTF8String::erase, pos, count )->Release();
		return shared_from_this();
	}

	HXMP_INLINE pIUTF8String_base IUTF8StringProxy::erase( sizet pos, sizet count, pcIError_base & error ) __NOTHROW__ {
		assert( false );
		mRawPtr->erase( pos, count, error );
		return this;
	}

	HXMP_INLINE void IUTF8StringProxy::resize( sizet n ) {
		CallSafeFunctionReturningVoid< IUTF8String, sizet >(
			mRawPtr, &IUTF8String::resize, n );
	}

	HXMP_INLINE void IUTF8StringProxy::resize( sizet n, pcIError_base & error ) __NOTHROW__ {
		assert( false );
		mRawPtr->resize( n, error );
	}

	HXMP_INLINE spIUTF8String IUTF8StringProxy::replace( sizet pos, sizet count, const char * buf, sizet srcCount ) {
		CallSafeFunction< IUTF8String, pIUTF8String_base, pIUTF8String_base, sizet, sizet, const char *, sizet >(
			mRawPtr, &IUTF8String::replace, pos, count, buf, srcCount )->Release();
		return shared_from_this();
	}

	HXMP_INLINE spIUTF8String IUTF8StringProxy::replace( sizet pos, sizet count, const spcIUTF8String & src, sizet srcPos, sizet srcCount ) {
		CallSafeFunction< IUTF8String, pIUTF8String_base, pIUTF8String_base, sizet, sizet, pcIUTF8String_base, sizet, sizet >(
			mRawPtr, &IUTF8String::replace, pos, count, src ? src->GetActualIUTF8String() : NULL, srcPos, srcCount )->Release();
		return shared_from_this();
	}

	HXMP_INLINE pIUTF8String_base IUTF8StringProxy::replace( sizet pos, sizet count, const char * buf, sizet srcCount, pcIError_base & error ) __NOTHROW__ {
		assert( false );
		mRawPtr->replace( pos, count, buf, srcCount, error );
		return this;
	}

	HXMP_INLINE pIUTF8String_base IUTF8StringProxy::replace( sizet pos, sizet count, pcIUTF8String_base src, sizet srcPos, sizet srcCount, pcIError_base & error ) __NOTHROW__ {
		assert( false );
		mRawPtr->replace( pos, count, src, srcPos, srcCount, error );
		return this;
	}

	HXMP_INLINE sizet IUTF8StringProxy::copy( char * buf, sizet len, sizet pos ) const {
		return CallConstSafeFunction< IUTF8String, sizet, sizet, char *, sizet, sizet >(
			mRawPtr, &IUTF8String::copy, buf, len, pos );
	}

	HXMP_INLINE sizet IUTF8StringProxy::copy( char * buf, sizet len, sizet pos, pcIError_base & error ) const __NOTHROW__ {
		assert( false );
		return mRawPtr->copy( buf, len, pos, error );
	}

	HXMP_INLINE sizet IUTF8StringProxy::find( const char * buf, sizet pos, sizet count ) const {
		return CallConstSafeFunction< IUTF8String, sizet, sizet, const char *, sizet, sizet >(
			mRawPtr, &IUTF8String::find, buf, pos, count );
	}

	HXMP_INLINE sizet IUTF8StringProxy::find( const spcIUTF8String & src, sizet pos, sizet count ) const {
		return CallConstSafeFunction< IUTF8String, sizet, sizet, pcIUTF8String_base, sizet, sizet >(
			mRawPtr, &IUTF8String::find, src ? src->GetActualIUTF8String() : NULL, pos, count );
	}

	HXMP_INLINE sizet IUTF8StringProxy::find( const char * buf, sizet pos, sizet count, pcIError_base & error ) const __NOTHROW__ {
		assert( false );
		return mRawPtr->find( buf, pos, count, error );
	}

	HXMP_INLINE sizet IUTF8StringProxy::find( pcIUTF8String_base src, sizet pos, sizet count, pcIError_base & error ) const __NOTHROW__ {
		assert( false );
		return mRawPtr->find( src, pos, count, error );
	}

	HXMP_INLINE sizet IUTF8StringProxy::rfind( const char * buf, sizet pos, sizet count ) const {
		return CallConstSafeFunction< IUTF8String, sizet, sizet, const char *, sizet, sizet >(
			mRawPtr, &IUTF8String::rfind, buf, pos, count );
	}

	HXMP_INLINE sizet IUTF8StringProxy::rfind( const spcIUTF8String & src, sizet pos, sizet count ) const {
		return CallConstSafeFunction< IUTF8String, sizet, sizet, pcIUTF8String_base, sizet, sizet >(
			mRawPtr, &IUTF8String::rfind, src ? src->GetActualIUTF8String() : NULL, pos, count );
	}

	HXMP_INLINE sizet IUTF8StringProxy::rfind( const char * buf, sizet pos, sizet count, pcIError_base & error ) const __NOTHROW__ {
		assert( false );
		return mRawPtr->rfind( buf, pos, count, error );
	}

	HXMP_INLINE sizet IUTF8StringProxy::rfind( pcIUTF8String_base src, sizet pos, sizet count, pcIError_base & error ) const __NOTHROW__ {
		assert( false );
		return mRawPtr->rfind( src, pos, count, error );
	}

	HXMP_INLINE int32 IUTF8StringProxy::compare( sizet pos, sizet len, const char * buf, sizet count ) const {
		return CallConstSafeFunction< IUTF8String, int32, int32, sizet, sizet, const char *, sizet >(
			mRawPtr, &IUTF8String::compare, pos, len, buf, count );
	}

	HXMP_INLINE int32 IUTF8StringProxy::compare( sizet pos, sizet len, const spcIUTF8String & str, sizet strPos, sizet strLen ) const {
		return CallConstSafeFunction< IUTF8String, int32, int32, sizet, sizet, pcIUTF8String_base, sizet, sizet >(
			mRawPtr, &IUTF8String::compare, pos, len, str ? str->GetActualIUTF8String() : NULL, strPos, strLen );
	}

	HXMP_INLINE int32 IUTF8StringProxy::compare( sizet pos, sizet len, const char * buf, sizet count, pcIError_base & error ) const __NOTHROW__ {
		assert( false );
		return mRawPtr->compare( pos, len, buf, count, error );
	}

	HXMP_INLINE int32 IUTF8StringProxy::compare( sizet pos, sizet len, pcIUTF8String_base str, sizet strPos, sizet strLen, pcIError_base & error ) const __NOTHROW__ {
		assert( false );
		return mRawPtr->compare( pos, len, str, strPos, strLen, error );
	}

	HXMP_INLINE spIUTF8String IUTF8StringProxy::substr( sizet pos, sizet count ) const {
		return CallConstSafeFunctionReturningPointer< IUTF8String, pIUTF8String_base, IUTF8String, sizet, sizet >(
			mRawPtr, &IUTF8String::substr, pos, count );
	}

	HXMP_INLINE pIUTF8String_base IUTF8StringProxy::substr( sizet pos, sizet count, pcIError_base & error ) const __NOTHROW__ {
		assert( false );
		return mRawPtr->substr( pos, count, error );
	}

	HXMP_INLINE bool IUTF8StringProxy::empty() const {
		return CallConstSafeFunction< IUTF8String, bool, uint32 >(
			mRawPtr, &IUTF8String::empty );
	}

	HXMP_INLINE uint32 IUTF8StringProxy::empty( pcIError_base & error ) const __NOTHROW__ {
		assert( false );
		return mRawPtr->empty();
	}

	HXMP_INLINE const char * IUTF8StringProxy::c_str() const __NOTHROW__ {
		return mRawPtr->c_str();
	}

	HXMP_INLINE void IUTF8StringProxy::clear() __NOTHROW__ {
		mRawPtr->clear();
	}

	HXMP_INLINE sizet IUTF8StringProxy::size() const __NOTHROW__ {
		return mRawPtr->size();
	}

	HXMP_INLINE AdobeXMPCommon_Int::pISharedObject_I IUTF8StringProxy::GetISharedObject_I() __NOTHROW__ {
		return mRawPtr->GetISharedObject_I();
	}

	HXMP_INLINE pvoid IUTF8StringProxy::GetInterfacePointer( uint64 interfaceID, uint32 interfaceVersion ) {
		return CallSafeFunction< IVersionable, pvoid, pvoid, uint64, uint32 >(
			mRawPtr, &IVersionable::getInterfacePointer, interfaceID, interfaceVersion );
	}

	HXMP_INLINE pvoid IUTF8StringProxy::getInterfacePointer( uint64 interfaceID, uint32 interfaceVersion, pcIError_base & error ) __NOTHROW__ {
		assert( false );
		return mRawPtr->getInterfacePointer( interfaceID, interfaceVersion, error );
	}



}

#endif
