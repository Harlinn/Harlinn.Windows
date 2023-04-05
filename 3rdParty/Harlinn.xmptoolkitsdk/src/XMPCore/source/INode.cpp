#include <xmp/XMPCore/Interfaces/INode.h>

#include <xmp/XMPCommon/Interfaces/IUTF8String.h>
#include <xmp/XMPCommon/Utilities/TWrapperFunctions.h>
#include <xmp/XMPCore/Interfaces/IPath.h>
#include <xmp/XMPCore/Interfaces/ISimpleNode.h>
#include <xmp/XMPCore/Interfaces/INodeIterator.h>
#include <xmp/XMPCore/Interfaces/IArrayNode.h>
#include <xmp/XMPCore/Interfaces/IMetadata.h>



#ifndef HXMP_USE_INLINE
#include <xmp/XMPCore/inl/INode.inl>
#endif

namespace AdobeXMPCore
{
	/*
	spINode INode_v1::MakeShared( pINode_base ptr )
	{
		if ( !ptr ) return spINode( );
		pINode p = INode::GetInterfaceVersion( ) > 1 ? ptr->GetInterfacePointer< INode >( ) : ptr;
		return shared_ptr< INode >( new INodeProxy( p ) );
	}
	*/
}
