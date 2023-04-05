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
            std::wstring msg = Format( L"%s: %s", sqlState, message );
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
            std::wstring msg = Format( L"%s: %s", sqlState, message );
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