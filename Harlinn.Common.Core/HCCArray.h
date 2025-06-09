#pragma once
#ifndef __HCCARRAY_H__
#define __HCCARRAY_H__
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

#include <HCCDef.h>

namespace Harlinn::Common::Core
{
    /// <summary>
    /// Concatenation of arrays
    /// </summary>
    /// <typeparam name="T">
    /// The element type
    /// </typeparam>
    /// <typeparam name="N1">
    /// The size of the lhs array
    /// </typeparam>
    /// <typeparam name="N2">
    /// The size of the rhs array
    /// </typeparam>
    /// <param name="lhs">
    /// The first array.
    /// </param>
    /// <param name="rhs">
    /// The second array.
    /// </param>
    /// <returns>
    /// An array containing the data from the first array and second array.
    /// The data from the second array is appended to the data from the first array.
    /// </returns>
    template<typename T, size_t N1, size_t N2>
    inline constexpr std::array<T, N1 + N2> operator + ( const std::array<T, N1>& lhs, const std::array<T, N2>& rhs ) noexcept
    {
        std::array<T, N1 + N2> result;
        auto newEnd = std::copy( lhs.begin( ), lhs.end( ), result.begin( ) );
        std::copy( rhs.begin( ), rhs.end( ), newEnd );
        return result;
    }
}

#endif
