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
#include <HODBC.h>
#include <HCCException.h>
#include <HCCString.h>

namespace Harlinn::ODBC
{
    namespace Internal
    {
        void ThrowException( SQLRETURN sqlReturn, ODBC::HandleType handleType, SQLHANDLE sqlHandle, const char* function, const char* file, int line )
        {
            ExceptionLocation location( function, file, line );
            SQLWCHAR sqlState[6] = {};
            SQLWCHAR message[2048] = {};
            SQLSMALLINT actualMessageLength = 0;
            SQLINTEGER nativeError = 0;
            GetDiagnosticRecord( handleType, sqlHandle, 1, sqlState, &nativeError, message, 2048, &actualMessageLength );
            WideString msg = Format( L"{}: {}", sqlState, message );
            Data::DbException exc( location, nativeError, msg );
            throw exc;
        }

        void ThrowException( SQLRETURN sqlReturn, ODBC::HandleType handleType, SQLHANDLE sqlHandle )
        {
            SQLWCHAR sqlState[6] = {};
            SQLWCHAR message[2048] = {};
            SQLSMALLINT actualMessageLength = 0;
            SQLINTEGER nativeError = 0;
            GetDiagnosticRecord( handleType, sqlHandle, 1, sqlState, &nativeError, message, 2048, &actualMessageLength );
            WideString msg = Format( L"{}: {}", sqlState, message );
            Data::DbException exc( nativeError, msg );
            throw exc;
        }

        void ThrowExceptionNoDiagnostic( SQLRETURN sqlReturn, ODBC::HandleType handleType, SQLHANDLE sqlHandle, const char* function, const char* file, int line )
        {
            ExceptionLocation location( function, file, line );
            Data::DbException exc( location, sqlReturn, L"Unknown" );
            throw exc;
        }

        void ThrowExceptionNoDiagnostic( SQLRETURN sqlReturn, ODBC::HandleType handleType, SQLHANDLE sqlHandle )
        {
            Data::DbException exc( sqlReturn, L"Unknown" );
            throw exc;
        }

    }
}