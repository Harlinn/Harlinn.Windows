/*
   Copyright 2024-2025 Espen Harlinn

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
    void DataReader::InitializeDefines( )
    {
        auto& serviceContext = statement_->ServiceContext( );
        auto& error = Base::Error( );
        auto serviceContextHandle = (OCISvcCtx*)serviceContext.Handle( );
        auto statementHandle = (OCIStmt*)statement_->Handle( );
        auto errorHandle = (OCIError*)error.Handle( );

        auto rc = OCIStmtExecute( serviceContextHandle, statementHandle, errorHandle, (ub4)1, (ub4)0, (const OCISnapshot*)0, (OCISnapshot*)0, OCI_DESCRIBE_ONLY );
        error.CheckResult( rc );

        auto descriptorCount = statement_->DescriptorCount( );

        defines_.reserve( descriptorCount );
        for ( UInt32 i = 0; i < descriptorCount; i++ )
        {
            auto define = statement_->Define( i + 1 );
            defines_.emplace_back( std::move( define ) );
        }
    }


}