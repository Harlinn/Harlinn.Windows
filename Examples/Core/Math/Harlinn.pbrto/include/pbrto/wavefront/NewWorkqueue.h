#pragma once
#ifndef PBRTO_WAVEFRONT_NEWWORKQUEUE_H_
#define PBRTO_WAVEFRONT_NEWWORKQUEUE_H_

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


// pbrt is Copyright(c) 1998-2020 Matt Pharr, Wenzel Jakob, and Greg Humphreys.
// The pbrt source code is licensed under the Apache License, Version 2.0.
// SPDX: Apache-2.0

#include <pbrto/NewPbrt.h>

#include <pbrto/NewOptions.h>
#ifdef PBRT_BUILD_GPU_RENDERER
#include <pbrto/gpu/NewUtil.h>
#endif  // PBRT_BUILD_GPU_RENDERER
#include <pbrto/util/NewParallel.h>
#include <pbrto/util/NewPStd.h>

#include <atomic>
#include <utility>

#ifdef __CUDACC__

#ifdef PBRT_IS_WINDOWS
#if (__CUDA_ARCH__ < 700)
#define PBRT_USE_LEGACY_CUDA_ATOMICS
#endif
#else
#if (__CUDA_ARCH__ < 600)
#define PBRT_USE_LEGACY_CUDA_ATOMICS
#endif
#endif  // PBRT_IS_WINDOWS

#ifndef PBRT_USE_LEGACY_CUDA_ATOMICS
#include <cuda/atomic>
#endif

#endif  // __CUDACC__

namespace pbrto
{

    // WorkQueue Definition
    template <typename WorkItem>
    class WorkQueue : public SOA<WorkItem>
    {
    public:
        // WorkQueue Public Methods
        WorkQueue( ) = default;
        WorkQueue( int n, Allocator alloc ) : SOA<WorkItem>( n, alloc ) {}
        WorkQueue& operator=( const WorkQueue& w )
        {
            SOA<WorkItem>::operator=( w );
#if defined(PBRT_IS_GPU_CODE) && defined(PBRT_USE_LEGACY_CUDA_ATOMICS)
            size = w.size;
#else
            size.store( w.size.load( ) );
#endif
            return *this;
        }

        PBRT_CPU_GPU
            int Size( ) const
        {
#ifdef PBRT_IS_GPU_CODE
#ifdef PBRT_USE_LEGACY_CUDA_ATOMICS
            return size;
#else
            return size.load( cuda::std::memory_order_relaxed );
#endif
#else
            return size.load( std::memory_order_relaxed );
#endif
        }
        PBRT_CPU_GPU
            void Reset( )
        {
#ifdef PBRT_IS_GPU_CODE
#ifdef PBRT_USE_LEGACY_CUDA_ATOMICS
            size = 0;
#else
            size.store( 0, cuda::std::memory_order_relaxed );
#endif
#else
            size.store( 0, std::memory_order_relaxed );
#endif
        }

        PBRT_CPU_GPU
            int Push( WorkItem w )
        {
            int index = AllocateEntry( );
            ( *this )[ index ] = w;
            return index;
        }

    protected:
        // WorkQueue Protected Methods
        PBRT_CPU_GPU
            int AllocateEntry( )
        {
#ifdef PBRT_IS_GPU_CODE
#ifdef PBRT_USE_LEGACY_CUDA_ATOMICS
            return atomicAdd( &size, 1 );
#else
            return size.fetch_add( 1, cuda::std::memory_order_relaxed );
#endif
#else
            return size.fetch_add( 1, std::memory_order_relaxed );
#endif
        }

    private:
        // WorkQueue Private Members
#ifdef PBRT_IS_GPU_CODE
#ifdef PBRT_USE_LEGACY_CUDA_ATOMICS
        int size = 0;
#else
        cuda::atomic<int, cuda::thread_scope_device> size{ 0 };
#endif
#else
        std::atomic<int> size{ 0 };
#endif  // PBRT_IS_GPU_CODE
    };

    // WorkQueue Inline Functions
    template <typename F, typename WorkItem>
    void ForAllQueued( const char* desc, const WorkQueue<WorkItem>* q, int maxQueued,
        F&& func )
    {
        if ( Options->useGPU )
        {
            // Launch GPU threads to process _q_ using _func_
#ifdef PBRT_BUILD_GPU_RENDERER
            GPUParallelFor( desc, maxQueued, [ = ] PBRT_GPU( int index ) mutable
            {
                if ( index >= q->Size( ) )
                    return;
                func( ( *q )[ index ] );
            } );
#else
            NLOG_FATAL( "Options->useGPU was set without PBRT_BUILD_GPU_RENDERER enabled" );
#endif

        }
        else
        {
            // Process _q_ using _func_ with CPU threads
            ParallelFor( 0, q->Size( ), [ & ]( int index ) { func( ( *q )[ index ] ); } );
        }
    }

    // MultiWorkQueue Definition
    template <typename T>
    class MultiWorkQueue;

    template <typename... Ts>
    class MultiWorkQueue<TypePack<Ts...>>
    {
    public:
        // MultiWorkQueue Public Methods
        template <typename T>
        PBRT_CPU_GPU WorkQueue<T>* Get( )
        {
            return &pstdo::get<WorkQueue<T>>( queues );
        }

        MultiWorkQueue( int n, Allocator alloc, pstdo::span<const bool> haveType )
        {
            int index = 0;
            ( ( *Get<Ts>( ) = WorkQueue<Ts>( haveType[ index++ ] ? n : 1, alloc ) ), ... );
        }

        template <typename T>
        PBRT_CPU_GPU int Size( ) const
        {
            return Get<T>( )->Size( );
        }
        template <typename T>
        PBRT_CPU_GPU int Push( const T& value )
        {
            return Get<T>( )->Push( value );
        }

        PBRT_CPU_GPU
            void Reset( ) { ( Get<Ts>( )->Reset( ), ... ); }

    private:
        // MultiWorkQueue Private Members
        pstdo::tuple<WorkQueue<Ts>...> queues;
    };

}

#endif
