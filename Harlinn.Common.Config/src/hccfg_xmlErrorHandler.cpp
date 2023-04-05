#include "pch.h"
#include "hccfg_xmlErrorHandler.h"

namespace Harlinn::Common::Config
{
    using namespace Harlinn::Common::Core;
    XERCES_CPP_NAMESPACE_USE

    void XmlErrorHandler::warning( const SAXParseException& toCatch )
    {
    }
    void XmlErrorHandler::error( const SAXParseException& toCatch )
    {
    }
    void XmlErrorHandler::fatalError( const SAXParseException& toCatch )
    {
    }
    void XmlErrorHandler::resetErrors( )
    {
    }
}

