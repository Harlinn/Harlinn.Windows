#pragma once
#ifndef PBRTO_UTIL_NEWSOBOLMATRICES_H_
#define PBRTO_UTIL_NEWSOBOLMATRICES_H_

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


// pbrt is Copyright(c) 1998-2020 Matt Pharr, Wenzel Jakob, and Greg Humphreys.
// The pbrt source code is licensed under the Apache License, Version 2.0.
// SPDX: Apache-2.0

#include <pbrto/NewPbrt.h>

#include <cstdint>

namespace pbrto
{

    // Sobol Matrix Declarations
    static constexpr int NSobolDimensions = 1024;
    static constexpr int SobolMatrixSize = 52;
    extern PBRT_CONST uint32_t SobolMatrices32[ NSobolDimensions * SobolMatrixSize ];

    extern PBRT_CONST uint64_t VdCSobolMatrices[ ][ SobolMatrixSize ];
    extern PBRT_CONST uint64_t VdCSobolMatricesInv[ ][ SobolMatrixSize ];

}

#endif
