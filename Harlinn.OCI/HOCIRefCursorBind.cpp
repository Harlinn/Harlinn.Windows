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
    RefCursorBind::~RefCursorBind( )
    {
        if ( !cursorStatement_ && boundStatementhandle_ )
        {
            auto& error = Error( );
            auto errorHandle = (OCIError*)error.Handle( );
            OCIStmtRelease( (OCIStmt*)boundStatementhandle_, errorHandle, nullptr, 0, OCI_DEFAULT );
        }
    }

    void RefCursorBind::Bind( UInt32 positon, UInt32 iters )
    {
        
        auto& environment = Environment( );
        auto environmentHandle = environment.Handle( );
        OCIStmt* tmp = nullptr;
        auto rc = OCIHandleAlloc( environmentHandle, (void**)( &tmp ), OCI_HTYPE_STMT, 0, NULL );
        if ( rc < OCI_SUCCESS )
        {
            ThrowOracleExceptionOnError( environmentHandle, rc );
        }
        boundStatementhandle_ = tmp;
        BindByPos( positon, OCI::OraType::RSET, &boundStatementhandle_, sizeof( boundStatementhandle_ ), &indicator_ );
    }
    void RefCursorBind::Bind( const WideString& name, UInt32 iters )
    {
        BindByName( name, OCI::OraType::RSET, &boundStatementhandle_, sizeof( boundStatementhandle_ ), &indicator_ );
    }

    const OCI::Statement& RefCursorBind::CursorStatement( )
    {
        if ( !cursorStatement_ && boundStatementhandle_ )
        {
            auto& statement = Statement( );
            if ( statement )
            {
                auto& serviceContext = statement.ServiceContext( );
                if ( serviceContext )
                {
                    cursorStatement_ = OCI::Statement( serviceContext, boundStatementhandle_, true );
                }
            }
        }
        return cursorStatement_;
    }
}