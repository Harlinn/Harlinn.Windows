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

#include <pbrto/NewTextures.h>

#include <pbrto/NewInteraction.h>
#include <pbrto/NewParamDict.h>
#include <pbrto/util/NewColor.h>
#include <pbrto/util/NewColorSpace.h>
#include <pbrto/util/NewError.h>
#include <pbrto/util/NewFile.h>
#include <pbrto/util/NewFloat.h>
#include <pbrto/util/NewSplines.h>
#include <pbrto/util/NewStats.h>

#include <algorithm>
#include <mutex>

#include <ptex/Ptexture.h>

// Windows strikes again.
#ifdef RGB
#undef RGB
#endif

namespace pbrto
{

    std::string TextureEvalContext::ToString( ) const
    {
        return StringPrintf(
            "[ TextureEvalContext p: %s dpdx: %s dpdy: %s n: %s uv: %s dudx: %f dudy: %f "
            "dvdx: %f dvdy: %f faceIndex: %d ]",
            p, dpdx, dpdy, n, uv, dudx, dudy, dvdx, dvdy, faceIndex );
    }

    std::string TexCoord2D::ToString( ) const
    {
        return StringPrintf( "[ TexCoord2D st: %s dsdx: %f dsdy: %f dtdx: %f dtdy: %f ]", st,
            dsdx, dsdy, dtdx, dtdy );
    }

    std::string TexCoord3D::ToString( ) const
    {
        return StringPrintf( "[ TexCoord3D p: %s dpdx: %s dpdy: %s ]", p, dpdx, dpdy );
    }

    TextureMapping2D TextureMapping2D::Create( const ParameterDictionary& parameters,
        const Transform& renderFromTexture,
        const FileLoc* loc, Allocator alloc )
    {
        std::string type = parameters.GetOneString( "mapping", "uv" );
        if ( type == "uv" )
        {
            Float su = parameters.GetOneFloat( "uscale", 1. );
            Float sv = parameters.GetOneFloat( "vscale", 1. );
            Float du = parameters.GetOneFloat( "udelta", 0. );
            Float dv = parameters.GetOneFloat( "vdelta", 0. );
            return alloc.new_object<UVMapping>( su, sv, du, dv );
        }
        else if ( type == "spherical" )
            return alloc.new_object<SphericalMapping>( Inverse( renderFromTexture ) );
        else if ( type == "cylindrical" )
            return alloc.new_object<CylindricalMapping>( Inverse( renderFromTexture ) );
        else if ( type == "planar" )
            return alloc.new_object<PlanarMapping>(
                Inverse( renderFromTexture ),
                parameters.GetOneVector3f( "v1", Vector3f( 1, 0, 0 ) ),
                parameters.GetOneVector3f( "v2", Vector3f( 0, 1, 0 ) ),
                parameters.GetOneFloat( "udelta", 0.f ), parameters.GetOneFloat( "vdelta", 0.f ) );
        else
        {
            Error( loc, "2D texture mapping \"%s\" unknown", type );
            return alloc.new_object<UVMapping>( );
        }
    }

    TextureMapping3D TextureMapping3D::Create( const ParameterDictionary& parameters,
        const Transform& renderFromTexture,
        const FileLoc* loc, Allocator alloc )
    {
        return alloc.new_object<PointTransformMapping>( Inverse( renderFromTexture ) );
    }

    std::string FloatTexture::ToString( ) const
    {
        if ( !ptr( ) )
            return "(nullptr)";

        auto toStr = []( auto ptr ) { return ptr->ToString( ); };
        return DispatchCPU( toStr );
    }

    std::string SpectrumTexture::ToString( ) const
    {
        if ( !ptr( ) )
            return "(nullptr)";

        auto toStr = []( auto ptr ) { return ptr->ToString( ); };
        return DispatchCPU( toStr );
    }

    std::string UVMapping::ToString( ) const
    {
        return StringPrintf( "[ UVMapping su: %f sv: %f du: %f dv: %f ]", su, sv, du, dv );
    }

    std::string SphericalMapping::ToString( ) const
    {
        return StringPrintf( "[ SphericalMapping textureFromRender: %s ]", textureFromRender );
    }

    std::string CylindricalMapping::ToString( ) const
    {
        return StringPrintf( "[ CylindricalMapping textureFromRender: %s ]",
            textureFromRender );
    }

    std::string PlanarMapping::ToString( ) const
    {
        return StringPrintf( "[ PlanarMapping vs: %s vt: %s ds: %f dt: %f]", vs, vt, ds, dt );
    }

    std::string PointTransformMapping::ToString( ) const
    {
        return StringPrintf( "[ PointTransformMapping textureFromRender: %s ]",
            textureFromRender );
    }

    std::string FloatConstantTexture::ToString( ) const
    {
        return StringPrintf( "[ FloatConstantTexture value: %f ]", value );
    }

    FloatConstantTexture* FloatConstantTexture::Create(
        const Transform& renderFromTexture, const TextureParameterDictionary& parameters,
        const FileLoc* loc, Allocator alloc )
    {
        return alloc.new_object<FloatConstantTexture>( parameters.GetOneFloat( "value", 1.f ) );
    }

    std::string SpectrumConstantTexture::ToString( ) const
    {
        return StringPrintf( "[ SpectrumConstantTexture value: %s ]", value );
    }

    SpectrumConstantTexture* SpectrumConstantTexture::Create(
        const Transform& renderFromTexture, const TextureParameterDictionary& parameters,
        SpectrumType spectrumType, const FileLoc* loc, Allocator alloc )
    {
        Spectrum one = alloc.new_object<ConstantSpectrum>( 1. );
        Spectrum c = parameters.GetOneSpectrum( "value", one, spectrumType, alloc );
        return alloc.new_object<SpectrumConstantTexture>( c );
    }

    FloatBilerpTexture* FloatBilerpTexture::Create(
        const Transform& renderFromTexture, const TextureParameterDictionary& parameters,
        const FileLoc* loc, Allocator alloc )
    {
        // Initialize 2D texture mapping _map_ from _tp_
        TextureMapping2D map =
            TextureMapping2D::Create( parameters, renderFromTexture, loc, alloc );

        return alloc.new_object<FloatBilerpTexture>(
            map, parameters.GetOneFloat( "v00", 0.f ), parameters.GetOneFloat( "v01", 1.f ),
            parameters.GetOneFloat( "v10", 0.f ), parameters.GetOneFloat( "v11", 1.f ) );
    }

    std::string FloatBilerpTexture::ToString( ) const
    {
        return StringPrintf(
            "[ FloatBilerpTexture mapping: %s v00: %f v01: %f v10: %f v11: %f ]", mapping,
            v00, v01, v10, v11 );
    }

    SpectrumBilerpTexture* SpectrumBilerpTexture::Create(
        const Transform& renderFromTexture, const TextureParameterDictionary& parameters,
        SpectrumType spectrumType, const FileLoc* loc, Allocator alloc )
    {
        // Initialize 2D texture mapping _map_ from _tp_
        TextureMapping2D map = TextureMapping2D::Create( parameters, renderFromTexture, loc, alloc );

        Spectrum zero = alloc.new_object<ConstantSpectrum>( 0. );
        Spectrum one = alloc.new_object<ConstantSpectrum>( 1. );

        return alloc.new_object<SpectrumBilerpTexture>(
            map, parameters.GetOneSpectrum( "v00", zero, spectrumType, alloc ),
            parameters.GetOneSpectrum( "v01", one, spectrumType, alloc ),
            parameters.GetOneSpectrum( "v10", zero, spectrumType, alloc ),
            parameters.GetOneSpectrum( "v11", one, spectrumType, alloc ) );
    }

    std::string SpectrumBilerpTexture::ToString( ) const
    {
        return StringPrintf(
            "[ SpectrumBilerpTexture mapping: %s v00: %s v01: %s v10: %s v11: %s ]", mapping,
            v00, v01, v10, v11 );
    }

    // CheckerboardTexture Function Definitions
    Float Checkerboard( const TextureEvalContext& ctx, TextureMapping2D map2D, TextureMapping3D map3D )
    {
        // Define 1D checkerboard filtered integral functions
        auto d = []( Float x ) {
            Float y = x / 2 - pstdo::floor( x / 2 ) - 0.5f;
            return x / 2 + y * ( 1 - 2 * Math::FastAbs( y ) );
            };

        auto bf = [ & ]( Float x, Float r ) -> Float {
            if ( pstdo::floor( x - r ) == pstdo::floor( x + r ) )
                return 1 - 2 * ( int( pstdo::floor( x ) ) & 1 );
            return ( d( x + r ) - 2 * d( x ) + d( x - r ) ) / Sqr( r );
            };

        if ( map2D )
        {
            // Return weights for 2D checkerboard texture
            NCHECK( !map3D );
            TexCoord2D c = map2D.Map( ctx );
            Float ds = Math::Max( Math::FastAbs( c.dsdx ), Math::FastAbs( c.dsdy ) );
            Float dt = Math::Max( Math::FastAbs( c.dtdx ), Math::FastAbs( c.dtdy ) );
            // Integrate product of 2D checkerboard function and triangle filter
            ds *= 1.5f;
            dt *= 1.5f;
            return 0.5f - bf( c.st[ 0 ], ds ) * bf( c.st[ 1 ], dt ) / 2;

        }
        else
        {
            // Return weights for 3D checkerboard texture
            NCHECK( map3D );
            TexCoord3D c = map3D.Map( ctx );
            Point3f cp = c.p;
            /*
            Float dx = 1.5f * std::max( Math::FastAbs( c.dpdx.x ), Math::FastAbs( c.dpdy.x ) );
            Float dy = 1.5f * std::max( Math::FastAbs( c.dpdx.y ), Math::FastAbs( c.dpdy.y ) );
            Float dz = 1.5f * std::max( Math::FastAbs( c.dpdx.z ), Math::FastAbs( c.dpdy.z ) );
            */
            Vector3f d = 1.5f * Math::Max( Math::Abs( c.dpdx ), Math::Abs( c.dpdy ) );

            return 0.5f - 0.5f * bf( cp.x, d.x ) * bf( cp.y, d.y ) * bf( cp.z, d.z );
        }
    }

