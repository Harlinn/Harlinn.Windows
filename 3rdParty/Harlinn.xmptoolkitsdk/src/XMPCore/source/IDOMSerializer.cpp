#include <xmp/XMPCore/Interfaces/IDOMSerializer.h>

#include <xmp/XMPCommon/Interfaces/IUTF8String.h>
#include <xmp/XMPCommon/Utilities/TWrapperFunctions.h>
#include <xmp/XMPCore/Interfaces/INode.h>
#include <xmp/XMPCore/Interfaces/INameSpacePrefixMap.h>


#ifndef HXMP_USE_INLINE
#include <xmp/XMPCore/inl/IDOMSerializer.inl>
#endif

namespace AdobeXMPCore
{
	spIDOMSerializer IDOMSerializer_v1::MakeShared( pIDOMSerializer_base ptr )
	{
		if ( !ptr ) return spIDOMSerializer( );
		pIDOMSerializer p = ptr->GetInterfacePointer< IDOMSerializer >( );
		return shared_ptr< IDOMSerializer >( new IDOMSerializerProxy( p ) );
	}
}