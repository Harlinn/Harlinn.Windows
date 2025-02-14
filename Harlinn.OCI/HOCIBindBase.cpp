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
    void BindBase::BindByPos( UInt32 positon, OraType dataType, void* dataAddress, Int64 dataSize, Int16* indicators, UInt32* actualLengths, UInt16* returnCodes, UInt32 plsqlMaxArrayLength, UInt32* plsqlArrayLength, UInt32 mode )
    {
        void* bindHandle = nullptr;
        auto& statement = Statement( );
        auto& error = statement.Error( );
        auto errorHandle = (OCIError*)error.Handle( );
        auto rc = OCIBindByPos2( (OCIStmt*)statement.Handle( ), (OCIBind**)&bindHandle, errorHandle, static_cast<UInt32>( positon ),
            dataAddress, dataSize, static_cast<UInt16>( dataType ), indicators, actualLengths, returnCodes, plsqlMaxArrayLength, plsqlArrayLength, mode );
        if ( rc < OCI_SUCCESS )
        {
            error.CheckResult( rc );
        }
        InitializeHandle( bindHandle, true );
    }
    void BindBase::BindByName( const WideString& name, OraType dataType, void* dataAddress, Int64 dataSize, Int16* indicators, UInt32* actualLengths, UInt16* returnCodes, UInt32 plsqlMaxArrayLength, UInt32* plsqlArrayLength, UInt32 mode )
    {
        void* bindHandle = nullptr;
        auto& statement = Statement( );
        auto& error = statement.Error( );
        auto errorHandle = (OCIError*)error.Handle( );
        auto rc = OCIBindByName2( (OCIStmt*)statement.Handle( ), (OCIBind**)&bindHandle, errorHandle, (OraText*)name.c_str( ), static_cast<sb4>( name.length( ) * sizeof( wchar_t ) ),
            dataAddress, dataSize, static_cast<UInt16>( dataType ), indicators, actualLengths, returnCodes, plsqlMaxArrayLength, plsqlArrayLength, mode );
        if ( rc < OCI_SUCCESS )
        {
            error.CheckResult( rc );
        }
        InitializeHandle( bindHandle, true );
    }
    void BindBase::Bind( UInt32 positon, UInt32 iters )
    {
        HCC_THROW( NotImplementedException );
    }

    void BindBase::Bind( const WideString& name, UInt32 iters )
    {
        HCC_THROW( NotImplementedException );
    }



}