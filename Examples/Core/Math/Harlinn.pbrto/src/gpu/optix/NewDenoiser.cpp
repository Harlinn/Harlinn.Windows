#include "pch.h"
// pbrt is Copyright(c) 1998-2020 Matt Pharr, Wenzel Jakob, and Greg Humphreys.
// The pbrt source code is licensed under the Apache License, Version 2.0.
// SPDX: Apache-2.0

#include <pbrto/gpu/optix/NewDenoiser.h>

//#include <pbrto/gpu/memory.h>
#include <pbrto/gpu/NewUtil.h>

#include <cuda.h>
#include <cuda_runtime.h>
#include <array>

#include <optix.h>
#include <optix_stubs.h>

#define NOPTIX_CHECK(EXPR)                                                           \
    do {                                                                            \
        OptixResult res = EXPR;                                                     \
        if (res != OPTIX_SUCCESS)                                                   \
            NLOG_FATAL("OptiX call " #EXPR " failed with code %d: \"%s\"", int(res), \
                      optixGetErrorString(res));                                    \
    } while (false) /* eat semicolon */

// Stop that, Windows.
#ifdef RGB
#undef RGB
#endif

namespace pbrto {

Denoiser::Denoiser(Vector2i resolution, bool haveAlbedoAndNormal)
    : resolution(resolution), haveAlbedoAndNormal(haveAlbedoAndNormal) {
    CUcontext cudaContext;
    NCU_CHECK(cuCtxGetCurrent(&cudaContext));
    NCHECK(cudaContext != nullptr);

    NOPTIX_CHECK(optixInit());
    OptixDeviceContext optixContext;
    NOPTIX_CHECK(optixDeviceContextCreate(cudaContext, 0, &optixContext));

    OptixDenoiserOptions options = {};
#if (OPTIX_VERSION >= 80000)
    options.denoiseAlpha = OPTIX_DENOISER_ALPHA_MODE_COPY;
#endif

#if (OPTIX_VERSION >= 70300)
    if (haveAlbedoAndNormal)
        options.guideAlbedo = options.guideNormal = 1;

    NOPTIX_CHECK(optixDenoiserCreate(optixContext, OPTIX_DENOISER_MODEL_KIND_HDR, &options,
                                    &denoiserHandle));
#else
    options.inputKind = haveAlbedoAndNormal ? OPTIX_DENOISER_INPUT_RGB_ALBEDO_NORMAL
                                            : OPTIX_DENOISER_INPUT_RGB;

    OPTIX_CHECK(optixDenoiserCreate(optixContext, &options, &denoiserHandle));

    OPTIX_CHECK(
        optixDenoiserSetModel(denoiserHandle, OPTIX_DENOISER_MODEL_KIND_HDR, nullptr, 0));
#endif

    NOPTIX_CHECK(optixDenoiserComputeMemoryResources(denoiserHandle, resolution.x,
                                                    resolution.y, &memorySizes));

    NCUDA_CHECK(cudaMalloc(&denoiserState, memorySizes.stateSizeInBytes));
    NCUDA_CHECK(cudaMalloc(&scratchBuffer, memorySizes.withoutOverlapScratchSizeInBytes));

    NOPTIX_CHECK(optixDenoiserSetup(
        denoiserHandle, 0 /* stream */, resolution.x, resolution.y,
        CUdeviceptr(denoiserState), memorySizes.stateSizeInBytes,
        CUdeviceptr(scratchBuffer), memorySizes.withoutOverlapScratchSizeInBytes));

    NCUDA_CHECK(cudaMalloc(&intensity, sizeof(float)));
}

void Denoiser::Denoise(RGB *rgb, Normal3f *n, RGB *albedo, RGB *result) {
    std::array<OptixImage2D, 3> inputLayers;
    int nLayers = haveAlbedoAndNormal ? 3 : 1;
    for (int i = 0; i < nLayers; ++i) {
        inputLayers[i].width = resolution.x;
        inputLayers[i].height = resolution.y;
        inputLayers[i].rowStrideInBytes = resolution.x * 3 * sizeof(float);
        inputLayers[i].pixelStrideInBytes = 0;
        inputLayers[i].format = OPTIX_PIXEL_FORMAT_FLOAT3;
    }
    inputLayers[0].data = CUdeviceptr(rgb);
    if (haveAlbedoAndNormal) {
        NCHECK(n != nullptr && albedo != nullptr);
        inputLayers[1].data = CUdeviceptr(albedo);
        inputLayers[2].data = CUdeviceptr(n);
    } else
        NCHECK(n == nullptr && albedo == nullptr);

    OptixImage2D outputImage;
    outputImage.width = resolution.x;
    outputImage.height = resolution.y;
    outputImage.rowStrideInBytes = resolution.x * 3 * sizeof(float);
    outputImage.pixelStrideInBytes = 0;
    outputImage.format = OPTIX_PIXEL_FORMAT_FLOAT3;
    outputImage.data = CUdeviceptr(result);

    NOPTIX_CHECK(optixDenoiserComputeIntensity(
        denoiserHandle, 0 /* stream */, &inputLayers[0], CUdeviceptr(intensity),
        CUdeviceptr(scratchBuffer), memorySizes.withoutOverlapScratchSizeInBytes));

    OptixDenoiserParams params = {};
#if (OPTIX_VERSION >= 80000)
    // denoiseAlpha is moved to OptixDenoiserOptions in OptiX 8.0
#elif (OPTIX_VERSION >= 70500)
    params.denoiseAlpha = OPTIX_DENOISER_ALPHA_MODE_COPY;
#else
    params.denoiseAlpha = 0;
#endif
    params.hdrIntensity = CUdeviceptr(intensity);
    params.blendFactor = 0;  // TODO what should this be??

#if (OPTIX_VERSION >= 70300)
    OptixDenoiserGuideLayer guideLayer;
    if (haveAlbedoAndNormal) {
        guideLayer.albedo = inputLayers[1];
        guideLayer.normal = inputLayers[2];
    }

    OptixDenoiserLayer layers;
    layers.input = inputLayers[0];
    layers.output = outputImage;

    NOPTIX_CHECK(optixDenoiserInvoke(
        denoiserHandle, 0 /* stream */, &params, CUdeviceptr(denoiserState),
        memorySizes.stateSizeInBytes, &guideLayer, &layers, 1 /* # layers to denoise */,
        0 /* offset x */, 0 /* offset y */, CUdeviceptr(scratchBuffer),
        memorySizes.withoutOverlapScratchSizeInBytes));
#else
    NOPTIX_CHECK(optixDenoiserInvoke(
        denoiserHandle, 0 /* stream */, &params, CUdeviceptr(denoiserState),
        memorySizes.stateSizeInBytes, inputLayers.data(), nLayers, 0 /* offset x */,
        0 /* offset y */, &outputImage, CUdeviceptr(scratchBuffer),
        memorySizes.withoutOverlapScratchSizeInBytes));
#endif
}

}  // namespace pbrt
