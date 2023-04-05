#include <xmp/XMPCore/Interfaces/ISimpleNode.h>

#include <xmp/XMPCommon/Interfaces/IUTF8String.h>
#include <xmp/XMPCommon/Utilities/TWrapperFunctions.h>
#include <xmp/XMPCore/Interfaces/ICoreObjectFactory.h>

#ifndef HXMP_USE_INLINE
#include <xmp/XMPCore/inl/ISimpleNode.inl>
#endif


namespace AdobeXMPCore
{
	/*
	spISimpleNode ISimpleNode_v1::CreateSimpleNode( const char* nameSpace, sizet nameSpaceLength, const char* name, sizet nameLength, const char* value, sizet valueLength )
	{
		return CallSafeFunctionReturningPointer< ICoreObjectFactory, pISimpleNode_base, ISimpleNode, const char*, sizet, const char*, sizet, const char*, sizet >(
			ICoreObjectFactory::GetCoreObjectFactory( ), &ICoreObjectFactory::CreateSimpleNode, nameSpace, nameSpaceLength, name, nameLength, value, valueLength );
	}

	spISimpleNode ISimpleNode_v1::MakeShared( pISimpleNode_base ptr )
	{
		if ( !ptr ) return spISimpleNode( );
		pISimpleNode p = ISimpleNode::GetInterfaceVersion( ) > 1 ? ptr->GetInterfacePointer< ISimpleNode >( ) : ptr;
		return shared_ptr< ISimpleNode >( new ISimpleNodeProxy( p ) );
	}
	*/
}