    FloatCheckerboardTexture* FloatCheckerboardTexture::Create(
        const Transform& renderFromTexture, const TextureParameterDictionary& parameters,
        const FileLoc* loc, Allocator alloc )
    {
        int dim = parameters.GetOneInt( "dimension", 2 );
        if ( dim != 2 && dim != 3 )
        {
            Error( loc, "%d dimensional checkerboard texture not supported", dim );
            return nullptr;
        }
        FloatTexture tex1 = parameters.GetFloatTexture( "tex1", 1.f, alloc );
        FloatTexture tex2 = parameters.GetFloatTexture( "tex2", 0.f, alloc );
        if ( dim == 2 )
        {
            // Initialize 2D texture mapping _map_ from _tp_
            TextureMapping2D map =
                TextureMapping2D::Create( parameters, renderFromTexture, loc, alloc );

            return alloc.new_object<FloatCheckerboardTexture>( map, nullptr, tex1, tex2 );
        }
        else
        {
            // Initialize 3D texture mapping _map_ from _tp_
            TextureMapping3D map =
                TextureMapping3D::Create( parameters, renderFromTexture, loc, alloc );
            return alloc.new_object<FloatCheckerboardTexture>( nullptr, map, tex1, tex2 );
        }
    }

    std::string FloatCheckerboardTexture::ToString( ) const
    {
        return StringPrintf( "[ FloatCheckerboardTexture map2D: %s map3D: %s "
            "tex[0]: %s tex[1]: %s ",
            map2D ? map2D.ToString( ).c_str( ) : "(nullptr)",
            map3D ? map3D.ToString( ).c_str( ) : "(nullptr)", tex[ 0 ], tex[ 1 ] );
    }

    SpectrumCheckerboardTexture* SpectrumCheckerboardTexture::Create(
        const Transform& renderFromTexture, const TextureParameterDictionary& parameters,
        SpectrumType spectrumType, const FileLoc* loc, Allocator alloc )
    {
        int dim = parameters.GetOneInt( "dimension", 2 );
        if ( dim != 2 && dim != 3 )
        {
            Error( loc, "%d dimensional checkerboard texture not supported", dim );
            return nullptr;
        }

        Spectrum zero = alloc.new_object<ConstantSpectrum>( 0. );
        Spectrum one = alloc.new_object<ConstantSpectrum>( 1. );

        SpectrumTexture tex1 =
            parameters.GetSpectrumTexture( "tex1", one, spectrumType, alloc );
        SpectrumTexture tex2 =
            parameters.GetSpectrumTexture( "tex2", zero, spectrumType, alloc );
        if ( dim == 2 )
        {
            // Initialize 2D texture mapping _map_ from _tp_
            TextureMapping2D map =
                TextureMapping2D::Create( parameters, renderFromTexture, loc, alloc );

            return alloc.new_object<SpectrumCheckerboardTexture>( map, nullptr, tex1, tex2 );
        }
        else
        {
            // Initialize 3D texture mapping _map_ from _tp_
            TextureMapping3D map =
                TextureMapping3D::Create( parameters, renderFromTexture, loc, alloc );
            return alloc.new_object<SpectrumCheckerboardTexture>( nullptr, map, tex1, tex2 );
        }
    }

    std::string SpectrumCheckerboardTexture::ToString( ) const
    {
        return StringPrintf( "[ SpectrumCheckerboardTexture map2D: %s map3D: %s "
            "tex[0]: %s tex[1]: %s ",
            map2D ? map2D.ToString( ).c_str( ) : "(nullptr)",
            map3D ? map3D.ToString( ).c_str( ) : "(nullptr)", tex[ 0 ], tex[ 1 ] );
    }

    // InsidePolkaDot Function Definition
    bool InsidePolkaDot( Point2f st )
    {
        // Compute cell indices (_sCell_,_tCell_ for dots
        int sCell = pstdo::floor( st[ 0 ] + .5f ), tCell = pstdo::floor( st[ 1 ] + .5f );

        if ( Noise( sCell + .5f, tCell + .5f ) > 0 )
        {
            // Determine dot position and test if _st_ is inside it
            Float radius = .35f;
            Float maxShift = 0.5f - radius;
            Float sCenter = sCell + maxShift * Noise( sCell + 1.5f, tCell + 2.8f );
            Float tCenter = tCell + maxShift * Noise( sCell + 4.5f, tCell + 9.8f );
            Vector2f dst = st - Point2f( sCenter, tCenter );
            if ( ScalarLengthSquared( dst ) < Sqr( radius ) )
                return true;
        }
        return false;
    }

    FloatDotsTexture* FloatDotsTexture::Create( const Transform& renderFromTexture,
        const TextureParameterDictionary& parameters,
        const FileLoc* loc, Allocator alloc )
    {
        // Initialize 2D texture mapping _map_ from _tp_
        TextureMapping2D map =
            TextureMapping2D::Create( parameters, renderFromTexture, loc, alloc );

        return alloc.new_object<FloatDotsTexture>(
            map, parameters.GetFloatTexture( "inside", 1.f, alloc ),
            parameters.GetFloatTexture( "outside", 0.f, alloc ) );
    }

    std::string FloatDotsTexture::ToString( ) const
    {
        return StringPrintf( "[ FloatDotsTexture mapping: %s insideDot: %s outsideDot: %s ]",
            mapping, insideDot, outsideDot );
    }

    SpectrumDotsTexture* SpectrumDotsTexture::Create(
        const Transform& renderFromTexture, const TextureParameterDictionary& parameters,
        SpectrumType spectrumType, const FileLoc* loc, Allocator alloc )
    {
        // Initialize 2D texture mapping _map_ from _tp_
        TextureMapping2D map =
            TextureMapping2D::Create( parameters, renderFromTexture, loc, alloc );
        Spectrum zero = alloc.new_object<ConstantSpectrum>( 0. );
        Spectrum one = alloc.new_object<ConstantSpectrum>( 1. );

        return alloc.new_object<SpectrumDotsTexture>(
            map, parameters.GetSpectrumTexture( "inside", one, spectrumType, alloc ),
            parameters.GetSpectrumTexture( "outside", zero, spectrumType, alloc ) );
    }

    std::string SpectrumDotsTexture::ToString( ) const
    {
        return StringPrintf(
            "[ SpectrumDotsTexture mapping: %s insideDot: %s outsideDot: %s ]", mapping,
            insideDot, outsideDot );
    }

    // FBmTexture Method Definitions
    FBmTexture* FBmTexture::Create( const Transform& renderFromTexture,
        const TextureParameterDictionary& parameters,
        const FileLoc* loc, Allocator alloc )
    {
        // Initialize 3D texture mapping _map_ from _tp_
        TextureMapping3D map =
            TextureMapping3D::Create( parameters, renderFromTexture, loc, alloc );
        return alloc.new_object<FBmTexture>( map, parameters.GetOneInt( "octaves", 8 ),
            parameters.GetOneFloat( "roughness", .5f ) );
    }

    std::string FBmTexture::ToString( ) const
    {
        return StringPrintf( "[ FBmTexture mapping: %s omega: %f octaves: %d ]", mapping,
            omega, octaves );
    }

    // SpectrumImageTexture Method Definitions
    SampledSpectrum SpectrumImageTexture::Evaluate( const TextureEvalContext& ctx, const SampledWavelengths& lambda ) const
    {
#ifdef PBRT_IS_GPU_CODE
        assert( !"Should not be called in GPU code" );
        return SampledSpectrum( 0 );
#else
        // Apply texture mapping and flip $t$ coordinate for image texture lookup
        TexCoord2D c = mapping.Map( ctx );
        c.st[ 1 ] = 1 - c.st[ 1 ];

        // Lookup filtered RGB value in _MIPMap_
        RGB rgb = scale * mipmap->Filter<RGB>( c.st, { c.dsdx, c.dtdx }, { c.dsdy, c.dtdy } );
        rgb = ClampZero( invert ? ( RGB( 1, 1, 1 ) - rgb ) : rgb );

        // Return _SampledSpectrum_ for RGB image texture value
        if ( const RGBColorSpace* cs = mipmap->GetRGBColorSpace( ); cs )
        {
            if ( spectrumType == SpectrumType::Unbounded )
                return RGBUnboundedSpectrum( *cs, rgb ).Sample( lambda );
            else if ( spectrumType == SpectrumType::Albedo )
                return RGBAlbedoSpectrum( *cs, Clamp( rgb, 0, 1 ) ).Sample( lambda );
            else
                return RGBIlluminantSpectrum( *cs, rgb ).Sample( lambda );
        }
        // otherwise it better be a one-channel texture
        NDCHECK( rgb[ 0 ] == rgb[ 1 ] && rgb[ 1 ] == rgb[ 2 ] );
        return SampledSpectrum( rgb[ 0 ] );

#endif
    }

