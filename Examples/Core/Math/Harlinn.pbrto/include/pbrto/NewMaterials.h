#pragma once
#ifndef PBRTO_NEWMATERIALS_H_
#define PBRTO_NEWMATERIALS_H_

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

#include <pbrto/base/NewBssrdf.h>
#include <pbrto/base/NewMaterial.h>
#include <pbrto/NewBsdf.h>
#include <pbrto/NewBssrdf.h>
#include <pbrto/NewInteraction.h>
#include <pbrto/NewTextures.h>
#include <pbrto/util/NewCheck.h>
#include <pbrto/util/NewSpectrum.h>
#include <pbrto/util/NewTaggedptr.h>
#include <pbrto/util/NewTransform.h>

#include <memory>
#include <string>
#include <type_traits>

namespace pbrto
{

    // MaterialEvalContext Definition
    struct MaterialEvalContext : public TextureEvalContext
    {
        Vector3f::Simd wo;
        Normal3f::Simd ns;
        Vector3f::Simd dpdus;

        // MaterialEvalContext Public Methods
        MaterialEvalContext( ) = default;
        MaterialEvalContext( const SurfaceInteraction& si )
            : TextureEvalContext( si ), wo( si.wo ), ns( si.shading.n ), dpdus( si.shading.dpdu )
        { }
        std::string ToString( ) const;

        
    };

    // NormalBumpEvalContext Definition
    struct NormalBumpEvalContext
    {
        // NormalBumpEvalContext Public Members
        Point3f::Simd p;
        Normal3f::Simd n;
        struct
        {
            Normal3f::Simd n;
            Vector3f::Simd dpdu, dpdv;
            Normal3f::Simd dndu, dndv;
        } shading;
        Vector3f::Simd dpdx, dpdy;
        Point2f uv;
        Float dudx = 0, dudy = 0, dvdx = 0, dvdy = 0;
        int faceIndex = 0;

        // NormalBumpEvalContext Public Methods
        NormalBumpEvalContext( ) = default;
        NormalBumpEvalContext( const SurfaceInteraction& si )
            : p( si.p( ) ),
              uv( si.uv ),
              n( si.n ),
              dudx( si.dudx ),
              dudy( si.dudy ),
              dvdx( si.dvdx ),
              dvdy( si.dvdy ),
              dpdx( si.dpdx ),
              dpdy( si.dpdy ),
              faceIndex( si.faceIndex )
        {
            shading.n = si.shading.n;
            shading.dpdu = si.shading.dpdu;
            shading.dpdv = si.shading.dpdv;
            shading.dndu = si.shading.dndu;
            shading.dndv = si.shading.dndv;
        }
        std::string ToString( ) const;

        operator TextureEvalContext( ) const
        {
            return TextureEvalContext( p, dpdx, dpdy, n, uv, dudx, dudy, dvdx, dvdy, faceIndex );
        }

        
    };

    /*
    // Normal Mapping Function Definitions
    inline void NormalMap( const Image& normalMap, const NormalBumpEvalContext& ctx, Vector3f::Simd* dpdu, Vector3f::Simd* dpdv )
    {
        // Get normalized normal vector from normal map
        WrapMode2D wrap( WrapMode::Repeat );
        Point2f uv( ctx.uv[ 0 ], 1 - ctx.uv[ 1 ] );
        Vector3f::Simd ns( 2 * normalMap.BilerpChannel( uv, 0, wrap ) - 1,
            2 * normalMap.BilerpChannel( uv, 1, wrap ) - 1,
            2 * normalMap.BilerpChannel( uv, 2, wrap ) - 1 );
        ns = Normalize( ns );

        // Transform tangent-space normal to rendering space
        Frame frame = Frame::FromXZ( Normalize( ctx.shading.dpdu ), Vector3f::Simd( ctx.shading.n ) );
        ns = frame.FromLocal( ns );

        // Find $\dpdu$ and $\dpdv$ that give shading normal
        Float ulen = ScalarLength( ctx.shading.dpdu ), vlen = ScalarLength( ctx.shading.dpdv );
        *dpdu = Normalize( GramSchmidt( ctx.shading.dpdu, ns ) ) * ulen;
        *dpdv = Normalize( Cross( ns, *dpdu ) ) * vlen;
    }

    // Bump Mapping Function Definitions
    template <typename TextureEvaluator>
    void BumpMap( TextureEvaluator texEval, FloatTexture displacement, const NormalBumpEvalContext& ctx, Vector3f::Simd* dpdu, Vector3f::Simd* dpdv )
    {
        NDCHECK( texEval.CanEvaluate( { displacement }, {} ) );
        // Compute offset positions and evaluate displacement texture
        TextureEvalContext shiftedCtx = ctx;
        // Shift _shiftedCtx_ _du_ in the $u$ direction
        Float du = .5f * ( Math::FastAbs( ctx.dudx ) + Math::FastAbs( ctx.dudy ) );
        if ( du == 0 )
            du = .0005f;
        shiftedCtx.p = ctx.p + du * ctx.shading.dpdu;
        shiftedCtx.uv = ctx.uv + Vector2f( du, 0.f );

        Float uDisplace = texEval( displacement, shiftedCtx );
        // Shift _shiftedCtx_ _dv_ in the $v$ direction
        Float dv = .5f * ( Math::FastAbs( ctx.dvdx ) + Math::FastAbs( ctx.dvdy ) );
        if ( dv == 0 )
            dv = .0005f;
        shiftedCtx.p = ctx.p + dv * ctx.shading.dpdv;
        shiftedCtx.uv = ctx.uv + Vector2f( 0.f, dv );

        Float vDisplace = texEval( displacement, shiftedCtx );
        Float displace = texEval( displacement, ctx );

        // Compute bump-mapped differential geometry
        *dpdu = ctx.shading.dpdu + ( uDisplace - displace ) / du * Vector3f::Simd( ctx.shading.n ) + displace * Vector3f::Simd( ctx.shading.dndu );
        *dpdv = ctx.shading.dpdv + ( vDisplace - displace ) / dv * Vector3f::Simd( ctx.shading.n ) + displace * Vector3f::Simd( ctx.shading.dndv );
    }
    */

