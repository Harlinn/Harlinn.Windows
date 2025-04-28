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

#include <pbrto/util/NewNoise.h>

#include <pbrto/util/NewVecMath.h>

#include <algorithm>
#include <cmath>

namespace pbrto
{

    PBRT_CPU_GPU
        inline Float Grad( int x, int y, int z, Float dx, Float dy, Float dz );
    PBRT_CPU_GPU
        inline Float NoiseWeight( Float t );

    // Perlin Noise Data
    static constexpr int NoisePermSize = 256;
    static PBRT_CONST int NoisePerm[ 2 * NoisePermSize ] = {
        151, 160, 137, 91, 90, 15, 131, 13, 201, 95, 96, 53, 194, 233, 7, 225, 140, 36, 103,
        30, 69, 142,
        // Remainder of the noise permutation table
        8, 99, 37, 240, 21, 10, 23, 190, 6, 148, 247, 120, 234, 75, 0, 26, 197, 62, 94, 252,
        219, 203, 117, 35, 11, 32, 57, 177, 33, 88, 237, 149, 56, 87, 174, 20, 125, 136, 171,
        168, 68, 175, 74, 165, 71, 134, 139, 48, 27, 166, 77, 146, 158, 231, 83, 111, 229,
        122, 60, 211, 133, 230, 220, 105, 92, 41, 55, 46, 245, 40, 244, 102, 143, 54, 65, 25,
        63, 161, 1, 216, 80, 73, 209, 76, 132, 187, 208, 89, 18, 169, 200, 196, 135, 130, 116,
        188, 159, 86, 164, 100, 109, 198, 173, 186, 3, 64, 52, 217, 226, 250, 124, 123, 5,
        202, 38, 147, 118, 126, 255, 82, 85, 212, 207, 206, 59, 227, 47, 16, 58, 17, 182, 189,
        28, 42, 223, 183, 170, 213, 119, 248, 152, 2, 44, 154, 163, 70, 221, 153, 101, 155,
        167, 43, 172, 9, 129, 22, 39, 253, 19, 98, 108, 110, 79, 113, 224, 232, 178, 185, 112,
        104, 218, 246, 97, 228, 251, 34, 242, 193, 238, 210, 144, 12, 191, 179, 162, 241, 81,
        51, 145, 235, 249, 14, 239, 107, 49, 192, 214, 31, 181, 199, 106, 157, 184, 84, 204,
        176, 115, 121, 50, 45, 127, 4, 150, 254, 138, 236, 205, 93, 222, 114, 67, 29, 24, 72,
        243, 141, 128, 195, 78, 66, 215, 61, 156, 180, 151, 160, 137, 91, 90, 15, 131, 13,
        201, 95, 96, 53, 194, 233, 7, 225, 140, 36, 103, 30, 69, 142, 8, 99, 37, 240, 21, 10,
        23, 190, 6, 148, 247, 120, 234, 75, 0, 26, 197, 62, 94, 252, 219, 203, 117, 35, 11,
        32, 57, 177, 33, 88, 237, 149, 56, 87, 174, 20, 125, 136, 171, 168, 68, 175, 74, 165,
        71, 134, 139, 48, 27, 166, 77, 146, 158, 231, 83, 111, 229, 122, 60, 211, 133, 230,
        220, 105, 92, 41, 55, 46, 245, 40, 244, 102, 143, 54, 65, 25, 63, 161, 1, 216, 80, 73,
        209, 76, 132, 187, 208, 89, 18, 169, 200, 196, 135, 130, 116, 188, 159, 86, 164, 100,
        109, 198, 173, 186, 3, 64, 52, 217, 226, 250, 124, 123, 5, 202, 38, 147, 118, 126,
        255, 82, 85, 212, 207, 206, 59, 227, 47, 16, 58, 17, 182, 189, 28, 42, 223, 183, 170,
        213, 119, 248, 152, 2, 44, 154, 163, 70, 221, 153, 101, 155, 167, 43, 172, 9, 129, 22,
        39, 253, 19, 98, 108, 110, 79, 113, 224, 232, 178, 185, 112, 104, 218, 246, 97, 228,
        251, 34, 242, 193, 238, 210, 144, 12, 191, 179, 162, 241, 81, 51, 145, 235, 249, 14,
        239, 107, 49, 192, 214, 31, 181, 199, 106, 157, 184, 84, 204, 176, 115, 121, 50, 45,
        127, 4, 150, 254, 138, 236, 205, 93, 222, 114, 67, 29, 24, 72, 243, 141, 128, 195, 78,
        66, 215, 61, 156, 180

    };

    inline Float NoiseWeight( Float t )
    {
        return 6 * FastPow<5>( t ) - 15 * FastPow<4>( t ) + 10 * FastPow<3>( t );
    }

    inline Vector3f::Simd NoiseWeight( Vector3f::Simd t )
    {
        return Vector3f::Simd(6.f) * FastPow<5>( t ) - 15 * FastPow<4>( t ) + 10 * FastPow<3>( t );
    }

