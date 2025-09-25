#include "pch.h"
// pbrt is Copyright(c) 1998-2020 Matt Pharr, Wenzel Jakob, and Greg Humphreys.
// The pbrt source code is licensed under the Apache License, Version 2.0.
// SPDX: Apache-2.0

#include <pbrto/gpu/NewUtil.h>

#include <pbrto/NewOptions.h>
#include <pbrto/util/NewCheck.h>
#include <pbrto/util/NewError.h>
#include <pbrto/util/NewLog.h>
#include <pbrto/util/NewPrint.h>

#include <algorithm>
#include <vector>

// Only in util.cpp:
//#include <optix_function_table_definition.h>

#ifdef NVTX
#ifdef PBRT_IS_WINDOWS
#include <windows.h>
#else
#include <sys/syscall.h>
#endif  // PBRT_IS_WINDOWS
#include "nvtx3/nvToolsExt.h"
#include "nvtx3/nvToolsExtCuda.h"
#endif

namespace pbrto {

PBRTO_EXPORT void GPUInit() {
    cudaFree(nullptr);

    int driverVersion;
    NCUDA_CHECK(cudaDriverGetVersion(&driverVersion));
    int runtimeVersion;
    NCUDA_CHECK(cudaRuntimeGetVersion(&runtimeVersion));
    auto versionToString = [](int version) {
        int major = version / 1000;
        int minor = (version - major * 1000) / 10;
        return StringPrintf("%d.%d", major, minor);
    };
    NLOG_VERBOSE("GPU CUDA driver %s, CUDA runtime %s", versionToString(driverVersion),
                versionToString(runtimeVersion));

    int nDevices;
    NCUDA_CHECK(cudaGetDeviceCount(&nDevices));
    std::string devices;
    for (int i = 0; i < nDevices; ++i) {
        cudaDeviceProp deviceProperties;
        NCUDA_CHECK(cudaGetDeviceProperties(&deviceProperties, i));
        NCHECK(deviceProperties.canMapHostMemory);

        int clockRateKHz;
        cudaDeviceGetAttribute(&clockRateKHz, cudaDevAttrClockRate, i);

        std::string deviceString = StringPrintf(
            "CUDA device %d (%s) with %f MiB, %d SMs running at %f MHz "
            "with shader model %d.%d",
            i, deviceProperties.name, deviceProperties.totalGlobalMem / (1024. * 1024.),
            deviceProperties.multiProcessorCount, clockRateKHz /*deviceProperties.clockRate*/ / 1000.,
            deviceProperties.major, deviceProperties.minor);
        NLOG_VERBOSE("%s", deviceString);
        devices += deviceString + "\n";
    }

#ifdef PBRT_IS_WINDOWS
    if (nDevices > 1)
        ErrorExit("Found multiple GPUs.\n"
                  "On Windows, this unfortunately causes a significant slowdown with "
                  "pbrt.\n"
                  "Please select a single GPU and use the --gpu-device command line "
                  "option to specify it.\n"
                  "Found devices:\n%s",
                  devices);
#endif

    int device = Options->gpuDevice ? *Options->gpuDevice : 0;
    NLOG_VERBOSE("Selecting GPU device %d", device);
#ifdef NVTX
    nvtxNameCuDevice(device, "PBRT_GPU");
#endif
    NCUDA_CHECK(cudaSetDevice(device));

    int hasUnifiedAddressing;
    NCUDA_CHECK(cudaDeviceGetAttribute(&hasUnifiedAddressing, cudaDevAttrUnifiedAddressing, device));
    if (!hasUnifiedAddressing)
        NLOG_FATAL("The selected GPU device (%d) does not support unified addressing.", device);

    NCUDA_CHECK(cudaDeviceSetLimit(cudaLimitStackSize, 8192));
    size_t stackSize;
    NCUDA_CHECK(cudaDeviceGetLimit(&stackSize, cudaLimitStackSize));
    NLOG_VERBOSE("Reset stack size to %d", stackSize);

    NCUDA_CHECK(cudaDeviceSetLimit(cudaLimitPrintfFifoSize, 32 * 1024 * 1024));

    NCUDA_CHECK(cudaDeviceSetCacheConfig(cudaFuncCachePreferL1));

#ifdef NVTX
#ifdef PBRT_IS_WINDOWS
    nvtxNameOsThread(GetCurrentThreadId(), "MAIN_THREAD");
#else
    nvtxNameOsThread(syscall(SYS_gettid), "MAIN_THREAD");
#endif
#endif  // NVTX
}

PBRTO_EXPORT void GPUThreadInit() {
    if (!Options->useGPU)
        return;
    int device = Options->gpuDevice ? *Options->gpuDevice : 0;
    NLOG_VERBOSE("Selecting GPU device %d", device);
    NCUDA_CHECK(cudaSetDevice(device));
}

PBRTO_EXPORT void GPURegisterThread(const char *name) {
#ifdef NVTX
#ifdef PBRT_IS_WINDOWS
    nvtxNameOsThread(GetCurrentThreadId(), name);
#else
    nvtxNameOsThread(syscall(SYS_gettid), name);
#endif
#endif
}

PBRTO_EXPORT void GPUNameStream(cudaStream_t stream, const char *name) {
#ifdef NVTX
    nvtxNameCuStream(stream, name);
#endif
}

struct KernelStats {
    KernelStats(const char *description) : description(description) {}

