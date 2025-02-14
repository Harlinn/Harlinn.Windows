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