    // Noise Function Definitions
    Float Noise( Vector3f::Simd v )
    {
        // Compute noise cell coordinates and offsets
        // Avoid overflow when computing deltas if the coordinates are too large to store in
        // int32s.
        v = Math::FMod( v, Vector3f::Simd( Float( 1 << 30 ) ) );
        auto ii = Math::Floor( v );
        Vector3f d = v - ii;
        Vector3f i( ii  );
        /*
        x = Math::FMod( x, Float( 1 << 30 ) );
        y = Math::FMod( y, Float( 1 << 30 ) );
        z = Math::FMod( z, Float( 1 << 30 ) );
        int ix = Math::Floor( x ); 
        int iy = Math::Floor( y ); 
        int iz = Math::Floor( z );
        Float dx = x - ix; 
        Float dy = y - iy; 
        Float dz = z - iz;
        */

        // Compute gradient weights
        int ix = static_cast< int >( i.x ) & NoisePermSize - 1;
        int iy = static_cast< int >( i.y ) & NoisePermSize - 1;
        int iz = static_cast< int >( i.z ) & NoisePermSize - 1;
        Float w000 = Grad( ix, iy, iz, d.x, d.y, d.z );
        Float w100 = Grad( ix + 1, iy, iz, d.x - 1, d.y, d.z );
        Float w010 = Grad( ix, iy + 1, iz, d.x, d.y - 1, d.z );
        Float w110 = Grad( ix + 1, iy + 1, iz, d.x - 1, d.y - 1, d.z );
        Float w001 = Grad( ix, iy, iz + 1, d.x, d.y, d.z - 1 );
        Float w101 = Grad( ix + 1, iy, iz + 1, d.x - 1, d.y, d.z - 1 );
        Float w011 = Grad( ix, iy + 1, iz + 1, d.x, d.y - 1, d.z - 1 );
        Float w111 = Grad( ix + 1, iy + 1, iz + 1, d.x - 1, d.y - 1, d.z - 1 );

        // Compute trilinear interpolation of weights
        Vector3f w = NoiseWeight( d );
        //Float wx = NoiseWeight( dx ), wy = NoiseWeight( dy ), wz = NoiseWeight( dz );
        Float x00 = Lerp2( w.x, w000, w100 );
        Float x10 = Lerp2( w.x, w010, w110 );
        Float x01 = Lerp2( w.x, w001, w101 );
        Float x11 = Lerp2( w.x, w011, w111 );
        Float y0 = Lerp2( w.y, x00, x10 );
        Float y1 = Lerp2( w.y, x01, x11 );
        return Lerp2( w.z, y0, y1 );
    }

    Float Noise( Float x, Float y, Float z )
    {
        return Noise( Vector3f::Simd( x, y, z ) );
    }

    Float Noise( Point3f::Simd p )
    {
        return Noise( Vector3f::Simd( p ) );
    }

    Float Noise( Point3f p )
    {
        return Noise( p.x, p.y, p.z );
    }

    inline Float Grad( int x, int y, int z, Float dx, Float dy, Float dz )
    {
        int h = NoisePerm[ NoisePerm[ NoisePerm[ x ] + y ] + z ];
        h &= 15;
        Float u = h < 8 || h == 12 || h == 13 ? dx : dy;
        Float v = h < 4 || h == 12 || h == 13 ? dy : dz;
        return ( ( h & 1 ) ? -u : u ) + ( ( h & 2 ) ? -v : v );
    }

    

    Vector3f DNoise( Point3f p )
    {
        Float delta = .01f;
        Float n = Noise( p );
        Point3f noiseDelta( Noise( p + Vector3f( delta, 0, 0 ) ), Noise( p + Vector3f( 0, delta, 0 ) ),
            Noise( p + Vector3f( 0, 0, delta ) ) );
        return ( noiseDelta - Point3f( n, n, n ) ) / delta;
    }

    Float FBm( Point3f p, Vector3f dpdx, Vector3f dpdy, Float omega, int maxOctaves )
    {
        // Compute number of octaves for antialiased FBm
        Float len2 = std::max( ScalarLengthSquared( dpdx ), ScalarLengthSquared( dpdy ) );
        Float n = Clamp( -1 - Log2( len2 ) / 2, 0, maxOctaves );
        int nInt = static_cast<int>(Math::Floor( n ));

        // Compute sum of octaves of noise for FBm
        Float sum = 0, lambda = 1, o = 1;
        for ( int i = 0; i < nInt; ++i )
        {
            sum += o * Noise( lambda * p );
            lambda *= 1.99f;
            o *= omega;
        }
        Float nPartial = n - nInt;
        sum += o * SmoothStep( nPartial, .3f, .7f ) * Noise( lambda * p );

        return sum;
    }

    Float Turbulence( Point3f p, Vector3f dpdx, Vector3f dpdy, Float omega, int maxOctaves )
    {
        // Compute number of octaves for antialiased FBm
        Float len2 = std::max( ScalarLengthSquared( dpdx ), ScalarLengthSquared( dpdy ) );
        Float n = Clamp( -1 - Log2( len2 ) / 2, 0, maxOctaves );
        int nInt = Math::Floor( n );

        // Compute sum of octaves of noise for turbulence
        Float sum = 0, lambda = 1, o = 1;
        for ( int i = 0; i < nInt; ++i )
        {
            sum += o * Math::FastAbs( Noise( lambda * p ) );
            lambda *= 1.99f;
            o *= omega;
        }

        // Account for contributions of clamped octaves in turbulence
        Float nPartial = n - nInt;
        sum += o * Lerp2( SmoothStep( nPartial, .3f, .7f ), 0.2, Math::FastAbs( Noise( lambda * p ) ) );
        for ( int i = nInt; i < maxOctaves; ++i )
        {
            sum += o * 0.2f;
            o *= omega;
        }

        return sum;
    }

}