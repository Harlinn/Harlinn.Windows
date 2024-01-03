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
