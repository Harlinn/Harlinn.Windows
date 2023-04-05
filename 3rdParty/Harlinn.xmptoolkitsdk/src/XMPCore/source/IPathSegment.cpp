#include <xmp/XMPCore/Interfaces/IPathSegment.h>

#include <xmp/XMPCommon/Interfaces/IUTF8String.h>
#include <xmp/XMPCommon/Utilities/TWrapperFunctions.h>
#include <xmp/XMPCommon/Interfaces/IError.h>
#include <xmp/XMPCore/Interfaces/ICoreObjectFactory.h>

#ifndef HXMP_USE_INLINE
#include <xmp/XMPCore/inl/IPathSegment.inl>
#endif

namespace AdobeXMPCore
{
	/*
	spIPathSegment IPathSegment_v1::MakeShared( pIPathSegment_base ptr )
	{
		if ( !ptr ) return spIPathSegment( );
		pIPathSegment p = IPathSegment::GetInterfaceVersion( ) > 1 ?
			ptr->GetInterfacePointer< IPathSegment >( ) : ptr;
		return shared_ptr< IPathSegment >( new IPathSegmentProxy( p ) );
	}

	spcIPathSegment IPathSegment_v1::CreatePropertyPathSegment( const char* nameSpace, sizet nameSpaceLength, const char* name, sizet nameLength )
	{
		return CallSafeFunctionReturningPointer< ICoreObjectFactory, pcIPathSegment_base, const IPathSegment, const char*, sizet, const char*, sizet >(
			ICoreObjectFactory::GetCoreObjectFactory( ), &ICoreObjectFactory::CreatePropertyPathSegment, nameSpace, nameSpaceLength, name, nameLength );
	}

	spcIPathSegment IPathSegment_v1::CreateArrayIndexPathSegment( const char* nameSpace, sizet nameSpaceLength, sizet index )
	{
		return CallSafeFunctionReturningPointer< ICoreObjectFactory, pcIPathSegment_base, const IPathSegment, const char*, sizet, sizet >(
			ICoreObjectFactory::GetCoreObjectFactory( ), &ICoreObjectFactory::CreateArrayIndexPathSegment, nameSpace, nameSpaceLength, index );
	}

	spcIPathSegment IPathSegment_v1::CreateQualifierPathSegment( const char* nameSpace, sizet nameSpaceLength, const char* name, sizet nameLength )
	{
		return CallSafeFunctionReturningPointer< ICoreObjectFactory, pcIPathSegment_base, const IPathSegment, const char*, sizet, const char*, sizet >(
			ICoreObjectFactory::GetCoreObjectFactory( ), &ICoreObjectFactory::CreateQualifierPathSegment, nameSpace, nameSpaceLength, name, nameLength );
	}

	spcIPathSegment IPathSegment_v1::CreateQualifierSelectorPathSegment( const char* nameSpace, sizet nameSpaceLength, const char* name, sizet nameLength,
		const char* value, sizet valueLength )
	{
		return CallSafeFunctionReturningPointer< ICoreObjectFactory, pcIPathSegment_base, const IPathSegment, const char*, sizet, const char*, sizet, const char*, sizet >(
			ICoreObjectFactory::GetCoreObjectFactory( ), &ICoreObjectFactory::CreateQualifierSelectorPathSegment, nameSpace, nameSpaceLength, name, nameLength, value, valueLength );
	}
	*/
}