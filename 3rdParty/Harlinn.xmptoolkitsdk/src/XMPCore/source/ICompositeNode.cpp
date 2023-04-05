#include <xmp/XMPCore/Interfaces/ICompositeNode.h>

#include <xmp/XMPCommon/Interfaces/IUTF8String.h>
#include <xmp/XMPCommon/Utilities/TWrapperFunctions.h>
#include <xmp/XMPCore/Interfaces/IPath.h>
#include <xmp/XMPCore/Interfaces/INodeIterator.h>

#ifndef HXMP_USE_INLINE
#include <xmp/XMPCore/inl/ICompositeNode.inl>
#endif

namespace AdobeXMPCore
{
	spICompositeNode ICompositeNode_v1::MakeShared( pICompositeNode_base ptr )
	{
		if ( !ptr ) return spICompositeNode( );
		pICompositeNode p = ICompositeNode::GetInterfaceVersion( ) > 1 ?
			ptr->GetInterfacePointer< ICompositeNode >( ) : ptr;
		return shared_ptr< ICompositeNode >( new ICompositeNodeProxy( p ) );
	}
}