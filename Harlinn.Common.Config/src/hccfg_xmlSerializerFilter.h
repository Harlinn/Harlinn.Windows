#pragma once
#ifndef HARLINN_COMMON_CONFIG_HCCFG_XMLSERIALIZERFILTER_H_
#define HARLINN_COMMON_CONFIG_HCCFG_XMLSERIALIZERFILTER_H_

#include <xercesc/dom/DOMLSSerializerFilter.hpp>

namespace Harlinn::Common::Config
{
    XERCES_CPP_NAMESPACE_USE

    class XmlSerializerFilter : public DOMLSSerializerFilter
    {
        ShowType whatToShow_;
    public:

        XmlSerializerFilter( ShowType whatToShow = DOMNodeFilter::SHOW_ALL );
        ~XmlSerializerFilter( ) {};

        virtual FilterAction acceptNode( const DOMNode* ) const override;
        virtual ShowType getWhatToShow( ) const  override { return whatToShow_; };

    private:
        // unimplemented copy ctor and assignement operator
        XmlSerializerFilter( const XmlSerializerFilter& ) = delete;
        XmlSerializerFilter& operator = ( const XmlSerializerFilter& ) = delete;

        
    };

}


#endif // HARLINN_COMMON_CONFIG_HCCFG_XMLSERIALIZERFILTER_H_
