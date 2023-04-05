#include <xmp/XMPCore/Interfaces/IDOMImplementationRegistry.h>

#include <xmp/XMPCommon/Interfaces/IUTF8String.h>
#include <xmp/XMPCommon/Utilities/TWrapperFunctions.h>

#include <xmp/XMPCore/Interfaces/IDOMParser.h>
#include <xmp/XMPCore/Interfaces/IDOMSerializer.h>
#include <xmp/XMPCore/Interfaces/ICoreObjectFactory.h>


#ifndef HXMP_USE_INLINE
#include <xmp/XMPCore/inl/IDOMImplementationRegistry.inl>
#endif

namespace AdobeXMPCore
{
	/*
	spIDOMImplementationRegistry IDOMImplementationRegistry_v1::GetDOMImplementationRegistry( )
	{
		return CallSafeFunctionReturningPointer< ICoreObjectFactory, pIDOMImplementationRegistry_base, IDOMImplementationRegistry >(
			ICoreObjectFactory::GetCoreObjectFactory( ), &ICoreObjectFactory::GetDOMImplementationRegistry );
	}

	spIDOMImplementationRegistry IDOMImplementationRegistry_v1::MakeShared( pIDOMImplementationRegistry_base ptr )
	{
		if ( !ptr ) return spIDOMImplementationRegistry( );
		pIDOMImplementationRegistry p = IDOMImplementationRegistry::GetInterfaceVersion( ) > 1 ? ptr->GetInterfacePointer< IDOMImplementationRegistry >( ) : ptr;
		return shared_ptr< IDOMImplementationRegistry >( new IDOMImplementationRegistryProxy( p ) );
	}
	*/
}