    // Normal Mapping Function Definitions
    inline Normal3f::Simd NormalMap( const Image& normalMap, const NormalBumpEvalContext& ctx )
    {
        // Get normalized normal vector from normal map
        WrapMode2D wrap( WrapMode::Repeat );
        Point2f uv( ctx.uv[ 0 ], 1 - ctx.uv[ 1 ] );
        Vector3f::Simd ns( 2 * normalMap.BilerpChannel( uv, 0, wrap ) - 1,
            2 * normalMap.BilerpChannel( uv, 1, wrap ) - 1,
            2 * normalMap.BilerpChannel( uv, 2, wrap ) - 1 );
        ns = Normalize( ns );

        // Transform tangent-space normal to rendering space
        Frame frame = Frame::FromXZ( Normalize( ctx.shading.dpdu ), Vector3f::Simd( ctx.shading.n ) );
        ns = frame.FromLocal( ns );

        // Find $\dpdu$ and $\dpdv$ that give shading normal
        Float ulen = ScalarLength( ctx.shading.dpdu ), vlen = ScalarLength( ctx.shading.dpdv );
        auto dpdu = Normalize( GramSchmidt( ctx.shading.dpdu, ns ) ) * ulen;
        auto dpdv = Normalize( Cross( ns, dpdu ) ) * vlen;
        return Normalize( Cross( dpdu, dpdv ) );
    }

    // Bump Mapping Function Definitions
    template <typename TextureEvaluator>
    inline Normal3f::Simd BumpMap( TextureEvaluator texEval, FloatTexture displacement, const NormalBumpEvalContext& ctx )
    {
        NDCHECK( texEval.CanEvaluate( { displacement }, {} ) );
        // Compute offset positions and evaluate displacement texture
        TextureEvalContext shiftedCtx = ctx;
        // Shift _shiftedCtx_ _du_ in the $u$ direction
        Float du = .5f * ( Math::FastAbs( ctx.dudx ) + Math::FastAbs( ctx.dudy ) );
        if ( du == 0 )
            du = .0005f;
        shiftedCtx.p = ctx.p + du * ctx.shading.dpdu;
        shiftedCtx.uv = ctx.uv + Vector2f( du, 0.f );

        Float uDisplace = texEval( displacement, shiftedCtx );
        // Shift _shiftedCtx_ _dv_ in the $v$ direction
        Float dv = .5f * ( Math::FastAbs( ctx.dvdx ) + Math::FastAbs( ctx.dvdy ) );
        if ( dv == 0 )
            dv = .0005f;
        shiftedCtx.p = ctx.p + dv * ctx.shading.dpdv;
        shiftedCtx.uv = ctx.uv + Vector2f( 0.f, dv );

        Float vDisplace = texEval( displacement, shiftedCtx );
        Float displace = texEval( displacement, ctx );

        // Compute bump-mapped differential geometry
        auto dpdu = ctx.shading.dpdu + ( uDisplace - displace ) / du * Vector3f::Simd( ctx.shading.n ) + displace * Vector3f::Simd( ctx.shading.dndu );
        auto dpdv = ctx.shading.dpdv + ( vDisplace - displace ) / dv * Vector3f::Simd( ctx.shading.n ) + displace * Vector3f::Simd( ctx.shading.dndv );

        return Normalize( Cross( dpdu, dpdv ) );
    }


    // DielectricMaterial Definition
    class DielectricMaterial
    {
        // DielectricMaterial Private Members
        Image* normalMap;
        FloatTexture displacement;
        FloatTexture uRoughness, vRoughness;
        bool remapRoughness;
        Spectrum eta;
    public:
        // DielectricMaterial Type Definitions
        using BxDF = DielectricBxDF;
        using BSSRDF = void;

        // DielectricMaterial Public Methods
        DielectricMaterial( FloatTexture uRoughness, FloatTexture vRoughness, Spectrum eta,
            FloatTexture displacement, Image* normalMap, bool remapRoughness )
            : normalMap( normalMap ),
              displacement( displacement ),
              uRoughness( uRoughness ),
              vRoughness( vRoughness ),
              eta( eta ),
              remapRoughness( remapRoughness )
        { }