    std::string SpectrumImageTexture::ToString( ) const
    {
        return StringPrintf( "[ SpectrumImageTexture filename: %s mapping: %s scale: %f "
            "invert: %s mipmap: %s ]",
            filename, mapping, scale, invert, *mipmap );
    }

    std::string FloatImageTexture::ToString( ) const
    {
        return StringPrintf(
            "[ FloatImageTexture filename: %s mapping: %s scale: %f invert: %s mipmap: %s ]",
            filename, mapping, scale, invert, *mipmap );
    }

    std::string TexInfo::ToString( ) const
    {
        return StringPrintf(
            "[ TexInfo filename: %s filterOptions: %s wrapMode: %s encoding: %s ]", filename,
            filterOptions, wrapMode, encoding );
    }

    std::mutex ImageTextureBase::textureCacheMutex;
    std::map<TexInfo, MIPMap*> ImageTextureBase::textureCache;

    FloatImageTexture* FloatImageTexture::Create( const Transform& renderFromTexture,
        const TextureParameterDictionary& parameters,
        const FileLoc* loc, Allocator alloc )
    {
        // Initialize 2D texture mapping _map_ from _tp_
        TextureMapping2D map =
            TextureMapping2D::Create( parameters, renderFromTexture, loc, alloc );

        // Initialize _ImageTexture_ parameters
        Float maxAniso = parameters.GetOneFloat( "maxanisotropy", 8.f );
        std::string filter = parameters.GetOneString( "filter", "bilinear" );
        MIPMapFilterOptions filterOptions;
        filterOptions.maxAnisotropy = maxAniso;
        pstdo::optional<FilterFunction> ff = ParseFilter( filter );
        if ( ff )
            filterOptions.filter = *ff;
        else
            Error( loc, "%s: filter function unknown", filter );

        std::string wrapString = parameters.GetOneString( "wrap", "repeat" );
        pstdo::optional<WrapMode> wrapMode = ParseWrapMode( wrapString.c_str( ) );
        if ( !wrapMode )
            ErrorExit( "%s: wrap mode unknown", wrapString );
        Float scale = parameters.GetOneFloat( "scale", 1.f );
        bool invert = parameters.GetOneBool( "invert", false );
        std::string filename = ResolveFilename( parameters.GetOneString( "filename", "" ) );

        const char* defaultEncoding = HasExtension( filename, "png" ) ? "sRGB" : "linear";
        std::string encodingString = parameters.GetOneString( "encoding", defaultEncoding );
        ColorEncoding encoding = ColorEncoding::Get( encodingString, alloc );

        return alloc.new_object<FloatImageTexture>( map, filename, filterOptions, *wrapMode,
            scale, invert, encoding, alloc );
    }

    SpectrumImageTexture* SpectrumImageTexture::Create(
        const Transform& renderFromTexture, const TextureParameterDictionary& parameters,
        SpectrumType spectrumType, const FileLoc* loc, Allocator alloc )
    {
        // Initialize 2D texture mapping _map_ from _tp_
        TextureMapping2D map =
            TextureMapping2D::Create( parameters, renderFromTexture, loc, alloc );

        // Initialize _ImageTexture_ parameters
        Float maxAniso = parameters.GetOneFloat( "maxanisotropy", 8.f );
        std::string filter = parameters.GetOneString( "filter", "bilinear" );
        MIPMapFilterOptions filterOptions;
        filterOptions.maxAnisotropy = maxAniso;
        pstdo::optional<FilterFunction> ff = ParseFilter( filter );
        if ( ff )
            filterOptions.filter = *ff;
        else
            Error( loc, "%s: filter function unknown", filter );

        std::string wrapString = parameters.GetOneString( "wrap", "repeat" );
        pstdo::optional<WrapMode> wrapMode = ParseWrapMode( wrapString.c_str( ) );
        if ( !wrapMode )
            ErrorExit( "%s: wrap mode unknown", wrapString );
        Float scale = parameters.GetOneFloat( "scale", 1.f );
        bool invert = parameters.GetOneBool( "invert", false );
        std::string filename = ResolveFilename( parameters.GetOneString( "filename", "" ) );

        const char* defaultEncoding = HasExtension( filename, "png" ) ? "sRGB" : "linear";
        std::string encodingString = parameters.GetOneString( "encoding", defaultEncoding );
        ColorEncoding encoding = ColorEncoding::Get( encodingString, alloc );

        return alloc.new_object<SpectrumImageTexture>( map, filename, filterOptions, *wrapMode,
            scale, invert, encoding, spectrumType,
            alloc );
    }

    // MarbleTexture Method Definitions
    SampledSpectrum MarbleTexture::Evaluate( const TextureEvalContext& ctx, const SampledWavelengths& lambda ) const
    {
        TexCoord3D c = mapping.Map( ctx );
        c.p *= scale;
        Float marble = c.p.y() + variation * FBm( c.p, scale * c.dpdx, scale * c.dpdy, omega, octaves );
        Float t = .5f + .5f * Math::Sin( marble );
        // Evaluate marble spline at $t$ to compute color _rgb_
        const RGB colors[ ] = {
            {.58f, .58f, .6f}, {.58f, .58f, .6f}, {.58f, .58f, .6f},
            {.5f, .5f, .5f},   {.6f, .59f, .58f}, {.58f, .58f, .6f},
            {.58f, .58f, .6f}, {.2f, .2f, .33f},  {.58f, .58f, .6f},
        };
        int nSeg = sizeof( colors ) / sizeof( colors[ 0 ] ) - 3;
        int first = std::min<int>( pstdo::floor( t * nSeg ), nSeg - 1 );
        t = t * nSeg - first;
        RGB rgb = 1.5f * EvaluateCubicBezier( std::span<const RGB, 4>( colors + first, 4 ), t );

#ifdef PBRT_IS_GPU_CODE
        return RGBAlbedoSpectrum( *RGBColorSpace_sRGB, rgb ).Sample( lambda );
#else
        return RGBAlbedoSpectrum( *RGBColorSpace::sRGB, rgb ).Sample( lambda );
#endif
    }

    std::string MarbleTexture::ToString( ) const
    {
        return StringPrintf( "[ MarbleTexture mapping: %s octaves: %d omega: %f "
            "scale: %f variation: %f ]",
            mapping, octaves, omega, scale, variation );
    }

    MarbleTexture* MarbleTexture::Create( const Transform& renderFromTexture,
        const TextureParameterDictionary& parameters,
        const FileLoc* loc, Allocator alloc )
    {
        // Initialize 3D texture mapping _map_ from _tp_
        TextureMapping3D map =
            TextureMapping3D::Create( parameters, renderFromTexture, loc, alloc );
        return alloc.new_object<MarbleTexture>(
            map, parameters.GetOneInt( "octaves", 8 ), parameters.GetOneFloat( "roughness", .5f ),
            parameters.GetOneFloat( "scale", 1.f ), parameters.GetOneFloat( "variation", .2f ) );
    }

    // MixTexture Method Definitions
    std::string FloatMixTexture::ToString( ) const
    {
        return StringPrintf( "[ FloatMixTexture tex1: %s tex2: %s amount: %s ]", tex1, tex2,
            amount );
    }

    std::string SpectrumMixTexture::ToString( ) const
    {
        return StringPrintf( "[ SpectrumMixTexture tex1: %s tex2: %s amount: %s ]", tex1, tex2,
            amount );
    }

    FloatMixTexture* FloatMixTexture::Create( const Transform& renderFromTexture,
        const TextureParameterDictionary& parameters,
        const FileLoc* loc, Allocator alloc )
    {
        return alloc.new_object<FloatMixTexture>(
            parameters.GetFloatTexture( "tex1", 0.f, alloc ),
            parameters.GetFloatTexture( "tex2", 1.f, alloc ),
            parameters.GetFloatTexture( "amount", 0.5f, alloc ) );
    }

    SpectrumMixTexture* SpectrumMixTexture::Create(
        const Transform& renderFromTexture, const TextureParameterDictionary& parameters,
        SpectrumType spectrumType, const FileLoc* loc, Allocator alloc )
    {
        Spectrum zero = alloc.new_object<ConstantSpectrum>( 0. );
        Spectrum one = alloc.new_object<ConstantSpectrum>( 1. );
        return alloc.new_object<SpectrumMixTexture>(
            parameters.GetSpectrumTexture( "tex1", zero, spectrumType, alloc ),
            parameters.GetSpectrumTexture( "tex2", one, spectrumType, alloc ),
            parameters.GetFloatTexture( "amount", 0.5f, alloc ) );
    }

    std::string FloatDirectionMixTexture::ToString( ) const
    {
        return StringPrintf( "[ FloatDirectionMixTexture tex1: %s tex2: %s dir: %s ]", tex1,
            tex2, dir );
    }

    std::string SpectrumDirectionMixTexture::ToString( ) const
    {
        return StringPrintf( "[ SpectrumDirectionMixTexture tex1: %s tex2: %s dir: %s ]", tex1,
            tex2, dir );
    }

