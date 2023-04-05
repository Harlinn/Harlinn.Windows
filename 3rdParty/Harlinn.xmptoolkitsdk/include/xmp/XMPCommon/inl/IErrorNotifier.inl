#pragma once
// =================================================================================================
// Copyright Adobe
// Copyright 2015 Adobe
// All Rights Reserved
//
// NOTICE:  Adobe permits you to use, modify, and distribute this file in accordance with the terms
// of the Adobe license agreement accompanying it. 
// =================================================================================================
#ifndef HARLINN_XMP_IERRORNOTIFIER_INL_
#define HARLINN_XMP_IERRORNOTIFIER_INL_


namespace AdobeXMPCommon {
	HXMP_INLINE uint32 IErrorNotifier_v1::notify( pcIError_base error, uint32 & exceptionThrown ) __NOTHROW__ {
		exceptionThrown = 0;
		bool retValue( false );
		try {
			retValue = Notify( IError::MakeShared( error ) );
		} catch ( ... ) {
			exceptionThrown = 1;
		}
		return retValue ? 1 : 0;
	}

}

#endif