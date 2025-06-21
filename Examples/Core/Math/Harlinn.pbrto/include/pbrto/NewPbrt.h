#pragma once
#ifndef NEWPBRT_H_
#define NEWPBRT_H_

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


#include <pbrto/pbrt.h>

namespace pstdo
{

    namespace pmr
    {
        template <typename T>
        class polymorphic_allocator;
    }

}

namespace pbrto
{
    using namespace Harlinn::Common::Core;
    using namespace Harlinn::Math;
    using namespace Harlinn;


    // Float Type Definitions
#ifdef PBRT_FLOAT_AS_DOUBLE
    using Float = double;
#else
    using Float = float;
#endif

#ifdef PBRT_FLOAT_AS_DOUBLE
    using FloatBits = uint64_t;
#else
    using FloatBits = uint32_t;
#endif  // PBRT_FLOAT_AS_DOUBLE
    static_assert( sizeof( Float ) == sizeof( FloatBits ),
        "Float and FloatBits must have the same size" );

    template <typename T>
    class Vector2;
    template <typename T>
    class Vector3;
    template <typename T>
    class Point3;
    template <typename T>
    class Point2;
    template <typename T>
    class Normal3;
    using Point2f = Point2<Float>;
    using Point2i = Point2<int>;
    using Point3f = Point3<Float>;
    using Vector2f = Vector2<Float>;
    using Vector2i = Vector2<int>;
    using Vector3f = Vector3<Float>;

    template <typename T>
    class Bounds2;
    using Bounds2f = Bounds2<Float>;
    using Bounds2i = Bounds2<int>;
    template <typename T>
    class Bounds3;
    using Bounds3f = Bounds3<Float>;
    using Bounds3i = Bounds3<int>;

    class AnimatedTransform;
    class BilinearPatchMesh;
    class Interaction;
    class Interaction;
    class MediumInteraction;
    class Ray;
    class RayDifferential;
    class SurfaceInteraction;
    class SurfaceInteraction;
    class Transform;
    class TriangleMesh;

    class RGB;
    class RGBColorSpace;
    class RGBSigmoidPolynomial;
    class RGBIlluminantSpectrum;
    class SampledSpectrum;
    class SampledWavelengths;
    class SpectrumWavelengths;
    class XYZ;
    enum class SpectrumType;

    class BSDF;
    class CameraTransform;
    class Image;
    class ParameterDictionary;
    struct NamedTextures;
    class TextureParameterDictionary;
    struct ImageMetadata;
    struct MediumInterface;
    struct PBRTOptions;

    class PiecewiseConstant1D;
    class PiecewiseConstant2D;
    class ProgressReporter;
    class RNG;
    struct FileLoc;
    class Interval;
    template <typename T>
    class Array2D;

    template <typename T>
    struct SOA;
    class ScratchBuffer;

    // Define _Allocator_
    using Allocator = pstdo::pmr::polymorphic_allocator<std::byte>;

    // Initialization and Cleanup Function Declarations
    PBRTO_EXPORT void InitPBRT( const PBRTOptions& opt );
    PBRTO_EXPORT void CleanupPBRT( );

}  // namespace pbrto


namespace std
{

}

#endif