    FloatDirectionMixTexture* FloatDirectionMixTexture::Create(
        const Transform& renderFromTexture, const TextureParameterDictionary& parameters,
        const FileLoc* loc, Allocator alloc )
    {
        Vector3f::Simd dir = parameters.GetOneVector3f( "dir", Vector3f( 0, 1, 0 ) );
        dir = Normalize( renderFromTexture( dir ) );
        return alloc.new_object<FloatDirectionMixTexture>(
            parameters.GetFloatTexture( "tex1", 0.f, alloc ),
            parameters.GetFloatTexture( "tex2", 1.f, alloc ), dir );
    }

    SpectrumDirectionMixTexture* SpectrumDirectionMixTexture::Create(
        const Transform& renderFromTexture, const TextureParameterDictionary& parameters,
        SpectrumType spectrumType, const FileLoc* loc, Allocator alloc )
    {
        Spectrum zero = alloc.new_object<ConstantSpectrum>( 0. );
        Spectrum one = alloc.new_object<ConstantSpectrum>( 1. );
        Vector3f::Simd dir = parameters.GetOneVector3f( "dir", Vector3f( 0, 1, 0 ) );
        dir = Normalize( renderFromTexture( dir ) );
        return alloc.new_object<SpectrumDirectionMixTexture>(
            parameters.GetSpectrumTexture( "tex1", zero, spectrumType, alloc ),
            parameters.GetSpectrumTexture( "tex2", one, spectrumType, alloc ), dir );
    }

    static std::mutex ptexMutex;
    static Ptex::PtexCache* cache;

    NSTAT_COUNTER( "Texture/Ptex lookups", nLookups );
    NSTAT_COUNTER( "Texture/Ptex files accessed", nFilesAccessed );
    NSTAT_COUNTER( "Texture/Ptex block reads", nBlockReads );
    NSTAT_MEMORY_COUNTER( "Memory/Ptex peak memory used", peakMemoryUsed );
    NSTAT_MEMORY_COUNTER( "Memory/GPU Ptex memory used", gpuPtexMemoryUsed );
    NSTAT_RATIO( "Texture/Ptex file cache hits", ptexCacheHits, ptexCacheLookups );

    struct : public PtexErrorHandler
    {
        void reportError( const char* error ) override { Error( "%s", error ); }
    } errorHandler;

    // PtexTexture Method Definitions

    PtexTextureBase::PtexTextureBase( const std::string& filename, ColorEncoding encoding,
        Float scale )
        : filename( filename ), encoding( encoding ), scale( scale )
    {
        ptexMutex.lock( );
        if ( !cache )
        {
            int maxFiles = 100;
            size_t maxMem = 1ull << 32;  // 4GB
            bool premultiply = true;

            cache = Ptex::PtexCache::create( maxFiles, maxMem, premultiply, nullptr,
                &errorHandler );
            // TODO? cache->setSearchPath(...);
        }
        ptexMutex.unlock( );

        // Issue an error if the texture doesn't exist or has an unsupported
        // number of channels.
        valid = false;
        Ptex::String error;
        Ptex::PtexTexture* texture = cache->get( filename.c_str( ), error );
        if ( !texture )
            Error( "%s", error );
        else
        {
            if ( texture->numChannels( ) != 1 && texture->numChannels( ) != 3 )
                Error( "%s: only one and three channel ptex textures are supported", filename );
            else
                valid = true;
            texture->release( );
        }
    }

    void PtexTextureBase::ReportStats( )
    {
        if ( !cache )
            return;

        Ptex::PtexCache::Stats stats;
        cache->getStats( stats );

        nFilesAccessed += stats.filesAccessed;
        nBlockReads += stats.blockReads;
        peakMemoryUsed = std::max( peakMemoryUsed, int64_t( stats.peakMemUsed ) );
    }

    int PtexTextureBase::SampleTexture( TextureEvalContext ctx, float result[ 3 ] ) const
    {
        if ( !valid )
        {
            result[ 0 ] = 0.;
            return 1;
        }

        ++nLookups;
        Ptex::String error;
        Ptex::PtexTexture* texture = cache->get( filename.c_str( ), error );
        NCHECK( texture );
        // TODO: make the filter an option?
        Ptex::PtexFilter::Options opts( Ptex::PtexFilter::FilterType::f_bspline );
        Ptex::PtexFilter* filter = Ptex::PtexFilter::getFilter( texture, opts );
        int nc = texture->numChannels( );

        int firstChan = 0;
        filter->eval( result, firstChan, nc, ctx.faceIndex, ctx.uv[ 0 ], ctx.uv[ 1 ], ctx.dudx,
            ctx.dvdx, ctx.dudy, ctx.dvdy );
        filter->release( );
        texture->release( );

        if ( encoding != ColorEncoding::Linear )
        {
            // It feels a little dirty to convert to 8-bits to run through the
            // encoding, but it's probably fine.
            uint8_t result8[ 3 ];
            for ( int i = 0; i < nc; ++i )
                result8[ i ] = uint8_t( Clamp( result[ i ] * 255.f + 0.5f, 0, 255 ) );

            // Handle Float == double.
            Float fResult[ 3 ];
            encoding.ToLinear( pstdo::MakeConstSpan( result8, nc ), pstdo::MakeSpan( fResult, nc ) );
            for ( int c = 0; c < nc; ++c )
                result[ c ] = fResult[ c ];
        }

        for ( int c = 0; c < nc; ++c )
            result[ c ] *= scale;

        return nc;
    }

    std::string PtexTextureBase::BaseToString( ) const
    {
        return StringPrintf( "valid: %s filename: %s encoding: %s scale: %f", valid, filename,
            encoding, scale );
    }

    std::string FloatPtexTexture::ToString( ) const
    {
        return StringPrintf( "[ FloatPtexTexture %s ]", BaseToString( ) );
    }

    std::string SpectrumPtexTexture::ToString( ) const
    {
        return StringPrintf( "[ SpectrumPtexTexture %s ]", BaseToString( ) );
    }

    Float FloatPtexTexture::Evaluate( const TextureEvalContext& ctx ) const
    {
#ifdef PBRT_IS_GPU_CODE
        NLOG_FATAL( "Ptex not supported with GPU renderer" );
        return 0;
#else
        float result[ 3 ];
        int nc = SampleTexture( ctx, result );
        if ( nc == 1 )
            return result[ 0 ];
        NDCHECK_EQ( 3, nc );
        return ( result[ 0 ] + result[ 1 ] + result[ 2 ] ) / 3;
#endif
    }

    SampledSpectrum SpectrumPtexTexture::Evaluate( const TextureEvalContext& ctx, const SampledWavelengths& lambda ) const
    {
#ifdef PBRT_IS_GPU_CODE
        NLOG_FATAL( "Ptex not supported with GPU renderer" );
        return SampledSpectrum( 0 );
#else
        float result[ 3 ];
        int nc = SampleTexture( ctx, result );
        if ( nc == 1 )
            return SampledSpectrum( result[ 0 ] );
        NDCHECK_EQ( 3, nc );
        RGB rgb( result[ 0 ], result[ 1 ], result[ 2 ] );
        if ( spectrumType == SpectrumType::Unbounded )
            return RGBUnboundedSpectrum( *RGBColorSpace::sRGB, rgb ).Sample( lambda );
        else if ( spectrumType == SpectrumType::Albedo )
            return RGBAlbedoSpectrum( *RGBColorSpace::sRGB, Clamp( rgb, 0, 1 ) ).Sample( lambda );
        else
            return RGBIlluminantSpectrum( *RGBColorSpace::sRGB, rgb ).Sample( lambda );
#endif
    }

    FloatPtexTexture* FloatPtexTexture::Create( const Transform& renderFromTexture,
        const TextureParameterDictionary& parameters,
        const FileLoc* loc, Allocator alloc )
    {
        std::string filename = ResolveFilename( parameters.GetOneString( "filename", "" ) );
        std::string encodingString = parameters.GetOneString( "encoding", "gamma 2.2" );
        ColorEncoding encoding = ColorEncoding::Get( encodingString, alloc );
        Float scale = parameters.GetOneFloat( "scale", 1.f );
        return alloc.new_object<FloatPtexTexture>( filename, encoding, scale );
    }

    SpectrumPtexTexture* SpectrumPtexTexture::Create(
        const Transform& renderFromTexture, const TextureParameterDictionary& parameters,
        SpectrumType spectrumType, const FileLoc* loc, Allocator alloc )
    {
        std::string filename = ResolveFilename( parameters.GetOneString( "filename", "" ) );
        std::string encodingString = parameters.GetOneString( "encoding", "gamma 2.2" );
        ColorEncoding encoding = ColorEncoding::Get( encodingString, alloc );
        Float scale = parameters.GetOneFloat( "scale", 1.f );
        return alloc.new_object<SpectrumPtexTexture>( filename, encoding, scale, spectrumType );
    }

