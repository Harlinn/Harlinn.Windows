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
#include "HWMgerror.h"
#include <gst/gst.h>

namespace Harlinn::Media::GLib
{
    HWM_EXPORT Quark ErrorDomainRegisterStatic( const char* errorTypeName, size_t errorTypePrivateSize, ErrorInitFunc errorTypeInit, ErrorCopyFunc errorTypeCopy, ErrorClearFunc errorTypeClear )
    {
        return g_error_domain_register_static( errorTypeName, errorTypePrivateSize, ( GErrorInitFunc )errorTypeInit, ( GErrorCopyFunc )errorTypeCopy, ( GErrorClearFunc )errorTypeClear );
    }

    HWM_EXPORT Quark ErrorDomainRegister( const char* errorTypeName, size_t errorTypePrivateSize, ErrorInitFunc errorTypeInit, ErrorCopyFunc errorTypeCopy, ErrorClearFunc errorTypeClear )
    {
        return g_error_domain_register( errorTypeName, errorTypePrivateSize, ( GErrorInitFunc )errorTypeInit, ( GErrorCopyFunc )errorTypeCopy, ( GErrorClearFunc )errorTypeClear );
    }

    HWM_EXPORT Error* ErrorNew( Quark domain, Int32 code, const char* format, ... )
    {
        va_list args;
        va_start( args, format );
        auto result = g_error_new_valist( domain, code, format, args );
        va_end( args );
        return reinterpret_cast< Error* >( result );
    }

    HWM_EXPORT Error* ErrorNewLiteral( Quark domain, Int32 code, const char* message )
    {
        auto result = g_error_new_literal( domain, code, message );
        return reinterpret_cast< Error* >( result );
    }

    HWM_EXPORT Error* ErrorNewVaList( Quark domain, Int32 code, const char* format, va_list args )
    {
        auto result = g_error_new_valist( domain, code, format, args );
        return reinterpret_cast< Error* >( result );
    }

    HWM_EXPORT void ErrorFree( Error* error )
    {
        g_error_free( reinterpret_cast< GError* >( error ) );
    }

    HWM_EXPORT Error* ErrorCopy( const Error* error )
    {
        auto result = g_error_copy( reinterpret_cast< const GError* >( error ) );
        return reinterpret_cast< Error* >( result );
    }

    HWM_EXPORT Bool32 ErrorMatches( const Error* error, Quark domain, Int32 code )
    {
        return g_error_matches( reinterpret_cast< const GError* >( error ), domain, code );
    }


    HWM_EXPORT void SetError( Error** err, Quark domain, Int32 code, const char* format, ... )
    {
        va_list args;
        va_start( args, format );
        auto count = _vscprintf( format, args );
        if ( count < 512 )
        {
            char buffer[ 512 ];
            vsprintf_s( buffer, format, args );
            g_set_error_literal( reinterpret_cast< GError** >( err ), domain, code, buffer );
        }
        else
        {
            auto buffer = std::make_unique<char[]>( static_cast<size_t>( count + 1) );
            vsprintf_s( buffer.get(), static_cast< size_t >( count + 1 ),format, args );
            g_set_error_literal( reinterpret_cast< GError** >( err ), domain, code, buffer.get( ) );
        }
        va_end( args );
    }

    HWM_EXPORT void SetErrorLiteral( Error** err, Quark domain, Int32 code, const char* message )
    {
        g_set_error_literal( reinterpret_cast< GError** >( err ), domain, code, message );
    }

    HWM_EXPORT void PropagateError( Error** dest, Error* src )
    {
        g_propagate_error( reinterpret_cast< GError** >( dest ), reinterpret_cast< GError* >( src ) );
    }

    HWM_EXPORT void ClearError( Error** err )
    {
        g_clear_error( reinterpret_cast< GError** >( err ) );
    }

    HWM_EXPORT void PrefixError( Error** err, const char* format, ... )
    {
        va_list args;
        va_start( args, format );
        auto count = _vscprintf( format, args );
        if ( count < 512 )
        {
            char buffer[ 512 ];
            vsprintf_s( buffer, format, args );
            g_prefix_error_literal( reinterpret_cast< GError** >( err ), buffer );
        }
        else
        {
            auto buffer = std::make_unique<char[ ]>( static_cast< size_t >( count + 1 ) );
            vsprintf_s( buffer.get( ), static_cast< size_t >( count + 1 ), format, args );
            g_prefix_error_literal( reinterpret_cast< GError** >( err ), buffer.get( ) );
        }
        va_end( args );
    }

    HWM_EXPORT void PrefixErrorLiteral( Error** err, const char* prefix )
    {
        g_prefix_error_literal( reinterpret_cast< GError** >( err ), prefix );
    }


    HWM_EXPORT void PropagatePrefixedError( Error** dest, Error* src, const char* format, ... )
    {
        va_list args;
        va_start( args, format );
        auto count = _vscprintf( format, args );
        if ( count < 512 )
        {
            char buffer[ 512 ];
            vsprintf_s( buffer, format, args );
            g_propagate_prefixed_error( reinterpret_cast< GError** >( dest ), reinterpret_cast< GError* >( src ), buffer );
        }
        else
        {
            auto buffer = std::make_unique<char[ ]>( static_cast< size_t >( count + 1 ) );
            vsprintf_s( buffer.get( ), static_cast< size_t >( count + 1 ), format, args );
            g_propagate_prefixed_error( reinterpret_cast< GError** >( dest ), reinterpret_cast< GError* >( src ), buffer.get( ) );
        }
        va_end( args );
    }
}