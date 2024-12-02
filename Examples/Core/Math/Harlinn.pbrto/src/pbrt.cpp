// pbrt is Copyright(c) 1998-2020 Matt Pharr, Wenzel Jakob, and Greg Humphreys.
// The pbrt source code is licensed under the Apache License, Version 2.0.
// SPDX: Apache-2.0
#include "pch.h"


#include <pbrto/pbrt.h>

#ifdef PBRT_BUILD_GPU_RENDERER
#include <pbrto/gpu/memory.h>
#include <pbrto/gpu/util.h>
#endif  // PBRT_BUILD_GPU_RENDERER
#include <pbrto/options.h>
#include <pbrto/shapes.h>
#include <pbrto/util/check.h>
#include <pbrto/util/color.h>
#include <pbrto/util/colorspace.h>
#include <pbrto/util/display.h>
#include <pbrto/util/error.h>
#include <pbrto/util/gui.h>
#include <pbrto/util/memory.h>
#include <pbrto/util/parallel.h>
#include <pbrto/util/print.h>
#include <pbrto/util/spectrum.h>
#include <pbrto/util/stats.h>

#include <ImfThreading.h>

#include <stdlib.h>

#ifdef PBRT_IS_WINDOWS
#include <Windows.h>
#endif  // PBRT_IS_WINDOWS

namespace pbrt {

#ifdef PBRT_IS_WINDOWS
static LONG WINAPI handleExceptions(PEXCEPTION_POINTERS info) {
    switch (info->ExceptionRecord->ExceptionCode) {
    case EXCEPTION_ACCESS_VIOLATION:
        LOG_ERROR("Access violation--terminating execution");
        break;
    case EXCEPTION_ARRAY_BOUNDS_EXCEEDED:
        LOG_ERROR("Array bounds violation--terminating execution");
        break;
    case EXCEPTION_DATATYPE_MISALIGNMENT:
        LOG_ERROR("Accessed misaligned data--terminating execution");
        break;
    case EXCEPTION_STACK_OVERFLOW:
        LOG_ERROR("Stack overflow--terminating execution");
        break;
    default:
        LOG_ERROR("Program generated exception %d--terminating execution",
                  int(info->ExceptionRecord->ExceptionCode));
    }
    return EXCEPTION_EXECUTE_HANDLER;
}
#endif  // PBRT_IS_WINDOWS

// API Function Definitions
PBRTO_EXPORT void InitPBRT(const PBRTOptions &opt) {
    Options = new PBRTOptions(opt);
    // API Initialization

    Imf::setGlobalThreadCount(opt.nThreads ? opt.nThreads : AvailableCores());

#if defined(PBRT_IS_WINDOWS)
    SetUnhandledExceptionFilter(handleExceptions);
#if defined(PBRT_BUILD_GPU_RENDERER)
    if (Options->useGPU && Options->gpuDevice && !getenv("CUDA_VISIBLE_DEVICES")) {
        // Limit CUDA to considering only a single GPU on Windows.  pbrt
        // only uses a single GPU anyway, and if there are multiple GPUs
        // plugged in with different architectures, pbrt's use of unified
        // memory causes a performance hit.  We set this early, before CUDA
        // gets going...
        std::string env = StringPrintf("CUDA_VISIBLE_DEVICES=%d", *Options->gpuDevice);
        _putenv(env.c_str());
        // Now CUDA should only see a single device, so tell it that zero
        // is the one to use.
        *Options->gpuDevice = 0;
    }
#endif  // PBRT_BUILD_GPU_RENDERER
#endif  // PBRT_IS_WINDOWS

    if (Options->quiet)
        SuppressErrorMessages();

    InitLogging(opt.logLevel, opt.logFile, opt.logUtilization, Options->useGPU);

    // General \pbrt Initialization
    int nThreads = Options->nThreads != 0 ? Options->nThreads : AvailableCores();
    ParallelInit(nThreads);  // Threads must be launched before the
                             // profiler is initialized.

    if (Options->useGPU) {
#ifdef PBRT_BUILD_GPU_RENDERER
        GPUInit();

        CopyOptionsToGPU();

        // Leak this so memory it allocates isn't freed
        pstd::pmr::monotonic_buffer_resource *bufferResource =
            new pstd::pmr::monotonic_buffer_resource(
                1024 * 1024, &CUDATrackedMemoryResource::singleton);
        Allocator alloc(bufferResource);
        ColorEncoding::Init(alloc);
        Spectra::Init(alloc);
        RGBToSpectrumTable::Init(alloc);

        RGBColorSpace::Init(alloc);
        Triangle::Init(alloc);
        BilinearPatch::Init(alloc);
#else
        LOG_FATAL("Options::useGPU set with non-GPU build");
#endif
    } else {
        ColorEncoding::Init(Allocator{});
        // Before RGBColorSpace::Init!
        Spectra::Init(Allocator{});
        RGBToSpectrumTable::Init(Allocator{});

        RGBColorSpace::Init(Allocator{});
        Triangle::Init({});
        BilinearPatch::Init({});
    }

    InitBufferCaches();

    if (Options->interactive) {
        GUI::Initialize();
    }

    if (!Options->displayServer.empty())
        ConnectToDisplayServer(Options->displayServer);
}

PBRTO_EXPORT void CleanupPBRT() {
    ForEachThread(ReportThreadStats);

    if (Options->recordPixelStatistics)
        StatsWritePixelImages();

    if (Options->printStatistics) {
        PrintStats(stdout);
        ClearStats();
    }
    if (PrintCheckRare(stdout))
        ErrorExit("CHECK_RARE failures");

    if (!Options->displayServer.empty())
        DisconnectFromDisplayServer();

    // API Cleanup
    ParallelCleanup();

    ShutdownLogging();

    Options = nullptr;
}

}  // namespace pbrt
