#include "pch.h"

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


// pbrt is Copyright(c) 1998-2020 Matt Pharr, Wenzel Jakob, and Greg Humphreys.
// The pbrt source code is licensed under the Apache License, Version 2.0.
// SPDX: Apache-2.0

#include <pbrto/util/NewPrint.h>

#include <pbrto/util/NewCheck.h>

#include <double-conversion/double-conversion.h>

namespace pbrto
{

    namespace detail
    {

        PBRTO_EXPORT
            std::string FloatToString( float v )
        {
            double_conversion::DoubleToStringConverter doubleConverter(
                double_conversion::DoubleToStringConverter::NO_FLAGS, "Inf", "NaN", 'e',
                -6 /* decimal_in_shortest_low */, 9 /* decimal_in_shortest_high */,
                5 /* max_leading_padding_zeroes_in_precision_mode */,
                5 /*  max_trailing_padding_zeroes_in_precision_mode */ );
            char buf[ 64 ];
            double_conversion::StringBuilder result( buf, PBRT_ARRAYSIZE( buf ) );
            doubleConverter.ToShortestSingle( v, &result );
            int length = result.position( );
            return std::string( buf, length );
        }

        PBRTO_EXPORT
            std::string DoubleToString( double v )
        {
            double_conversion::DoubleToStringConverter doubleConverter(
                double_conversion::DoubleToStringConverter::NO_FLAGS, "Inf", "NaN", 'e',
                -6 /* decimal_in_shortest_low */, 9 /* decimal_in_shortest_high */,
                5 /* max_leading_padding_zeroes_in_precision_mode */,
                5 /*  max_trailing_padding_zeroes_in_precision_mode */ );
            char buf[ 64 ];
            double_conversion::StringBuilder result( buf, PBRT_ARRAYSIZE( buf ) );
            doubleConverter.ToShortest( v, &result );
            int length = result.position( );
            return std::string( buf, length );
        }

        PBRTO_EXPORT
            void stringPrintfRecursive( std::string* s, const char* fmt )
        {
            const char* c = fmt;
            // No args left; make sure there aren't any extra formatting
            // specifiers.
            while ( *c )
            {
                if ( *c == '%' )
                {
                    if ( c[ 1 ] != '%' )
                        NLOG_FATAL( "Not enough optional values passed to Printf." );
                    ++c;
                }
                *s += *c++;
            }
        }

        // 1. Copy from fmt to *s, up to the next formatting directive.
        // 2. Advance fmt past the next formatting directive and return the
        //    formatting directive as a string.
        PBRTO_EXPORT
            std::string copyToFormatString( const char** fmt_ptr, std::string* s )
        {
            const char*& fmt = *fmt_ptr;
            while ( *fmt )
            {
                if ( *fmt != '%' )
                {
                    *s += *fmt;
                    ++fmt;
                }
                else if ( fmt[ 1 ] == '%' )
                {
                    // "%%"; let it pass through
                    *s += '%';
                    *s += '%';
                    fmt += 2;
                }
                else
                    // fmt is at the start of a formatting directive.
                    break;
            }

            std::string nextFmt;
            while ( *fmt )
            {
                char c = *fmt;
                nextFmt += c;
                ++fmt;
                // Is it a conversion specifier?
                if ( c == 'd' || c == 'i' || c == 'o' || c == 'u' || c == 'x' || c == 'e' ||
                    c == 'E' || c == 'f' || c == 'F' || c == 'g' || c == 'G' || c == 'a' ||
                    c == 'A' || c == 'c' || c == 'C' || c == 's' || c == 'S' || c == 'p' )
                    break;
            }

            return nextFmt;
        }

    }  // namespace detail

}