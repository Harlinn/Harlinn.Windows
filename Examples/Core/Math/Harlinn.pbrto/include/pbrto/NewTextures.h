#pragma once
#ifndef PBRTO_NEWTEXTURES_H_
#define PBRTO_NEWTEXTURES_H_

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

#include <pbrto/base/NewTexture.h>
#include <pbrto/NewInteraction.h>
#include <pbrto/NewParamdict.h>
#include <pbrto/util/NewColorspace.h>
#include <pbrto/util/NewMath.h>
#include <pbrto/util/NewMipmap.h>
#include <pbrto/util/NewNoise.h>
#include <pbrto/util/NewSpectrum.h>
#include <pbrto/util/NewTaggedPtr.h>
#include <pbrto/util/NewTransform.h>
#include <pbrto/util/NewVecMath.h>

#include <initializer_list>
#include <map>
#include <mutex>
#include <string>

namespace pbrto
{

    // TextureEvalContext Definition
    struct TextureEvalContext
    {
        Point3f::Simd p;
        Vector3f::Simd dpdx, dpdy;
        Normal3f::Simd n;
        Point2f uv;
        Float dudx = 0, dudy = 0, dvdx = 0, dvdy = 0;
        int faceIndex = 0;

        // TextureEvalContext Public Methods
        TextureEvalContext( ) = default;
        TextureEvalContext( const Interaction& intr ) 
            : p( intr.p( ) ), uv( intr.uv ) 
        { }
        TextureEvalContext( const SurfaceInteraction& si )
            : p( si.p( ) ),
              dpdx( si.dpdx ),
              dpdy( si.dpdy ),
              n( si.n ),
              uv( si.uv ),
              dudx( si.dudx ),
              dudy( si.dudy ),
              dvdx( si.dvdx ),
              dvdy( si.dvdy ),
              faceIndex( si.faceIndex )
        {
        }
        TextureEvalContext( const Point3f::Simd& p, const Vector3f::Simd& dpdx, const Vector3f::Simd& dpdy, const Normal3f::Simd& n, const Point2f& uv, Float dudx, Float dudy, Float dvdx, Float dvdy, int faceIndex )
            : p( p ),
              dpdx( dpdx ),
              dpdy( dpdy ),
              n( n ),
              uv( uv ),
              dudx( dudx ),
              dudy( dudy ),
              dvdx( dvdx ),
              dvdy( dvdy ),
              faceIndex( faceIndex )
        {
        }

        std::string ToString( ) const;

        
    };

    // TexCoord2D Definition
    struct TexCoord2D
    {
        Point2f st;
        Float dsdx, dsdy, dtdx, dtdy;
        std::string ToString( ) const;
    };

    // TexCoord3D Definition
    struct TexCoord3D
    {
        Point3f::Simd p;
        Vector3f::Simd dpdx, dpdy;
        std::string ToString( ) const;
    };

    // UVMapping Definition
    class UVMapping
    {
        Float su, sv, du, dv;
    public:
        // UVMapping Public Methods
        UVMapping( Float su = 1, Float sv = 1, Float du = 0, Float dv = 0 )
            : su( su ), sv( sv ), du( du ), dv( dv )
        {
        }

        std::string ToString( ) const;

        TexCoord2D Map( const TextureEvalContext& ctx ) const
        {
            // Compute texture differentials for 2D $(u,v)$ mapping
            Float dsdx = su * ctx.dudx, dsdy = su * ctx.dudy;
            Float dtdx = sv * ctx.dvdx, dtdy = sv * ctx.dvdy;

            Point2f st( su * ctx.uv[ 0 ] + du, sv * ctx.uv[ 1 ] + dv );
            return TexCoord2D{ st, dsdx, dsdy, dtdx, dtdy };
        }
    };

    // SphericalMapping Definition
    class SphericalMapping
    {
        // SphericalMapping Private Members
        Transform textureFromRender;
    public:
        // SphericalMapping Public Methods
        SphericalMapping( const Transform& textureFromRender )
            : textureFromRender( textureFromRender )
        { }

        std::string ToString( ) const;

        TexCoord2D Map( const TextureEvalContext& ctx ) const
        {
            Point3f pt = textureFromRender( ctx.p );
            // Compute $\partial\,s/\partial\,\pt{}$ and $\partial\,t/\partial\,\pt{}$ for
            // spherical mapping
            Float x2y2 = Sqr( pt.x ) + Sqr( pt.y );
            Float sqrtx2y2 = Math::Sqrt( x2y2 );
            Vector3f::Simd dsdp = Vector3f::Simd( -pt.y, pt.x, 0 ) / ( 2 * Pi * x2y2 );
            Vector3f::Simd dtdp = 1 / ( Pi * ( x2y2 + Sqr( pt.z ) ) ) * Vector3f::Simd( pt.x * pt.z / sqrtx2y2, pt.y * pt.z / sqrtx2y2, -sqrtx2y2 );

            // Compute texture coordinate differentials for spherical mapping
            Vector3f::Simd dpdx = textureFromRender( ctx.dpdx );
            Vector3f::Simd dpdy = textureFromRender( ctx.dpdy );
            Float dsdx = ScalarDot( dsdp, dpdx ), dsdy = ScalarDot( dsdp, dpdy );
            Float dtdx = ScalarDot( dtdp, dpdx ), dtdy = ScalarDot( dtdp, dpdy );

            // Return $(s,t)$ texture coordinates and differentials based on spherical mapping
            Vector3f vec = Normalize( pt - Point3f( 0, 0, 0 ) );
            Point2f st( SphericalTheta( vec ) * InvPi, SphericalPhi( vec ) * Inv2Pi );
            return TexCoord2D{ st, dsdx, dsdy, dtdx, dtdy };
        }

    private:
        
    };