    GPUFloatPtexTexture::GPUFloatPtexTexture( const std::string& filename,
        ColorEncoding encoding, Float scale,
        Allocator alloc )
        : faceValues( alloc )
    {
        FloatPtexTexture tex( filename, encoding, scale );

        Ptex::String error;
        Ptex::PtexTexture* texture = cache->get( filename.c_str( ), error );
        NCHECK( texture );
        int nFaces = texture->getInfo( ).numFaces;
        texture->release( );

        faceValues.resize( nFaces );
        for ( int i = 0; i < nFaces; ++i )
        {
            Float filterWidth = 0.75f;
            TextureEvalContext ctx( Point3f( ), Vector3f( ), Vector3f( ), Normal3f( ),
                Point2f( 0.5f, 0.5f ), filterWidth, filterWidth, filterWidth,
                filterWidth, i );
            faceValues[ i ] = Evaluate( ctx );
        }

        gpuPtexMemoryUsed += nFaces * sizeof( faceValues[ 0 ] );
    }

    static std::mutex ptexCacheMutex;
    static std::map<std::tuple<std::string, std::string, Float>, GPUFloatPtexTexture*>
        ptexFloatTextureCache;

    GPUFloatPtexTexture* GPUFloatPtexTexture::Create(
        const Transform& renderFromTexture, const TextureParameterDictionary& parameters,
        const FileLoc* loc, Allocator alloc )
    {
        std::string filename = ResolveFilename( parameters.GetOneString( "filename", "" ) );
        std::string encodingString = parameters.GetOneString( "encoding", "gamma 2.2" );
        Float scale = parameters.GetOneFloat( "scale", 1.f );

        auto key = std::make_tuple( filename, encodingString, scale );
        ++ptexCacheLookups;
        ptexCacheMutex.lock( );
        if ( auto iter = ptexFloatTextureCache.find( key );
            iter != ptexFloatTextureCache.end( ) )
        {
            GPUFloatPtexTexture* tex = iter->second;
            ptexCacheMutex.unlock( );
            ++ptexCacheHits;
            return tex;
        }
        else
        {
            ptexCacheMutex.unlock( );
            ColorEncoding encoding = ColorEncoding::Get( encodingString, alloc );
            GPUFloatPtexTexture* tex =
                alloc.new_object<GPUFloatPtexTexture>( filename, encoding, scale, alloc );

            ptexCacheMutex.lock( );
            NCHECK( ptexFloatTextureCache.find( key ) == ptexFloatTextureCache.end( ) );
            ptexFloatTextureCache[ key ] = tex;
            ptexCacheMutex.unlock( );
            return tex;
        }
    }

    std::string GPUFloatPtexTexture::ToString( ) const
    {
        return StringPrintf( "[ GPUFloatPtexTexture faceValues: %s ]", faceValues );
    }

    GPUSpectrumPtexTexture::GPUSpectrumPtexTexture( const std::string& filename,
        ColorEncoding encoding, Float scale,
        SpectrumType spectrumType, Allocator alloc )
        : spectrumType( spectrumType ), faceValues( alloc )
    {
        SpectrumPtexTexture tex( filename, encoding, scale, spectrumType );

        Ptex::String error;
        Ptex::PtexTexture* texture = cache->get( filename.c_str( ), error );
        NCHECK( texture );
        int nFaces = texture->getInfo( ).numFaces;
        texture->release( );

        faceValues.resize( nFaces );
        for ( int i = 0; i < nFaces; ++i )
        {
            Float filterWidth = 0.75f;
            TextureEvalContext ctx( Point3f( ), Vector3f( ), Vector3f( ), Normal3f( ),
                Point2f( 0.5f, 0.5f ), filterWidth, filterWidth, filterWidth,
                filterWidth, i );

            float result[ 3 ];
            int nc = tex.SampleTexture( ctx, result );
            if ( nc == 1 )
                result[ 1 ] = result[ 2 ] = result[ 0 ];
            else
                NDCHECK_EQ( 3, nc );

            faceValues[ i ] = RGB( result[ 0 ], result[ 1 ], result[ 2 ] );
        }

        gpuPtexMemoryUsed += nFaces * sizeof( faceValues[ 0 ] );
    }

    static std::map<std::tuple<std::string, std::string, Float>, GPUSpectrumPtexTexture*>
        ptexSpectrumTextureCache;

    GPUSpectrumPtexTexture* GPUSpectrumPtexTexture::Create(
        const Transform& renderFromTexture, const TextureParameterDictionary& parameters,
        SpectrumType spectrumType, const FileLoc* loc, Allocator alloc )
    {
        std::string filename = ResolveFilename( parameters.GetOneString( "filename", "" ) );
        std::string encodingString = parameters.GetOneString( "encoding", "gamma 2.2" );
        Float scale = parameters.GetOneFloat( "scale", 1.f );

        auto key = std::make_tuple( filename, encodingString, scale );
        ptexCacheMutex.lock( );
        if ( auto iter = ptexSpectrumTextureCache.find( key );
            iter != ptexSpectrumTextureCache.end( ) )
        {
            GPUSpectrumPtexTexture* tex = iter->second;
            ptexCacheMutex.unlock( );
            return tex;
        }
        else
        {
            ptexCacheMutex.unlock( );
            ColorEncoding encoding = ColorEncoding::Get( encodingString, alloc );
            GPUSpectrumPtexTexture* tex = alloc.new_object<GPUSpectrumPtexTexture>(
                filename, encoding, scale, spectrumType, alloc );

            ptexCacheMutex.lock( );
            NCHECK( ptexSpectrumTextureCache.find( key ) == ptexSpectrumTextureCache.end( ) );
            ptexSpectrumTextureCache[ key ] = tex;
            ptexCacheMutex.unlock( );
            return tex;
        }
    }

    std::string GPUSpectrumPtexTexture::ToString( ) const
    {
        return StringPrintf( "[ GPUSpectrumPtexTexture spectrumType: %s faceValues: %s ]",
            spectrumType, faceValues );
    }

    // ScaledTexture Method Definitions
    std::string FloatScaledTexture::ToString( ) const
    {
        return StringPrintf( "[ FloatScaledTexture tex: %s scale: %s ]", tex, scale );
    }

    std::string SpectrumScaledTexture::ToString( ) const
    {
        return StringPrintf( "[ SpectrumScaledTexture tex: %s scale: %s ]", tex, scale );
    }

    FloatTexture FloatScaledTexture::Create( const Transform& renderFromTexture,
        const TextureParameterDictionary& parameters,
        const FileLoc* loc, Allocator alloc )
    {
        FloatTexture tex = parameters.GetFloatTexture( "tex", 1.f, alloc );
        FloatTexture scale = parameters.GetFloatTexture( "scale", 1.f, alloc );

        for ( int i = 0; i < 2; ++i )
        {
            if ( FloatConstantTexture* cscale = scale.CastOrNullptr<FloatConstantTexture>( ) )
            {
                Float cs = cscale->Evaluate( {} );
                if ( cs == 1 )
                {
                    return tex;
                }
                else if ( FloatImageTexture* image =
                    tex.CastOrNullptr<FloatImageTexture>( ) )
                {
                    FloatImageTexture* imageCopy =
                        alloc.new_object<FloatImageTexture>( *image );
                    imageCopy->MultiplyScale( cs );
                    return imageCopy;
                }
#if defined(PBRT_BUILD_GPU_RENDERER)
                else if ( GPUFloatImageTexture* gimage =
                    tex.CastOrNullptr<GPUFloatImageTexture>( ) )
                {
                    GPUFloatImageTexture* gimageCopy =
                        alloc.new_object<GPUFloatImageTexture>( *gimage );
                    gimageCopy->MultiplyScale( cs );
                    return gimageCopy;
                }
#endif
            }
            std::swap( tex, scale );
        }

        std::swap( tex, scale );
        return alloc.new_object<FloatScaledTexture>( tex, scale );
    }

    SpectrumTexture SpectrumScaledTexture::Create(
        const Transform& renderFromTexture, const TextureParameterDictionary& parameters,
        SpectrumType spectrumType, const FileLoc* loc, Allocator alloc )
    {
        Spectrum one = alloc.new_object<ConstantSpectrum>( 1. );
        SpectrumTexture tex = parameters.GetSpectrumTexture( "tex", one, spectrumType, alloc );
        FloatTexture scale = parameters.GetFloatTexture( "scale", 1.f, alloc );

        if ( FloatConstantTexture* cscale = scale.CastOrNullptr<FloatConstantTexture>( ) )
        {
            Float cs = cscale->Evaluate( {} );
            if ( cs == 1 )
            {
                return tex;
            }
            else if ( SpectrumImageTexture* image =
                tex.CastOrNullptr<SpectrumImageTexture>( ) )
            {
                SpectrumImageTexture* imageCopy =
                    alloc.new_object<SpectrumImageTexture>( *image );
                imageCopy->MultiplyScale( cs );
                return imageCopy;
            }
#if defined(PBRT_BUILD_GPU_RENDERER)
            else if ( GPUSpectrumImageTexture* gimage =
                tex.CastOrNullptr<GPUSpectrumImageTexture>( ) )
            {
                GPUSpectrumImageTexture* gimageCopy =
                    alloc.new_object<GPUSpectrumImageTexture>( *gimage );
                gimageCopy->MultiplyScale( cs );
                return gimageCopy;
            }
#endif
        }

        return alloc.new_object<SpectrumScaledTexture>( tex, scale );
    }

    // WindyTexture Method Definitions
    std::string WindyTexture::ToString( ) const
    {
        return StringPrintf( "[ WindyTexture mapping: %s ]", mapping );
    }

