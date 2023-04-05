#pragma once
#ifndef IErrorNotifier_h__
#define IErrorNotifier_h__ 1

// =================================================================================================
// Copyright Adobe
// Copyright 2014 Adobe
// All Rights Reserved
//
// NOTICE:  Adobe permits you to use, modify, and distribute this file in accordance with the terms
// of the Adobe license agreement accompanying it. 
// =================================================================================================

#include <xmp/XMPCommon/XMPCommonFwdDeclarations.h>
#include <xmp/XMPCommon/Interfaces/IError.h>

namespace XMP_COMPONENT_INT_NAMESPACE
{
	class ErrorNotifierWrapperImpl_v1;
}

namespace AdobeXMPCommon {

	//!
	//! \brief Version1 of the interface that represents an interface to be implemented by client
	//! in case he is interested in getting notifications with respect to errors/warnings encountered
	//! by library.
	//! \details In case client is interested in error notifications he can implement this interface
	//! and register the same with the \#AdobeXMPCommon::IConfigurationManager. For every warning or error
	//! encountered the NotifyError function will be called by the library. In case of warnings ( indicated
	//! by the severity of the error ) the client has the option to continue ignoring the warning by returning
	//! true else he can return false and the warning will be thrown aborting the current operation.
	//!
	class IErrorNotifier_v1
	{
		friend class XMP_COMPONENT_INT_NAMESPACE::ErrorNotifierWrapperImpl_v1;
	public:
		//!
		//! @brief Called by the library to notify the client about the warning/error.
		//! \param[in] error const pointer to a \#AdobeXMPCommon::IError. Client can use the information
		//! in the error to decide what should be the future course of action.
		//! \return A value of bool type that will indicate the future course of action.
		//!
		virtual bool Notify( const spcIError & error ) = 0;
        virtual ~IErrorNotifier_v1() {}

	protected:
		//! \cond XMP_INTERNAL_DOCUMENTATION
		HXMP_INLINE_DECL virtual uint32 notify( pcIError_base error, uint32& exceptionThrown ) __NOTHROW__;
		//! \endcond

	};
}

#endif  // IErrorNotifier_h__
