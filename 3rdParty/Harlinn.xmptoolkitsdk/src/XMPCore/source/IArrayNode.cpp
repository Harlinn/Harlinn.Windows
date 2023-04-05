#include <xmp/XMPCore/Interfaces/IArrayNode.h>

#include <xmp/XMPCommon/Interfaces/IUTF8String.h>
#include <xmp/XMPCommon/Utilities/TWrapperFunctions.h>

#ifndef HXMP_USE_INLINE
#include <xmp/XMPCore/inl/IArrayNode.inl>
#endif

namespace AdobeXMPCore
{
	/*
	spIArrayNode IArrayNode_v1::MakeShared( pIArrayNode_base ptr )
	{
		if ( !ptr ) return spIArrayNode( );
		pIArrayNode p = IArrayNode::GetInterfaceVersion( ) > 1 ? ptr->GetInterfacePointer< IArrayNode >( ) : ptr;
		return shared_ptr< IArrayNode >( new IArrayNodeProxy( p ) );
	}

	spIArrayNode IArrayNode_v1::CreateUnorderedArrayNode( const char* nameSpace, sizet nameSpaceLength, const char* name, sizet nameLength )
	{
		return CallSafeFunctionReturningPointer< ICoreObjectFactory, pIArrayNode_base, IArrayNode, uint32, const char*, sizet, const char*, sizet >(
			ICoreObjectFactory::GetCoreObjectFactory( ), &ICoreObjectFactory::CreateArrayNode, static_cast<uint32>( IArrayNode::kAFUnordered ),
			nameSpace, nameSpaceLength, name, nameLength );
	}

	spIArrayNode IArrayNode_v1::CreateOrderedArrayNode( const char* nameSpace, sizet nameSpaceLength, const char* name, sizet nameLength )
	{
		return CallSafeFunctionReturningPointer< ICoreObjectFactory, pIArrayNode_base, IArrayNode, uint32, const char*, sizet, const char*, sizet >(
			ICoreObjectFactory::GetCoreObjectFactory( ), &ICoreObjectFactory::CreateArrayNode, static_cast<uint32>( IArrayNode::kAFOrdered ),
			nameSpace, nameSpaceLength, name, nameLength );
	}

	spIArrayNode IArrayNode_v1::CreateAlternativeArrayNode( const char* nameSpace, sizet nameSpaceLength, const char* name, sizet nameLength )
	{
		return CallSafeFunctionReturningPointer< ICoreObjectFactory, pIArrayNode_base, IArrayNode, uint32, const char*, sizet, const char*, sizet >(
			ICoreObjectFactory::GetCoreObjectFactory( ), &ICoreObjectFactory::CreateArrayNode, static_cast<uint32>( IArrayNode::kAFAlternative ),
			nameSpace, nameSpaceLength, name, nameLength );
	}
	*/
}