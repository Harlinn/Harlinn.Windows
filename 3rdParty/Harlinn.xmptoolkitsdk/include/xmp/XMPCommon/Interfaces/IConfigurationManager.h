#pragma once
//! @file IConfigurationManager.h

#ifndef IConfigurationManager_h__
#define IConfigurationManager_h__ 1

//
// =================================================================================================
// Copyright Adobe
// Copyright 2014 Adobe
// All Rights Reserved
// 
// NOTICE:  Adobe permits you to use, modify, and distribute this file in accordance with the terms
// of the Adobe license agreement accompanying it. 
// =================================================================================================
//

#include <xmp/XMPCommon/Interfaces/BaseInterfaces/ISharedObject.h>
#include <xmp/XMPCommon/Interfaces/BaseInterfaces/IVersionable.h>
#include <xmp/XMPCommon/XMPCommonFwdDeclarations.h>
#include <xmp/XMPCommon/Interfaces/IError.h>

namespace AdobeXMPCommon {

	//!
	//! @class IConfigurationManager_v1
	//! \brief Version1 of the interface that represents configuration settings controllable by the client.
	//! \details Provides functions through which client can plug in its own memory allocators, error notifiers.
	//! \attention Not Thread Safe as this functionality is generally used at the initialization phase.
	//!
	class IConfigurationManager_v1
		: public virtual ISharedObject
		, public virtual IVersionable
	{
		friend class IConfigurationManagerProxy;
	public:

		//!
		//! @brief Allows the client to plug in its own memory allocation procedures which will be used to allocate/deallocate memory from the heap.
		//! 
		//! \param[in] memoryAllocator A pointer to an object of type AdobeXMPCommon::IMemoryAllocator.
		//! NULL pointer will switch to default allocator built in the library.
		//! \return A value of bool type; true means successful and false otherwise.
		//!
		virtual bool RegisterMemoryAllocator( pIMemoryAllocator memoryAllocator ) = 0;

		//!
		//! @brief Allows the client to plug in its own error notification procedures which will be used to
		//! inform client about various warnings and errors.
		//! \param[in] clientErrorNotifier A pointer to an object of type AdobeXMPCommon::IErrorNotifier. NULL
		//! pointer means client no longer wants to be notified of any warnings or errors.
		//! \return a value of bool type; true means successful and false otherwise.
		//!
		virtual bool RegisterErrorNotifier( pIErrorNotifier_base clientErrorNotifier ) = 0;

		//!
		//! @brief Allows the client to disable the support for multi threading inside the library.
		//! By default library supports multi-threading.
		//! \return A value of bool type; true means successful and false otherwise.
		//!
		virtual bool DisableMultiThreading() = 0;

		//!
		//! @brief Returns whether library supports multi threading or not
		//! \return A value of bool type; true means it supports multi threading and false otherwise.
		//!
		virtual bool IsMultiThreaded() const = 0;

		//!
		//! \cond XMP_INTERNAL_DOCUMENTATION
		//! @{
		//!  @brief Returns the actual raw pointer from the shared pointer, which can be a shared pointer of a proxy class.
		//!  \return Either a const or non const pointer to IConfigurationManager interface.
		//!
		virtual pIConfigurationManager GetActualIConfigurationManager() __NOTHROW__ = 0;
		XMP_PRIVATE pcIConfigurationManager GetActualIConfigurationManager() const __NOTHROW__ {
			return const_cast< IConfigurationManager_v1 * >( this )->GetActualIConfigurationManager();
		}
		//!
		//! @}

		//!
		//! @{
		//! @brief Convert raw pointer to shared pointer. 
		//! @detail The raw pointer is of version 1 interface where as the returned shared pointer depends on the version client is interested in.
		//! 
		//! \return Shared pointer to const or non constant IConfigurationManager interface.
		//!
		HXMP_EXPORT static spIConfigurationManager MakeShared( pIConfigurationManager_base ptr );
		XMP_PRIVATE static spcIConfigurationManager MakeShared( pcIConfigurationManager_base ptr ) {
			return MakeShared( const_cast< pIConfigurationManager_base >( ptr ) );
		}
		//!
		//! @}

		//!
		//!  @brief Return the unique ID assigned to the interface.
		//! \return 64 bit unsigned integer representing the unique ID assigned to the interface.
		//!
		XMP_PRIVATE static uint64 GetInterfaceID() { return kIConfigurationManagerID; }

		//!
		//! @brief Returns the version of the interface.
		//! \return 32 bit unsigned integer representing the version of the interface.
		//!
		XMP_PRIVATE static uint32 GetInterfaceVersion() { return 1; }
		//! \endcond

        virtual ~IConfigurationManager_v1() __NOTHROW__ {}
    
	protected:
    
		//! \cond XMP_INTERNAL_DOCUMENTATION
		virtual uint32 registerMemoryAllocator( pIMemoryAllocator_base memoryAllocator, pcIError_base & error ) __NOTHROW__ = 0;
		virtual uint32 registerErrorNotifier( pIErrorNotifier_base clientErrorNotifier, pcIError_base & error ) __NOTHROW__ = 0;
		virtual uint32 disableMultiThreading( pcIError_base & error ) __NOTHROW__ = 0;
		virtual uint32 isMultiThreaded( pcIError_base & error ) const __NOTHROW__ = 0;
		//! \endcond

		#ifdef FRIEND_CLASS_DECLARATION
			FRIEND_CLASS_DECLARATION();
		#endif
		REQ_FRIEND_CLASS_DECLARATION();
		//! \endcond
	};
}