        static const char* Name( ) 
        { 
            return "DielectricMaterial"; 
        }

        template <typename TextureEvaluator>
        bool CanEvaluateTextures( TextureEvaluator texEval ) const
        {
            return texEval.CanEvaluate( { uRoughness, vRoughness }, {} );
        }

        FloatTexture GetDisplacement( ) const 
        { 
            return displacement; 
        }
        const Image* GetNormalMap( ) const 
        { 
            return normalMap; 
        }

        static DielectricMaterial* Create( const TextureParameterDictionary& parameters, Image* normalMap, const FileLoc* loc, Allocator alloc );

        std::string ToString( ) const;

        template <typename TextureEvaluator>
        void GetBSSRDF( TextureEvaluator texEval, const MaterialEvalContext& ctx, SampledWavelengths& lambda ) const
        { }

        static constexpr bool HasSubsurfaceScattering( ) { return false; }

        template <typename TextureEvaluator>
        DielectricBxDF GetBxDF( TextureEvaluator texEval, const MaterialEvalContext& ctx, SampledWavelengths& lambda ) const
        {
            // Compute index of refraction for dielectric material
            Float sampledEta = eta( lambda[ 0 ] );
            if ( !eta.template Is<ConstantSpectrum>( ) )
            {
                lambda.TerminateSecondary( );
            }
            // Handle edge case in case lambda[0] is beyond the wavelengths stored by the
            // Spectrum.
            if ( sampledEta == 0 )
                sampledEta = 1;

            // Create microfacet distribution for dielectric material
            Float urough = texEval( uRoughness, ctx ), vrough = texEval( vRoughness, ctx );
            if ( remapRoughness )
            {
                urough = TrowbridgeReitzDistribution::RoughnessToAlpha( urough );
                vrough = TrowbridgeReitzDistribution::RoughnessToAlpha( vrough );
            }
            TrowbridgeReitzDistribution distrib( urough, vrough );

            // Return BSDF for dielectric material
            return DielectricBxDF( sampledEta, distrib );
        }
    };

    // ThinDielectricMaterial Definition
    class ThinDielectricMaterial
    {
    public:
        using BxDF = ThinDielectricBxDF;
        using BSSRDF = void;
        // ThinDielectricMaterial Public Methods
        template <typename TextureEvaluator>
        bool CanEvaluateTextures( TextureEvaluator texEval ) const
        {
            return true;
        }

        template <typename TextureEvaluator>
        ThinDielectricBxDF GetBxDF( TextureEvaluator texEval, const MaterialEvalContext& ctx, SampledWavelengths& lambda ) const
        {
            // Compute index of refraction for dielectric material
            Float sampledEta = eta( lambda[ 0 ] );
            if ( !eta.template Is<ConstantSpectrum>( ) )
                lambda.TerminateSecondary( );
            // Handle edge case in case lambda[0] is beyond the wavelengths stored by the
            // Spectrum.
            if ( sampledEta == 0 )
                sampledEta = 1;

            // Return BxDF for _ThinDielectricMaterial_
            return ThinDielectricBxDF( sampledEta );
        }

        ThinDielectricMaterial( Spectrum eta, FloatTexture displacement, Image* normalMap )
            : displacement( displacement ), normalMap( normalMap ), eta( eta )
        {
        }

        static const char* Name( ) { return "ThinDielectricMaterial"; }

        FloatTexture GetDisplacement( ) const { return displacement; }
        const Image* GetNormalMap( ) const { return normalMap; }

        static ThinDielectricMaterial* Create( const TextureParameterDictionary& parameters, Image* normalMap, const FileLoc* loc, Allocator alloc );

        template <typename TextureEvaluator>
        void GetBSSRDF( TextureEvaluator texEval, const MaterialEvalContext& ctx, SampledWavelengths& lambda ) const
        {
        }

        static constexpr bool HasSubsurfaceScattering( ) { return false; }

        std::string ToString( ) const;

    private:
        // ThinDielectricMaterial Private Data
        FloatTexture displacement;
        Image* normalMap;
        Spectrum eta;
    };

    // MixMaterial Definition
    class MixMaterial
    {
    public:
        // MixMaterial Type Definitions
        using BxDF = void;
        using BSSRDF = void;

        // MixMaterial Public Methods
        MixMaterial( Material m[ 2 ], FloatTexture amount ) : amount( amount )
        {
            materials[ 0 ] = m[ 0 ];
            materials[ 1 ] = m[ 1 ];
        }

        template <typename TextureEvaluator>
        Material ChooseMaterial( TextureEvaluator texEval, const MaterialEvalContext& ctx ) const
        {
            Float amt = texEval( amount, ctx );
            if ( amt <= 0 )
                return materials[ 0 ];
            if ( amt >= 1 )
                return materials[ 1 ];
            Float u = HashFloat( ctx.p, ctx.wo, materials[ 0 ], materials[ 1 ] );
            return ( amt < u ) ? materials[ 0 ] : materials[ 1 ];
        }

        Material GetMaterial( int i ) const { return materials[ i ]; }

        static const char* Name( ) { return "MixMaterial"; }

