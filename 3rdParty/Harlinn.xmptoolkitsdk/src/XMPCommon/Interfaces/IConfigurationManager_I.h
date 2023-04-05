#pragma once
#ifndef IConfigurationManager_I_h__
#define IConfigurationManager_I_h__ 1

// =================================================================================================
// Copyright Adobe
// Copyright 2014 Adobe
// All Rights Reserved
//
// NOTICE:  Adobe permits you to use, modify, and distribute this file in accordance with the terms
// of the Adobe license agreement accompanying it. 
// =================================================================================================

#include "XMPCommon/XMPCommonFwdDeclarations_I.h"
#include <xmp/XMPCommon/Interfaces/IConfigurationManager.h>
#include "XMPCommon/Interfaces/BaseInterfaces/ISharedObject_I.h"

namespace XMP_COMPONENT_INT_NAMESPACE {

	//!
	//! \brief Internal interface that represents configuration settings controllable by the client.
	//! \details Provides functions through which client can plug in its own memory allocators, error notifiers.
	//! \attention Not Thread Safe as this functionality is generally used at the initialization phase.
	//!
#if XMP_WinBuild
	#pragma warning( push )
	#pragma warning( disable : 4250 )
#endif

	class IConfigurationManager_I
		: public virtual IConfigurationManager
		, public virtual ISharedObject_I
	{
	public:

		//!
		//! return the version of the interface.
		//! \return 32 bit unsigned integer representing the version of the interface.
		//!
		static uint32 GetInterfaceVersion() { return kInternalInterfaceVersionNumber; }

		virtual pIConfigurationManager GetActualIConfigurationManager() __NOTHROW__ { return this; }
		virtual pvoid GetInterfacePointer( uint64 interfaceID, uint32 interfaceVersion );

        virtual ~IConfigurationManager_I() __NOTHROW__{}

	protected:
		virtual uint32 registerMemoryAllocator( pIMemoryAllocator_base memoryAllocator, pcIError_base & error ) __NOTHROW__;
		virtual uint32 registerErrorNotifier( pIErrorNotifier_base clientErrorNotifier, pcIError_base & error ) __NOTHROW__;
		virtual uint32 disableMultiThreading( pcIError_base & error ) __NOTHROW__;
		virtual uint32 isMultiThreaded( pcIError_base & error ) const __NOTHROW__;
		virtual pvoid getInterfacePointer( uint64 interfaceID, uint32 interfaceVersion, pcIError_base & error ) __NOTHROW__;
		pvoid GetInterfacePointerInternal( uint64 interfaceID, uint32 interfaceVersion, bool isTopLevel );

	#ifdef FRIEND_CLASS_DECLARATION
		REQ_FRIEND_CLASS_DECLARATION();
	#endif
		REQ_FRIEND_CLASS_DECLARATION();
	};

	#if XMP_WinBuild
		#pragma warning( pop )
	#endif
}

#endif // IConfigurationManager_I_h__