namespace AdobeXMPCommon {
	class IConfigurationManagerProxy
		: public virtual IConfigurationManager
	{
	private:
		pIConfigurationManager mRawPtr;

	public:
		IConfigurationManagerProxy( pIConfigurationManager ptr )
			: mRawPtr( ptr )
		{
			mRawPtr->Acquire();
		}

		~IConfigurationManagerProxy() __NOTHROW__ { mRawPtr->Release(); }
		pIConfigurationManager GetActualIConfigurationManager() __NOTHROW__ { return mRawPtr; }
		AdobeXMPCommon_Int::pISharedObject_I GetISharedObject_I() __NOTHROW__ { return mRawPtr->GetISharedObject_I(); }

		HXMP_INLINE_DECL void Acquire() const __NOTHROW__;
		HXMP_INLINE_DECL void Release() const __NOTHROW__;
		HXMP_INLINE_DECL pvoid GetInterfacePointer( uint64 interfaceID, uint32 interfaceVersion );
		HXMP_INLINE_DECL virtual bool RegisterMemoryAllocator( pIMemoryAllocator memoryAllocator );
		HXMP_INLINE_DECL virtual bool RegisterErrorNotifier( pIErrorNotifier_base clientErrorNotifier );
		HXMP_INLINE_DECL virtual bool DisableMultiThreading();
		HXMP_INLINE_DECL virtual bool IsMultiThreaded() const;

	protected:
		HXMP_INLINE_DECL virtual uint32 registerMemoryAllocator( pIMemoryAllocator_base memoryAllocator, pcIError_base & error ) __NOTHROW__;
		HXMP_INLINE_DECL virtual uint32 registerErrorNotifier( pIErrorNotifier_base clientErrorNotifier, pcIError_base & error ) __NOTHROW__;
		HXMP_INLINE_DECL virtual uint32 disableMultiThreading( pcIError_base & error ) __NOTHROW__;
		HXMP_INLINE_DECL virtual uint32 isMultiThreaded( pcIError_base & error ) const __NOTHROW__;
		HXMP_INLINE_DECL pvoid getInterfacePointer( uint64 interfaceID, uint32 interfaceVersion, pcIError_base & error ) __NOTHROW__;
	};
}


#endif // IConfigurationManager_h__
