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

#include <pbrto/Newoptions.h>

#if defined(PBRT_BUILD_GPU_RENDERER)
#include <pbrto/gpu/util.h>
#endif  // PBRT_BUILD_GPU_RENDERER

namespace pbrto
{

    PBRTO_EXPORT
        PBRTOptions* Options;

#if defined(PBRT_BUILD_GPU_RENDERER)
    __constant__ BasicPBRTOptions OptionsGPU;

    void CopyOptionsToGPU( )
    {
        CUDA_CHECK( cudaMemcpyToSymbol( OptionsGPU, Options, sizeof( OptionsGPU ) ) );
    }
#endif

    PBRTO_EXPORT
        std::string ToString( const RenderingCoordinateSystem& r )
    {
        if ( r == RenderingCoordinateSystem::Camera )
            return "RenderingCoordinateSystem::Camera";
        else if ( r == RenderingCoordinateSystem::CameraWorld )
            return "RenderingCoordinateSystem::CameraWorld";
        else
        {
            NCHECK( r == RenderingCoordinateSystem::World );
            return "RenderingCoordinateSystem::World";
        }
    }


    std::string PBRTOptions::ToString( ) const
    {
        return StringPrintf(
            "[ PBRTOptions seed: %s quiet: %s disablePixelJitter: %s "
            "disableWavelengthJitter: %s disableTextureFiltering: %s disableImageTextures: %s "
            "forceDiffuse: %s useGPU: %s wavefront: %s interactive: %s fullscreen %s "
            "renderingSpace: %s nThreads: %s logLevel: %s logFile: %s logUtilization: %s "
            "writePartialImages: %s recordPixelStatistics: %s "
            "printStatistics: %s pixelSamples: %s gpuDevice: %s quickRender: %s upgrade: %s "
            "imageFile: %s mseReferenceImage: %s mseReferenceOutput: %s debugStart: %s "
            "displayServer: %s cropWindow: %s pixelBounds: %s pixelMaterial: %s "
            "displacementEdgeScale: %f ]",
            seed, quiet, disablePixelJitter, disableWavelengthJitter, disableTextureFiltering,
            disableImageTextures, forceDiffuse, useGPU, wavefront, interactive, fullscreen,
            renderingSpace, nThreads, logLevel, logFile, logUtilization, writePartialImages,
            recordPixelStatistics, printStatistics, pixelSamples, gpuDevice, quickRender, upgrade,
            imageFile, mseReferenceImage, mseReferenceOutput, debugStart, displayServer, cropWindow,
            pixelBounds, pixelMaterial, displacementEdgeScale );
    }

}
