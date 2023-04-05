#include <xmp/XMPCore/Interfaces/IStructureNode.h>

#include <xmp/XMPCommon/Interfaces/IUTF8String.h>
#include <xmp/XMPCommon/Utilities/TWrapperFunctions.h>
#include <xmp/XMPCore/Interfaces/ICoreObjectFactory.h>

#ifndef HXMP_USE_INLINE
#include <xmp/XMPCore/inl/IStructureNode.inl>
#endif

namespace AdobeXMPCore
{
	/*
	spIStructureNode IStructureNode_v1::MakeShared( pIStructureNode_base ptr )
	{
		if ( !ptr ) return spIStructureNode( );
		pIStructureNode p = IStructureNode::GetInterfaceVersion( ) > 1 ? ptr->GetInterfacePointer< IStructureNode >( ) : ptr;
		return shared_ptr< IStructureNode >( new IStructureNodeProxy( p ) );
	}

	spIStructureNode IStructureNode_v1::CreateStructureNode( const char* nameSpace, sizet nameSpaceLength, const char* name, sizet nameLength )
	{
		return CallSafeFunctionReturningPointer< ICoreObjectFactory, pIStructureNode_base, IStructureNode, const char*, sizet, const char*, sizet >(
			ICoreObjectFactory::GetCoreObjectFactory( ), &ICoreObjectFactory::CreateStructureNode, nameSpace, nameSpaceLength, name, nameLength );
	}
	*/
}