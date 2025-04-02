#pragma once
#ifndef PBRTO_UTIL_NEWCOLORSPACE_H_
#define PBRTO_UTIL_NEWCOLORSPACE_H_

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

#include <pbrto/util/NewColor.h>
#include <pbrto/util/NewMath.h>
#include <pbrto/util/NewSpectrum.h>
#include <pbrto/util/NewVecMath.h>

#include <string>

namespace pbrto
{

    // RGBColorSpace Definition
    class RGBColorSpace
    {
    public:
        // RGBColorSpace Public Methods
        RGBColorSpace( Point2f r, Point2f g, Point2f b, Spectrum illuminant,
            const RGBToSpectrumTable* rgbToSpectrumTable, Allocator alloc );

        PBRT_CPU_GPU
            RGBSigmoidPolynomial ToRGBCoeffs( RGB rgb ) const;

        static void Init( Allocator alloc );

        // RGBColorSpace Public Members
        Point2f r, g, b, w;
        DenselySampledSpectrum illuminant;
        SquareMatrix<3> XYZFromRGB, RGBFromXYZ;
        static const RGBColorSpace* sRGB, * DCI_P3, * Rec2020, * ACES2065_1;

        PBRT_CPU_GPU
            bool operator==( const RGBColorSpace& cs ) const
        {
            return ( r == cs.r && g == cs.g && b == cs.b && w == cs.w &&
                rgbToSpectrumTable == cs.rgbToSpectrumTable );
        }
        PBRT_CPU_GPU
            bool operator!=( const RGBColorSpace& cs ) const
        {
            return ( r != cs.r || g != cs.g || b != cs.b || w != cs.w ||
                rgbToSpectrumTable != cs.rgbToSpectrumTable );
        }

        std::string ToString( ) const;

        PBRT_CPU_GPU
            RGB LuminanceVector( ) const
        {
            return RGB( XYZFromRGB[ 1 ][ 0 ], XYZFromRGB[ 1 ][ 1 ], XYZFromRGB[ 1 ][ 2 ] );
        }

        PBRT_CPU_GPU
            RGB ToRGB( XYZ xyz ) const { return Mul<RGB>( RGBFromXYZ, xyz ); }
        PBRT_CPU_GPU
            XYZ ToXYZ( RGB rgb ) const { return Mul<XYZ>( XYZFromRGB, rgb ); }

        static const RGBColorSpace* GetNamed( std::string name );
        static const RGBColorSpace* Lookup( Point2f r, Point2f g, Point2f b, Point2f w );

    private:
        // RGBColorSpace Private Members
        const RGBToSpectrumTable* rgbToSpectrumTable;
    };

#ifdef PBRT_BUILD_GPU_RENDERER
    extern PBRT_CONST RGBColorSpace* RGBColorSpace_sRGB;
    extern PBRT_CONST RGBColorSpace* RGBColorSpace_DCI_P3;
    extern PBRT_CONST RGBColorSpace* RGBColorSpace_Rec2020;
    extern PBRT_CONST RGBColorSpace* RGBColorSpace_ACES2065_1;
#endif

    SquareMatrix<3> ConvertRGBColorSpace( const RGBColorSpace& from, const RGBColorSpace& to );

}

#endif
