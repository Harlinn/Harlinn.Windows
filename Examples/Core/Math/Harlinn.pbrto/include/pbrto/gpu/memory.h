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

#ifndef PBRT_GPU_MEMORY_H
#define PBRT_GPU_MEMORY_H

#include <pbrto/pbrt.h>

#include <pbrto/util/check.h>
#include <pbrto/util/math.h>
#include <pbrto/util/pstd.h>

#include <atomic>
#include <cstddef>
#include <memory>
#include <mutex>
#include <type_traits>
#include <unordered_map>

namespace pbrt
{

#ifdef PBRT_BUILD_GPU_RENDERER

    class CUDAMemoryResource : public pstd::pmr::memory_resource
    {
        void* do_allocate( size_t size, size_t alignment );
        void do_deallocate( void* p, size_t bytes, size_t alignment );

        bool do_is_equal( const memory_resource& other ) const noexcept
        {
            return this == &other;
        }
    };

    class CUDATrackedMemoryResource : public CUDAMemoryResource
    {
    public:
        void* do_allocate( size_t size, size_t alignment );
        void do_deallocate( void* p, size_t bytes, size_t alignment );

        bool do_is_equal( const memory_resource& other ) const noexcept
        {
            return this == &other;
        }

        void PrefetchToGPU( ) const;
        size_t BytesAllocated( ) const { return bytesAllocated; }

        static CUDATrackedMemoryResource singleton;

    private:
        mutable std::mutex mutex;
        std::atomic<size_t> bytesAllocated{};
        std::unordered_map<void*, size_t> allocations;
    };

#endif

}  // namespace pbrt

#endif  // PBRT_GPU_MEMORY_H
