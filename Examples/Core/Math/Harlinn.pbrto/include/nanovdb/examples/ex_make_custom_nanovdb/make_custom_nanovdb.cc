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
// Copyright Contributors to the OpenVDB Project
// SPDX-License-Identifier: MPL-2.0

#include <nanovdb/util/GridBuilder.h>

#include <iostream>

/// @brief Creates a NanoVDB grids with custom values and access them.
///
/// @note This example only depends on NanoVDB.
int main()
{
    try {
        nanovdb::GridBuilder<float> builder(0.0f);
        auto acc = builder.getAccessor();
        acc.setValue(nanovdb::Coord(1, 2, 3), 1.0f);

        printf("GridBuilder: (%i,%i,%i)=%4.2f\t", 1, 2, 3, acc.getValue(nanovdb::Coord(1, 2, 3)));
        printf("GridBuilder: (%i,%i,%i)=%4.2f\n", 1, 2,-3, acc.getValue(nanovdb::Coord(1, 2,-3)));

        auto handle = builder.getHandle<>();
        auto* dstGrid = handle.grid<float>(); // Get a (raw) pointer to the NanoVDB grid form the GridManager.
        if (!dstGrid)
            throw std::runtime_error("GridHandle does not contain a grid with value type float");

        printf("NanoVDB cpu: (%i,%i,%i)=%4.2f\t", 1, 2, 3, dstGrid->tree().getValue(nanovdb::Coord(1, 2, 3)));
        printf("NanoVDB cpu: (%i,%i,%i)=%4.2f\n", 1, 2,-3, dstGrid->tree().getValue(nanovdb::Coord(1, 2,-3)));
    }
    catch (const std::exception& e) {
        std::cerr << "An exception occurred: \"" << e.what() << "\"" << std::endl;
    }
    return 0;
}