        FloatTexture GetDisplacement( ) const
        {
#ifndef PBRT_IS_GPU_CODE
            NLOG_FATAL( "Shouldn't be called" );
#endif
            return nullptr;
        }

        const Image* GetNormalMap( ) const
        {
#ifndef PBRT_IS_GPU_CODE
            NLOG_FATAL( "Shouldn't be called" );
#endif
            return nullptr;
        }

        static MixMaterial* Create( Material materials[ 2 ],
            const TextureParameterDictionary& parameters,
            const FileLoc* loc, Allocator alloc );

        template <typename TextureEvaluator>
        void GetBSSRDF( TextureEvaluator texEval, const MaterialEvalContext& ctx, SampledWavelengths& lambda ) const
        {
#ifndef PBRT_IS_GPU_CODE
            NLOG_FATAL( "Shouldn't be called" );
#endif
        }

        static constexpr bool HasSubsurfaceScattering( ) { return false; }

        std::string ToString( ) const;

        template <typename TextureEvaluator>
        bool CanEvaluateTextures( TextureEvaluator texEval ) const
        {
            return texEval.CanEvaluate( { amount }, {} );
        }

        template <typename TextureEvaluator>
        void GetBxDF( TextureEvaluator texEval, const MaterialEvalContext& ctx, SampledWavelengths& lambda ) const
        {
#ifndef PBRT_IS_GPU_CODE
            NLOG_FATAL( "MixMaterial::GetBxDF() shouldn't be called" );
#endif
        }

    private:
        // MixMaterial Private Members
        FloatTexture amount;
        Material materials[ 2 ];
    };

    // HairMaterial Definition
    class HairMaterial
    {
    public:
        using BxDF = HairBxDF;
        using BSSRDF = void;

        // HairMaterial Public Methods
        HairMaterial( SpectrumTexture sigma_a, SpectrumTexture color, FloatTexture eumelanin,
            FloatTexture pheomelanin, FloatTexture eta, FloatTexture beta_m,
            FloatTexture beta_n, FloatTexture alpha )
            : sigma_a( sigma_a ),
            color( color ),
            eumelanin( eumelanin ),
            pheomelanin( pheomelanin ),
            eta( eta ),
            beta_m( beta_m ),
            beta_n( beta_n ),
            alpha( alpha )
        {
        }

        static const char* Name( ) { return "HairMaterial"; }

        template <typename TextureEvaluator>
        bool CanEvaluateTextures( TextureEvaluator texEval ) const
        {
            return texEval.CanEvaluate( { eumelanin, pheomelanin, eta, beta_m, beta_n, alpha },
                { sigma_a, color } );
        }

        template <typename TextureEvaluator>
        HairBxDF GetBxDF( TextureEvaluator texEval, const MaterialEvalContext& ctx, SampledWavelengths& lambda ) const
        {
            Float bm = std::max<Float>( 1e-2, std::min<Float>( 1.0, texEval( beta_m, ctx ) ) );
            Float bn = std::max<Float>( 1e-2, std::min<Float>( 1.0, texEval( beta_n, ctx ) ) );
            Float a = texEval( alpha, ctx );
            Float e = texEval( eta, ctx );

            SampledSpectrum sig_a;
            if ( sigma_a )
                sig_a = ClampZero( texEval( sigma_a, ctx, lambda ) );
            else if ( color )
            {
                SampledSpectrum c = Clamp( texEval( color, ctx, lambda ), 0, 1 );
                sig_a = HairBxDF::SigmaAFromReflectance( c, bn, lambda );
            }
            else
            {
                NCHECK( eumelanin || pheomelanin );
                sig_a = HairBxDF::SigmaAFromConcentration(
                    std::max( Float( 0 ), eumelanin ? texEval( eumelanin, ctx ) : 0 ),
                    std::max( Float( 0 ), pheomelanin ? texEval( pheomelanin, ctx ) : 0 ) )
                    .Sample( lambda );
            }

            // Offset along width
            Float h = -1 + 2 * ctx.uv[ 1 ];
            return HairBxDF( h, e, sig_a, bm, bn, a );
        }

        static HairMaterial* Create( const TextureParameterDictionary& parameters, const FileLoc* loc, Allocator alloc );

        FloatTexture GetDisplacement( ) const { return nullptr; }
        const Image* GetNormalMap( ) const { return nullptr; }

        template <typename TextureEvaluator>
        void GetBSSRDF( TextureEvaluator texEval, const MaterialEvalContext& ctx, SampledWavelengths& lambda ) const
        {
        }

        PBRT_CPU_GPU static constexpr bool HasSubsurfaceScattering( ) { return false; }

        std::string ToString( ) const;

    private:
        // HairMaterial Private Data
        SpectrumTexture sigma_a, color;
        FloatTexture eumelanin, pheomelanin, eta;
        FloatTexture beta_m, beta_n, alpha;
    };

    // DiffuseMaterial Definition
    class DiffuseMaterial
    {
    public:
        // DiffuseMaterial Type Definitions
        using BxDF = DiffuseBxDF;
        using BSSRDF = void;

        // DiffuseMaterial Public Methods
        static const char* Name( ) { return "DiffuseMaterial"; }

