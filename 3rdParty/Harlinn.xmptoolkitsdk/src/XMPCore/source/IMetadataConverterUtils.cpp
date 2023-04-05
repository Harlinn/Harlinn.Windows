#include <xmp/XMPCore/Interfaces/IMetadataConverterUtils.h>

#include <xmp/XMPCommon/Interfaces/IUTF8String.h>
#include <xmp/XMPCommon/Utilities/TWrapperFunctions.h>
#include <xmp/XMPCore/Interfaces/ICoreObjectFactory.h>
#include <xmp/XMPCore/Interfaces/IMetadata.h>
#include <xmp/XMPCore/XMPCoreFwdDeclarations.h>

#ifndef HXMP_USE_INLINE
#include <xmp/XMPCore/inl/IMetadataConverterUtils.inl>
#endif

namespace AdobeXMPCore
{
    /*
    spIMetadataConverterUtils IMetadataConverterUtils_v1::MakeShared( pIMetadataConverterUtils_base ptr )
    {
        if ( !ptr ) return spIMetadataConverterUtils( );
        pIMetadataConverterUtils p = IMetadataConverterUtils::GetInterfaceVersion( ) > 1 ? ptr->GetInterfacePointer< IMetadataConverterUtils >( ) : ptr;
        return shared_ptr< IMetadataConverterUtils >( new IMetadataConverterUtilsProxy( p ) );
    }

    AdobeXMPCore::spIMetadata IMetadataConverterUtils_v1::ConvertXMPMetatoIMetadata( const SXMPMeta* inOldXMP )
    {
        if ( !inOldXMP ) return  AdobeXMPCore::spIMetadata( );
        return CallSafeFunctionReturningPointer< ICoreObjectFactory, pIMetadata, IMetadata, XMPMetaRef >(
            ICoreObjectFactory::GetCoreObjectFactory( ), &ICoreObjectFactory::ConvertXMPMetatoIMetadata, inOldXMP->GetInternalRef( ) );
    }

    SXMPMeta IMetadataConverterUtils_v1::ConvertIMetadatatoXMPMeta( AdobeXMPCore::spIMetadata inNewXMP )
    {
        if ( !inNewXMP ) return SXMPMeta( );
        pcIError_base error( NULL );
        XMPMetaRef returnValue = ICoreObjectFactory::GetCoreObjectFactory( )->ConvertIMetadatatoXMPMeta( inNewXMP->GetActualIMetadata( ), error );
        if ( error ) throw IError::MakeShared( error );
        return SXMPMeta( returnValue );
    }
    */
}