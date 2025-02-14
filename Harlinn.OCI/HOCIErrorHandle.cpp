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
    Int32 ErrorHandle::CheckResult( void* errorHandle, OCI::HandleType handleType, Int32 rc ) const
    {
        return ThrowOracleExceptionOnError( Handle( ), rc, OCI::HandleType::Error );
    }

    Int32 ErrorHandle::CheckResult( Int32 rc ) const
    {
        return CheckResult( Handle( ), OCI::HandleType::Error, rc );
    }

    UInt32 ErrorHandle::DMLRowOffset( ) const
    {
        auto result = GetUInt32Attribute( Attribute::DML_ROW_OFFSET );
        return result;
    }
}