        FloatTexture GetDisplacement( ) const { return displacement; }
        const Image* GetNormalMap( ) const { return normalMap; }

        static DiffuseMaterial* Create( const TextureParameterDictionary& parameters, Image* normalMap, const FileLoc* loc, Allocator alloc );

        template <typename TextureEvaluator>
        void GetBSSRDF( TextureEvaluator texEval, const MaterialEvalContext& ctx, SampledWavelengths& lambda, void* ) const
        {
        }

        static constexpr bool HasSubsurfaceScattering( ) { return false; }

        std::string ToString( ) const;

        DiffuseMaterial( SpectrumTexture reflectance, FloatTexture displacement, Image* normalMap )
            : normalMap( normalMap ), displacement( displacement ), reflectance( reflectance )
        {
        }

        template <typename TextureEvaluator>
        PBRT_CPU_GPU bool CanEvaluateTextures( TextureEvaluator texEval ) const
        {
            return texEval.CanEvaluate( {}, { reflectance } );
        }

        template <typename TextureEvaluator>
        DiffuseBxDF GetBxDF( TextureEvaluator texEval, const MaterialEvalContext& ctx, SampledWavelengths& lambda ) const
        {
            SampledSpectrum r = Clamp( texEval( reflectance, ctx, lambda ), 0, 1 );
            return DiffuseBxDF( r );
        }

    private:
        // DiffuseMaterial Private Members
        Image* normalMap;
        FloatTexture displacement;
        SpectrumTexture reflectance;
    };

    // ConductorMaterial Definition
    class ConductorMaterial
    {
    public:
        using BxDF = ConductorBxDF;
        using BSSRDF = void;

        // ConductorMaterial Public Methods
        template <typename TextureEvaluator>
        bool CanEvaluateTextures( TextureEvaluator texEval ) const
        {
            return texEval.CanEvaluate( { uRoughness, vRoughness }, { eta, k, reflectance } );
        }

        template <typename TextureEvaluator>
        ConductorBxDF GetBxDF( TextureEvaluator texEval, const MaterialEvalContext& ctx, SampledWavelengths& lambda ) const
        {
            // Return BSDF for _ConductorMaterial_
            Float uRough = texEval( uRoughness, ctx ), vRough = texEval( vRoughness, ctx );
            if ( remapRoughness )
            {
                uRough = TrowbridgeReitzDistribution::RoughnessToAlpha( uRough );
                vRough = TrowbridgeReitzDistribution::RoughnessToAlpha( vRough );
            }
            SampledSpectrum etas, ks;
            if ( eta )
            {
                etas = texEval( eta, ctx, lambda );
                ks = texEval( k, ctx, lambda );
            }
            else
            {
                // Avoid r==0 NaN case...
                SampledSpectrum r = Clamp( texEval( reflectance, ctx, lambda ), 0, .9999 );
                etas = SampledSpectrum( 1.f );
                ks = 2 * Sqrt( r ) / Sqrt( ClampZero( SampledSpectrum( 1 ) - r ) );
            }
            TrowbridgeReitzDistribution distrib( uRough, vRough );
            return ConductorBxDF( distrib, etas, ks );
        }

        ConductorMaterial( SpectrumTexture eta, SpectrumTexture k, SpectrumTexture reflectance,
            FloatTexture uRoughness, FloatTexture vRoughness,
            FloatTexture displacement, Image* normalMap, bool remapRoughness )
            : displacement( displacement ),
            normalMap( normalMap ),
            eta( eta ),
            k( k ),
            reflectance( reflectance ),
            uRoughness( uRoughness ),
            vRoughness( vRoughness ),
            remapRoughness( remapRoughness )
        {
        }

        static const char* Name( ) { return "ConductorMaterial"; }

        FloatTexture GetDisplacement( ) const { return displacement; }
        const Image* GetNormalMap( ) const { return normalMap; }

        static ConductorMaterial* Create( const TextureParameterDictionary& parameters, Image* normalMap, const FileLoc* loc, Allocator alloc );

        template <typename TextureEvaluator>
        void GetBSSRDF( TextureEvaluator texEval, const MaterialEvalContext& ctx, SampledWavelengths& lambda ) const
        {
        }

        static constexpr bool HasSubsurfaceScattering( ) { return false; }

        std::string ToString( ) const;

    private:
        // ConductorMaterial Private Data
        FloatTexture displacement;
        Image* normalMap;
        SpectrumTexture eta, k, reflectance;
        FloatTexture uRoughness, vRoughness;
        bool remapRoughness;
    };

    // CoatedDiffuseMaterial Definition
    class CoatedDiffuseMaterial
    {
    public:
        using BxDF = CoatedDiffuseBxDF;
        using BSSRDF = void;
        // CoatedDiffuseMaterial Public Methods
        CoatedDiffuseMaterial( SpectrumTexture reflectance, FloatTexture uRoughness,
            FloatTexture vRoughness, FloatTexture thickness,
            SpectrumTexture albedo, FloatTexture g, Spectrum eta,
            FloatTexture displacement, Image* normalMap,
            bool remapRoughness, int maxDepth, int nSamples )
            : displacement( displacement ),
            normalMap( normalMap ),
            reflectance( reflectance ),
            uRoughness( uRoughness ),
            vRoughness( vRoughness ),
            thickness( thickness ),
            albedo( albedo ),
            g( g ),
            eta( eta ),
            remapRoughness( remapRoughness ),
            maxDepth( maxDepth ),
            nSamples( nSamples )
        {
        }

