/*
   Copyright 2024 Espen Harlinn

   Licensed under the Apache License, Version 2.0 (the "License");
   you may not use this file except in compliance with the License.
   You may obtain a copy of the License at

       http://www.apache.org/licenses/LICENSE-2.0

   Unless required by applicable law or agreed to in writing, software
   distributed under the License is distributed on an "AS IS" BASIS,
   WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
   See the License for the specific language governing permissions and
   limitations under the License.
*/

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