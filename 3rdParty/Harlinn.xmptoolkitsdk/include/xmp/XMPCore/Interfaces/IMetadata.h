#pragma once
#ifndef __IMetadata_h__
#define __IMetadata_h__ 1

// =================================================================================================
// Copyright Adobe
// Copyright 2014 Adobe
// All Rights Reserved
//
// NOTICE:  Adobe permits you to use, modify, and distribute this file in accordance with the terms
// of the Adobe license agreement accompanying it. 
// =================================================================================================

#include <xmp/XMPCore/Interfaces/IStructureNode.h>

namespace AdobeXMPCore {

	class IMetadataProxy;
	//!
	//! \brief Version1 of the interface that represents the whole xmp metadata for an asset.
	//! @details Provides all the functions to add or remove nodes to and from metadata.
	//! \attention Support multi threading through locks but can be enabled/disabled by the client. By default
	//!  every object created does not support multi-threading.
	//!

	class IMetadata_v1
		: public virtual IStructureNode_v1
	{
		friend class IMetadataProxy;
	public:
		//!

		//! @brief Gets the about URI string for the XMP metadata.
		//! \return A shared pointer to const \#AdobeXMPCommon::IUTF8String object containing URI string.
		//! \note By default this is an empty string.
		//!
		virtual spcIUTF8String GetAboutURI() const = 0;

		//!
		//! @brief Sets the about URI string for the XMP metadata.
		//! \param[in] uri Pointer to a constant char buffer containing uri string.
		//! \param[in] uriLength Number of characters in uri. In case name is null terminated set it to \#AdobeXMPCommon::npos.
		//!
		virtual void SetAboutURI( const char * uri, sizet uriLength ) __NOTHROW__ = 0;

		//!
		//! @brief Enables support for a particular feature.
		//! \param[in] key A const char buffer containing key for the feature.
		//! \param[in] keyLength Number of characters in key.
		//! \note Following keys are supported:
		//!		- alias Enable support for aliases on the metadata object.
		//!
		virtual void EnableFeature( const char * key, sizet keyLength ) const __NOTHROW__ = 0;

		//!
		//! @brief Disables support for a particular feature.
		//! \param[in] key A const char buffer containing key for the feature.
		//! \param[in] keyLength Number of characters in key.
		//!
		virtual void DisableFeature( const char * key, sizet keyLength ) const __NOTHROW__ = 0;

		//! \cond XMP_INTERNAL_DOCUMENTATION

		//!
		//! @{
		//! @brief Returns the actual raw pointer from the shared pointer, which can be a shared pointer of a proxy class.
		//! \return Either a const or non const pointer to IMetadata interface.
		//!
		virtual pIMetadata GetActualIMetadata() __NOTHROW__ = 0;
		XMP_PRIVATE pcIMetadata GetActualIMetadata() const __NOTHROW__ {
			return const_cast< IMetadata_v1 * >( this )->GetActualIMetadata();
		}
		//!
		//! @}

		//!
		//! @{
		//! @brief Returns the pointer to internal interfaces.
		//! \return Either a const or non const pointer to IMetadata_I interface.
		//!
		virtual AdobeXMPCore_Int::pIMetadata_I GetIMetadata_I() __NOTHROW__ = 0;

		XMP_PRIVATE AdobeXMPCore_Int::pcIMetadata_I GetIMetadata_I() const __NOTHROW__ {
			return const_cast< IMetadata_v1 * >( this )->GetIMetadata_I();
		}
		//!
		//! @}

		//!
		//! @{
		//! @brief Converts raw pointer to shared pointer. The raw pointer is of version 1 interface
		//! where as the returned shared pointer depends on the version client is interested in.
		//! \return Shared pointer to const or non constant interface.
		//!
		HXMP_EXPORT static spIMetadata MakeShared( pIMetadata_base ptr );
		XMP_PRIVATE static spcIMetadata MakeShared( pcIMetadata_base ptr ) {
			return MakeShared( const_cast< pIMetadata_base >( ptr ) );
		}
		//!
		//! @}

		//!
		//! @brief Returns the unique ID assigned to the interface.
		//! \return 64 bit unsigned integer representing the unique ID assigned to the interface.
		//!
		XMP_PRIVATE static uint64 GetInterfaceID() { return kIMetadataID; }

		//!
		//! @brief Returns the version of the interface.
		//! \return 32 bit unsigned integer representing the version of the interface.
		//!
		XMP_PRIVATE static uint32 GetInterfaceVersion() { return 1; }
		//! \endcond

		// static factory functions

		//!
		//! @brief Creates an empty IMetadata object.
		//! \return A shared pointer to an empty \#IMetadata object.
		//!
		HXMP_EXPORT static spIMetadata CreateMetadata();

	protected:
		//!
		//! Destructor
		//! 
		virtual ~IMetadata_v1() __NOTHROW__ {}

		//! Hiding some functions from derived classes
		using INode_v1::GetParent;
		using INode_v1::GetNameSpace;
		using INode_v1::SetNameSpace;
		using INode_v1::GetName;
		using INode_v1::SetName;

		//! \cond XMP_INTERNAL_DOCUMENTATION
		virtual pcIUTF8String_base getAboutURI( pcIError_base & error ) const __NOTHROW__ = 0;

	#ifdef FRIEND_CLASS_DECLARATION
		FRIEND_CLASS_DECLARATION();
	#endif
		REQ_FRIEND_CLASS_DECLARATION();
		//! \endcond

	};

#if XMP_WinBuild
#pragma warning( push )
#pragma warning( disable : 4250 )
#endif

	class IMetadataProxy
		: public virtual IMetadata
		, public virtual IStructureNodeProxy
	{
	private:
		pIMetadata mRawPtr;

	public:
		HXMP_INLINE_DECL IMetadataProxy( pIMetadata ptr );

		HXMP_INLINE_DECL ~IMetadataProxy( ) __NOTHROW__;

		pIMetadata GetActualIMetadata( ) __NOTHROW__ { return mRawPtr; }

		HXMP_INLINE_DECL void Acquire( ) const __NOTHROW__;

		HXMP_INLINE_DECL void Release( ) const __NOTHROW__;

		HXMP_INLINE_DECL AdobeXMPCommon_Int::pISharedObject_I GetISharedObject_I( ) __NOTHROW__;

		HXMP_INLINE_DECL AdobeXMPCore_Int::pIMetadata_I GetIMetadata_I( ) __NOTHROW__;

		HXMP_INLINE_DECL pvoid GetInterfacePointer( uint64 interfaceID, uint32 interfaceVersion );

		HXMP_INLINE_DECL pvoid getInterfacePointer( uint64 interfaceID, uint32 interfaceVersion, pcIError_base& error ) __NOTHROW__;

		HXMP_INLINE_DECL virtual spcIUTF8String GetAboutURI( ) const;

		HXMP_INLINE_DECL virtual void SetAboutURI( const char* uri, sizet uriLength ) __NOTHROW__;

		HXMP_INLINE_DECL virtual pcIUTF8String_base getAboutURI( pcIError_base& error ) const __NOTHROW__;

		HXMP_INLINE_DECL virtual void EnableFeature( const char* key, sizet keyLength ) const __NOTHROW__;

		HXMP_INLINE_DECL virtual void DisableFeature( const char* key, sizet keyLength ) const __NOTHROW__;
	};

#if XMP_WinBuild
#pragma warning( pop )
#endif



}

#endif  // __IMetadata_h__
