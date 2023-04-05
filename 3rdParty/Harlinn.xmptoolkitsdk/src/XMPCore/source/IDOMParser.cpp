#include <xmp/XMPCore/Interfaces/IDOMParser.h>

#include <xmp/XMPCommon/Interfaces/IUTF8String.h>
#include <xmp/XMPCommon/Utilities/TWrapperFunctions.h>
#include <xmp/XMPCore/Interfaces/IMetadata.h>

#ifndef HXMP_USE_INLINE
#include <xmp/XMPCore/inl/IDOMParser.inl>
#endif

namespace AdobeXMPCore
{
	spIDOMParser IDOMParser_v1::MakeShared( pIDOMParser_base ptr )
	{
		if ( !ptr ) return spIDOMParser( );
		pIDOMParser p = IDOMParser::GetInterfaceVersion( ) > 1 ? ptr->GetInterfacePointer< IDOMParser >( ) : ptr;
		return shared_ptr< IDOMParser >( new IDOMParserProxy( p ) );
	}
}