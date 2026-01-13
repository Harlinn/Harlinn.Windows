/*
    Copyright 2024-2026 Espen Harlinn
 
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
#pragma once
#ifndef TENSORUTIL_H_
#define TENSORUTIL_H_

//-----------------------------------------------------------------------------
//
//  Copyright (c) Microsoft Corporation. All rights reserved.
//
//-----------------------------------------------------------------------------


#include "TensorExtents.h"

namespace TensorUtil
{
    template <size_t N>
    UInt32 GetElementCount( TensorExtents<N> sizes )
    {
        UInt32 elementCount = 1;
        for ( size_t i = 0; i < N; ++i )
        {
            elementCount *= sizes[ i ];
        }
        return elementCount;
    }

    template <size_t N>
    TensorExtents<N> GetPackedStrides( TensorExtents<N> sizes )
    {
        TensorExtents<N> strides;

        strides[ N - 1 ] = 1;
        for ( ptrdiff_t i = static_cast< ptrdiff_t >( N ) - 2; i >= 0; --i )
        {
            strides[ i ] = strides[ i + 1 ] * sizes[ i + 1 ];
        }
        return strides;
    }

    template <size_t N>
    UInt32 GetElementOffset( TensorExtents<N> indices, TensorExtents<N> strides )
    {
        UInt32 elementOffset = 0;
        for ( size_t i = 0; i < N; ++i )
        {
            elementOffset += indices[ i ] * strides[ i ];
        }
        return elementOffset;
    }

    template <size_t N>
    TensorExtents<N> GetElementIndices( UInt32 elementIndex, TensorExtents<N> sizes )
    {
        TensorExtents<N> indices;

        for ( ptrdiff_t i = static_cast< ptrdiff_t >( N ) - 1; i >= 0; --i )
        {
            UInt32 size = sizes[ i ];
            indices[ i ] = elementIndex % size;
            elementIndex /= size;
        }

        // The element should have been reduced to zero by all dimensions by now.
        // If not, then the passed-in index is out of bounds.
        assert( elementIndex == 0 );

        return indices;
    }
}

#endif
