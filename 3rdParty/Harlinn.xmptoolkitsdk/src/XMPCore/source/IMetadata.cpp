#include <xmp/XMPCore/Interfaces/IMetadata.h>

#include <xmp/XMPCommon/Interfaces/IUTF8String.h>
#include <xmp/XMPCommon/Utilities/TWrapperFunctions.h>
#include <xmp/XMPCore/Interfaces/ICoreObjectFactory.h>

#ifndef HXMP_USE_INLINE
#include <xmp/XMPCore/inl/IMetadata.inl>
#endif
namespace AdobeXMPCore
{
	/*
	spIMetadata IMetadata_v1::MakeShared( pIMetadata_base ptr )
	{
		if ( !ptr ) return spIMetadata( );
		pIMetadata p = IMetadata::GetInterfaceVersion( ) > 1 ? ptr->GetInterfacePointer< IMetadata >( ) : ptr;
		return shared_ptr< IMetadata >( new IMetadataProxy( p ) );
	}

	spIMetadata IMetadata_v1::CreateMetadata( )
	{
		return CallSafeFunctionReturningPointer< ICoreObjectFactory, pIMetadata, IMetadata >(
			ICoreObjectFactory::GetCoreObjectFactory( ), &ICoreObjectFactory::CreateMetadata );
	}
	*/
}