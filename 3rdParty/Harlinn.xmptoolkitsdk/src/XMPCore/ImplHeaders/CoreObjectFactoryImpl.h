#pragma once
#ifndef CoreObjectFactoryImpl_h__
#define CoreObjectFactoryImpl_h__ 1

// =================================================================================================
// Copyright Adobe
// Copyright 2014 Adobe
// All Rights Reserved
//
// NOTICE:  Adobe permits you to use, modify, and distribute this file in accordance with the terms
// of the Adobe license agreement accompanying it. 
// =================================================================================================

#if !(IMPLEMENTATION_HEADERS_CAN_BE_INCLUDED)
	#error "Not adhering to design constraints"
	// this file should only be included from its own cpp file
#endif

#include "XMPCore/Interfaces/ICoreObjectFactory_I.h"
#include "XMPCommon/BaseClasses/MemoryManagedObject.h"
#if ENABLE_CPP_DOM_MODEL
#include "XMPCommon/ImplHeaders/SharedObjectImpl.h"
#endif

#if XMP_WinBuild
	#pragma warning( push )
	#pragma warning( disable : 4250 )
#endif

extern "C" XMP_PUBLIC AdobeXMPCore::pICoreObjectFactory_base WXMPMeta_GetXMPDOMFactoryInstance_1();

namespace AdobeXMPCore_Int {

	class CoreObjectFactoryImpl
		: public virtual ICoreObjectFactory_I
	{
	public:
		CoreObjectFactoryImpl() {}
		virtual ~CoreObjectFactoryImpl() __NOTHROW__ {}

		virtual pIError_base CreateError( uint32 domain, uint32 code, uint32 severity, pcIError_base & error ) __NOTHROW__;
		virtual pIUTF8String_base CreateUTF8String( const char * buf, sizet count, pcIError_base & error ) __NOTHROW__;
		virtual pcIPathSegment_base CreateArrayIndexPathSegment( const char * nameSpace, sizet nameSpaceLength, sizet index, pcIError_base & error ) __NOTHROW__;
		virtual pIArrayNode_base CreateArrayNode( uint32 arrayForm, const char * nameSpace, sizet nameSpaceLength, const char * name, sizet nameLength, pcIError_base & error ) __NOTHROW__;
		virtual pIMetadata_base CreateMetadata( pcIError_base & error ) __NOTHROW__;
		virtual pINameSpacePrefixMap_base CreateNameSpacePrefixMap( pcIError_base & error ) __NOTHROW__;
		virtual pIPath_base CreatePath( pcIError_base & error ) __NOTHROW__;
		virtual pcIPathSegment_base CreatePropertyPathSegment( const char * nameSpace, sizet nameSpaceLength, const char * name, sizet nameLength, pcIError_base & error ) __NOTHROW__;
		virtual pcIPathSegment_base CreateQualifierPathSegment( const char * nameSpace, sizet nameSpaceLength, const char * name, sizet nameLength, pcIError_base & error ) __NOTHROW__;
		virtual pcIPathSegment_base CreateQualifierSelectorPathSegment( const char * nameSpace, sizet nameSpaceLength, const char * name, sizet nameLength, const char * value, sizet valueLength, pcIError_base & error ) __NOTHROW__;
		virtual pISimpleNode_base CreateSimpleNode( const char * nameSpace, sizet nameSpaceLength, const char * name, sizet nameLength, const char * value, sizet valueLength, pcIError_base & error ) __NOTHROW__;
		virtual pIStructureNode_base CreateStructureNode( const char * nameSpace, sizet nameSpaceLength, const char * name, sizet nameLength, pcIError_base & error ) __NOTHROW__;
		virtual pICoreConfigurationManager_base GetCoreConfigurationManager( pcIError_base & error ) __NOTHROW__;
		virtual pIDOMImplementationRegistry_base GetDOMImplementationRegistry( pcIError_base & error ) __NOTHROW__;
		virtual pcINameSpacePrefixMap_base GetDefaultNameSpacePrefixMap( pcIError_base & error ) __NOTHROW__;
		virtual pIPath_base ParsePath( const char * path, sizet pathLength, pcINameSpacePrefixMap_base map, pcIError_base & error ) __NOTHROW__;
        virtual pIMetadata_base ConvertXMPMetatoIMetadata(XMPMetaRef xmpref, pcIError_base & error ) __NOTHROW__;
        virtual XMPMetaRef ConvertIMetadatatoXMPMeta( pIMetadata iMeta, pcIError_base & error ) __NOTHROW__;

	protected:

	#ifdef FRIEND_CLASS_DECLARATION
		FRIEND_CLASS_DECLARATION();


	#endif
		REQ_FRIEND_CLASS_DECLARATION();
	};
}


#endif // CoreObjectFactoryImpl_h__
