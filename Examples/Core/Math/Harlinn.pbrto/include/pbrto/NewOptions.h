#pragma once
#ifndef PBRTO_NEWOPTIONS_H_
#define PBRTO_NEWOPTIONS_H_

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
#include <pbrto/util/NewLog.h>
#include <pbrto/util/NewPStd.h>
#include <pbrto/util/NewVecMath.h>

#include <string>

namespace pbrto
{

    // RenderingCoordinateSystem Definition
    enum class RenderingCoordinateSystem { Camera, CameraWorld, World };

    PBRTO_EXPORT
        std::string ToString( const RenderingCoordinateSystem& );

    // BasicPBRTOptions Definition
    struct BasicPBRTOptions
    {
        int seed = 0;
        bool quiet = false;
        bool disablePixelJitter = false, disableWavelengthJitter = false;
        bool disableTextureFiltering = false;
        bool disableImageTextures = false;
        bool forceDiffuse = false;
        bool useGPU = false;
        bool wavefront = false;
        bool interactive = false;
        bool fullscreen = false;
        RenderingCoordinateSystem renderingSpace = RenderingCoordinateSystem::CameraWorld;
    };

    // PBRTOptions Definition
    struct PBRTOptions : BasicPBRTOptions
    {
        int nThreads = 0;
        LogLevel logLevel = LogLevel::Error;
        std::string logFile;
        bool logUtilization = false;
        bool writePartialImages = false;
        bool recordPixelStatistics = false;
        bool printStatistics = false;
        pstdo::optional<int> pixelSamples;
        pstdo::optional<int> gpuDevice;
        bool quickRender = false;
        bool upgrade = false;
        std::string imageFile;
        std::string mseReferenceImage, mseReferenceOutput;
        std::string debugStart;
        std::string displayServer;
        pstdo::optional<Bounds2f> cropWindow;
        pstdo::optional<Bounds2i> pixelBounds;
        pstdo::optional<Point2i> pixelMaterial;
        Float displacementEdgeScale = 1;

        PBRTO_EXPORT
            std::string ToString( ) const;
    };

    // Options Global Variable Declaration
    PBRTO_EXPORT
        extern PBRTOptions* Options;

#if defined(PBRT_BUILD_GPU_RENDERER)
#if defined(__CUDACC__)
    extern __constant__ BasicPBRTOptions OptionsGPU;
#endif  // __CUDACC__

    void CopyOptionsToGPU( );
#endif  // PBRT_BUILD_GPU_RENDERER

    // Options Inline Functions
    PBRT_CPU_GPU inline const BasicPBRTOptions& GetOptions( );

    PBRT_CPU_GPU inline const BasicPBRTOptions& GetOptions( )
    {
#if defined(PBRT_IS_GPU_CODE)
        return OptionsGPU;
#else
        return *Options;
#endif
    }

}

#endif
