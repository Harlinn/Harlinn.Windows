#include "pch.h"
#include <HCCException.h>
#include <hccfg/hccfg_node.h>

#include <xercesc/util/PlatformUtils.hpp>

#include <xercesc/dom/DOM.hpp>
#include <xercesc/dom/DOMException.hpp>

#include <xercesc/framework/StdOutFormatTarget.hpp>
#include <xercesc/framework/LocalFileFormatTarget.hpp>
#include <xercesc/parsers/XercesDOMParser.hpp>
#include <xercesc/util/XMLUni.hpp>

#include "hccfg_xmlDOMErrorHandler.h"
#include "hccfg_xmlSerializerFilter.h"
#include "hccfg_xmlErrorHandler.h"
#include <xercesc/util/OutOfMemoryException.hpp>

namespace Harlinn::Common::Config
{
    using namespace Harlinn::Common::Core;
    XERCES_CPP_NAMESPACE_USE

    namespace
    {
        class XmlPlatform
        {
        public:
            XmlPlatform( )
            {
                XMLPlatformUtils::Initialize( );
            }
            ~XmlPlatform( )
            {
                XMLPlatformUtils::Terminate( );
            }
        };


        void ProcessAttribute( Element& element, XERCES_CPP_NAMESPACE::DOMAttr* xmlAttr )
        {
            auto name = (wchar_t*)xmlAttr->getName( );
            auto value = (wchar_t*)xmlAttr->getValue( );
            element.AddWideString( name, value );
        }

        void ProcessAttributes( Element& element, XERCES_CPP_NAMESPACE::DOMElement* xmlElement )
        {
            auto attributes = xmlElement->getAttributes( );
            if ( attributes )
            {
                auto attributeCount = attributes->getLength( );
                for ( size_t i = 0; i < attributeCount; ++i )
                {
                    auto attribute = (DOMAttr*)attributes->item( i );
                    ProcessAttribute( element, attribute );
                }
            }
        }

        void ProcessElement( Element& element, XERCES_CPP_NAMESPACE::DOMElement* xmlElement );
        void ProcessChildElements( Element& element, XERCES_CPP_NAMESPACE::DOMElement* xmlElement )
        {
            auto childXMLElement = xmlElement->getFirstElementChild( );
            if ( childXMLElement )
            {
                auto sequence = element.AddSequence( L"Elements" );
                while ( childXMLElement )
                {
                    auto name = (wchar_t*)childXMLElement->getNodeName( );
                    auto chileElement = sequence->AddElement( name );
                    ProcessElement( *chileElement.get( ), childXMLElement );
                    childXMLElement = childXMLElement->getNextElementSibling( );
                }
            }
        }

        void ProcessElement( Element& element, XERCES_CPP_NAMESPACE::DOMElement* xmlElement )
        {
            ProcessAttributes( element, xmlElement );
            ProcessChildElements( element, xmlElement );
        }

    }

    HCCFG_EXPORT void LoadFromURI( Element& element, const std::wstring& filename, const XmlParserOptions& options )
    {
        XmlPlatform platform;
        std::wstringstream errorMessage;

        std::unique_ptr<XercesDOMParser> parser( new XercesDOMParser );
        parser->setValidationScheme( static_cast<XercesDOMParser::ValSchemes>(  options.ValidationScheme() ) );
        parser->setDoNamespaces( options.EnableNamespaces() );
        parser->setDoSchema( options.EnableSchema() );
        parser->setHandleMultipleImports( true );
        parser->setValidationSchemaFullChecking( options.EnableFullSchemaChecking() );
        parser->setCreateEntityReferenceNodes( options.CreateEntityReferenceNodes() );

        std::unique_ptr<XmlErrorHandler> xmlErrorHandler( new XmlErrorHandler( ) );
        parser->setErrorHandler( xmlErrorHandler.get() );

        bool errorsOccured = false;
        try
        {
            parser->parse( reinterpret_cast<const XMLCh*>( filename.c_str() ) );
        }
        catch ( const OutOfMemoryException& )
        {
            errorMessage << L"OutOfMemoryException" << XERCES_STD_QUALIFIER endl;
            errorsOccured = true;
        }
        catch ( const XMLException& e )
        {
            errorMessage << "An error occurred during parsing\n   Message: "
                << StrX( e.getMessage( ) ) << XERCES_STD_QUALIFIER endl;
            errorsOccured = true;
        }
        catch ( const XERCES_CPP_NAMESPACE::DOMException& e )
        {
            const unsigned int maxChars = 2047;
            XMLCh errText[maxChars + 1];

            errorMessage <<  L"\nDOM Error during parsing: '" << filename << L"'\n"
                << L"DOMException code is:  " << e.code << std::endl;

            if ( DOMImplementation::loadDOMExceptionMsg( e.code, errText, maxChars ) )
                errorMessage << L"Message is: " << StrX( errText ) << std::endl;

            errorsOccured = true;
        }
        catch ( ... )
        {
            errorMessage << "An error occurred during parsing\n " << std::endl;
            errorsOccured = true;
        }
        if ( errorsOccured )
        {
            auto message = errorMessage.str( );
            HCC_THROW( Exception, message );
        }

        // get the DOM representation
        XERCES_CPP_NAMESPACE::DOMDocument* doc = parser->getDocument( );
        XERCES_CPP_NAMESPACE::DOMElement* root = doc->getDocumentElement( );
        ProcessElement( element, root );
    }
}