    // CylindricalMapping Definition
    class CylindricalMapping
    {
        // CylindricalMapping Private Members
        Transform textureFromRender;
    public:
        // CylindricalMapping Public Methods
        CylindricalMapping( const Transform& textureFromRender )
            : textureFromRender( textureFromRender )
        {
        }
        std::string ToString( ) const;

        TexCoord2D Map(const  TextureEvalContext& ctx ) const
        {
            Point3f pt = textureFromRender( ctx.p );
            // Compute texture coordinate differentials for cylinder $(u,v)$ mapping
            Float x2y2 = Sqr( pt.x ) + Sqr( pt.y );
            Vector3f::Simd dsdp = Vector3f::Simd( -pt.y, pt.x, 0 ) / ( 2 * Pi * x2y2 ),
                dtdp = Vector3f::Simd( 0, 0, 1 );
            Vector3f::Simd dpdx = textureFromRender( ctx.dpdx ), dpdy = textureFromRender( ctx.dpdy );
            Float dsdx = ScalarDot( dsdp, dpdx ), dsdy = ScalarDot( dsdp, dpdy );
            Float dtdx = ScalarDot( dtdp, dpdx ), dtdy = ScalarDot( dtdp, dpdy );

            Point2f st( ( Pi + Math::ATan2( pt.y, pt.x ) ) * Inv2Pi, pt.z );
            return TexCoord2D{ st, dsdx, dsdy, dtdx, dtdy };
        }

    private:
        
    };

    // PlanarMapping Definition
    class PlanarMapping
    {
        // PlanarMapping Private Members
        Transform textureFromRender;
        Vector3f::Simd vs, vt;
        Float ds, dt;
    public:
        // PlanarMapping Public Methods
        PlanarMapping( const Transform& textureFromRender, const Vector3f::Simd& vs, const Vector3f::Simd& vt, Float ds, Float dt )
            : textureFromRender( textureFromRender ), vs( vs ), vt( vt ), ds( ds ), dt( dt )
        { }

        TexCoord2D Map( const TextureEvalContext& ctx ) const
        {
            Vector3f::Simd vec( textureFromRender( ctx.p ) );
            // Initialize partial derivatives of planar mapping $(s,t)$ coordinates
            Vector3f::Simd dpdx = textureFromRender( ctx.dpdx );
            Vector3f::Simd dpdy = textureFromRender( ctx.dpdy );
            Float dsdx = ScalarDot( vs, dpdx ), dsdy = ScalarDot( vs, dpdy );
            Float dtdx = ScalarDot( vt, dpdx ), dtdy = ScalarDot( vt, dpdy );

            Point2f st( ds + ScalarDot( vec, vs ), dt + ScalarDot( vec, vt ) );
            return TexCoord2D{ st, dsdx, dsdy, dtdx, dtdy };
        }

        std::string ToString( ) const;

    private:
        
    };

    // TextureMapping2D Definition
    class TextureMapping2D : public TaggedPointer<UVMapping, SphericalMapping,
        CylindricalMapping, PlanarMapping>
    {
    public:
        // TextureMapping2D Interface
        using TaggedPointer::TaggedPointer;
        TextureMapping2D( TaggedPointer<UVMapping, SphericalMapping, CylindricalMapping, PlanarMapping> tp )
            : TaggedPointer( tp )
        {
        }

        static TextureMapping2D Create( const ParameterDictionary& parameters,
            const Transform& renderFromTexture, const FileLoc* loc,
            Allocator alloc );

        inline TexCoord2D Map( const TextureEvalContext& ctx ) const;
    };

    // TextureMapping2D Inline Functions
    inline TexCoord2D TextureMapping2D::Map( const TextureEvalContext& ctx ) const
    {
        auto map = [ & ]( auto ptr ) { return ptr->Map( ctx ); };
        return Dispatch( map );
    }

    // PointTransformMapping Definition
    class PointTransformMapping
    {
        Transform textureFromRender;
    public:
        // PointTransformMapping Public Methods
        PointTransformMapping( const Transform& textureFromRender )
            : textureFromRender( textureFromRender )
        {
        }

        std::string ToString( ) const;

        TexCoord3D Map( const TextureEvalContext& ctx ) const
        {
            return TexCoord3D{ textureFromRender( ctx.p ), textureFromRender( ctx.dpdx ), textureFromRender( ctx.dpdy ) };
        }

    private:
        
    };

    // TextureMapping3D Definition
    class TextureMapping3D : public TaggedPointer<PointTransformMapping>
    {
    public:
        // TextureMapping3D Interface
        using TaggedPointer::TaggedPointer;
        TextureMapping3D( TaggedPointer<PointTransformMapping> tp ) 
            :  TaggedPointer( tp ) 
        { }

        static TextureMapping3D Create( const ParameterDictionary& parameters, const Transform& renderFromTexture, const FileLoc* loc, Allocator alloc );

        TexCoord3D Map( const TextureEvalContext& ctx ) const;
    };

    inline TexCoord3D TextureMapping3D::Map( const TextureEvalContext& ctx ) const
    {
        auto map = [ & ]( auto ptr ) { return ptr->Map( ctx ); };
        return Dispatch( map );
    }

    // FloatConstantTexture Definition
    class FloatConstantTexture
    {
    public:
        FloatConstantTexture( Float value ) 
            : value( value ) 
        { }
        Float Evaluate( const TextureEvalContext& ctx ) const
        { 
            return value; 
        }
        // FloatConstantTexture Public Methods
        static FloatConstantTexture* Create( const Transform& renderFromTexture,
            const TextureParameterDictionary& parameters,
            const FileLoc* loc, Allocator alloc );

        std::string ToString( ) const;

    private:
        Float value;
    };

    // SpectrumConstantTexture Definition
    class SpectrumConstantTexture
    {
        Spectrum value;
    public:
        // SpectrumConstantTexture Public Methods
        SpectrumConstantTexture( Spectrum value ) : value( value ) {}

