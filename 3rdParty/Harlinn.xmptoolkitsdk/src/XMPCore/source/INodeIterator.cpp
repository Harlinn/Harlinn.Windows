#include <xmp/XMPCore/Interfaces/INodeIterator.h>

#include <xmp/XMPCommon/Interfaces/IUTF8String.h>
#include <xmp/XMPCommon/Utilities/TWrapperFunctions.h>

#ifndef HXMP_USE_INLINE
#include <xmp/XMPCore/inl/INodeIterator.inl>
#endif

namespace AdobeXMPCore
{
	/*
	spINodeIterator INodeIterator_v1::MakeShared( pINodeIterator_base ptr )
	{
		if ( !ptr ) return spINodeIterator( );
		//return shared_ptr< INodeIterator >( new INodeIteratorProxy( ptr ) );
		pINodeIterator p = INodeIterator::GetInterfaceVersion( ) > 1 ? ptr->GetInterfacePointer< INodeIterator >( ) : ptr;
		return shared_ptr< INodeIterator >( new INodeIteratorProxy( p ) );
	}
	*/
}
