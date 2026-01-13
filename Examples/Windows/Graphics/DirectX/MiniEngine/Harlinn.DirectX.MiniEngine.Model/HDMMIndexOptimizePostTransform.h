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
//
// Copyright (c) Microsoft. All rights reserved.
// This code is licensed under the MIT License (MIT).
// THIS CODE IS PROVIDED *AS IS* WITHOUT WARRANTY OF
// ANY KIND, EITHER EXPRESS OR IMPLIED, INCLUDING ANY
// IMPLIED WARRANTIES OF FITNESS FOR A PARTICULAR
// PURPOSE, MERCHANTABILITY, OR NON-INFRINGEMENT.
//
// Developed by Minigraph
//
// Author(s):  Alex Nankervis
//             James Stanard
//

#pragma once

#include "HDMMDef.h"

namespace Harlinn::Windows::DirectX::MiniEngine
{

    //-----------------------------------------------------------------------------
    //  OptimizeFaces
    //-----------------------------------------------------------------------------
    //  Parameters:
    //      indexList
    //          input index list
    //      indexCount
    //          the number of indices in the list
    //      newIndexList
    //          a pointer to a preallocated buffer the same size as indexList to
    //          hold the optimized index list
    //      lruCacheSize
    //          the size of the simulated post-transform cache (max:64)
    //-----------------------------------------------------------------------------
    template <typename SrcIndexType, typename DstIndexType>
    HDMM_EXPORT void OptimizeFaces( const SrcIndexType* indexList, size_t indexCount, DstIndexType* newIndexList, size_t lruCacheSize );

    template HDMM_TEMPLATE_EXPORT_DECL void OptimizeFaces<uint16_t, uint16_t>( const uint16_t* indexList, size_t indexCount, uint16_t* newIndexList, size_t lruCacheSize );
    template HDMM_TEMPLATE_EXPORT_DECL void OptimizeFaces<uint32_t, uint16_t>( const uint32_t* indexList, size_t indexCount, uint16_t* newIndexList, size_t lruCacheSize );
    template HDMM_TEMPLATE_EXPORT_DECL void OptimizeFaces<uint32_t, uint32_t>( const uint32_t* indexList, size_t indexCount, uint32_t* newIndexList, size_t lruCacheSize );

}