        SampledSpectrum Evaluate( const TextureEvalContext& ctx, const SampledWavelengths& lambda ) const
        {
            return value.Sample( lambda );
        }

        static SpectrumConstantTexture* Create( const Transform& renderFromTexture,
            const TextureParameterDictionary& parameters,
            SpectrumType spectrumType, const FileLoc* loc,
            Allocator alloc );
        std::string ToString( ) const;

    private:
        
    };

    // FloatBilerpTexture Definition
    class FloatBilerpTexture
    {
        // BilerpTexture Private Data
        TextureMapping2D mapping;
        Float v00, v01, v10, v11;
    public:
        FloatBilerpTexture( TextureMapping2D mapping, Float v00, Float v01, Float v10,
            Float v11 )
            : mapping( mapping ), v00( v00 ), v01( v01 ), v10( v10 ), v11( v11 )
        {
        }

        Float Evaluate( const TextureEvalContext& ctx ) const
        {
            TexCoord2D c = mapping.Map( ctx );
            return ( 1 - c.st[ 0 ] ) * ( 1 - c.st[ 1 ] ) * v00 + c.st[ 0 ] * ( 1 - c.st[ 1 ] ) * v10 +
                ( 1 - c.st[ 0 ] ) * c.st[ 1 ] * v01 + c.st[ 0 ] * c.st[ 1 ] * v11;
        }

        static FloatBilerpTexture* Create( const Transform& renderFromTexture,
            const TextureParameterDictionary& parameters,
            const FileLoc* loc, Allocator alloc );

        std::string ToString( ) const;

    private:
        
    };

    // SpectrumBilerpTexture Definition
    class SpectrumBilerpTexture
    {
        // BilerpTexture Private Data
        TextureMapping2D mapping;
        Spectrum v00, v01, v10, v11;
    public:
        SpectrumBilerpTexture( TextureMapping2D mapping, Spectrum v00, Spectrum v01, Spectrum v10, Spectrum v11 )
            : mapping( mapping ), v00( v00 ), v01( v01 ), v10( v10 ), v11( v11 )
        {
        }

        SampledSpectrum Evaluate( const TextureEvalContext& ctx, const SampledWavelengths& lambda ) const
        {
            TexCoord2D c = mapping.Map( ctx );
            return Bilerp( { c.st[ 0 ], c.st[ 1 ] }, { v00.Sample( lambda ), v10.Sample( lambda ),
                                               v01.Sample( lambda ), v11.Sample( lambda ) } );
        }

        static SpectrumBilerpTexture* Create( const Transform& renderFromTexture,
            const TextureParameterDictionary& parameters,
            SpectrumType spectrumType, const FileLoc* loc,
            Allocator alloc );

        std::string ToString( ) const;

    private:
        
    };

    Float Checkerboard( const TextureEvalContext& ctx, TextureMapping2D map2D, TextureMapping3D map3D );

    class FloatCheckerboardTexture
    {
        TextureMapping2D map2D;
        TextureMapping3D map3D;
        FloatTexture tex[ 2 ];
    public:
        FloatCheckerboardTexture( TextureMapping2D map2D, TextureMapping3D map3D, FloatTexture tex1, FloatTexture tex2 )
            : map2D( map2D ), map3D( map3D ), tex{ tex1, tex2 }
        {
        }

        Float Evaluate( const TextureEvalContext& ctx ) const
        {
            Float w = Checkerboard( ctx, map2D, map3D );
            Float t0 = 0, t1 = 0;
            if ( w != 1 )
                t0 = tex[ 0 ].Evaluate( ctx );
            if ( w != 0 )
                t1 = tex[ 1 ].Evaluate( ctx );
            return ( 1 - w ) * t0 + w * t1;
        }

        static FloatCheckerboardTexture* Create( const Transform& renderFromTexture,
            const TextureParameterDictionary& parameters,
            const FileLoc* loc, Allocator alloc );

        std::string ToString( ) const;

    private:
        
    };

    // SpectrumCheckerboardTexture Definition
    class SpectrumCheckerboardTexture
    {
        // SpectrumCheckerboardTexture Private Members
        TextureMapping2D map2D;
        TextureMapping3D map3D;
        SpectrumTexture tex[ 2 ];
    public:
        // SpectrumCheckerboardTexture Public Methods
        SpectrumCheckerboardTexture( TextureMapping2D map2D, TextureMapping3D map3D, SpectrumTexture tex1, SpectrumTexture tex2 )
            : map2D( map2D ), map3D( map3D ), tex{ tex1, tex2 }
        {
        }

        static SpectrumCheckerboardTexture* Create(
            const Transform& renderFromTexture, const TextureParameterDictionary& parameters,
            SpectrumType spectrumType, const FileLoc* loc, Allocator alloc );

        std::string ToString( ) const;

        SampledSpectrum Evaluate( const TextureEvalContext& ctx, const SampledWavelengths& lambda ) const
        {
            Float w = Checkerboard( ctx, map2D, map3D );
            SampledSpectrum t0, t1;
            if ( w != 1 )
                t0 = tex[ 0 ].Evaluate( ctx, lambda );
            if ( w != 0 )
                t1 = tex[ 1 ].Evaluate( ctx, lambda );
            return ( 1 - w ) * t0 + w * t1;
        }

    private:
        
    };

    PBRT_CPU_GPU
        bool InsidePolkaDot( Point2f st );

    class FloatDotsTexture
    {
        // DotsTexture Private Data
        TextureMapping2D mapping;
        FloatTexture outsideDot, insideDot;
    public:
        FloatDotsTexture( TextureMapping2D mapping, FloatTexture outsideDot,
            FloatTexture insideDot )
            : mapping( mapping ), outsideDot( outsideDot ), insideDot( insideDot )
        {
        }

        Float Evaluate( const TextureEvalContext& ctx ) const
        {
            TexCoord2D c = mapping.Map( ctx );
            return InsidePolkaDot( c.st ) ? insideDot.Evaluate( ctx ) : outsideDot.Evaluate( ctx );
        }

