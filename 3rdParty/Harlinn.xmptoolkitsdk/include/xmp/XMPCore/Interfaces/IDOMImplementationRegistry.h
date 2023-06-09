#pragma once
#ifndef IDOMImplementationRegistry_h__
#define IDOMImplementationRegistry_h__ 1

// =================================================================================================
// Copyright Adobe
// Copyright 2014 Adobe
// All Rights Reserved
//
// NOTICE:  Adobe permits you to use, modify, and distribute this file in accordance with the terms
// of the Adobe license agreement accompanying it. 
// =================================================================================================

#include <xmp/XMPCore/XMPCoreFwdDeclarations.h>
#include <xmp/XMPCommon/Interfaces/BaseInterfaces/ISharedObject.h>
#include <xmp/XMPCommon/Interfaces/BaseInterfaces/IVersionable.h>

namespace AdobeXMPCore {

	class IDOMImplementationRegistryProxy;
	//!
	//! \brief Version1 of the interface that serves as a database/registry of all the parsers and
	//!  serializers available with the XMPCore library.
	//! \details Provides all the functions to
	//!		-# get registered serializers and parsers from the database.
	//!		-# add client defined serializers and parsers to the database.
	//! \attention Support multi threading if library is configured to support multi-threading by default.
	//! \note By default following keys are registered by default with the database by the library:
	//!		-# rdf
	//!
	class IDOMImplementationRegistry_v1
		: public virtual ISharedObject
		, public virtual IVersionable
	{
		friend class IDOMImplementationRegistryProxy;
	public:

		//!
		//! @brief Gets a parser corresponding to the key and returns to the client for usage.
		//! \param[in] key Pointer to a const NULL terminated char buffer containing key of the parser in the database.
		//! \return A shared pointer to a \#IDOMParser object.
		//! \note In case the key is not present in the database an invalid shared pointer will be returned.
		//! \note key is case sensitive.
		//!
		virtual spIDOMParser GetParser( const char * key ) const = 0;

		//!
		//! @brief Gets a serializer corresponding to the key and returns to the client for usage.
		//! \param[in] key Pointer to a const NULL terminated char buffer containing key of the serializer in the database.
		//! \return A shared pointer to a \#IDOMSerializer object.
		//! \note In case the key is not present in the database an invalid shared pointer will be returned.
		//! \note key is case sensitive.
		//!
		virtual spIDOMSerializer GetSerializer( const char * key ) const = 0;

		//!
		//! @brief Registers a parser with the database along with the key.
		//! \param[in] key Pointer to a const NULL terminated char buffer containing key of the parser to be used while registering.
		//! \param[in] parser A pointer to \#IClientDOMParser object to be registered with the database
		//! \return True in case parser is successfully registered, false otherwise like in case key is already registered.
		//!
		virtual bool RegisterParser( const char * key, pIClientDOMParser_base parser ) = 0;

		//!
		//! @brief Registers a serializer with the database along with the key.
		//! \param[in] key Pointer to a const NULL terminated char buffer containing key of the serializer to be used while registering.
		//! \param[in] serializer A pointer to \#IClientDOMSerializer object to be registered with the database.
		//! \return True in case serializer is successfully registered, false otherwise like in case key is already registered.
		//!
		virtual bool RegisterSerializer( const char * key, pIClientDOMSerializer_base serializer ) = 0;

		//!
		//! @brief Provides the reference to the database of Serializers and Parsers available with the library.
		//! \return A shared pointer to \#IDOMImplementationRegistry object containing all the entries for serailizers and parsers.
		//!
		HXMP_EXPORT static spIDOMImplementationRegistry GetDOMImplementationRegistry();

		//!
		//! \cond XMP_INTERNAL_DOCUMENTATION
		
		//!
		//! @{
		//! @brief Returns the actual raw pointer from the shared pointer, which can be a shared pointer of a proxy class.
		//! \return Either a const or non const pointer to IDOMImplementationRegistry interface.
		//!
		virtual pIDOMImplementationRegistry GetActualIDOMImplementationRegistry() __NOTHROW__ = 0;
		XMP_PRIVATE pcIDOMImplementationRegistry GetActualIDOMImplementationRegistry() const __NOTHROW__ {
			return const_cast< IDOMImplementationRegistry_v1 * >( this )->GetActualIDOMImplementationRegistry();
		}
		//!
		//! @}

		//!
		//! @{
		//! @brief Returns the pointer to internal interfaces.
		//! \return Either a const or non const pointer to IDOMImplementationRegistry_I interface.
		//!
		virtual AdobeXMPCore_Int::pIDOMImplementationRegistry_I GetIDOMImplementationRegistry_I() __NOTHROW__ = 0;

		XMP_PRIVATE AdobeXMPCore_Int::pcIDOMImplementationRegistry_I GetIDOMImplementationRegistry_I() const __NOTHROW__ {
			return const_cast< IDOMImplementationRegistry_v1 * >( this )->GetIDOMImplementationRegistry_I();
		}
		//!
		//! @}
		
		//!
		//! @{
		//! @brief Converts raw pointer to shared pointer. The raw pointer is of version 1 interface
		//!        where as the returned shared pointer depends on the version client is interested in.
		//! \return Shared pointer to const or non constant interface.
		//!
		HXMP_EXPORT static spIDOMImplementationRegistry MakeShared( pIDOMImplementationRegistry_base ptr );
		XMP_PRIVATE static spcIDOMImplementationRegistry MakeShared( pcIDOMImplementationRegistry_base ptr ) {
			return MakeShared( const_cast< pIDOMImplementationRegistry_base >( ptr ) );
		}
		//!
		//! @}

		//!
		//! @brief Returns the unique ID assigned to the interface.
		//! \return 64 bit unsigned integer representing the unique ID assigned to the interface.
		//!
		XMP_PRIVATE static uint64 GetInterfaceID() { return kIDOMImplementationRegistryID; }

		//!
		//! @brief Returns the version of the interface.
		//! \return 32 bit unsigned integer representing the version of the interface.
		//!
		XMP_PRIVATE static uint32 GetInterfaceVersion() { return 1; }
		//! \endcond

	protected:
		//!
		//! Destructor
		//! 
		virtual ~IDOMImplementationRegistry_v1() __NOTHROW__ {}

		//! \cond XMP_INTERNAL_DOCUMENTATION
		virtual pIDOMParser_base getParser( const char * key, pcIError_base & error ) const __NOTHROW__ = 0;
		virtual pIDOMSerializer_base getSerializer( const char * key, pcIError_base & error ) const __NOTHROW__ = 0;
		virtual uint32 registerParser( const char * key, pIClientDOMParser_base parser, pcIError_base & error ) __NOTHROW__ = 0;
		virtual uint32 registerSerializer( const char * key, pIClientDOMSerializer_base serializer, pcIError_base & error ) __NOTHROW__= 0;

		#ifdef FRIEND_CLASS_DECLARATION
			FRIEND_CLASS_DECLARATION();
		#endif
		REQ_FRIEND_CLASS_DECLARATION();
		//! \endcond

	};