    WindyTexture* WindyTexture::Create( const Transform& renderFromTexture,
        const TextureParameterDictionary& parameters,
        const FileLoc* loc, Allocator alloc )
    {
        // Initialize 3D texture mapping _map_ from _tp_
        TextureMapping3D map =
            TextureMapping3D::Create( parameters, renderFromTexture, loc, alloc );
        return alloc.new_object<WindyTexture>( map );
    }

    // WrinkledTexture Method Definitions
    std::string WrinkledTexture::ToString( ) const
    {
        return StringPrintf( "[ WrinkledTexture mapping: %s octaves: %d "
            "omega: %f ]",
            mapping, octaves, omega );
    }

    WrinkledTexture* WrinkledTexture::Create( const Transform& renderFromTexture,
        const TextureParameterDictionary& parameters,
        const FileLoc* loc, Allocator alloc )
    {
        // Initialize 3D texture mapping _map_ from _tp_
        TextureMapping3D map =
            TextureMapping3D::Create( parameters, renderFromTexture, loc, alloc );
        return alloc.new_object<WrinkledTexture>( map, parameters.GetOneInt( "octaves", 8 ),
            parameters.GetOneFloat( "roughness", .5f ) );
    }

#if defined(PBRT_BUILD_GPU_RENDERER)

    struct LuminanceTextureCacheItem
    {
        cudaMipmappedArray_t mipArray;
        cudaTextureReadMode readMode;
        int nMIPMapLevels;
        bool originallySingleChannel;
    };

    struct RGBTextureCacheItem
    {
        cudaMipmappedArray_t mipArray;
        cudaTextureReadMode readMode;
        int nMIPMapLevels;
        const RGBColorSpace* colorSpace;
    };

    static std::mutex textureCacheMutex;
    static std::map<std::string, LuminanceTextureCacheItem> lumTextureCache;
    static std::map<std::string, RGBTextureCacheItem> rgbTextureCache;

    STAT_MEMORY_COUNTER( "Memory/ImageTextures", gpuImageTextureBytes );

    static cudaMipmappedArray_t createSingleChannelTextureArray(
        const Image& image, const RGBColorSpace* colorSpace, int* nMIPMapLevels )
    {
        NCHECK_EQ( 1, image.NChannels( ) );
        cudaMipmappedArray_t mipArray;

        cudaChannelFormatDesc channelDesc;
        switch ( image.Format( ) )
        {
            case PixelFormat::U256:
                channelDesc = cudaCreateChannelDesc( 8, 0, 0, 0, cudaChannelFormatKindUnsigned );
                break;
            case PixelFormat::Half:
                channelDesc = cudaCreateChannelDesc( 16, 0, 0, 0, cudaChannelFormatKindFloat );
                break;
            case PixelFormat::Float:
                channelDesc = cudaCreateChannelDesc( 32, 0, 0, 0, cudaChannelFormatKindFloat );
                break;
            default:
                NLOG_FATAL( "Unhandled PixelFormat" );
        }

        MIPMap mipmap( image, colorSpace, WrapMode::Clamp /* TODO */, Allocator( ),
            MIPMapFilterOptions( ) );
        *nMIPMapLevels = mipmap.Levels( );

        const Image& baseImage = mipmap.GetLevel( 0 );
        cudaExtent extent =
            make_cudaExtent( baseImage.Resolution( ).x, baseImage.Resolution( ).y, 0 );
        CUDA_CHECK( cudaMallocMipmappedArray( &mipArray, &channelDesc, extent, mipmap.Levels( ),
            0 /* flags */ ) );

        for ( int level = 0; level < mipmap.Levels( ); ++level )
        {
            const Image& levelImage = mipmap.GetLevel( level );
            cudaArray_t levelArray;
            CUDA_CHECK( cudaGetMipmappedArrayLevel( &levelArray, mipArray, level ) );

            int pitch;
            switch ( image.Format( ) )
            {
                case PixelFormat::U256:
                    pitch = levelImage.Resolution( ).x * sizeof( uint8_t );
                    break;
                case PixelFormat::Half:
                    pitch = levelImage.Resolution( ).x * sizeof( Half );
                    break;
                case PixelFormat::Float:
                    pitch = levelImage.Resolution( ).x * sizeof( float );
                    break;
                default:
                    NLOG_FATAL( "Unhandled PixelFormat" );
            }

            gpuImageTextureBytes += pitch * levelImage.Resolution( ).y;

            CUDA_CHECK( cudaMemcpy2DToArray(
                levelArray, /* offset */ 0, 0, levelImage.RawPointer( { 0, 0 } ), pitch, pitch,
                levelImage.Resolution( ).y, cudaMemcpyHostToDevice ) );
        }

        return mipArray;
    }

    static cudaTextureAddressMode convertAddressMode( const std::string& mode )
    {
        if ( mode == "repeat" )
            return cudaAddressModeWrap;
        else if ( mode == "clamp" )
            return cudaAddressModeClamp;
        else if ( mode == "black" )
            return cudaAddressModeBorder;
        else
            ErrorExit( "%s: texture wrap mode not supported", mode );
    }

