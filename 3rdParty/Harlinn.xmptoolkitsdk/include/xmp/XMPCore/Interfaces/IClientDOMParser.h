#pragma once
// =================================================================================================
// Copyright Adobe
// Copyright 2015 Adobe
// All Rights Reserved
//
// NOTICE:  Adobe permits you to use, modify, and distribute this file in accordance with the terms
// of the Adobe license agreement accompanying it. 
// =================================================================================================
#ifndef HARLINN_XMP_ICLIENTDOMPARSER_H_
#define HARLINN_XMP_ICLIENTDOMPARSER_H_

#include <xmp/XMPCore/XMPCoreFwdDeclarations.h>
#include <xmp/XMPCommon/Interfaces/IError.h>
#include <xmp/XMPCommon/Interfaces/BaseInterfaces/IConfigurable.h>
#include <xmp/XMPCore/XMPCoreErrorCodes.h>

namespace AdobeXMPCore {

	//!
	//! @brief Version 1 of the interface that supports parsing by the client supplied parser of the XMP Data Model.
	//! @details Provides functions to parse the XMP Data Model.
	//!  Thread safety is controllable by the client.
	//!
	class IClientDOMParser_v1
	{
	public:

		//!
		//! @brief Parse the contents present in the buffer taking into account the configuration parameters.
		//! \param[in] buffer Pointer to a constant char buffer containing serialized XMP Data Model.
		//! \param[in] bufferLength Number of characters in buffer. In case name is null terminated set it to \#AdobeXMPCommon::npos.
		//! \param[in] configurationParameters An object of type \#AdobeXMPCommon::IConfigurable containing all the configuration parameters requested by client
		//!  to be taken care of while parsing.
		//! \param[in] proc A function pointer to be used by the parse operation to report back any encountered errors/warnings.
		//! \return A shared pointer to \#INode object containing all the parsed XMP Data Model.
		//!
		virtual spINode Parse( const char * buffer, sizet bufferLength, pcIConfigurable configurationParameters, ReportErrorAndContinueFunctor proc ) = 0;

		//!
		//! @brief Indicates whether object supports case sensitive keys or not.
		//! \return True in case object supports case sensitive keys, false otherwise.
		//! \note Default implementation makes keys case insensitive.
		//!
		virtual bool AreKeysCaseSensitive() const { return false; }

		//!
		//! @brief Initialize the default configuration parameters.
		//! @details The object needs to fill the default configuration parameters supported by it.
		//! \param[in] configurationParameters an empty object of type \#AdobeXMPCommon::IConfigurable.
		//! \note default implementation does not fill anything in the configuration parameters.
		//!
		virtual void Initialize( pIConfigurable configurationParameters ) {};

		//!
		//! @brief Validate the data type and value for a parameter.
		//! \param[in] key An unsigned 64 bit integer value indicating the key.
		//! \param[in] dataType A value of type \#AdobeXMPCommon::IConfigurable::eDataType indicating the type of value the parameter holds.
		//! \param[in] dataValue A value of \#AdobeXMPCommon::IConfigurable::CombinedDataValue indicating the value the parameter holds.
		//! \return An error code in case there is something wrong with the combination, otherwise returns \ p0-\#AdobeXMPCommon::eCECNone.
		//! \note Default implementation validates all the keys + dataTypes + dataValue combinations.
		//!
		virtual eConfigurableErrorCode Validate( const uint64 & key, IConfigurable::eDataType dataType, const IConfigurable::CombinedDataValue & dataValue ) {
			return kCECNone;
		}

		//!
		//! @brief Called by the library when the object is no longer required by it and client can free up the resources or memory associated with the object.
		//!
		virtual void Release() const __NOTHROW__ = 0;

	protected:
		//!
		//! Destructor
		//! 
		virtual ~IClientDOMParser_v1() {}

		//! \cond XMP_INTERNAL_DOCUMENTATION
		HXMP_INLINE_DECL virtual pINode_base parse( const char * buffer, sizet bufferLength, pcIConfigurable configurationParameters, ReportErrorAndContinueABISafeProc proc, pcIError_base & error, uint32 & unknownExceptionCaught ) __NOTHROW__;
		HXMP_INLINE_DECL virtual uint32 areKeysCaseSensitive( pcIError_base & error, uint32 & unknownExceptionCaught ) const __NOTHROW__;
		HXMP_INLINE_DECL virtual void initialize( pIConfigurable configurationParameters, pcIError_base & error, uint32 & unknownExceptionCaught ) __NOTHROW__;
		HXMP_INLINE_DECL virtual uint32 validate( const uint64 & key, uint32 dataType, const IConfigurable::CombinedDataValue & dataValue, pcIError_base & error, uint32 & unknownExceptionCaught ) __NOTHROW__;

		#ifdef FRIEND_CLASS_DECLARATION
			FRIEND_CLASS_DECLARATION();
		#endif
		REQ_FRIEND_CLASS_DECLARATION();
		//! \endcond

	};
}
#endif