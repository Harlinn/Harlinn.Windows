#pragma once
// =================================================================================================
// Copyright Adobe
// Copyright 2015 Adobe
// All Rights Reserved
//
// NOTICE:  Adobe permits you to use, modify, and distribute this file in accordance with the terms
// of the Adobe license agreement accompanying it. 
// =================================================================================================
#ifndef HARLINN_XMP_IDOMPARSER_INL_
#define HARLINN_XMP_IDOMPARSER_INL_

#include <assert.h>

namespace AdobeXMPCore {

#if XMP_WinBuild
	#pragma warning( push )
	#pragma warning( disable : 4250 )
#endif

	HXMP_INLINE IDOMParserProxy::IDOMParserProxy( pIDOMParser ptr )
		: IConfigurableProxy( ptr )
		, mRawPtr( ptr )
	{
		mRawPtr->Acquire();
	}

	HXMP_INLINE IDOMParserProxy::~IDOMParserProxy() __NOTHROW__ { mRawPtr->Release(); }

	

	HXMP_INLINE void IDOMParserProxy::Acquire() const __NOTHROW__ { assert( false ); }

	HXMP_INLINE void IDOMParserProxy::Release() const __NOTHROW__ { assert( false ); }

	HXMP_INLINE AdobeXMPCommon_Int::pISharedObject_I IDOMParserProxy::GetISharedObject_I() __NOTHROW__ {
		return mRawPtr->GetISharedObject_I();
	}

	HXMP_INLINE AdobeXMPCore_Int::pIDOMParser_I IDOMParserProxy::GetIDOMParser_I() __NOTHROW__ {
		return mRawPtr->GetIDOMParser_I();
	}

	HXMP_INLINE pvoid IDOMParserProxy::GetInterfacePointer( uint64 interfaceID, uint32 interfaceVersion ) {
		return CallSafeFunction< IVersionable, pvoid, pvoid, uint64, uint32 >(
			mRawPtr, &IVersionable::getInterfacePointer, interfaceID, interfaceVersion );
	}

	HXMP_INLINE pvoid IDOMParserProxy::getInterfacePointer( uint64 interfaceID, uint32 interfaceVersion, pcIError_base & error ) __NOTHROW__ {
		assert( false );
		return mRawPtr->getInterfacePointer( interfaceID, interfaceVersion, error );
	}

	HXMP_INLINE spIDOMParser IDOMParserProxy::Clone() const {
		return CallConstSafeFunctionReturningPointer< IDOMParser, pIDOMParser_base, IDOMParser >(
			mRawPtr, &IDOMParser::clone );
	}

	HXMP_INLINE spIMetadata IDOMParserProxy::Parse( const char * buffer, sizet bufferLength ) {
		return CallSafeFunctionReturningPointer< IDOMParser, pIMetadata_base, IMetadata, const char *, sizet >(
			mRawPtr, &IDOMParser::parse, buffer, bufferLength );
	}

	HXMP_INLINE void IDOMParserProxy::ParseWithSpecificAction( const char * buffer, sizet bufferLength, eActionType actionType, spINode & node ) {
		return CallSafeFunctionReturningVoid< IDOMParser, const char *, sizet, uint32, pINode_base >(
			mRawPtr, &IDOMParser::parseWithSpecificAction, buffer, bufferLength, static_cast< uint32 >( actionType ), node ? node->GetActualINode() : NULL );
	}

	HXMP_INLINE pIDOMParser_base IDOMParserProxy::clone( pcIError_base & error ) const __NOTHROW__ {
		assert( false );
		return mRawPtr->clone( error );
	}

	HXMP_INLINE pIMetadata_base IDOMParserProxy::parse( const char * buffer, sizet bufferLength, pcIError_base & error ) __NOTHROW__ {
		assert( false );
		return mRawPtr->parse( buffer, bufferLength, error );
	}

	HXMP_INLINE void IDOMParserProxy::parseWithSpecificAction( const char * buffer, sizet bufferLength, uint32 actionType, pINode_base node, pcIError_base & error ) __NOTHROW__ {
		assert( false );
		return mRawPtr->parseWithSpecificAction( buffer, bufferLength, actionType, node, error );
	}

#if XMP_WinBuild
	#pragma warning( pop )
#endif

	

}
#endif