        static FloatDotsTexture* Create( const Transform& renderFromTexture,
            const TextureParameterDictionary& parameters,
            const FileLoc* loc, Allocator alloc );

        std::string ToString( ) const;

    private:
        
    };

    // SpectrumDotsTexture Definition
    class SpectrumDotsTexture
    {
        // SpectrumDotsTexture Private Members
        TextureMapping2D mapping;
        SpectrumTexture outsideDot, insideDot;
    public:
        // SpectrumDotsTexture Public Methods
        SpectrumDotsTexture( TextureMapping2D mapping, SpectrumTexture outsideDot,
            SpectrumTexture insideDot )
            : mapping( mapping ), outsideDot( outsideDot ), insideDot( insideDot )
        {
        }

        SampledSpectrum Evaluate( const TextureEvalContext& ctx, const SampledWavelengths& lambda ) const
        {
            TexCoord2D c = mapping.Map( ctx );
            return InsidePolkaDot( c.st ) ? insideDot.Evaluate( ctx, lambda )
                : outsideDot.Evaluate( ctx, lambda );
        }

        static SpectrumDotsTexture* Create( const Transform& renderFromTexture,
            const TextureParameterDictionary& parameters,
            SpectrumType spectrumType, const FileLoc* loc,
            Allocator alloc );

        std::string ToString( ) const;

    private:
        
    };

    // FBmTexture Definition
    class FBmTexture
    {
        TextureMapping3D mapping;
        Float omega;
        int octaves;
    public:
        // FBmTexture Public Methods
        FBmTexture( TextureMapping3D mapping, int octaves, Float omega )
            : mapping( mapping ), omega( omega ), octaves( octaves )
        {
        }

        Float Evaluate( const TextureEvalContext& ctx ) const
        {
            TexCoord3D c = mapping.Map( ctx );
            return FBm( c.p, c.dpdx, c.dpdy, omega, octaves );
        }

        static FBmTexture* Create( const Transform& renderFromTexture,
            const TextureParameterDictionary& parameters,
            const FileLoc* loc, Allocator alloc );

        std::string ToString( ) const;

    private:
        
    };

    // TexInfo Definition
    struct TexInfo
    {
        // TexInfo Public Methods
        TexInfo( const std::string& f, MIPMapFilterOptions filterOptions, WrapMode wm,
            ColorEncoding encoding )
            : filename( f ), filterOptions( filterOptions ), wrapMode( wm ), encoding( encoding )
        {
        }

        bool operator<( const TexInfo& t ) const
        {
            return std::tie( filename, filterOptions, encoding, wrapMode ) <
                std::tie( t.filename, t.filterOptions, t.encoding, t.wrapMode );
        }

        std::string ToString( ) const;

        std::string filename;
        MIPMapFilterOptions filterOptions;
        WrapMode wrapMode;
        ColorEncoding encoding;
    };

    // ImageTextureBase Definition
    class ImageTextureBase
    {
    protected:
        // ImageTextureBase Protected Members
        TextureMapping2D mapping;
        std::string filename;
        Float scale;
        bool invert;
        MIPMap* mipmap;

    private:
        // ImageTextureBase Private Members
        static std::mutex textureCacheMutex;
        static std::map<TexInfo, MIPMap*> textureCache;
    public:
        // ImageTextureBase Public Methods
        ImageTextureBase( TextureMapping2D mapping, std::string filename,
            MIPMapFilterOptions filterOptions, WrapMode wrapMode, Float scale,
            bool invert, ColorEncoding encoding, Allocator alloc )
            : mapping( mapping ), filename( filename ), scale( scale ), invert( invert )
        {
            // Get _MIPMap_ from texture cache if present
            TexInfo texInfo( filename, filterOptions, wrapMode, encoding );
            std::unique_lock<std::mutex> lock( textureCacheMutex );
            if ( auto iter = textureCache.find( texInfo ); iter != textureCache.end( ) )
            {
                mipmap = iter->second;
                return;
            }
            lock.unlock( );

            // Create _MIPMap_ for _filename_ and add to texture cache
            mipmap =
                MIPMap::CreateFromFile( filename, filterOptions, wrapMode, encoding, alloc );
            lock.lock( );
            // This is actually ok, but if it hits, it means we've wastefully
            // loaded this texture. (Note that in that case, should just return
            // the one that's already in there and not replace it.)
            NCHECK( textureCache.find( texInfo ) == textureCache.end( ) );
            textureCache[ texInfo ] = mipmap;
        }

        static void ClearCache( ) { textureCache.clear( ); }

        void MultiplyScale( Float s ) { scale *= s; }

    
    };

    // FloatImageTexture Definition
    class FloatImageTexture : public ImageTextureBase
    {
    public:
        FloatImageTexture( TextureMapping2D m, const std::string& filename,
            MIPMapFilterOptions filterOptions, WrapMode wm, Float scale,
            bool invert, ColorEncoding encoding, Allocator alloc )
            : ImageTextureBase( m, filename, filterOptions, wm, scale, invert, encoding,
                alloc )
        {
        }
        Float Evaluate( const TextureEvalContext& ctx ) const
        {
#ifdef PBRT_IS_GPU_CODE
            assert( !"Should not be called in GPU code" );
            return 0;
#else
            TexCoord2D c = mapping.Map( ctx );
            // Texture coordinates are (0,0) in the lower left corner, but
            // image coordinates are (0,0) in the upper left.
            c.st[ 1 ] = 1 - c.st[ 1 ];
            Float v = scale * mipmap->Filter<Float>( c.st, { c.dsdx, c.dtdx }, { c.dsdy, c.dtdy } );
            return invert ? std::max<Float>( 0, 1 - v ) : v;
#endif
        }

        static FloatImageTexture* Create( const Transform& renderFromTexture,
            const TextureParameterDictionary& parameters,
            const FileLoc* loc, Allocator alloc );

