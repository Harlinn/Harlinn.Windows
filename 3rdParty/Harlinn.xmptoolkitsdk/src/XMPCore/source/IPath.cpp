#include <xmp/XMPCore/Interfaces/IPath.h>

#include <xmp/XMPCommon/Interfaces/IUTF8String.h>
#include <xmp/XMPCommon/Utilities/TWrapperFunctions.h>

#include <xmp/XMPCore/Interfaces/INameSpacePrefixMap.h>
#include <xmp/XMPCore/Interfaces/IPathSegment.h>
#include <xmp/XMPCore/Interfaces/ICoreObjectFactory.h>


#ifndef HXMP_USE_INLINE
#include <xmp/XMPCore/inl/IPath.inl>
#endif

namespace AdobeXMPCore
{
	/*
	spIPath IPath_v1::MakeShared( pIPath_base ptr )
	{
		if ( !ptr ) return spIPath( );
		pIPath p = IPath::GetInterfaceVersion( ) > 1 ? ptr->GetInterfacePointer< IPath >( ) : ptr;
		return shared_ptr< IPath >( new IPathProxy( p ) );
	}

	spIPath IPath_v1::CreatePath( )
	{
		return CallSafeFunctionReturningPointer< ICoreObjectFactory, pIPath_base, IPath >(
			ICoreObjectFactory::GetCoreObjectFactory( ), &ICoreObjectFactory::CreatePath );
	}

	spIPath IPath_v1::ParsePath( const char* path, sizet pathLength, const spcINameSpacePrefixMap& map )
	{
		return CallSafeFunctionReturningPointer< ICoreObjectFactory, pIPath_base, IPath, const char*, sizet, pcINameSpacePrefixMap_base >(
			ICoreObjectFactory::GetCoreObjectFactory( ), &ICoreObjectFactory::ParsePath, path, pathLength, map ? map->GetActualINameSpacePrefixMap( ) : NULL );
	}
	*/
}