    GPUSpectrumImageTexture* GPUSpectrumImageTexture::Create(
        const Transform& renderFromTexture, const TextureParameterDictionary& parameters,
        SpectrumType spectrumType, const FileLoc* loc, Allocator alloc )
    {
        // Initialize _ImageTexture_ parameters
        Float maxAniso = parameters.GetOneFloat( "maxanisotropy", 8.f );
        std::string filter = parameters.GetOneString( "filter", "bilinear" );
        MIPMapFilterOptions filterOptions;
        filterOptions.maxAnisotropy = maxAniso;
        pstdo::optional<FilterFunction> ff = ParseFilter( filter );
        if ( ff )
            filterOptions.filter = *ff;
        else
            Error( loc, "%s: filter function unknown", filter );

        std::string wrapString = parameters.GetOneString( "wrap", "repeat" );
        pstdo::optional<WrapMode> wrapMode = ParseWrapMode( wrapString.c_str( ) );
        if ( !wrapMode )
            ErrorExit( "%s: wrap mode unknown", wrapString );
        Float scale = parameters.GetOneFloat( "scale", 1.f );
        bool invert = parameters.GetOneBool( "invert", false );
        std::string filename = ResolveFilename( parameters.GetOneString( "filename", "" ) );

        const char* defaultEncoding = HasExtension( filename, "png" ) ? "sRGB" : "linear";
        std::string encodingString = parameters.GetOneString( "encoding", defaultEncoding );
        ColorEncoding encoding = ColorEncoding::Get( encodingString, alloc );

        // These have to be initialized one way or another in the below
        cudaMipmappedArray_t mipArray;
        int nMIPMapLevels = 0;
        cudaTextureReadMode readMode;
        const RGBColorSpace* colorSpace = nullptr;
        bool isSingleChannel = false;

        textureCacheMutex.lock( );
        auto rgbIter = rgbTextureCache.find( filename );
        if ( rgbIter != rgbTextureCache.end( ) )
        {
            NLOG_VERBOSE( "Found %s in RGB tex array cache!", filename );
            mipArray = rgbIter->second.mipArray;
            readMode = rgbIter->second.readMode;
            nMIPMapLevels = rgbIter->second.nMIPMapLevels;
            colorSpace = rgbIter->second.colorSpace;
            textureCacheMutex.unlock( );
        }
        else
        {
            auto lumIter = lumTextureCache.find( filename );
            // We don't want to take it if it was originally an RGB texture and
            // GPUFloatImageTexture converted it to single channel
            if ( lumIter != lumTextureCache.end( ) && lumIter->second.originallySingleChannel )
            {
                NLOG_VERBOSE( "Found %s in luminance tex array cache!", filename );
                mipArray = lumIter->second.mipArray;
                readMode = lumIter->second.readMode;
                nMIPMapLevels = lumIter->second.nMIPMapLevels;
                colorSpace = RGBColorSpace::sRGB;
                textureCacheMutex.unlock( );
                isSingleChannel = true;
            }
            else
            {
                textureCacheMutex.unlock( );

                {
                    ImageAndMetadata immeta = Image::Read( filename );
                    Image& image = immeta.image;

                    readMode = image.Format( ) == PixelFormat::U256
                        ? cudaReadModeNormalizedFloat
                        : cudaReadModeElementType;
                    colorSpace = immeta.metadata.GetColorSpace( );

                    ImageChannelDesc rgbDesc = image.GetChannelDesc( { "R", "G", "B" } );
                    if ( rgbDesc )
                    {
                        image = image.SelectChannels( rgbDesc );

                        MIPMap mipmap( image, colorSpace, WrapMode::Clamp /* TODO */,
                            Allocator( ), MIPMapFilterOptions( ) );
                        nMIPMapLevels = mipmap.Levels( );
                        const Image& baseImage = mipmap.GetLevel( 0 );

                        switch ( image.Format( ) )
                        {
                            case PixelFormat::U256:
                            {
                                cudaChannelFormatDesc channelDesc = cudaCreateChannelDesc(
                                    8, 8, 8, 8, cudaChannelFormatKindUnsigned );

                                cudaExtent extent = make_cudaExtent( baseImage.Resolution( ).x,
                                    baseImage.Resolution( ).y, 0 );
                                CUDA_CHECK( cudaMallocMipmappedArray( &mipArray, &channelDesc,
                                    extent, mipmap.Levels( ),
                                    0 /* flags */ ) );
                                for ( int level = 0; level < mipmap.Levels( ); ++level )
                                {
                                    const Image& levelImage = mipmap.GetLevel( level );
                                    cudaArray_t levelArray;
                                    CUDA_CHECK(
                                        cudaGetMipmappedArrayLevel( &levelArray, mipArray, level ) );

                                    std::vector<uint8_t> rgba( 4 * levelImage.Resolution( ).x *
                                        levelImage.Resolution( ).y );
                                    size_t offset = 0;
                                    for ( int y = 0; y < levelImage.Resolution( ).y; ++y )
                                        for ( int x = 0; x < levelImage.Resolution( ).x; ++x )
                                        {
                                            for ( int c = 0; c < 3; ++c )
                                                rgba[ offset++ ] =
                                                ( ( uint8_t* )levelImage.RawPointer( { x, y } ) )[ c ];
                                            rgba[ offset++ ] = 255;
                                        }

                                    int pitch = levelImage.Resolution( ).x * 4 * sizeof( uint8_t );
                                    gpuImageTextureBytes += pitch * levelImage.Resolution( ).y;

                                    CUDA_CHECK( cudaMemcpy2DToArray(
                                        levelArray,
                                        /* offset */ 0, 0, rgba.data( ), pitch, pitch,
                                        levelImage.Resolution( ).y, cudaMemcpyHostToDevice ) );
                                }
                                break;
                            }
                            case PixelFormat::Half:
                            {
                                cudaChannelFormatDesc channelDesc = cudaCreateChannelDesc(
                                    16, 16, 16, 16, cudaChannelFormatKindFloat );

                                cudaExtent extent = make_cudaExtent( baseImage.Resolution( ).x,
                                    baseImage.Resolution( ).y, 0 );
                                CUDA_CHECK( cudaMallocMipmappedArray( &mipArray, &channelDesc,
                                    extent, mipmap.Levels( ),
                                    0 /* flags */ ) );

                                for ( int level = 0; level < mipmap.Levels( ); ++level )
                                {
                                    const Image& levelImage = mipmap.GetLevel( level );
                                    cudaArray_t levelArray;
                                    CUDA_CHECK(
                                        cudaGetMipmappedArrayLevel( &levelArray, mipArray, level ) );

                                    std::vector<Half> rgba( 4 * levelImage.Resolution( ).x *
                                        levelImage.Resolution( ).y );

                                    size_t offset = 0;
                                    for ( int y = 0; y < levelImage.Resolution( ).y; ++y )
                                        for ( int x = 0; x < levelImage.Resolution( ).x; ++x )
                                        {
                                            for ( int c = 0; c < 3; ++c )
                                                rgba[ offset++ ] =
                                                Half( levelImage.GetChannel( { x, y }, c ) );
                                            rgba[ offset++ ] = Half( 1.f );
                                        }

                                    int pitch = levelImage.Resolution( ).x * 4 * sizeof( Half );
                                    gpuImageTextureBytes += pitch * levelImage.Resolution( ).y;

                                    CUDA_CHECK( cudaMemcpy2DToArray(
                                        levelArray,
                                        /* offset */ 0, 0, rgba.data( ), pitch, pitch,
                                        levelImage.Resolution( ).y, cudaMemcpyHostToDevice ) );
                                }
                                break;
                            }
                            case PixelFormat::Float:
                            {
                                cudaChannelFormatDesc channelDesc = cudaCreateChannelDesc(
                                    32, 32, 32, 32, cudaChannelFormatKindFloat );

                                cudaExtent extent = make_cudaExtent( baseImage.Resolution( ).x,
                                    baseImage.Resolution( ).y, 0 );
                                CUDA_CHECK( cudaMallocMipmappedArray( &mipArray, &channelDesc,
                                    extent, mipmap.Levels( ),
                                    0 /* flags */ ) );

                                for ( int level = 0; level < mipmap.Levels( ); ++level )
                                {
                                    const Image& levelImage = mipmap.GetLevel( level );
                                    cudaArray_t levelArray;
                                    CUDA_CHECK(
                                        cudaGetMipmappedArrayLevel( &levelArray, mipArray, level ) );

                                    std::vector<float> rgba( 4 * levelImage.Resolution( ).x *
                                        levelImage.Resolution( ).y );

                                    size_t offset = 0;
                                    for ( int y = 0; y < levelImage.Resolution( ).y; ++y )
                                        for ( int x = 0; x < levelImage.Resolution( ).x; ++x )
                                        {
                                            for ( int c = 0; c < 3; ++c )
                                                rgba[ offset++ ] = levelImage.GetChannel( { x, y }, c );
                                            rgba[ offset++ ] = 1.f;
                                        }

                                    int pitch = levelImage.Resolution( ).x * 4 * sizeof( float );
                                    gpuImageTextureBytes += pitch * levelImage.Resolution( ).y;

                                    CUDA_CHECK( cudaMemcpy2DToArray(
                                        levelArray,
                                        /* offset */ 0, 0, rgba.data( ), pitch, pitch,
                                        levelImage.Resolution( ).y, cudaMemcpyHostToDevice ) );
                                }
                                break;
                            }
                            default:
                                NLOG_FATAL( "Unexpected PixelFormat" );
                        }

                        textureCacheMutex.lock( );
                        rgbTextureCache[ filename ] = RGBTextureCacheItem{
                            mipArray, readMode, nMIPMapLevels, colorSpace };
                        textureCacheMutex.unlock( );
                    }
                    else if ( image.NChannels( ) == 1 )
                    {
                        mipArray = createSingleChannelTextureArray( image, colorSpace,
                            &nMIPMapLevels );

                        textureCacheMutex.lock( );
                        lumTextureCache[ filename ] = LuminanceTextureCacheItem{
                            mipArray, readMode, nMIPMapLevels, true };
                        textureCacheMutex.unlock( );
                        isSingleChannel = true;
                    }
                    else
                    {
                        Warning( loc, "%s: unable to decipher image format", filename );
                        return nullptr;
                    }
                }  // profile scope
            }
        }

        cudaResourceDesc resDesc = {};
        resDesc.resType = cudaResourceTypeMipmappedArray;
        resDesc.res.mipmap.mipmap = mipArray;

        cudaTextureDesc texDesc = {};
        texDesc.addressMode[ 0 ] = convertAddressMode( wrapString );
        texDesc.addressMode[ 1 ] = convertAddressMode( wrapString );
        texDesc.filterMode = filter == "point" ? cudaFilterModePoint : cudaFilterModeLinear;
        texDesc.readMode = readMode;
        texDesc.normalizedCoords = 1;
        texDesc.maxAnisotropy = Clamp( maxAniso, 1, 16 );
        texDesc.maxMipmapLevelClamp = nMIPMapLevels - 1;
        texDesc.minMipmapLevelClamp = 0;
        texDesc.mipmapFilterMode =
            ( filter == "trilinear" || filter == "ewa" || filter == "EWA" )
            ? cudaFilterModeLinear
            : cudaFilterModePoint;
        texDesc.borderColor[ 0 ] = texDesc.borderColor[ 1 ] = texDesc.borderColor[ 2 ] =
            texDesc.borderColor[ 3 ] = 0.f;
        texDesc.sRGB = 1;

        cudaTextureObject_t texObj;
        CUDA_CHECK( cudaCreateTextureObject( &texObj, &resDesc, &texDesc, nullptr ) );

        TextureMapping2D mapping =
            TextureMapping2D::Create( parameters, renderFromTexture, loc, alloc );

        return alloc.new_object<GPUSpectrumImageTexture>( filename, mapping, texObj, scale,
            invert, isSingleChannel, colorSpace,
            spectrumType );
    }

    std::string GPUSpectrumImageTexture::ToString( ) const
    {
        return StringPrintf(
            "[ GPUSpectrumImageTexture filename: %s mapping: %s scale: %f invert: %s ]",
            filename, mapping, scale, invert );
    }

