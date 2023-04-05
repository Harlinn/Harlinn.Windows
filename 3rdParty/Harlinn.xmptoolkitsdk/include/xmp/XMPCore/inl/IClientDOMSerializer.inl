#pragma once
// =================================================================================================
// Copyright Adobe
// Copyright 2015 Adobe
// All Rights Reserved
//
// NOTICE:  Adobe permits you to use, modify, and distribute this file in accordance with the terms
// of the Adobe license agreement accompanying it. 
// =================================================================================================
#ifndef HARLINN_XMP_ICLIENTDOMSERIALIZER_INL_
#define HARLINN_XMP_ICLIENTDOMSERIALIZER_INL_


namespace AdobeXMPCore {

	HXMP_INLINE void IClientDOMSerializer_v1::serialize( pINode_base node, pcINameSpacePrefixMap_base map, pcIConfigurable configurationParameters, ReportErrorAndContinueABISafeProc proc, pIUTF8String_base string, pcIError_base & error, uint32 & unknownErrorThrown ) __NOTHROW__ {
		unknownErrorThrown = 0;
		error = NULL;
		try {
			Serialize( INode::MakeShared( node ), INameSpacePrefixMap::MakeShared( map ), configurationParameters, proc, IUTF8String::MakeShared( string ) );
		} catch ( spcIError err ) {
			error = err->GetActualIError();
			error->Acquire();
		} catch ( ... ) {
			unknownErrorThrown = 1;
		}
	}

	HXMP_INLINE uint32 IClientDOMSerializer_v1::areKeysCaseSensitive( pcIError_base & error, uint32 & unknownExceptionCaught ) const __NOTHROW__ {
		unknownExceptionCaught = 0;
		error = NULL;
		try {
			return AreKeysCaseSensitive() ? 1 : 0;
		} catch ( spcIError err ) {
			error = err->GetActualIError();
			error->Acquire();
		} catch ( ... ) {
			unknownExceptionCaught = 1;
		}
		return 0;
	}

	HXMP_INLINE void IClientDOMSerializer_v1::initialize( pIConfigurable configurationParameters, pcIError_base & error, uint32 & unknownExceptionCaught ) __NOTHROW__ {
		unknownExceptionCaught = 0;
		error = NULL;
		try {
			Initialize( configurationParameters );
		} catch ( spcIError err ) {
			error = err->GetActualIError();
			error->Acquire();
		} catch ( ... ) {
			unknownExceptionCaught = 1;
		}
	}

	HXMP_INLINE uint32 IClientDOMSerializer_v1::validate( const uint64 & key, uint32 dataType, const IConfigurable::CombinedDataValue & dataValue, pcIError_base & error, uint32 & unknownExceptionCaught ) __NOTHROW__ {
		unknownExceptionCaught = 0;
		error = NULL;
		try {
			return static_cast< uint32 >( Validate( key, static_cast< IConfigurable::eDataType >( dataType ), dataValue ) );
		} catch ( spcIError err ) {
			error = err->GetActualIError();
			error->Acquire();
		} catch ( ... ) {
			unknownExceptionCaught = 1;
		}
		return 0;
	}

}
#endif