        static const char* Name( ) { return "CoatedDiffuseMaterial"; }

        template <typename TextureEvaluator>
        bool CanEvaluateTextures( TextureEvaluator texEval ) const
        {
            return texEval.CanEvaluate( { uRoughness, vRoughness, thickness, g },
                { reflectance, albedo } );
        }

        template <typename TextureEvaluator>
        CoatedDiffuseBxDF GetBxDF( TextureEvaluator texEval, const MaterialEvalContext& ctx, SampledWavelengths& lambda ) const;

        FloatTexture GetDisplacement( ) const { return displacement; }
        const Image* GetNormalMap( ) const { return normalMap; }

        static CoatedDiffuseMaterial* Create( const TextureParameterDictionary& parameters, Image* normalMap, const FileLoc* loc, Allocator alloc );

        template <typename TextureEvaluator>
        void GetBSSRDF( TextureEvaluator texEval, const MaterialEvalContext& ctx, SampledWavelengths& lambda ) const
        {
        }

        static constexpr bool HasSubsurfaceScattering( ) { return false; }

        std::string ToString( ) const;

    private:
        // CoatedDiffuseMaterial Private Members
        FloatTexture displacement;
        Image* normalMap;
        SpectrumTexture reflectance, albedo;
        FloatTexture uRoughness, vRoughness, thickness, g;
        Spectrum eta;
        bool remapRoughness;
        int maxDepth, nSamples;
    };

    // CoatedConductorMaterial Definition
    class CoatedConductorMaterial
    {
    public:
        using BxDF = CoatedConductorBxDF;
        using BSSRDF = void;
        // CoatedConductorMaterial Public Methods
        CoatedConductorMaterial( FloatTexture interfaceURoughness,
            FloatTexture interfaceVRoughness, FloatTexture thickness,
            Spectrum interfaceEta, FloatTexture g, SpectrumTexture albedo,
            FloatTexture conductorURoughness,
            FloatTexture conductorVRoughness,
            SpectrumTexture conductorEta, SpectrumTexture k,
            SpectrumTexture reflectance, FloatTexture displacement,
            Image* normalMap, bool remapRoughness, int maxDepth,
            int nSamples )
            : displacement( displacement ),
            normalMap( normalMap ),
            interfaceURoughness( interfaceURoughness ),
            interfaceVRoughness( interfaceVRoughness ),
            thickness( thickness ),
            interfaceEta( interfaceEta ),
            albedo( albedo ),
            g( g ),
            conductorURoughness( conductorURoughness ),
            conductorVRoughness( conductorVRoughness ),
            conductorEta( conductorEta ),
            k( k ),
            reflectance( reflectance ),
            remapRoughness( remapRoughness ),
            maxDepth( maxDepth ),
            nSamples( nSamples )
        {
        }

        static const char* Name( ) { return "CoatedConductorMaterial"; }

        template <typename TextureEvaluator>
        bool CanEvaluateTextures( TextureEvaluator texEval ) const
        {
            return texEval.CanEvaluate( { interfaceURoughness, interfaceVRoughness, thickness,
                                        g, conductorURoughness, conductorVRoughness },
                { conductorEta, k, reflectance, albedo } );
        }

        template <typename TextureEvaluator>
        CoatedConductorBxDF GetBxDF( TextureEvaluator texEval, const MaterialEvalContext& ctx, SampledWavelengths& lambda ) const;

        FloatTexture GetDisplacement( ) const { return displacement; }
        const Image* GetNormalMap( ) const { return normalMap; }

        static CoatedConductorMaterial* Create( const TextureParameterDictionary& parameters, Image* normalMap, const FileLoc* loc, Allocator alloc );

        template <typename TextureEvaluator>
        void GetBSSRDF( TextureEvaluator texEval, const MaterialEvalContext& ctx, SampledWavelengths& lambda, void* ) const
        {
        }

        static constexpr bool HasSubsurfaceScattering( ) { return false; }

        std::string ToString( ) const;

    private:
        // CoatedConductorMaterial Private Members
        FloatTexture displacement;
        Image* normalMap;
        FloatTexture interfaceURoughness, interfaceVRoughness, thickness;
        Spectrum interfaceEta;
        FloatTexture g;
        SpectrumTexture albedo;
        FloatTexture conductorURoughness, conductorVRoughness;
        SpectrumTexture conductorEta, k, reflectance;
        bool remapRoughness;
        int maxDepth, nSamples;
    };

    // SubsurfaceMaterial Definition
    class SubsurfaceMaterial
    {
    public:
        // SubsurfaceMaterial Type Definitions
        using BxDF = DielectricBxDF;
        using BSSRDF = TabulatedBSSRDF;