        std::string ToString( ) const;
    };

    // SpectrumImageTexture Definition
    class SpectrumImageTexture : public ImageTextureBase
    {
    public:
        // SpectrumImageTexture Public Methods
        SpectrumImageTexture( TextureMapping2D mapping, std::string filename,
            MIPMapFilterOptions filterOptions, WrapMode wrapMode,
            Float scale, bool invert, ColorEncoding encoding,
            SpectrumType spectrumType, Allocator alloc )
            : ImageTextureBase( mapping, filename, filterOptions, wrapMode, scale, invert,
                encoding, alloc ),
            spectrumType( spectrumType )
        {
        }

        SampledSpectrum Evaluate( const TextureEvalContext& ctx, const SampledWavelengths& lambda ) const;

        static SpectrumImageTexture* Create( const Transform& renderFromTexture,
            const TextureParameterDictionary& parameters,
            SpectrumType spectrumType, const FileLoc* loc,
            Allocator alloc );

        std::string ToString( ) const;

    private:
        // SpectrumImageTexture Private Members
        SpectrumType spectrumType;
    };

#if defined(PBRT_BUILD_GPU_RENDERER) && defined(__NVCC__)
    class GPUSpectrumImageTexture
    {
    public:
        GPUSpectrumImageTexture( std::string filename, TextureMapping2D mapping,
            cudaTextureObject_t texObj, Float scale, bool invert,
            bool isSingleChannel, const RGBColorSpace* colorSpace,
            SpectrumType spectrumType )
            : mapping( mapping ),
            filename( filename ),
            texObj( texObj ),
            scale( scale ),
            invert( invert ),
            isSingleChannel( isSingleChannel ),
            colorSpace( colorSpace ),
            spectrumType( spectrumType )
        {
        }

        PBRT_CPU_GPU
            SampledSpectrum Evaluate( TextureEvalContext ctx, const SampledWavelengths& lambda ) const
        {
#ifndef PBRT_IS_GPU_CODE
            NLOG_FATAL( "GPUSpectrumImageTexture::Evaluate called from CPU" );
            return SampledSpectrum( 0 );
#else
            // flip y coord since image has (0,0) at upper left, texture at lower
            // left
            TexCoord2D c = mapping.Map( ctx );
            RGB rgb;
            if ( isSingleChannel )
            {
                float tex = scale * tex2DGrad<float>( texObj, c.st[ 0 ], 1 - c.st[ 1 ],
                    make_float2( c.dsdx, c.dsdy ),
                    make_float2( c.dtdx, c.dtdy ) );
                rgb = RGB( tex, tex, tex );
            }
            else
            {
                float4 tex = tex2DGrad<float4>( texObj, c.st[ 0 ], 1 - c.st[ 1 ],
                    make_float2( c.dsdx, c.dsdy ),
                    make_float2( c.dtdx, c.dtdy ) );
                rgb = scale * RGB( tex.x, tex.y, tex.z );
            }
            if ( invert )
                rgb = ClampZero( RGB( 1, 1, 1 ) - rgb );
            if ( spectrumType == SpectrumType::Unbounded )
                return RGBUnboundedSpectrum( *colorSpace, rgb ).Sample( lambda );
            else if ( spectrumType == SpectrumType::Albedo )
            {
                rgb = Clamp( rgb, 0, 1 );
                return RGBAlbedoSpectrum( *colorSpace, rgb ).Sample( lambda );
            }
            else
                return RGBIlluminantSpectrum( *colorSpace, rgb ).Sample( lambda );
#endif
        }

        static GPUSpectrumImageTexture* Create( const Transform& renderFromTexture,
            const TextureParameterDictionary& parameters,
            SpectrumType spectrumType, const FileLoc* loc,
            Allocator alloc );

        std::string ToString( ) const;

        void MultiplyScale( Float s ) { scale *= s; }

        TextureMapping2D mapping;
        std::string filename;
        cudaTextureObject_t texObj;
        Float scale;
        bool invert, isSingleChannel;
        const RGBColorSpace* colorSpace;
        SpectrumType spectrumType;
    };

    class GPUFloatImageTexture
    {
    public:
        GPUFloatImageTexture( std::string filename, TextureMapping2D mapping,
            cudaTextureObject_t texObj, Float scale, bool invert )
            : mapping( mapping ),
            filename( filename ),
            texObj( texObj ),
            scale( scale ),
            invert( invert )
        {
        }

        PBRT_CPU_GPU
            Float Evaluate( TextureEvalContext ctx ) const
        {
#ifndef PBRT_IS_GPU_CODE
            NLOG_FATAL( "GPUSpectrumImageTexture::Evaluate called from CPU" );
            return 0;
#else
            TexCoord2D c = mapping.Map( ctx );
            // flip y coord since image has (0,0) at upper left, texture at lower
            // left
            Float v = scale * tex2DGrad<float>( texObj, c.st[ 0 ], 1 - c.st[ 1 ],
                make_float2( c.dsdx, c.dsdy ),
                make_float2( c.dtdx, c.dtdy ) );
            return invert ? std::max<Float>( 0, 1 - v ) : v;
#endif
        }

        static GPUFloatImageTexture* Create( const Transform& renderFromTexture,
            const TextureParameterDictionary& parameters,
            const FileLoc* loc, Allocator alloc );

        std::string ToString( ) const;

        void MultiplyScale( Float s ) { scale *= s; }

        TextureMapping2D mapping;
        std::string filename;
        cudaTextureObject_t texObj;
        Float scale;
        bool invert;
    };

#else  // PBRT_BUILD_GPU_RENDERER && __NVCC__

    class GPUSpectrumImageTexture
    {
    public:
        SampledSpectrum Evaluate( const TextureEvalContext& ctx, const SampledWavelengths& lambda ) const
        {
            NLOG_FATAL( "GPUSpectrumImageTexture::Evaluate called from CPU" );
            return SampledSpectrum( 0 );
        }

