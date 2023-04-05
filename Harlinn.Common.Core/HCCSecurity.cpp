#include "pch.h"
#include <HCCSecurity.h>
#include <HCCLogging.h>
#include <HCCException.h>

namespace Harlinn::Common::Core::Security
{

    namespace Internal
    {
        void ThrowOwnershipRequiredException( const wchar_t* message, const wchar_t* function, const wchar_t* file, int lineNumber )
        {
            ExceptionLocation location( function, file, lineNumber );
            Exception exception( location, message );
            throw exception;
        }

        void ThrowInvalidOperationException( const wchar_t* message, const wchar_t* function, const wchar_t* file, int lineNumber )
        {
            ExceptionLocation location( function, file, lineNumber );
            InvalidOperationException exception( location, message );
            throw exception;
        }

    }


    namespace
    {
        /*
        SID* ToSid( const wchar_t* stringSid )
        {
            SID* psid = nullptr;
            auto rc = ConvertStringSidToSidW( stringSid, (PSID*)&psid );
            if ( !rc )
            {
                ThrowLastOSError( );
            }
            return psid;
        }
        */
    }




}