        // SubsurfaceMaterial Public Methods
        SubsurfaceMaterial( Float scale, SpectrumTexture sigma_a, SpectrumTexture sigma_s,
            SpectrumTexture reflectance, SpectrumTexture mfp, Float g,
            Float eta, FloatTexture uRoughness, FloatTexture vRoughness,
            FloatTexture displacement, Image* normalMap, bool remapRoughness,
            Allocator alloc )
            : displacement( displacement ),
            normalMap( normalMap ),
            scale( scale ),
            sigma_a( sigma_a ),
            sigma_s( sigma_s ),
            reflectance( reflectance ),
            mfp( mfp ),
            uRoughness( uRoughness ),
            vRoughness( vRoughness ),
            eta( eta ),
            remapRoughness( remapRoughness ),
            table( 100, 64, alloc )
        {
            ComputeBeamDiffusionBSSRDF( g, eta, &table );
        }

        static const char* Name( ) { return "SubsurfaceMaterial"; }

        template <typename TextureEvaluator>
        bool CanEvaluateTextures( TextureEvaluator texEval ) const
        {
            return texEval.CanEvaluate( { uRoughness, vRoughness }, { sigma_a, sigma_s } );
        }

        template <typename TextureEvaluator>
        DielectricBxDF GetBxDF( TextureEvaluator texEval, const MaterialEvalContext& ctx, SampledWavelengths& lambda ) const
        {
            // Initialize BSDF for _SubsurfaceMaterial_

            Float urough = texEval( uRoughness, ctx ), vrough = texEval( vRoughness, ctx );
            if ( remapRoughness )
            {
                urough = TrowbridgeReitzDistribution::RoughnessToAlpha( urough );
                vrough = TrowbridgeReitzDistribution::RoughnessToAlpha( vrough );
            }
            TrowbridgeReitzDistribution distrib( urough, vrough );

            // Initialize _bsdf_ for smooth or rough dielectric
            return DielectricBxDF( eta, distrib );
        }

        template <typename TextureEvaluator>
        TabulatedBSSRDF GetBSSRDF( TextureEvaluator texEval, const MaterialEvalContext& ctx, SampledWavelengths& lambda ) const
        {
            SampledSpectrum sig_a, sig_s;
            if ( sigma_a && sigma_s )
            {
                // Evaluate textures for $\sigma_\roman{a}$ and $\sigma_\roman{s}$
                sig_a = ClampZero( scale * texEval( sigma_a, ctx, lambda ) );
                sig_s = ClampZero( scale * texEval( sigma_s, ctx, lambda ) );

            }
            else
            {
                // Compute _sig_a_ and _sig_s_ from reflectance and mfp
                NDCHECK( reflectance && mfp );
                SampledSpectrum mfree = ClampZero( scale * texEval( mfp, ctx, lambda ) );
                SampledSpectrum r = Clamp( texEval( reflectance, ctx, lambda ), 0, 1 );
                SubsurfaceFromDiffuse( table, r, mfree, &sig_a, &sig_s );
            }
            return TabulatedBSSRDF( ctx.p, ctx.ns, ctx.wo, eta, sig_a, sig_s, &table );
        }

        FloatTexture GetDisplacement( ) const { return displacement; }
        const Image* GetNormalMap( ) const { return normalMap; }

        PBRT_CPU_GPU
            static constexpr bool HasSubsurfaceScattering( ) { return true; }

        static SubsurfaceMaterial* Create( const TextureParameterDictionary& parameters,
            Image* normalMap, const FileLoc* loc,
            Allocator alloc );

        std::string ToString( ) const;

    private:
        // SubsurfaceMaterial Private Members
        FloatTexture displacement;
        Image* normalMap;
        SpectrumTexture sigma_a, sigma_s, reflectance, mfp;
        Float scale, eta;
        FloatTexture uRoughness, vRoughness;
        bool remapRoughness;
        BSSRDFTable table;
    };

    // DiffuseTransmissionMaterial Definition
    class DiffuseTransmissionMaterial
    {
    public:
        using BxDF = DiffuseTransmissionBxDF;
        using BSSRDF = void;
        // DiffuseTransmissionMaterial Public Methods
        DiffuseTransmissionMaterial( SpectrumTexture reflectance, SpectrumTexture transmittance, FloatTexture displacement, Image* normalMap, Float scale )
            : displacement( displacement ),
              normalMap( normalMap ),
              reflectance( reflectance ),
              transmittance( transmittance ),
             scale( scale )
        {
        }

        static const char* Name( ) { return "DiffuseTransmissionMaterial"; }

        template <typename TextureEvaluator>
        bool CanEvaluateTextures( TextureEvaluator texEval ) const
        {
            return texEval.CanEvaluate( {}, { reflectance, transmittance } );
        }

        template <typename TextureEvaluator>
        DiffuseTransmissionBxDF GetBxDF( TextureEvaluator texEval, const MaterialEvalContext& ctx, SampledWavelengths& lambda ) const
        {
            SampledSpectrum r = Clamp( scale * texEval( reflectance, ctx, lambda ), 0, 1 );
            SampledSpectrum t = Clamp( scale * texEval( transmittance, ctx, lambda ), 0, 1 );
            return DiffuseTransmissionBxDF( r, t );
        }

        FloatTexture GetDisplacement( ) const { return displacement; }
        const Image* GetNormalMap( ) const { return normalMap; }

