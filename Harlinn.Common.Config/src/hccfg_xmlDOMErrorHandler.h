#pragma once
#ifndef HARLINN_COMMON_CONFIG_HCCFG_XMLDOMERRORHANDLER_H_
#define HARLINN_COMMON_CONFIG_HCCFG_XMLDOMERRORHANDLER_H_

#include <xercesc/dom/DOMErrorHandler.hpp>

namespace Harlinn::Common::Config
{
    XERCES_CPP_NAMESPACE_USE

    class XmlDOMErrorHandler : public DOMErrorHandler
    {
    public:
        XmlDOMErrorHandler( ) {};
        ~XmlDOMErrorHandler( ) {};

        /** @name The error handler interface */
        bool handleError( const DOMError& domError ) override;
        void resetErrors( ) {};

    private:
        XmlDOMErrorHandler( const DOMErrorHandler& ) = delete;
        void operator=( const DOMErrorHandler& ) = delete;

    };


}

#endif