        static GPUSpectrumImageTexture* Create( const Transform& renderFromTexture,
            const TextureParameterDictionary& parameters,
            SpectrumType spectrumType, const FileLoc* loc,
            Allocator alloc )
        {
            NLOG_FATAL( "GPUSpectrumImageTexture::Create called in non-GPU configuration." );
            return nullptr;
        }

        std::string ToString( ) const { return "GPUSpectrumImageTexture"; }
    };

    class GPUFloatImageTexture
    {
    public:
        Float Evaluate( const TextureEvalContext& ) const
        {
            NLOG_FATAL( "GPUFloatImageTexture::Evaluate called from CPU" );
            return 0;
        }

        static GPUFloatImageTexture* Create( const Transform& renderFromTexture,
            const TextureParameterDictionary& parameters,
            const FileLoc* loc, Allocator alloc )
        {
            NLOG_FATAL( "GPUFloatImageTexture::Create called in non-GPU configuration." );
            return nullptr;
        }

        std::string ToString( ) const { return "GPUFloatImageTexture"; }
    };

#endif  // PBRT_BUILD_GPU_RENDERER && __NVCC__

    // MarbleTexture Definition
    class MarbleTexture
    {
        // MarbleTexture Private Members
        TextureMapping3D mapping;
        int octaves;
        Float omega, scale, variation;
    public:
        // MarbleTexture Public Methods
        MarbleTexture( TextureMapping3D mapping, int octaves, Float omega, Float scale,
            Float variation )
            : mapping( mapping ),
            octaves( octaves ),
            omega( omega ),
            scale( scale ),
            variation( variation )
        {
        }

        SampledSpectrum Evaluate( const TextureEvalContext& ctx, const SampledWavelengths& lambda ) const;

        static MarbleTexture* Create( const Transform& renderFromTexture,
            const TextureParameterDictionary& parameters,
            const FileLoc* loc, Allocator alloc );

        std::string ToString( ) const;

    private:
        
    };

    // FloatMixTexture Definition
    class FloatMixTexture
    {
        FloatTexture tex1, tex2;
        FloatTexture amount;
    public:
        // FloatMixTexture Public Methods
        FloatMixTexture( FloatTexture tex1, FloatTexture tex2, FloatTexture amount )
            : tex1( tex1 ), tex2( tex2 ), amount( amount )
        {
        }

        Float Evaluate( const TextureEvalContext& ctx ) const
        {
            Float amt = amount.Evaluate( ctx );
            Float t1 = 0, t2 = 0;
            if ( amt != 1 )
                t1 = tex1.Evaluate( ctx );
            if ( amt != 0 )
                t2 = tex2.Evaluate( ctx );
            return ( 1 - amt ) * t1 + amt * t2;
        }

        static FloatMixTexture* Create( const Transform& renderFromTexture,
            const TextureParameterDictionary& parameters,
            const FileLoc* loc, Allocator alloc );

        std::string ToString( ) const;

    private:
        
    };

    // FloatDirectionMixTexture Definition
    class FloatDirectionMixTexture
    {
        // FloatDirectionMixTexture Private Members
        FloatTexture tex1, tex2;
        Vector3f::Simd dir;
    public:
        // FloatDirectionMixTexture Public Methods
        FloatDirectionMixTexture( FloatTexture tex1, FloatTexture tex2, Vector3f::Simd dir )
            : tex1( tex1 ), tex2( tex2 ), dir( dir )
        {
        }

        Float Evaluate( const TextureEvalContext& ctx ) const
        {
            Float amt = ScalarAbsDot( ctx.n, dir );
            Float t1 = 0, t2 = 0;
            if ( amt != 0 )
                t1 = tex1.Evaluate( ctx );
            if ( amt != 1 )
                t2 = tex2.Evaluate( ctx );
            return amt * t1 + ( 1 - amt ) * t2;
        }

        static FloatDirectionMixTexture* Create( const Transform& renderFromTexture,
            const TextureParameterDictionary& parameters,
            const FileLoc* loc, Allocator alloc );

        std::string ToString( ) const;

    private:
        
    };

    // SpectrumMixTexture Definition
    class SpectrumMixTexture
    {
        SpectrumTexture tex1, tex2;
        FloatTexture amount;
    public:
        SpectrumMixTexture( SpectrumTexture tex1, SpectrumTexture tex2, FloatTexture amount )
            : tex1( tex1 ), tex2( tex2 ), amount( amount )
        {
        }

        SampledSpectrum Evaluate( const TextureEvalContext& ctx, const SampledWavelengths& lambda ) const
        {
            Float amt = amount.Evaluate( ctx );
            SampledSpectrum t1, t2;
            if ( amt != 1 )
                t1 = tex1.Evaluate( ctx, lambda );
            if ( amt != 0 )
                t2 = tex2.Evaluate( ctx, lambda );
            return ( 1 - amt ) * t1 + amt * t2;
        }

        static SpectrumMixTexture* Create( const Transform& renderFromTexture,
            const TextureParameterDictionary& parameters,
            SpectrumType spectrumType, const FileLoc* loc,
            Allocator alloc );

        std::string ToString( ) const;

    private:
        
    };

    // SpectrumDirectionMixTexture Definition
    class SpectrumDirectionMixTexture
    {
        // SpectrumDirectionMixTexture Private Members
        SpectrumTexture tex1, tex2;
        Vector3f::Simd dir;
    public:
        // SpectrumDirectionMixTexture Public Methods
        SpectrumDirectionMixTexture( SpectrumTexture tex1, SpectrumTexture tex2, Vector3f::Simd dir )
            : tex1( tex1 ), tex2( tex2 ), dir( dir )
        {
        }

