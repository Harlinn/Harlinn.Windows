#pragma once
#ifndef IClientDOMSerializer_h__
#define IClientDOMSerializer_h__ 1

// =================================================================================================
// Copyright Adobe
// Copyright 2015 Adobe
// All Rights Reserved
//
// NOTICE:  Adobe permits you to use, modify, and distribute this file in accordance with the terms
// of the Adobe license agreement accompanying it. 
// =================================================================================================

#include <xmp/XMPCore/XMPCoreFwdDeclarations.h>
#include <xmp/XMPCommon/Interfaces/IError.h>
#include <xmp/XMPCommon/Interfaces/BaseInterfaces/IConfigurable.h>
#include <xmp/XMPCommon/XMPCommonErrorCodes.h>

namespace AdobeXMPCore_Int
{
	class ClientDOMSerializerWrapperImpl;
}


namespace AdobeXMPCore {

	//!
	//! @brief Version 1 of the interface that supports serializing by the client supplied serializer of the XMP Data Model.
	//! @details Provides functions to serialize the XMP Data Model.
	//! Thread safety is controllable by the client.
	//!
	class IClientDOMSerializer_v1
	{
		friend class AdobeXMPCore_Int::ClientDOMSerializerWrapperImpl;
	public:

		//!
		//! @brief Serialize the XMP Data Model taking into account the configuration parameters.
		//! \param[in] node The node to be serialized.
		//! \param[in] nameSpacePrefixMap An object of type \#INameSpacePrefixMap which contains preferred prefixes for namespaces.
		//! \param[in] configurationParameters An object of type #AdobeXMPCommon::IConfigurable containing all the configuration parameters requested by client
		//!  to be taken care of while serializing.
		//! \param[in] functor A function object to be used by the serializing operation to report back any encountered errors/warnings.
		//! \param[out] string A shared pointer to an IUTF8String object which should be filled with the serialized form of XMP Data Model.
		//!
		virtual void Serialize( const spINode & node, const spcINameSpacePrefixMap & nameSpacePrefixMap, pcIConfigurable configurationParameters,
			ReportErrorAndContinueFunctor functor, const spIUTF8String & string ) = 0;

		//!
		//! @brief Indicates whether object supports case sensitive keys or not.
		//! \return True in case object supports case sensitive keys, false otherwise.
		//! \note Default implementation makes keys case insensitive.
		//!
		virtual bool AreKeysCaseSensitive() const { return false; }

		//!
		//! @brief Initializes the default configuration parameters.
		//! The object needs to fill the default configuration parameters supported by it.
		//! \param[in] configurationParameters An empty object of type #AdobeXMPCommon::IConfigurable.
		//! \note Default implementation does not fill anything in the configuration parameters.
		//!
		virtual void Initialize( pIConfigurable configurationParameters ) {};

		//!
		//! @brief Validate the data type and value for a parameter.
		//! \param[in] key An unsigned 64 bit integer value indicating the key.
		//! \param[in] dataType A value of type #AdobeXMPCommon::IConfigurable::eDataType indicating the type of value the parameter holds.
		//! \param[in] dataValue A value of \#AdobeXMPCommon::IConfigurable::CombinedDataValue indicating the value the parameter holds.
		//! \return An error code in case there is something wrong with the combination, otherwise returns \#AdobeXMPCommon::eCECNone.
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
		virtual ~IClientDOMSerializer_v1() {}

		//! \cond XMP_INTERNAL_DOCUMENTATION
		HXMP_INLINE_DECL virtual void serialize( pINode_base node, pcINameSpacePrefixMap_base nameSpacePrefixMap, pcIConfigurable configurationParameters, ReportErrorAndContinueABISafeProc proc, pIUTF8String_base string, pcIError_base & error, uint32 & unknownExceptionCaught ) __NOTHROW__;
		HXMP_INLINE_DECL virtual uint32 areKeysCaseSensitive( pcIError_base & error, uint32 & unknownExceptionCaught ) const __NOTHROW__;
		HXMP_INLINE_DECL virtual void initialize( pIConfigurable configurationParameters, pcIError_base & error, uint32 & unknownExceptionCaught ) __NOTHROW__;
		HXMP_INLINE_DECL virtual uint32 validate( const uint64 & key, uint32 dataType, const IConfigurable::CombinedDataValue & dataValue, pcIError_base & error, uint32 & unknownExceptionCaught ) __NOTHROW__;
		//! \endcond

	};
}

#endif  // IClientDOMSerializer_h__
