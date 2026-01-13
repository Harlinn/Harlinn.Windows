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

#include <nanovdb/util/IO.h> // this is required to read (and write) NanoVDB files on the host
#include <nanovdb/util/CudaDeviceBuffer.h> // required for CUDA memory management

extern "C" void launch_kernels(const nanovdb::NanoGrid<float>*,
                               const nanovdb::NanoGrid<float>*,
                               cudaStream_t stream);

/// @brief Read a NanoVDB grid from a file and print out multiple values on both the cpu and gpu.
///
/// @note Note This example does NOT depend on OpenVDB, only NanoVDB and CUDA.
int main()
{
    try {
        // returns a GridHandle using CUDA for memory management.
        auto handle = nanovdb::io::readGrid<nanovdb::CudaDeviceBuffer>("data/sphere.nvdb");

        cudaStream_t stream; // Create a CUDA stream to allow for asynchronous copy of pinned CUDA memory.
        cudaStreamCreate(&stream);

        handle.deviceUpload(stream, false); // Copy the NanoVDB grid to the GPU asynchronously

        auto* cpuGrid = handle.grid<float>(); // get a (raw) pointer to a NanoVDB grid of value type float on the CPU
        auto* deviceGrid = handle.deviceGrid<float>(); // get a (raw) pointer to a NanoVDB grid of value type float on the GPU

        if (!deviceGrid || !cpuGrid)
            throw std::runtime_error("GridHandle did not contain a grid with value type float");

        launch_kernels(deviceGrid, cpuGrid, stream); // Call a host method to print a grid values on both the CPU and GPU

        cudaStreamDestroy(stream); // Destroy the CUDA stream
    }
    catch (const std::exception& e) {
        std::cerr << "An exception occurred: \"" << e.what() << "\"" << std::endl;
    }

    return 0;
}