        SampledSpectrum Evaluate( const TextureEvalContext& ctx, const SampledWavelengths& lambda ) const
        {
            Float amt = ScalarAbsDot( ctx.n, dir );
            SampledSpectrum t1, t2;
            if ( amt != 0 )
                t1 = tex1.Evaluate( ctx, lambda );
            if ( amt != 1 )
                t2 = tex2.Evaluate( ctx, lambda );
            return amt * t1 + ( 1 - amt ) * t2;
        }

        static SpectrumDirectionMixTexture* Create(
            const Transform& renderFromTexture, const TextureParameterDictionary& parameters,
            SpectrumType spectrumType, const FileLoc* loc, Allocator alloc );

        std::string ToString( ) const;

    private:
        
    };

    // PtexTexture Declarations
    class PtexTextureBase
    {
        bool valid;
        std::string filename;
        ColorEncoding encoding;
        Float scale;
    public:
        PtexTextureBase( const std::string& filename, ColorEncoding encoding, Float scale );

        static void ReportStats( );

        int SampleTexture( TextureEvalContext ctx, float* result ) const;

    protected:
        std::string BaseToString( ) const;

    private:
        
    };

    class FloatPtexTexture : public PtexTextureBase
    {
    public:
        FloatPtexTexture( const std::string& filename, ColorEncoding encoding, Float scale )
            : PtexTextureBase( filename, encoding, scale )
        {
        }

        Float Evaluate( const TextureEvalContext& ctx ) const;

        static FloatPtexTexture* Create( const Transform& renderFromTexture,
            const TextureParameterDictionary& parameters,
            const FileLoc* loc, Allocator alloc );
        std::string ToString( ) const;
    };

    class SpectrumPtexTexture : public PtexTextureBase
    {
        SpectrumType spectrumType;
    public:
        SpectrumPtexTexture( const std::string& filename, ColorEncoding encoding, Float scale,
            SpectrumType spectrumType )
            : PtexTextureBase( filename, encoding, scale ), spectrumType( spectrumType )
        {
        }

        SampledSpectrum Evaluate( const TextureEvalContext& ctx, const SampledWavelengths& lambda ) const;

        static SpectrumPtexTexture* Create( const Transform& renderFromTexture,
            const TextureParameterDictionary& parameters,
            SpectrumType spectrumType, const FileLoc* loc,
            Allocator alloc );

        std::string ToString( ) const;

    private:
        
    };

    class GPUFloatPtexTexture
    {
        pstdo::vector<Float> faceValues;
    public:
        GPUFloatPtexTexture( const std::string& filename, ColorEncoding encoding, Float scale,
            Allocator alloc );

        Float Evaluate( const TextureEvalContext& ctx ) const
        {
            NDCHECK( ctx.faceIndex >= 0 && ctx.faceIndex < faceValues.size( ) );
            return faceValues[ ctx.faceIndex ];
        }

        static GPUFloatPtexTexture* Create( const Transform& renderFromTexture,
            const TextureParameterDictionary& parameters,
            const FileLoc* loc, Allocator alloc );
        std::string ToString( ) const;

    private:
        
    };

    class GPUSpectrumPtexTexture
    {
        SpectrumType spectrumType;
        pstdo::vector<RGB> faceValues;
    public:
        GPUSpectrumPtexTexture( const std::string& filename, ColorEncoding encoding,
            Float scale, SpectrumType spectrumType, Allocator alloc );

        SampledSpectrum Evaluate( const TextureEvalContext& ctx, const SampledWavelengths& lambda ) const
        {
            NCHECK( ctx.faceIndex >= 0 && ctx.faceIndex < faceValues.size( ) );

            RGB rgb = faceValues[ ctx.faceIndex ];
            const RGBColorSpace* sRGB =
#ifdef PBRT_IS_GPU_CODE
                RGBColorSpace_sRGB;
#else
                RGBColorSpace::sRGB;
#endif
            if ( spectrumType == SpectrumType::Unbounded )
                return RGBUnboundedSpectrum( *sRGB, rgb ).Sample( lambda );
            else if ( spectrumType == SpectrumType::Albedo )
                return RGBAlbedoSpectrum( *sRGB, Clamp( rgb, 0, 1 ) ).Sample( lambda );
            else
                return RGBIlluminantSpectrum( *sRGB, rgb ).Sample( lambda );
        }

        static GPUSpectrumPtexTexture* Create( const Transform& renderFromTexture,
            const TextureParameterDictionary& parameters,
            SpectrumType spectrumType, const FileLoc* loc,
            Allocator alloc );

        std::string ToString( ) const;

    private:
        
    };

    // FloatScaledTexture Definition
    class FloatScaledTexture
    {
        FloatTexture tex, scale;
    public:
        // FloatScaledTexture Public Methods
        FloatScaledTexture( FloatTexture tex, FloatTexture scale ) : tex( tex ), scale( scale ) {}

        static FloatTexture Create( const Transform& renderFromTexture,
            const TextureParameterDictionary& parameters,
            const FileLoc* loc, Allocator alloc );

        Float Evaluate( const TextureEvalContext& ctx ) const
        {
            Float sc = scale.Evaluate( ctx );
            if ( sc == 0 )
                return 0;
            return tex.Evaluate( ctx ) * sc;
        }

        std::string ToString( ) const;

    private:
        
    };

    // SpectrumScaledTexture Definition
    class SpectrumScaledTexture
    {
        SpectrumTexture tex;
        FloatTexture scale;
    public:
        SpectrumScaledTexture( SpectrumTexture tex, FloatTexture scale )
            : tex( tex ), scale( scale )
        {
        }

        SampledSpectrum Evaluate( const TextureEvalContext& ctx, const SampledWavelengths& lambda ) const
        {
            Float sc = scale.Evaluate( ctx );
            if ( sc == 0 )
                return SampledSpectrum( 0.f );
            return tex.Evaluate( ctx, lambda ) * sc;
        }

