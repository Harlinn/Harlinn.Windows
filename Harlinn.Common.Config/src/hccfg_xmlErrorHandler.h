#pragma once
#ifndef HARLINN_COMMON_CONFIG_HCCFG_XMLERRORHANDLER_H_
#define HARLINN_COMMON_CONFIG_HCCFG_XMLERRORHANDLER_H_

#include <xercesc/util/XercesDefs.hpp>
#include <xercesc/util/XMLString.hpp>
#include <xercesc/sax/ErrorHandler.hpp>
#if defined(XERCES_NEW_IOSTREAMS)
#include <iostream>
#else
#include <iostream.h>
#endif

namespace Harlinn::Common::Config
{
    XERCES_CPP_NAMESPACE_USE

    class XmlErrorHandler : public ErrorHandler
    {
        // -----------------------------------------------------------------------
        //  Private data members
        //
        //  fSawErrors
        //      This is set if we get any errors, and is queryable via a getter
        //      method. Its used by the main code to suppress output if there are
        //      errors.
        // -----------------------------------------------------------------------
        bool    fSawErrors;
    public:
        // -----------------------------------------------------------------------
        //  Constructors and Destructor
        // -----------------------------------------------------------------------
        XmlErrorHandler( ) 
            : fSawErrors( false )
        {
        }

        ~XmlErrorHandler( )
        {
        }


        // -----------------------------------------------------------------------
        //  Implementation of the error handler interface
        // -----------------------------------------------------------------------
        void warning( const SAXParseException& toCatch ) override;
        void error( const SAXParseException& toCatch ) override;
        void fatalError( const SAXParseException& toCatch ) override;
        void resetErrors( ) override;

        // -----------------------------------------------------------------------
        //  Getter methods
        // -----------------------------------------------------------------------
        bool getSawErrors( ) const
        {
            return fSawErrors;
        }
    };

    // ---------------------------------------------------------------------------
    //  This is a simple class that lets us do easy (though not terribly efficient)
    //  trancoding of XMLCh data to local code page for display.
    // ---------------------------------------------------------------------------
    class StrX
    {
    public:
        // -----------------------------------------------------------------------
        //  Constructors and Destructor
        // -----------------------------------------------------------------------
        StrX( const XMLCh* const toTranscode )
        {
            // Call the private transcoding method
            fLocalForm = XMLString::transcode( toTranscode );
        }

        ~StrX( )
        {
            XMLString::release( &fLocalForm );
        }


        // -----------------------------------------------------------------------
        //  Getter methods
        // -----------------------------------------------------------------------
        const char* localForm( ) const
        {
            return fLocalForm;
        }

    private:
        // -----------------------------------------------------------------------
        //  Private data members
        //
        //  fLocalForm
        //      This is the local code page form of the string.
        // -----------------------------------------------------------------------
        char* fLocalForm;
    };

    inline std::ostream& operator<<( std::ostream& target, const StrX& toDump )
    {
        target << toDump.localForm( );
        return target;
    }
    inline std::wostream& operator<<( std::wostream& target, const StrX& toDump )
    {
        target << toDump.localForm( );
        return target;
    }
}

#endif //HARLINN_COMMON_CONFIG_HCCFG_XMLERRORHANDLER_H_

