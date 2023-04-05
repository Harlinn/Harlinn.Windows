#include "pch.h"
#include <HOCIInternal.h>

namespace Harlinn::OCI::Metadata
{
    TableOrView::ColumnContainer TableOrView::Columns( ) const
    {
        ColumnContainer result;
        auto* serviceContext = ServiceContext( );
        auto qualifiedName = this->QuotedQualifiedName( );
        auto describe = serviceContext->Describe( qualifiedName, this->Kind() == Metadata::Kind::Table? OCI::ParameterType::Table: OCI::ParameterType::View, false );
        auto tableViewBaseDescriptor = describe.Descriptor<TableViewBaseDescriptor>( );
        auto columnDescriptors = tableViewBaseDescriptor->Columns( );
        for ( auto& parameterDescriptor : columnDescriptors )
        {
            auto* columnDescriptor = parameterDescriptor.get( );
            auto column = std::make_unique<Column>( serviceContext, this, columnDescriptor );
            result.emplace_back( std::move( column ) );
        }
        return result;
    }
}
