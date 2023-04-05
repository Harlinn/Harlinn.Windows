#include "pch.h"
#include <HOCIInternal.h>

namespace Harlinn::OCI
{

    std::vector<std::unique_ptr<OCI::ColumnDescriptor>> TableViewBaseDescriptor::Columns( ) const
    {
        std::vector<std::unique_ptr<OCI::ColumnDescriptor>> result;
        auto& serviceContext = ServiceContext( );
        auto& error = Error( );
        auto errorHandle = (OCIError*)error.Handle( );

        auto numberOfColumns = NumberOfColumns( );
        OCIParam* columnList = (OCIParam*)GetPointerAttribute( OCI::Attribute::LIST_COLUMNS );
        for ( UInt16 i = 0; i < numberOfColumns; i++ )
        {
            OCIParam* column = nullptr;
            auto rc = OCIParamGet( (void*)columnList, OCI_DTYPE_PARAM, errorHandle, (void**)&column, (ub4)i + 1 );
            if ( rc < OCI_SUCCESS )
            {
                ThrowOracleExceptionOnError( errorHandle, rc );
            }
            std::unique_ptr<OCI::ColumnDescriptor> columnDescriptor( static_cast<OCI::ColumnDescriptor*>( OCI::ParameterDescriptor::CreateParameter( serviceContext, column ).release() ) );
            result.emplace_back( std::move( columnDescriptor ) );
        }
        return result;
    }

}