    std::string description;
    int numLaunches = 0;
    float sumMS = 0, minMS = 0, maxMS = 0;
};

// Store pointers so that reallocs don't mess up held KernelStats pointers
// in ProfilerEvent..
static std::vector<KernelStats *> kernelStats;

struct ProfilerEvent {
    ProfilerEvent() {
        NCUDA_CHECK(cudaEventCreate(&start));
        NCUDA_CHECK(cudaEventCreate(&stop));
    }

    void Sync() {
        NCHECK(active);
        NCUDA_CHECK(cudaEventSynchronize(start));
        NCUDA_CHECK(cudaEventSynchronize(stop));

        float ms = 0;
        NCUDA_CHECK(cudaEventElapsedTime(&ms, start, stop));

        ++stats->numLaunches;
        if (stats->numLaunches == 1)
            stats->sumMS = stats->minMS = stats->maxMS = ms;
        else {
            stats->sumMS += ms;
            stats->minMS = std::min(stats->minMS, ms);
            stats->maxMS = std::max(stats->maxMS, ms);
        }

        active = false;
    }

    cudaEvent_t start, stop;
    bool active = false;
    KernelStats *stats = nullptr;
};

// Ring buffer
static std::vector<ProfilerEvent> eventPool;
static size_t eventPoolOffset = 0;

std::pair<cudaEvent_t, cudaEvent_t> GetProfilerEvents(const char *description) {
    if (eventPool.empty())
        eventPool.resize(1024);  // how many? This is probably more than we need...

    if (eventPoolOffset == eventPool.size())
        eventPoolOffset = 0;

    ProfilerEvent &pe = eventPool[eventPoolOffset++];
    if (pe.active)
        pe.Sync();

    pe.active = true;
    pe.stats = nullptr;

    for (size_t i = 0; i < kernelStats.size(); ++i) {
        if (kernelStats[i]->description == description) {
            pe.stats = kernelStats[i];
            break;
        }
    }
    if (!pe.stats) {
        kernelStats.push_back(new KernelStats(description));
        pe.stats = kernelStats.back();
    }

    return {pe.start, pe.stop};
}

PBRTO_EXPORT void GPUWait() {
    NCUDA_CHECK(cudaDeviceSynchronize());
}

PBRTO_EXPORT void GPUMemset(void *ptr, int byte, size_t bytes) {
    NCUDA_CHECK(cudaMemset(ptr, byte, bytes));
}

PBRTO_EXPORT void ReportKernelStats() {
    NCUDA_CHECK(cudaDeviceSynchronize());

    // Drain active profiler events
    for (size_t i = 0; i < eventPool.size(); ++i)
        if (eventPool[i].active)
            eventPool[i].Sync();

    // Compute total milliseconds over all kernels and launches
    float totalMS = 0;
    for (size_t i = 0; i < kernelStats.size(); ++i)
        totalMS += kernelStats[i]->sumMS;

    printf("Wavefront Kernel Profile:\n");
    int otherLaunches = 0;
    float otherMS = 0;
    const float otherCutoff = 0.001f * totalMS;
    for (size_t i = 0; i < kernelStats.size(); ++i) {
        KernelStats *stats = kernelStats[i];
        if (stats->sumMS > otherCutoff)
            Printf("  %-49s %5d launches %9.2f ms / %5.1f%s (avg %6.3f, min "
                   "%6.3f, max %7.3f)\n",
                   stats->description, stats->numLaunches, stats->sumMS,
                   100.f * stats->sumMS / totalMS, "%", stats->sumMS / stats->numLaunches,
                   stats->minMS, stats->maxMS);
        else {
            otherMS += stats->sumMS;
            otherLaunches += stats->numLaunches;
        }
    }
    Printf("  %-49s %5d launches %9.2f ms / %5.1f%s (avg %6.3f)\n", "Other",
           otherLaunches, otherMS, 100.f * otherMS / totalMS, "%",
           otherMS / otherLaunches);
    Printf("\nTotal rendering time: %9.2f ms\n", totalMS);
    Printf("\n");
}

}  // namespace pbrt