	class IDOMImplementationRegistryProxy
		: public virtual IDOMImplementationRegistry
	{
	private:
		pIDOMImplementationRegistry mRawPtr;

	public:
		HXMP_INLINE_DECL IDOMImplementationRegistryProxy( pIDOMImplementationRegistry ptr );

		HXMP_INLINE_DECL ~IDOMImplementationRegistryProxy( ) __NOTHROW__;

		pIDOMImplementationRegistry GetActualIDOMImplementationRegistry( ) __NOTHROW__ { return mRawPtr; }

		HXMP_INLINE_DECL void Acquire( ) const __NOTHROW__;

		HXMP_INLINE_DECL void Release( ) const __NOTHROW__;

		HXMP_INLINE_DECL AdobeXMPCommon_Int::pISharedObject_I GetISharedObject_I( ) __NOTHROW__;

		HXMP_INLINE_DECL AdobeXMPCore_Int::pIDOMImplementationRegistry_I GetIDOMImplementationRegistry_I( ) __NOTHROW__;

		HXMP_INLINE_DECL pvoid GetInterfacePointer( uint64 interfaceID, uint32 interfaceVersion );

		HXMP_INLINE_DECL pvoid getInterfacePointer( uint64 interfaceID, uint32 interfaceVersion, pcIError_base& error ) __NOTHROW__;

		HXMP_INLINE_DECL virtual spIDOMParser GetParser( const char* key ) const;

		HXMP_INLINE_DECL virtual spIDOMSerializer GetSerializer( const char* key ) const;

		HXMP_INLINE_DECL virtual bool RegisterParser( const char* key, pIClientDOMParser_base parser );

		HXMP_INLINE_DECL virtual bool RegisterSerializer( const char* key, pIClientDOMSerializer_base serializer );

		HXMP_INLINE_DECL virtual pIDOMParser_base getParser( const char* key, pcIError_base& error ) const __NOTHROW__;

		HXMP_INLINE_DECL virtual pIDOMSerializer_base getSerializer( const char* key, pcIError_base& error ) const __NOTHROW__;

		HXMP_INLINE_DECL virtual uint32 registerParser( const char* key, pIClientDOMParser_base parser, pcIError_base& error ) __NOTHROW__;

		HXMP_INLINE_DECL virtual uint32 registerSerializer( const char* key, pIClientDOMSerializer_base serializer, pcIError_base& error ) __NOTHROW__;

	};



}

#endif // IDOMImplementationRegistry_h__
