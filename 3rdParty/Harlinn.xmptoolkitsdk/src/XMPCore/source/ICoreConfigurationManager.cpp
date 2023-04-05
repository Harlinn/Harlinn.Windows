#include <xmp/XMPCore/Interfaces/ICoreConfigurationManager.h>

#include <xmp/XMPCommon/Interfaces/IUTF8String.h>
#include <xmp/XMPCommon/Utilities/TWrapperFunctions.h>
#include <xmp/XMPCore/Interfaces/ICoreObjectFactory.h>

#ifndef HXMP_USE_INLINE
#include <xmp/XMPCore/inl/ICoreConfigurationManager.inl>
#endif

namespace AdobeXMPCore
{
	/*
	spICoreConfigurationManager ICoreConfigurationManager_v1::MakeShared( pICoreConfigurationManager_base ptr )
	{
		if ( !ptr ) return spICoreConfigurationManager( );
		pICoreConfigurationManager p = ICoreConfigurationManager::GetInterfaceVersion( ) > 1 ? ptr->GetInterfacePointer< ICoreConfigurationManager >( ) : ptr;
		return shared_ptr< ICoreConfigurationManager >( new ICoreConfigurationManagerProxy( p ) );
	}

	spICoreConfigurationManager ICoreConfigurationManager_v1::GetCoreConfigurationManager( )
	{
		return CallSafeFunctionReturningPointer< ICoreObjectFactory, pICoreConfigurationManager_base, ICoreConfigurationManager >(
			ICoreObjectFactory::GetCoreObjectFactory( ), &ICoreObjectFactory::GetCoreConfigurationManager );
	}
	*/
}