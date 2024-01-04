#pragma once
#ifndef HARLINN_MEDIA_GLIB_HWMGERROR_H_
#define HARLINN_MEDIA_GLIB_HWMGERROR_H_

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

#include "HWMgquark.h"

namespace Harlinn::Media::GLib
{
    struct Error
    {
        Quark domain;
        Int32 code;
        char* message;
    };

    using ErrorInitFunc = void ( * ) ( Error* error );
    using ErrorCopyFunc = void ( * ) ( const Error* sourceError, Error* destinationError );
    using ErrorClearFunc = void ( * ) ( Error* error );

    HWM_EXPORT Quark ErrorDomainRegisterStatic( const char* errorTypeName, size_t errorTypePrivateSize, ErrorInitFunc errorTypeInit, ErrorCopyFunc errorTypeCopy, ErrorClearFunc errorTypeClear );

    HWM_EXPORT Quark ErrorDomainRegister( const char* errorTypeName, size_t errorTypePrivateSize, ErrorInitFunc errorTypeInit, ErrorCopyFunc errorTypeCopy, ErrorClearFunc errorTypeClear );
    
    HWM_EXPORT Error* ErrorNew( Quark domain, Int32 code, const char* format, ... );

    HWM_EXPORT Error* ErrorNewLiteral( Quark domain, Int32 code, const char* message );
    
    HWM_EXPORT Error* ErrorNewVaList( Quark domain, Int32 code, const char* format, va_list args );

    HWM_EXPORT void ErrorFree( Error* error );
    
    HWM_EXPORT Error* ErrorCopy( const Error* error );

    HWM_EXPORT Bool32 ErrorMatches( const Error* error, Quark domain, Int32 code );

    
    HWM_EXPORT void SetError( Error** err, Quark domain, Int32 code, const char* format, ... );

    HWM_EXPORT void SetErrorLiteral( Error** err, Quark domain, Int32 code, const char* message );

    HWM_EXPORT void PropagateError( Error** dest, Error* src );
    
    HWM_EXPORT void ClearError( Error** err );

    HWM_EXPORT void PrefixError( Error** err, const char* format, ... );

    HWM_EXPORT void PrefixErrorLiteral( Error** err, const char* prefix );

    
    HWM_EXPORT void PropagatePrefixedError( Error** dest, Error* src, const char* format, ... );


}



#endif