        static DiffuseTransmissionMaterial* Create(
            const TextureParameterDictionary& parameters, Image* normalMap,
            const FileLoc* loc, Allocator alloc );

        template <typename TextureEvaluator>
        void GetBSSRDF( TextureEvaluator texEval, const MaterialEvalContext& ctx, SampledWavelengths& lambda ) const
        {
        }

        static constexpr bool HasSubsurfaceScattering( ) { return false; }

        std::string ToString( ) const;

    private:
        // DiffuseTransmissionMaterial Private Data
        FloatTexture displacement;
        Image* normalMap;
        SpectrumTexture reflectance, transmittance;
        Float scale;
    };

    // MeasuredMaterial Definition
    class MeasuredMaterial
    {
    public:
        using BxDF = MeasuredBxDF;
        using BSSRDF = void;
        // MeasuredMaterial Public Methods
        template <typename TextureEvaluator>
        PBRT_CPU_GPU MeasuredBxDF GetBxDF( TextureEvaluator texEval, const MaterialEvalContext& ctx, SampledWavelengths& lambda ) const
        {
            return MeasuredBxDF( brdf, lambda );
        }

        MeasuredMaterial( const std::string& filename, FloatTexture displacement,
            Image* normalMap, Allocator alloc );

        static const char* Name( ) { return "MeasuredMaterial"; }

        template <typename TextureEvaluator>
        PBRT_CPU_GPU bool CanEvaluateTextures( TextureEvaluator texEval ) const
        {
            return true;
        }

        FloatTexture GetDisplacement( ) const { return displacement; }
        const Image* GetNormalMap( ) const { return normalMap; }

        static MeasuredMaterial* Create( const TextureParameterDictionary& parameters,
            Image* normalMap, const FileLoc* loc,
            Allocator alloc );

        template <typename TextureEvaluator>
        void GetBSSRDF( TextureEvaluator texEval, const MaterialEvalContext& ctx, SampledWavelengths& lambda, void* ) const
        {
        }

        PBRT_CPU_GPU static constexpr bool HasSubsurfaceScattering( ) { return false; }

        std::string ToString( ) const;

    private:
        // MeasuredMaterial Private Members
        FloatTexture displacement;
        Image* normalMap;
        const MeasuredBxDFData* brdf;
    };

    // Material Inline Method Definitions
    template <typename TextureEvaluator>
    inline BSDF Material::GetBSDF( TextureEvaluator texEval, const MaterialEvalContext& ctx, SampledWavelengths& lambda, ScratchBuffer& scratchBuffer ) const
    {
        // Define _getBSDF_ lambda function for _Material::GetBSDF()_
        auto getBSDF = [ & ]( auto mtl ) -> BSDF 
            {
                using ConcreteMtl = typename std::remove_reference_t<decltype( *mtl )>;
                using ConcreteBxDF = typename ConcreteMtl::BxDF;
                if constexpr ( std::is_same_v<ConcreteBxDF, void> )
                    return BSDF( );
                else
                {
                    // Allocate memory for _ConcreteBxDF_ and return _BSDF_ for material
                    ConcreteBxDF* bxdf = scratchBuffer.Alloc<ConcreteBxDF>( );
                    *bxdf = mtl->GetBxDF( texEval, ctx, lambda );
                    return BSDF( ctx.ns, ctx.dpdus, bxdf );
                }
            };

        return DispatchCPU( getBSDF );
    }

    template <typename TextureEvaluator>
    inline bool Material::CanEvaluateTextures( TextureEvaluator texEval ) const
    {
        auto eval = [ & ]( auto ptr ) { return ptr->CanEvaluateTextures( texEval ); };
        return Dispatch( eval );
    }

    template <typename TextureEvaluator>
    inline BSSRDF Material::GetBSSRDF( TextureEvaluator texEval, const MaterialEvalContext& ctx, SampledWavelengths& lambda, ScratchBuffer& scratchBuffer ) const
    {
        auto get = [ & ]( auto mtl ) -> BSSRDF {
            using Material = typename std::remove_reference_t<decltype( *mtl )>;
            using MaterialBSSRDF = typename Material::BSSRDF;
            if constexpr ( std::is_same_v<MaterialBSSRDF, void> )
                return nullptr;
            else
            {
                MaterialBSSRDF* bssrdf = scratchBuffer.Alloc<MaterialBSSRDF>( );
                *bssrdf = mtl->GetBSSRDF( texEval, ctx, lambda );
                return BSSRDF( bssrdf );
            }
            };
        return DispatchCPU( get );
    }

    inline bool Material::HasSubsurfaceScattering( ) const
    {
        auto has = [ & ]( auto ptr ) { return ptr->HasSubsurfaceScattering( ); };
        return Dispatch( has );
    }

    inline FloatTexture Material::GetDisplacement( ) const
    {
        auto disp = [ & ]( auto ptr ) { return ptr->GetDisplacement( ); };
        return Dispatch( disp );
    }

    inline const Image* Material::GetNormalMap( ) const
    {
        auto nmap = [ & ]( auto ptr ) { return ptr->GetNormalMap( ); };
        return Dispatch( nmap );
    }

}

#endif
