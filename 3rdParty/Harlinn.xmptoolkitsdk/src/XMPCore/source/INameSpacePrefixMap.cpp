#include <xmp/XMPCore/Interfaces/INameSpacePrefixMap.h>
#include <xmp/XMPCore/Interfaces/ICoreObjectFactory.h>

#include <xmp/XMPCommon/Interfaces/IUTF8String.h>
#include <xmp/XMPCommon/Utilities/TWrapperFunctions.h>

#ifndef HXMP_USE_INLINE
#include <xmp/XMPCore/inl/INameSpacePrefixMap.inl>
#endif

namespace AdobeXMPCore
{
	/*
	spINameSpacePrefixMap INameSpacePrefixMap_v1::MakeShared( pINameSpacePrefixMap_base ptr )
	{
		if ( !ptr ) return spINameSpacePrefixMap( );
		pINameSpacePrefixMap p = INameSpacePrefixMap::GetInterfaceVersion( ) > 1 ?
			ptr->GetInterfacePointer< INameSpacePrefixMap >( ) : ptr;
		return shared_ptr< INameSpacePrefixMap >( new INameSpacePrefixMapProxy( p ) );
	}

	spINameSpacePrefixMap INameSpacePrefixMap_v1::CreateNameSpacePrefixMap( )
	{
		return CallSafeFunctionReturningPointer< ICoreObjectFactory, pINameSpacePrefixMap_base, INameSpacePrefixMap >(
			ICoreObjectFactory::GetCoreObjectFactory( ), &ICoreObjectFactory::CreateNameSpacePrefixMap );
	}

	spcINameSpacePrefixMap INameSpacePrefixMap_v1::GetDefaultNameSpacePrefixMap( )
	{
		return CallSafeFunctionReturningPointer< ICoreObjectFactory, pcINameSpacePrefixMap_base, const INameSpacePrefixMap >(
			ICoreObjectFactory::GetCoreObjectFactory( ), &ICoreObjectFactory::GetDefaultNameSpacePrefixMap );
	}
	*/
}