    GPUFloatImageTexture* GPUFloatImageTexture::Create(
        const Transform& renderFromTexture, const TextureParameterDictionary& parameters,
        const FileLoc* loc, Allocator alloc )
    {
        // Initialize _ImageTexture_ parameters
        Float maxAniso = parameters.GetOneFloat( "maxanisotropy", 8.f );
        std::string filter = parameters.GetOneString( "filter", "bilinear" );
        MIPMapFilterOptions filterOptions;
        filterOptions.maxAnisotropy = maxAniso;
        pstdo::optional<FilterFunction> ff = ParseFilter( filter );
        if ( ff )
            filterOptions.filter = *ff;
        else
            Error( loc, "%s: filter function unknown", filter );

        std::string wrapString = parameters.GetOneString( "wrap", "repeat" );
        pstdo::optional<WrapMode> wrapMode = ParseWrapMode( wrapString.c_str( ) );
        if ( !wrapMode )
            ErrorExit( "%s: wrap mode unknown", wrapString );
        Float scale = parameters.GetOneFloat( "scale", 1.f );
        bool invert = parameters.GetOneBool( "invert", false );
        std::string filename = ResolveFilename( parameters.GetOneString( "filename", "" ) );

        const char* defaultEncoding = HasExtension( filename, "png" ) ? "sRGB" : "linear";
        std::string encodingString = parameters.GetOneString( "encoding", defaultEncoding );
        ColorEncoding encoding = ColorEncoding::Get( encodingString, alloc );

        cudaMipmappedArray_t mipArray;
        int nMIPMapLevels = 0;
        cudaTextureReadMode readMode;

        textureCacheMutex.lock( );
        auto iter = lumTextureCache.find( filename );
        if ( iter != lumTextureCache.end( ) )
        {
            NLOG_VERBOSE( "Found %s in luminance tex array cache!", filename );
            mipArray = iter->second.mipArray;
            readMode = iter->second.readMode;
            nMIPMapLevels = iter->second.nMIPMapLevels;
            textureCacheMutex.unlock( );
        }
        else
        {
            textureCacheMutex.unlock( );

            ImageAndMetadata immeta = Image::Read( filename );
            Image& image = immeta.image;
            const RGBColorSpace* colorSpace = immeta.metadata.GetColorSpace( );

            bool convertedImage = false;
            if ( image.NChannels( ) != 1 )
            {
                ImageChannelDesc rgbaDesc = image.GetChannelDesc( { "R", "G", "B", "A" } );
                ImageChannelDesc rgbDesc = image.GetChannelDesc( { "R", "G", "B" } );
                auto allOnes = [ & ]( ) {
                    for ( int y = 0; y < image.Resolution( ).y; ++y )
                        for ( int x = 0; x < image.Resolution( ).x; ++x )
                            if ( image.GetChannels( { x, y }, rgbaDesc )[ 3 ] != 1 )
                                return false;
                    return true;
                    };
                if ( rgbaDesc && !allOnes( ) )
                {
                    ImageChannelDesc alphaDesc = image.GetChannelDesc( { "A" } );
                    image = image.SelectChannels( alphaDesc );
                    convertedImage = true;
                }
                else if ( rgbDesc )
                {
                    // Convert to one channel
                    Image avgImage( image.Format( ), image.Resolution( ), { "Y" },
                        image.Encoding( ) );

                    for ( int y = 0; y < image.Resolution( ).y; ++y )
                        for ( int x = 0; x < image.Resolution( ).x; ++x )
                            avgImage.SetChannel( { x, y }, 0,
                                image.GetChannels( { x, y }, rgbDesc ).Average( ) );

                    image = std::move( avgImage );
                    convertedImage = true;
                }
                else
                    ErrorExit( loc, "%s: %d channel image, without RGB channels.", filename,
                        image.NChannels( ) );
            }

            mipArray = createSingleChannelTextureArray( image, colorSpace, &nMIPMapLevels );
            readMode = ( image.Format( ) == PixelFormat::U256 ) ? cudaReadModeNormalizedFloat
                : cudaReadModeElementType;

            textureCacheMutex.lock( );
            lumTextureCache[ filename ] =
                LuminanceTextureCacheItem{ mipArray, readMode, nMIPMapLevels, !convertedImage };
            textureCacheMutex.unlock( );
        }

        cudaResourceDesc resDesc = {};
        resDesc.resType = cudaResourceTypeMipmappedArray;
        resDesc.res.mipmap.mipmap = mipArray;

        cudaTextureDesc texDesc = {};
        texDesc.addressMode[ 0 ] = convertAddressMode( wrapString );
        texDesc.addressMode[ 1 ] = convertAddressMode( wrapString );
        texDesc.filterMode = filter == "point" ? cudaFilterModePoint : cudaFilterModeLinear;
        texDesc.readMode = readMode;
        texDesc.normalizedCoords = 1;
        texDesc.maxAnisotropy = Clamp( maxAniso, 1, 16 );
        texDesc.maxMipmapLevelClamp = nMIPMapLevels - 1;
        texDesc.minMipmapLevelClamp = 0;
        texDesc.mipmapFilterMode =
            ( filter == "trilinear" || filter == "ewa" || filter == "EWA" )
            ? cudaFilterModeLinear
            : cudaFilterModePoint;
        texDesc.borderColor[ 0 ] = texDesc.borderColor[ 1 ] = texDesc.borderColor[ 2 ] =
            texDesc.borderColor[ 3 ] = 0.f;
        texDesc.sRGB = 1;

        cudaTextureObject_t texObj;
        CUDA_CHECK( cudaCreateTextureObject( &texObj, &resDesc, &texDesc, nullptr ) );

        TextureMapping2D mapping =
            TextureMapping2D::Create( parameters, renderFromTexture, loc, alloc );

        return alloc.new_object<GPUFloatImageTexture>( filename, mapping, texObj, scale,
            invert );
    }

    std::string GPUFloatImageTexture::ToString( ) const
    {
        return StringPrintf(
            "[ GPUFloatImageTexture filename: %s mapping: %s scale: %f invert: %s ]",
            filename, mapping, scale, invert );
    }

#endif  // PBRT_BUILD_GPU_RENDERER

    NSTAT_COUNTER( "Scene/Textures", nTextures );

    FloatTexture FloatTexture::Create( const std::string& name,
        const Transform& renderFromTexture,
        const TextureParameterDictionary& parameters,
        const FileLoc* loc, Allocator alloc, bool gpu )
    {
        FloatTexture tex;
        if ( name == "constant" )
            tex = FloatConstantTexture::Create( renderFromTexture, parameters, loc, alloc );
        else if ( name == "scale" )
            tex = FloatScaledTexture::Create( renderFromTexture, parameters, loc, alloc );
        else if ( name == "mix" )
            tex = FloatMixTexture::Create( renderFromTexture, parameters, loc, alloc );
        else if ( name == "directionmix" )
            tex = FloatDirectionMixTexture::Create( renderFromTexture, parameters, loc, alloc );
        else if ( name == "bilerp" )
            tex = FloatBilerpTexture::Create( renderFromTexture, parameters, loc, alloc );
        else if ( name == "imagemap" )
        {
            if ( gpu )
                tex = GPUFloatImageTexture::Create( renderFromTexture, parameters, loc, alloc );
            else
                tex = FloatImageTexture::Create( renderFromTexture, parameters, loc, alloc );
        }
        else if ( name == "checkerboard" )
            tex = FloatCheckerboardTexture::Create( renderFromTexture, parameters, loc, alloc );
        else if ( name == "dots" )
            tex = FloatDotsTexture::Create( renderFromTexture, parameters, loc, alloc );
        else if ( name == "fbm" )
            tex = FBmTexture::Create( renderFromTexture, parameters, loc, alloc );
        else if ( name == "wrinkled" )
            tex = WrinkledTexture::Create( renderFromTexture, parameters, loc, alloc );
        else if ( name == "windy" )
            tex = WindyTexture::Create( renderFromTexture, parameters, loc, alloc );
        else if ( name == "ptex" )
        {
            if ( gpu )
                tex = GPUFloatPtexTexture::Create( renderFromTexture, parameters, loc, alloc );
            else
                tex = FloatPtexTexture::Create( renderFromTexture, parameters, loc, alloc );
        }
        else
            ErrorExit( loc, "%s: float texture type unknown.", name );

        if ( !tex )
            ErrorExit( loc, "%s: unable to create texture.", name );

        ++nTextures;

        parameters.ReportUnused( );
        return tex;
    }

    SpectrumTexture SpectrumTexture::Create( const std::string& name,
        const Transform& renderFromTexture,
        const TextureParameterDictionary& parameters,
        SpectrumType spectrumType, const FileLoc* loc,
        Allocator alloc, bool gpu )
    {
        SpectrumTexture tex;
        if ( name == "constant" )
            tex = SpectrumConstantTexture::Create( renderFromTexture, parameters, spectrumType,
                loc, alloc );
        else if ( name == "scale" )
            tex = SpectrumScaledTexture::Create( renderFromTexture, parameters, spectrumType,
                loc, alloc );
        else if ( name == "mix" )
            tex = SpectrumMixTexture::Create( renderFromTexture, parameters, spectrumType, loc,
                alloc );
        else if ( name == "directionmix" )
            tex = SpectrumDirectionMixTexture::Create( renderFromTexture, parameters,
                spectrumType, loc, alloc );
        else if ( name == "bilerp" )
            tex = SpectrumBilerpTexture::Create( renderFromTexture, parameters, spectrumType,
                loc, alloc );
        else if ( name == "imagemap" )
        {
            if ( gpu )
                tex = GPUSpectrumImageTexture::Create( renderFromTexture, parameters,
                    spectrumType, loc, alloc );
            else
                tex = SpectrumImageTexture::Create( renderFromTexture, parameters,
                    spectrumType, loc, alloc );
        }
        else if ( name == "checkerboard" )
            tex = SpectrumCheckerboardTexture::Create( renderFromTexture, parameters,
                spectrumType, loc, alloc );
        else if ( name == "dots" )
            tex = SpectrumDotsTexture::Create( renderFromTexture, parameters, spectrumType,
                loc, alloc );
        else if ( name == "marble" )
            tex = MarbleTexture::Create( renderFromTexture, parameters, loc, alloc );
        else if ( name == "ptex" )
        {
            if ( gpu )
                tex = GPUSpectrumPtexTexture::Create( renderFromTexture, parameters,
                    spectrumType, loc, alloc );
            else
                tex = SpectrumPtexTexture::Create( renderFromTexture, parameters, spectrumType,
                    loc, alloc );
        }
        else
            ErrorExit( loc, "%s: spectrum texture type unknown.", name );

        if ( !tex )
            ErrorExit( loc, "%s: unable to create texture.", name );

        ++nTextures;

        parameters.ReportUnused( );

        return tex;
    }

    

}
