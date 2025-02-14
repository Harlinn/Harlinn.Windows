#pragma once
#ifndef HARLINN_COMMON_CORE_INTERNAL_MATH_NEARESTINTEGER_H_
#define HARLINN_COMMON_CORE_INTERNAL_MATH_NEARESTINTEGER_H_

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

#include <HCCLib.h>

namespace Harlinn::Common::Core::Math::Internal
{
    inline constexpr float NearestInteger( float x ) 
    { 
        if ( std::is_constant_evaluated( ) )
        {
            if ( x < 0x1p24f && x > -0x1p24f )
            {
                float result = x < 0 ? ( x - 0x1.0p23f ) + 0x1.0p23f : ( x + 0x1.0p23f ) - 0x1.0p23f;
                float diff = x - result;
                if ( diff > 0.5f )
                {
                    return result + 1.0f;
                }
                if ( diff < -0.5f )
                {
                    return result - 1.0f;
                }
                return result;
            }
            return x;
        }
        else
        {
            return __rintf( x );
        }
    }

    inline constexpr double NearestInteger( double x )
    { 
        if ( std::is_constant_evaluated( ) )
        {
            if ( x < 0x1p53 && x > -0x1p53 )
            {
                double result = x < 0 ? ( x - 0x1.0p52 ) + 0x1.0p52 : ( x + 0x1.0p52 ) - 0x1.0p52;
                double diff = x - result;
                if ( diff > 0.5 )
                {
                    return result + 1.0;
                }
                if ( diff < -0.5 )
                {
                    return result - 1.0;
                }
                return result;
            }
            return x;
        }
        else
        {
            return __rint( x );
        }
    }
}


#endif