        static SpectrumTexture Create( const Transform& renderFromTexture,
            const TextureParameterDictionary& parameters,
            SpectrumType spectrumType, const FileLoc* loc,
            Allocator alloc );

        std::string ToString( ) const;

    private:
        
    };

    // WindyTexture Definition
    class WindyTexture
    {
        TextureMapping3D mapping;
    public:
        // WindyTexture Public Methods
        WindyTexture( TextureMapping3D mapping ) : mapping( mapping ) {}

        Float Evaluate( const TextureEvalContext& ctx ) const
        {
            TexCoord3D c = mapping.Map( ctx );
            Float windStrength = FBm( .1f * c.p, .1f * c.dpdx, .1f * c.dpdy, .5, 3 );
            Float waveHeight = FBm( c.p, c.dpdx, c.dpdy, .5, 6 );
            return Math::FastAbs( windStrength ) * waveHeight;
        }

        static WindyTexture* Create( const Transform& renderFromTexture,
            const TextureParameterDictionary& parameters,
            const FileLoc* loc, Allocator alloc );

        std::string ToString( ) const;

    private:
        
    };

    // WrinkledTexture Definition
    class WrinkledTexture
    {
    public:
        // WrinkledTexture Public Methods
        WrinkledTexture( TextureMapping3D mapping, int octaves, Float omega )
            : mapping( mapping ), octaves( octaves ), omega( omega )
        {
        }

        Float Evaluate( const TextureEvalContext& ctx ) const
        {
            TexCoord3D c = mapping.Map( ctx );
            return Turbulence( c.p, c.dpdx, c.dpdy, omega, octaves );
        }

        static WrinkledTexture* Create( const Transform& renderFromTexture,
            const TextureParameterDictionary& parameters,
            const FileLoc* loc, Allocator alloc );

        std::string ToString( ) const;

    private:
        // WrinkledTexture Private Data
        TextureMapping3D mapping;
        int octaves;
        Float omega;
    };

    inline Float FloatTexture::Evaluate( const TextureEvalContext& ctx ) const
    {
        auto eval = [ & ]( auto ptr ) { return ptr->Evaluate( ctx ); };
        return Dispatch( eval );
    }

    inline SampledSpectrum SpectrumTexture::Evaluate( const TextureEvalContext& ctx, const SampledWavelengths& lambda ) const
    {
        auto eval = [ & ]( auto ptr ) { return ptr->Evaluate( ctx, lambda ); };
        return Dispatch( eval );
    }

    // UniversalTextureEvaluator Definition
    class UniversalTextureEvaluator
    {
    public:
        // UniversalTextureEvaluator Public Methods
        bool CanEvaluate( std::initializer_list<FloatTexture>, std::initializer_list<SpectrumTexture> ) const
        {
            return true;
        }

        Float operator()( FloatTexture tex, TextureEvalContext ctx );

        SampledSpectrum operator()( SpectrumTexture tex, const TextureEvalContext& ctx, const SampledWavelengths& lambda );
    };

    // BasicTextureEvaluator Definition
    class BasicTextureEvaluator
    {
    public:
        // BasicTextureEvaluator Public Methods
        bool CanEvaluate( std::initializer_list<FloatTexture> ftex, std::initializer_list<SpectrumTexture> stex ) const
        {
            // Return _false_ if any _FloatTexture_s cannot be evaluated
            for ( FloatTexture f : ftex )
                if ( f && !f.Is<FloatConstantTexture>( ) && !f.Is<FloatImageTexture>( ) &&
                    !f.Is<GPUFloatPtexTexture>( ) && !f.Is<GPUFloatImageTexture>( ) )
                    return false;

            // Return _false_ if any _SpectrumTexture_s cannot be evaluated
            for ( SpectrumTexture s : stex )
                if ( s && !s.Is<SpectrumConstantTexture>( ) && !s.Is<SpectrumImageTexture>( ) &&
                    !s.Is<GPUSpectrumPtexTexture>( ) && !s.Is<GPUSpectrumImageTexture>( ) )
                    return false;

            return true;
        }

        Float operator()( FloatTexture tex, const TextureEvalContext& ctx )
        {
            if ( tex.Is<FloatConstantTexture>( ) )
                return tex.Cast<FloatConstantTexture>( )->Evaluate( ctx );
            else if ( tex.Is<FloatImageTexture>( ) )
                return tex.Cast<FloatImageTexture>( )->Evaluate( ctx );
            else if ( tex.Is<GPUFloatImageTexture>( ) )
                return tex.Cast<GPUFloatImageTexture>( )->Evaluate( ctx );
            else if ( tex.Is<GPUFloatPtexTexture>( ) )
                return tex.Cast<GPUFloatPtexTexture>( )->Evaluate( ctx );
            else
            {
                if ( tex )
                    NLOG_FATAL( "BasicTextureEvaluator::operator() called with %s", tex );
                return 0.f;
            }
        }

        SampledSpectrum operator()( SpectrumTexture tex, const TextureEvalContext& ctx, const SampledWavelengths& lambda )
        {
            if ( tex.Is<SpectrumConstantTexture>( ) )
                return tex.Cast<SpectrumConstantTexture>( )->Evaluate( ctx, lambda );
            else if ( tex.Is<SpectrumImageTexture>( ) )
                return tex.Cast<SpectrumImageTexture>( )->Evaluate( ctx, lambda );
            else if ( tex.Is<GPUSpectrumImageTexture>( ) )
                return tex.Cast<GPUSpectrumImageTexture>( )->Evaluate( ctx, lambda );
            else if ( tex.Is<GPUSpectrumPtexTexture>( ) )
                return tex.Cast<GPUSpectrumPtexTexture>( )->Evaluate( ctx, lambda );
            else
            {
                if ( tex )
                    NLOG_FATAL( "BasicTextureEvaluator::operator() called with %s", tex );
                return SampledSpectrum( 0.f );
            }
        }
    };

}

#endif
