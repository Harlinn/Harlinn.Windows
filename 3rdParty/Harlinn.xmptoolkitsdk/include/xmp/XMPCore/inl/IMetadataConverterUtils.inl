#pragma once
// =================================================================================================
// Copyright Adobe
// Copyright 2015 Adobe
// All Rights Reserved
//
// NOTICE:  Adobe permits you to use, modify, and distribute this file in accordance with the terms
// of the Adobe license agreement accompanying it. 
// =================================================================================================
#ifndef HARLINN_XMP_IMETADATACONVERTERUTILS_INL_
#define HARLINN_XMP_IMETADATACONVERTERUTILS_INL_

#include <assert.h>
namespace AdobeXMPCore {
    
    HXMP_INLINE IMetadataConverterUtilsProxy::IMetadataConverterUtilsProxy( pIMetadataConverterUtils ptr )
        : mRawPtr( ptr )
    {
        mRawPtr->Acquire();
    }
        
    HXMP_INLINE IMetadataConverterUtilsProxy::~IMetadataConverterUtilsProxy() __NOTHROW__ { mRawPtr->Release(); }
        
        
    HXMP_INLINE void IMetadataConverterUtilsProxy::Acquire() const __NOTHROW__ { assert( false ); }
        
    HXMP_INLINE void IMetadataConverterUtilsProxy::Release() const __NOTHROW__ { assert( false ); }
        
    HXMP_INLINE AdobeXMPCommon_Int::pISharedObject_I IMetadataConverterUtilsProxy::GetISharedObject_I() __NOTHROW__ {
        return mRawPtr->GetISharedObject_I();
    }
        
    HXMP_INLINE AdobeXMPCore_Int::pIMetadataConverterUtils_I IMetadataConverterUtilsProxy::GetIMetadataConverterUtils_I() __NOTHROW__ {
        return mRawPtr->GetIMetadataConverterUtils_I();
    }
        
    HXMP_INLINE pvoid IMetadataConverterUtilsProxy::GetInterfacePointer( uint64 interfaceID, uint32 interfaceVersion ) {
        return CallSafeFunction< IVersionable, pvoid, pvoid, uint64, uint32 >(mRawPtr, &IVersionable::getInterfacePointer, interfaceID, interfaceVersion );
    }
        
    HXMP_INLINE pvoid IMetadataConverterUtilsProxy::getInterfacePointer( uint64 interfaceID, uint32 interfaceVersion, pcIError_base & error ) __NOTHROW__ {
        assert( false );
        return mRawPtr->getInterfacePointer( interfaceID, interfaceVersion, error );
    }
    
    
}

#endif


