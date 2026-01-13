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
#include <nanovdb/util/IO.h> // this is required to read (and write) NanoVDB files on the host

/// @brief Read a NanoVDB grid from a file and print out multiple values.
///
/// @note Note This example does NOT depend on OpenVDB (nor CUDA), only NanoVDB.
int main()
{
    try {
        auto handle = nanovdb::io::readGrid("data/sphere.nvdb"); // reads first grid from file

        auto* grid = handle.grid<float>(); // get a (raw) pointer to a NanoVDB grid of value type float

        if (!grid)
            throw std::runtime_error("File did not contain a grid with value type float");

        auto acc = grid->getAccessor(); // create an accessor for fast access to multiple values
        for (int i = 97; i < 104; ++i) {
            printf("(%3i,0,0) NanoVDB cpu: % -4.2f\n", i, acc.getValue(nanovdb::Coord(i, 0, 0)));
        }
    }
    catch (const std::exception& e) {
        std::cerr << "An exception occurred: \"" << e.what() << "\"" << std::endl;
    }
    return 0;
}