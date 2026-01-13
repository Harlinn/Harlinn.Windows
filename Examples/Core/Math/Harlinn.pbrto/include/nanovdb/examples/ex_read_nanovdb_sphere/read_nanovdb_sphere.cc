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

#include <nanovdb/util/IO.h>

/// @brief Read a NanoVDB grid form file, check pointer and access a single value
///
/// @note This example does NOT dpend on OpenVDB (or CUDA), only NanoVDB.
int main()
{
    try {
        auto handle = nanovdb::io::readGrid("data/sphere.nvdb"); // read first grid in file

        auto* grid = handle.grid<float>(); // get a (raw) pointer to the first NanoVDB grid of value type float

        if (grid == nullptr)
            throw std::runtime_error("File did not contain a grid with value type float");

        // Access and print out a single value in the NanoVDB grid
        printf("NanoVDB cpu: %4.2f\n", grid->tree().getValue(nanovdb::Coord(99, 0, 0)));
    }
    catch (const std::exception& e) {
        std::cerr << "An exception occurred: \"" << e.what() << "\"" << std::endl;
    }

    return 0;
}