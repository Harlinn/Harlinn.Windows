#pragma once
#ifndef HARLINN_XMP_ICLIENTDOMPARSER_INL_
#define HARLINN_XMP_ICLIENTDOMPARSER_INL_
// =================================================================================================
// Copyright Adobe
// Copyright 2015 Adobe
// All Rights Reserved
//
// NOTICE:  Adobe permits you to use, modify, and distribute this file in accordance with the terms
// of the Adobe license agreement accompanying it. 
// =================================================================================================

namespace AdobeXMPCore {

	HXMP_INLINE pINode_base IClientDOMParser_v1::parse( const char * buffer, sizet bufferLength, pcIConfigurable configurationParameters, ReportErrorAndContinueABISafeProc proc, pcIError_base & error, uint32 & unknownExceptionCaught ) __NOTHROW__ {
		unknownExceptionCaught = 0;
		error = NULL;
		try {
			auto node = Parse( buffer, bufferLength, configurationParameters, proc );
			if ( node ) {
				node->Acquire();
				return node->GetActualINode();
			}
			return NULL;
		} catch ( spcIError err ) {
			error = err->GetActualIError();
			error->Acquire();
		} catch ( ... ) {
			unknownExceptionCaught = 1;
		}
		return NULL;
	}

	HXMP_INLINE uint32 IClientDOMParser_v1::areKeysCaseSensitive( pcIError_base & error, uint32 & unknownExceptionCaught ) const __NOTHROW__ {
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

	HXMP_INLINE void IClientDOMParser_v1::initialize( pIConfigurable configurationParameters, pcIError_base & error, uint32 & unknownExceptionCaught ) __NOTHROW__ {
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

	HXMP_INLINE uint32 IClientDOMParser_v1::validate( const uint64 & key, uint32 dataType, const IConfigurable::CombinedDataValue & dataValue, pcIError_base & error, uint32 & unknownExceptionCaught ) __NOTHROW__ {
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