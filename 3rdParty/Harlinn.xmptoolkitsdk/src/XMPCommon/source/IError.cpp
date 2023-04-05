#include <xmp/XMPCommon/Interfaces/IError.h>
#include <xmp/XMPCommon/Interfaces/IUTF8String.h>
#include <xmp/XMPCommon/Utilities/TWrapperFunctions.h>

#ifndef HXMP_USE_INLINE
#include <xmp/XMPCommon/inl/IError.inl>
#endif

namespace AdobeXMPCommon
{
	/*
	spIError IError_v1::CreateError( pIObjectFactory objFactory, eErrorDomain errDomain, eErrorCode errCode, eErrorSeverity errSeverity )
	{
		pIError_base temp = CallSafeFunction< IObjectFactory_base, pIError_base, pIError_base, uint32, uint32, uint32 >(
			objFactory, &IObjectFactory_base::CreateError, static_cast<uint32>( errDomain ),
			static_cast<uint32>( errCode ), static_cast<uint32>( errSeverity ) );
		return MakeShared( temp );
	}

	spIError IError_v1::MakeShared( pIError_base ptr )
	{
		if ( !ptr ) return spIError( );
		pIError p = IError::GetInterfaceVersion( ) > 1 ? ptr->GetInterfacePointer<IError>( ) : ptr;
		return shared_ptr< IError >( new IErrorProxy( p ) );
	}
	*/
}