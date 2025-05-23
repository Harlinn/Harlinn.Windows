// pbrt is Copyright(c) 1998-2020 Matt Pharr, Wenzel Jakob, and Greg Humphreys.
// The pbrt source code is licensed under the Apache License, Version 2.0.
// SPDX: Apache-2.0

#ifndef PBRTO_GPU_NEWUTIL_H
#define PBRTO_GPU_NEWUTIL_H

#include <pbrto/NewPbrt.h>

#include <pbrto/util/NewCheck.h>
#include <pbrto/util/NewLog.h>
#include <pbrto/util/NewParallel.h>
#include <pbrto/util/NewProgressReporter.h>

#include <map>
#include <typeindex>
#include <typeinfo>
#include <utility>
#include <vector>

#include <cuda.h>
#include <cuda_runtime_api.h>

#ifdef NVTX
#ifdef UNICODE
#undef UNICODE
#endif
#include <nvtx3/nvToolsExt.h>

#ifdef RGB
#undef RGB
#endif  // RGB
#endif

#define NCUDA_CHECK(EXPR)                                        \
    if (EXPR != cudaSuccess) {                                  \
        cudaError_t error = cudaGetLastError();                 \
        NLOG_FATAL("CUDA error: %s", cudaGetErrorString(error)); \
    } else /* eat semicolon */

#define NCU_CHECK(EXPR)                                              \
    do {                                                            \
        CUresult result = EXPR;                                     \
        if (result != CUDA_SUCCESS) {                               \
            const char *str;                                        \
            NCHECK_EQ(CUDA_SUCCESS, cuGetErrorString(result, &str)); \
            NLOG_FATAL("CUDA error: %s", str);                       \
        }                                                           \
    } while (false) /* eat semicolon */

namespace pbrto
{

    std::pair<cudaEvent_t, cudaEvent_t> GetProfilerEvents( const char* description );

    template <typename F>
    inline int GetBlockSize( const char* description, F kernel )
    {
        // Note: this isn't reentrant, but that's fine for our purposes...
        static std::map<std::type_index, int> kernelBlockSizes;

        std::type_index index = std::type_index( typeid( F ) );

        auto iter = kernelBlockSizes.find( index );
        if ( iter != kernelBlockSizes.end( ) )
            return iter->second;

        int minGridSize, blockSize;
        NCUDA_CHECK(
            cudaOccupancyMaxPotentialBlockSize( &minGridSize, &blockSize, kernel, 0, 0 ) );
        kernelBlockSizes[ index ] = blockSize;
        NLOG_VERBOSE( "[%s]: block size %d", description, blockSize );

        return blockSize;
    }

#ifdef __NVCC__
    template <typename F>
    __global__ void Kernel( F func, int nItems )
    {
        int tid = blockIdx.x * blockDim.x + threadIdx.x;
        if ( tid >= nItems )
            return;

        func( tid );
    }

    // GPU Launch Function Declarations
    template <typename F>
    void GPUParallelFor( const char* description, int nItems, F func );

    template <typename F>
    void GPUParallelFor( const char* description, int nItems, F func )
    {
#ifdef NVTX
        nvtxRangePush( description );
#endif
        auto kernel = &Kernel<F>;

        int blockSize = GetBlockSize( description, kernel );
        std::pair<cudaEvent_t, cudaEvent_t> events = GetProfilerEvents( description );

#ifdef PBRT_DEBUG_BUILD
        LOG_VERBOSE( "Launching %s", description );
#endif
        cudaEventRecord( events.first );
        int gridSize = ( nItems + blockSize - 1 ) / blockSize;
        kernel << <gridSize, blockSize >> > ( func, nItems );
        cudaEventRecord( events.second );

#ifdef PBRT_DEBUG_BUILD
        CUDA_CHECK( cudaDeviceSynchronize( ) );
        LOG_VERBOSE( "Post-sync %s", description );
#endif
#ifdef NVTX
        nvtxRangePop( );
#endif
    }

#endif  // __NVCC__

    // GPU Synchronization Function Declarations
    PBRTO_EXPORT void GPUWait( );

    PBRTO_EXPORT void ReportKernelStats( );

    PBRTO_EXPORT void GPUInit( );
    PBRTO_EXPORT void GPUThreadInit( );

    PBRTO_EXPORT void GPUMemset( void* ptr, int byte, size_t bytes );

    PBRTO_EXPORT void GPURegisterThread( const char* name );
    PBRTO_EXPORT void GPUNameStream( cudaStream_t stream, const char* name );

}  // namespace pbrt

#endif  // PBRT_GPU_UTIL_H
