#include <xmp/XMPCommon/Interfaces/IConfigurationManager.h>
#include <xmp/XMPCommon/Utilities/TWrapperFunctions.h>

#ifndef HXMP_USE_INLINE
#include <xmp/XMPCommon/inl/IConfigurationManager.inl>
#endif


namespace AdobeXMPCommon
{
	/*
	spIConfigurationManager IConfigurationManager_v1::MakeShared( pIConfigurationManager_base ptr )
	{
		if ( !ptr ) return spIConfigurationManager( );
		pIConfigurationManager p = IConfigurationManager::GetInterfaceVersion( ) > 1 ?
			ptr->GetInterfacePointer< IConfigurationManager >( ) : ptr;
		return shared_ptr< IConfigurationManager >( new IConfigurationManagerProxy( p ) );
	}
	*/
}
