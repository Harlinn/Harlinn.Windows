#pragma once
#ifndef __IMetadataConverterUtils_h__
#define __IMetadataConverterUtils_h__ 1

// =================================================================================================
// Copyright Adobe
// Copyright 2014 Adobe
// All Rights Reserved
//
// NOTICE:  Adobe permits you to use, modify, and distribute this file in accordance with the terms
// of the Adobe license agreement accompanying it. 
// =================================================================================================
#include <string>
#define TXMP_STRING_TYPE std::string
#include <xmp/XMP.hpp>

#include <xmp/XMPCore/XMPCoreFwdDeclarations.h>
#include <xmp/XMPCommon/Interfaces/BaseInterfaces/ISharedObject.h>
#include <xmp/XMPCommon/Interfaces/BaseInterfaces/IVersionable.h>
#include <xmp/XMPCommon/Interfaces/BaseInterfaces/IConfigurable.h>



namespace AdobeXMPCore {
    class IMetadataConverterUtilsProxy;
    //!
    //! @brief Version1 of the interface that represents an utility functions that can convert old xmp object(SXMPMeta) to new xmp object(IMetadata) and vice versa.
    //!

    class IMetadataConverterUtils_v1
    : public virtual ISharedObject
    , public virtual IVersionable
    {
        public:
        
        //!
        //! @brief Converts SXMPMeta object to IMetadata object.
        //! \return An shared pointer of type AdobeXMPCore::spIMetadata indicating converted meta object.
        //!
        HXMP_EXPORT static spIMetadata ConvertXMPMetatoIMetadata(const SXMPMeta* inOldXMP);
        
        //!
        //! @brief Converts IMetadata object to SXMPMeta object.
        //! \return SXMPMeta object indicating converted meta object.
        //!
        HXMP_EXPORT static SXMPMeta ConvertIMetadatatoXMPMeta(AdobeXMPCore::spIMetadata inNewXMP);
        
        //! \cond XMP_INTERNAL_DOCUMENTATION
        
        //!
        //! @{
        //! @brief Returns the actual raw pointer from the shared pointer, which can be a shared pointer of a proxy class.
        //! \return Either a const or non const pointer to IMetadataConverterUtils interface.
        //!
        virtual pIMetadataConverterUtils GetActualIMetadataConverterUtils() __NOTHROW__ = 0;
        XMP_PRIVATE pcIMetadataConverterUtils GetActualIMetadataConverterUtils() const __NOTHROW__ {
        return const_cast< IMetadataConverterUtils_v1 * >( this )->GetActualIMetadataConverterUtils();}
    //!
    //! @}
    
    //!
    //! @{
    //! @brief Returns the pointer to internal interfaces.
    //! \return Either a const or non const pointer to IMetadataConverterUtils_I interface.
    //!
    virtual AdobeXMPCore_Int::pIMetadataConverterUtils_I GetIMetadataConverterUtils_I() __NOTHROW__ = 0;
    
    XMP_PRIVATE AdobeXMPCore_Int::pcIMetadataConverterUtils_I GetIMetadataConverterUtils_I() const __NOTHROW__ {
    return const_cast< IMetadataConverterUtils_v1 * >( this )->GetIMetadataConverterUtils_I();}
    //!
    //! @}

    //!
    //! @{
    //! @brief Converts raw pointer to shared pointer. The raw pointer is of version 1 interface
    //! where as the returned shared pointer depends on the version client is interested in.
    //! \return Shared pointer to const or non constant interface.
    //!
    HXMP_EXPORT static spIMetadataConverterUtils MakeShared( pIMetadataConverterUtils_base ptr );
    XMP_PRIVATE static spcIMetadataConverterUtils MakeShared( pcIMetadataConverterUtils_base ptr ) {
    return MakeShared( const_cast< pIMetadataConverterUtils_base >( ptr ) );
    }
    //!
    //! @}

    //!
    //! @brief Returns the unique ID assigned to the interface.
    //! \return 64 bit unsigned integer representing the unique ID assigned to the interface.
    //!
    XMP_PRIVATE static uint64 GetInterfaceID() { return kIMetadataConverterUtilsID; }

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
        virtual ~IMetadataConverterUtils_v1() __NOTHROW__ {}

#ifdef FRIEND_CLASS_DECLARATION
    FRIEND_CLASS_DECLARATION();
#endif
    REQ_FRIEND_CLASS_DECLARATION();
    //! \endcond

    };


    class IMetadataConverterUtilsProxy
        : public virtual IMetadataConverterUtils
    {
    private:
        pIMetadataConverterUtils mRawPtr;

    public:
        HXMP_INLINE_DECL IMetadataConverterUtilsProxy( pIMetadataConverterUtils ptr );

        HXMP_INLINE_DECL virtual ~IMetadataConverterUtilsProxy( ) __NOTHROW__;

        pIMetadataConverterUtils GetActualIMetadataConverterUtils( ) __NOTHROW__ { return mRawPtr; }

        HXMP_INLINE_DECL void Acquire( ) const __NOTHROW__;

        HXMP_INLINE_DECL void Release( ) const __NOTHROW__;

        HXMP_INLINE_DECL AdobeXMPCommon_Int::pISharedObject_I GetISharedObject_I( ) __NOTHROW__;

        HXMP_INLINE_DECL AdobeXMPCore_Int::pIMetadataConverterUtils_I GetIMetadataConverterUtils_I( ) __NOTHROW__;

        HXMP_INLINE_DECL pvoid GetInterfacePointer( uint64 interfaceID, uint32 interfaceVersion );

        HXMP_INLINE_DECL pvoid getInterfacePointer( uint64 interfaceID, uint32 interfaceVersion, pcIError_base& error ) __NOTHROW__;
    };


}


#endif /*__IMetadataConverterUtils_h__*/
