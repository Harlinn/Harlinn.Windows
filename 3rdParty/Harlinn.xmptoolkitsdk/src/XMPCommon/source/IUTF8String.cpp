#include <xmp/xmpdef.h>
#include <xmp/XMPCommon/Interfaces/IUTF8String.h>
#include <xmp/XMPCommon/Utilities/TWrapperFunctions.h>

#ifndef HXMP_USE_INLINE
#include <xmp/XMPCommon/inl/IUTF8String.inl>
#endif

namespace AdobeXMPCommon
{
	/*
	spIUTF8String IUTF8String_v1::MakeShared( pIUTF8String_base ptr )
	{
		if ( !ptr ) return spIUTF8String( );
		pIUTF8String p = IUTF8String::GetInterfaceVersion( ) > 1 ? ptr->GetInterfacePointer< IUTF8String >( ) : ptr;
		return shared_ptr< IUTF8StringProxy >( new IUTF8StringProxy( p ) );
	}

	spIUTF8String IUTF8String_v1::CreateUTF8String( pIObjectFactory objFactory )
	{
		return CallSafeFunctionReturningPointer< IObjectFactory, pIUTF8String_base, IUTF8String, const char*, sizet >(
			objFactory, &IObjectFactory::CreateUTF8String, NULL, (sizet)0 );
	}

	spIUTF8String IUTF8String_v1::CreateUTF8String( pIObjectFactory objFactory, const char* buf, sizet count )
	{
		return CallSafeFunctionReturningPointer< IObjectFactory, pIUTF8String_base, IUTF8String, const char*, sizet >(
			objFactory, &IObjectFactory::CreateUTF8String, buf, count );
	}
	*/
}