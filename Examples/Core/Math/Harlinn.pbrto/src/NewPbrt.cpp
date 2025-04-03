#include "pch.h"

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
#include <pbrto/NewShapes.h>
#include <pbrto/util/NewCheck.h>
#include <pbrto/util/NewColor.h>
#include <pbrto/util/NewColorSpace.h>
#include <pbrto/util/NewDisplay.h>
#include <pbrto/util/NewError.h>
#include <pbrto/util/NewGui.h>
#include <pbrto/util/NewMemory.h>
#include <pbrto/util/NewParallel.h>
#include <pbrto/util/NewSpectrum.h>
#include <pbrto/util/NewStats.h>

#include <ImfThreading.h>

#include <stdlib.h>

#ifdef PBRT_IS_WINDOWS
#include <Windows.h>
#endif  // PBRT_IS_WINDOWS

namespace pbrto
{

#ifdef PBRT_IS_WINDOWS
    static LONG WINAPI handleExceptions( PEXCEPTION_POINTERS info )
    {
        switch ( info->ExceptionRecord->ExceptionCode )
        {
            case EXCEPTION_ACCESS_VIOLATION:
                NLOG_ERROR( "Access violation--terminating execution" );
                break;
            case EXCEPTION_ARRAY_BOUNDS_EXCEEDED:
                NLOG_ERROR( "Array bounds violation--terminating execution" );
                break;
            case EXCEPTION_DATATYPE_MISALIGNMENT:
                NLOG_ERROR( "Accessed misaligned data--terminating execution" );
                break;
            case EXCEPTION_STACK_OVERFLOW:
                NLOG_ERROR( "Stack overflow--terminating execution" );
                break;
            default:
                NLOG_ERROR( "Program generated exception %d--terminating execution",
                    int( info->ExceptionRecord->ExceptionCode ) );
        }
        return EXCEPTION_EXECUTE_HANDLER;
    }
#endif  // PBRT_IS_WINDOWS

    // API Function Definitions
    PBRTO_EXPORT void InitPBRT( const PBRTOptions& opt )
    {
        Options = new PBRTOptions( opt );
        // API Initialization

        Imf::setGlobalThreadCount( opt.nThreads ? opt.nThreads : AvailableCores( ) );

#if defined(PBRT_IS_WINDOWS)
        SetUnhandledExceptionFilter( handleExceptions );
#if defined(PBRT_BUILD_GPU_RENDERER)
        if ( Options->useGPU && Options->gpuDevice && !getenv( "CUDA_VISIBLE_DEVICES" ) )
        {
            // Limit CUDA to considering only a single GPU on Windows.  pbrt
            // only uses a single GPU anyway, and if there are multiple GPUs
            // plugged in with different architectures, pbrt's use of unified
            // memory causes a performance hit.  We set this early, before CUDA
            // gets going...
            std::string env = StringPrintf( "CUDA_VISIBLE_DEVICES=%d", *Options->gpuDevice );
            _putenv( env.c_str( ) );
            // Now CUDA should only see a single device, so tell it that zero
            // is the one to use.
            *Options->gpuDevice = 0;
        }
#endif  // PBRT_BUILD_GPU_RENDERER
#endif  // PBRT_IS_WINDOWS

        if ( Options->quiet )
            SuppressErrorMessages( );

        InitLogging( opt.logLevel, opt.logFile, opt.logUtilization, Options->useGPU );

        // General \pbrt Initialization
        int nThreads = Options->nThreads != 0 ? Options->nThreads : AvailableCores( );
        ParallelInit( nThreads );  // Threads must be launched before the
        // profiler is initialized.

        if ( Options->useGPU )
        {
#ifdef PBRT_BUILD_GPU_RENDERER
            GPUInit( );

            CopyOptionsToGPU( );

            // Leak this so memory it allocates isn't freed
            pstdo::pmr::monotonic_buffer_resource* bufferResource =
                new pstdo::pmr::monotonic_buffer_resource(
                    1024 * 1024, &CUDATrackedMemoryResource::singleton );
            Allocator alloc( bufferResource );
            ColorEncoding::Init( alloc );
            Spectra::Init( alloc );
            RGBToSpectrumTable::Init( alloc );

            RGBColorSpace::Init( alloc );
            Triangle::Init( alloc );
            BilinearPatch::Init( alloc );
#else
            NLOG_FATAL( "Options::useGPU set with non-GPU build" );
#endif
        }
        else
        {
            ColorEncoding::Init( Allocator{} );
            // Before RGBColorSpace::Init!
            Spectra::Init( Allocator{} );
            RGBToSpectrumTable::Init( Allocator{} );

            RGBColorSpace::Init( Allocator{} );
            Triangle::Init( {} );
            BilinearPatch::Init( {} );
        }

        InitBufferCaches( );

        if ( Options->interactive )
        {
            GUI::Initialize( );
        }

        if ( !Options->displayServer.empty( ) )
            ConnectToDisplayServer( Options->displayServer );
    }

    PBRTO_EXPORT void CleanupPBRT( )
    {
        ForEachThread( ReportThreadStats );

        if ( Options->recordPixelStatistics )
            StatsWritePixelImages( );

        if ( Options->printStatistics )
        {
            PrintStats( stdout );
            ClearStats( );
        }
        if ( PrintCheckRare( stdout ) )
            ErrorExit( "CHECK_RARE failures" );

        if ( !Options->displayServer.empty( ) )
            DisconnectFromDisplayServer( );

        // API Cleanup
        ParallelCleanup( );

        ShutdownLogging( );

        Options = nullptr;
    }

}